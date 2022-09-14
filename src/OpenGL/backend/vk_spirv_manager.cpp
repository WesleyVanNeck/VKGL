/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Anvil/include/wrappers/device.h"
#include "Anvil/include/wrappers/shader_module.h"
#include "Anvil/include/misc/buffer_create_info.h"
#include "Anvil/include/wrappers/buffer.h"
#include "Anvil/include/wrappers/descriptor_set_group.h"
#include "Anvil/include/misc/memory_allocator.h"
#include "Anvil/include/wrappers/memory_block.h"
#include "OpenGL/backend/thread_pool.h"
#include "OpenGL/backend/vk_spirv_manager.h"
#include "OpenGL/backend/vk_buffer_manager.h"
#include "OpenGL/frontend/gl_limits.h"
#include "OpenGL/frontend/gl_program_manager.h"
#include "OpenGL/frontend/gl_shader_manager.h"
#include "OpenGL/frontend/gl_state_manager.h"
#include "OpenGL/frontend/gl_buffer_manager.h"
#include "OpenGL/utils_enum.h"
#include "vkgl_limits.h"

#include <regex>

#ifdef max
    #undef max
#endif

#include "Anvil/deps/glslang/glslang/MachineIndependent/localintermediate.h"
#include "Anvil/deps/glslang/glslang/MachineIndependent/iomapper.h"
#include "Anvil/deps/glslang/SPIRV/disassemble.h"


#define VKGL_DEFAULT_UNIFORM_BLOCK_NAME "gl_DefaultUniformBlock"


OpenGL::VKSPIRVManager::ProgramData::ProgramData(const SPIRVBlobID&                  in_id,
                                                 const std::vector<ShaderData*>&     in_shader_ptrs,
                                                 OpenGL::GLProgramReferenceUniquePtr in_program_reference_ptr)
    :id                   (in_id),
     link_status          (false),
     link_task_fence_ptr  (nullptr,
                           std::default_delete<VKGL::Fence>() ),
     program_reference_ptr(std::move(in_program_reference_ptr) ),
     shader_ptrs          (in_shader_ptrs),
     need_rebuild_uniform_resources(false)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    link_task_fence_ptr.reset(new VKGL::Fence() );
    vkgl_assert(link_task_fence_ptr != nullptr);

    program_id = program_reference_ptr->get_payload().id;
}

OpenGL::VKSPIRVManager::ShaderData::ShaderData(const SPIRVBlobID&        in_id,
                                               const OpenGL::ShaderType& in_shader_type,
                                               const std::string&        in_glsl)
    :compilation_status    (false),
     compile_task_fence_ptr(nullptr,
                            std::default_delete<VKGL::Fence>() ),
     glsl                  (in_glsl),
     id                    (in_id),
     sm_entrypoint_name    (nullptr),
     type                  (in_shader_type)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    FUN_ENTRY(DEBUG_DEPTH);
    
    vkgl_assert(in_shader_type != OpenGL::ShaderType::Unknown);

    compile_task_fence_ptr.reset(new VKGL::Fence() );
    vkgl_assert(compile_task_fence_ptr != nullptr);
}

OpenGL::VKSPIRVManager::VKSPIRVManager(IBackend*                             in_backend_ptr,
                                       const OpenGL::IContextObjectManagers* in_frontend_ptr)
    :m_backend_ptr          (in_backend_ptr),
     m_frontend_ptr         (in_frontend_ptr),
     m_n_entities_registered(0)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    vkgl_assert(in_backend_ptr != nullptr);

    glslang::InitializeProcess();
}

OpenGL::VKSPIRVManager::~VKSPIRVManager()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    glslang::FinalizeProcess();
}

void OpenGL::VKSPIRVManager::compile_shader(ShaderData* in_shader_data_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: This function is called back from one of the backend thread pool's threads */
    std::string                       glsl_code            = in_shader_data_ptr->glsl;
    std::unique_ptr<glslang::TShader> glslang_shader_ptr;
    const auto                        glslang_shader_stage = OpenGL::Utils::get_sh_language_for_opengl_shader_type(in_shader_data_ptr->type);
    const char*                       sm_entrypoint_name   = "main";
    //std::vector<std::string> 			resource_set_binding = {"0"};

    vkgl_assert(in_shader_data_ptr->type == OpenGL::ShaderType::Fragment ||
                in_shader_data_ptr->type == OpenGL::ShaderType::Geometry ||
                in_shader_data_ptr->type == OpenGL::ShaderType::Vertex);
    vkgl_assert(glslang_shader_stage     != EShLanguage::EShLangCount);

    glslang_shader_ptr.reset(new glslang::TShader(glslang_shader_stage) );
    vkgl_assert(glslang_shader_ptr != nullptr);

    patch_glsl_code(in_shader_data_ptr,
                    glsl_code);

    {
        const char* glsl_code_raw_ptr = glsl_code.c_str();

        glslang_shader_ptr->setStrings(&glsl_code_raw_ptr,
                                       1); /* in_n */
    }

    glslang_shader_ptr->setEntryPoint				(sm_entrypoint_name);
    glslang_shader_ptr->setSourceEntryPoint			(sm_entrypoint_name);
    glslang_shader_ptr->setEnvInput					(glslang::EShSource::EShSourceGlsl, glslang_shader_stage, glslang::EShClientVulkan, glslang::EShTargetVulkan_1_0);
    glslang_shader_ptr->setEnvClient				(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_0);
    glslang_shader_ptr->setEnvTarget				(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);
    glslang_shader_ptr->setAutoMapLocations			(true);
    glslang_shader_ptr->setAutoMapBindings			(true);
    glslang_shader_ptr->setEnvInputVulkanRulesRelaxed();
    glslang_shader_ptr->setGlobalUniformBlockName	(VKGL_DEFAULT_UNIFORM_BLOCK_NAME);
    glslang_shader_ptr->setGlobalUniformSet			(0);
    //glslang_shader_ptr->setGlobalUniformBinding		(0);
    //glslang_shader_ptr->setResourceSetBinding		(resource_set_binding);

    in_shader_data_ptr->compilation_status = glslang_shader_ptr->parse(m_glslang_resources_ptr.get(),
                                                                       450,   /* defaultVersion    */
                                                                       ECoreProfile,   /* defaultProfile    */
                                                                       false,
                                                                       false, /* forwardCompatible */
                                                                       static_cast<EShMessages>(EShMsgDefault | EShMsgSpvRules | EShMsgVulkanRules) );
    in_shader_data_ptr->compilation_log    = glslang_shader_ptr->getInfoLog();

	{
		restore_glsl_symbol_names(in_shader_data_ptr->compilation_log);
	}

vkgl_printf(">>>>COMPILATION_LOG>>>>\n%s\n>>>>>>>>", in_shader_data_ptr->compilation_log.c_str() );
    if (in_shader_data_ptr->compilation_status)
    {
        const auto            intermediate_ptr = glslang_shader_ptr->getIntermediate();
        vkgl_assert(intermediate_ptr != nullptr);

        {
        	remove_unused_symbols(*intermediate_ptr);
        }

        glslang::SpvOptions spv_options;
        std::vector<uint32_t> result_spirv_blob;

        glslang::GlslangToSpv(*intermediate_ptr,
                              result_spirv_blob,
                              nullptr,
                              &spv_options);

        if (result_spirv_blob.size() == 0)
        {
            vkgl_assert_fail();
        }
        else
        {
            in_shader_data_ptr->spirv_blob.resize(result_spirv_blob.size() * sizeof(uint32_t) );

            memcpy(&in_shader_data_ptr->spirv_blob.at(0),
                   &result_spirv_blob.at(0),
                    in_shader_data_ptr->spirv_blob.size() );
        }
    }

    in_shader_data_ptr->glslang_shader_ptr = std::move(glslang_shader_ptr);
    in_shader_data_ptr->sm_entrypoint_name = sm_entrypoint_name;

    in_shader_data_ptr->compile_task_fence_ptr->signal();
}

OpenGL::VKSPIRVManagerUniquePtr OpenGL::VKSPIRVManager::create(IBackend*                             in_backend_ptr,
                                                               const OpenGL::IContextObjectManagers* in_frontend_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::VKSPIRVManagerUniquePtr result_ptr;

    result_ptr.reset(new VKSPIRVManager(in_backend_ptr,
                                        in_frontend_ptr) );

    if (result_ptr != nullptr)
    {
        if (!result_ptr->init() )
        {
            result_ptr.reset();
        }
    }

    vkgl_assert(result_ptr != nullptr);
    return result_ptr;
}

OpenGL::PostLinkDataUniquePtr OpenGL::VKSPIRVManager::create_post_link_data(const glslang::TProgram* in_program_data_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    const auto                    n_live_attributes = in_program_data_ptr->getNumLiveAttributes      ();
    const auto                    n_live_ubs        = in_program_data_ptr->getNumLiveUniformBlocks   ();
    const auto                    n_live_uniforms   = in_program_data_ptr->getNumLiveUniformVariables();
    OpenGL::PostLinkDataUniquePtr result_ptr;

    result_ptr.reset(new OpenGL::PostLinkData() );
    vkgl_assert(result_ptr != nullptr);

    /* Miscellaneous stuff */
    {
        auto gs_intermediate_ptr = in_program_data_ptr->getIntermediate(EShLanguage::EShLangGeometry);

        if (gs_intermediate_ptr != nullptr)
        {
            result_ptr->gs_input_type               = get_geometry_input_type_for_layout_geometry (gs_intermediate_ptr->getInputPrimitive () );
            result_ptr->gs_output_type              = get_geometry_output_type_for_layout_geometry(gs_intermediate_ptr->getOutputPrimitive() );
            result_ptr->n_max_gs_vertices_generated = gs_intermediate_ptr->getVertices            ();
        }
    }

    /* Active attribs */
    result_ptr->active_attributes.reserve(n_live_attributes);
    result_ptr->active_attributes.clear  ();

    result_ptr->active_attribute_max_length = 0;
    result_ptr->active_attribute_name_to_location_map.clear();

    for (auto  n_live_attribute = 0;
               n_live_attribute < n_live_attributes;
             ++n_live_attribute)
    {
        const auto                        live_attribute_name_ptr = in_program_data_ptr->getAttributeName (n_live_attribute);
        const auto                        live_attribute_type_ptr = in_program_data_ptr->getAttributeTType(n_live_attribute);
        OpenGL::ActiveAttributeProperties live_attribute_props;

        live_attribute_props.location = live_attribute_type_ptr->getQualifier().layoutLocation;
        live_attribute_props.name     = live_attribute_name_ptr;
        live_attribute_props.size     = (live_attribute_type_ptr->getArraySizes() != nullptr) ? live_attribute_type_ptr->getOuterArraySize()
                                                                                              : 1;
        live_attribute_props.type     = get_variable_type_for_glslang_type(*live_attribute_type_ptr);

    	{
        	restore_glsl_symbol_names(live_attribute_props.name);
    	}

        result_ptr->active_attribute_max_length = std::max(result_ptr->active_attribute_max_length,
                                                           static_cast<uint32_t>(live_attribute_props.name.length() + 1) );

vkgl_printf("live_attribute_props.name = %s", live_attribute_props.name.c_str() );
        vkgl_assert(result_ptr->active_attribute_name_to_location_map.find(live_attribute_props.name) == result_ptr->active_attribute_name_to_location_map.end() );
        result_ptr->active_attribute_name_to_location_map[live_attribute_props.name] = live_attribute_props.location;

        result_ptr->active_attributes.push_back(live_attribute_props);

        if (n_live_attribute == 0)
        {
            result_ptr->max_active_attribute_location = live_attribute_props.location;
        }
        else
        {
            result_ptr->max_active_attribute_location = std::max(result_ptr->max_active_attribute_location,
                                                                 live_attribute_props.location);
        }
    }

    /* Active uniforms */
    result_ptr->active_uniform_blocks.reserve(n_live_ubs);
    result_ptr->active_uniform_blocks.clear  ();
    {
        for (int i = 0;
        		i < n_live_ubs;
        		++i)
        {
        	result_ptr->active_uniform_blocks.push_back(OpenGL::ActiveUniformBlock() );
        }
        vkgl_assert(n_live_ubs == result_ptr->active_uniform_blocks.size() );
    }

    result_ptr->active_uniform_block_max_name_length = 0;
    result_ptr->active_uniform_block_by_name_map.clear();
    
    result_ptr->active_uniforms.reserve(n_live_uniforms);
    result_ptr->active_uniforms.clear  ();

    result_ptr->active_uniform_max_length = 0;
    result_ptr->active_uniform_by_name_map.clear();

    for (auto  n_live_uniform = 0;
               n_live_uniform < n_live_uniforms;
             ++n_live_uniform)
    {
        const auto                        live_uniform_object = in_program_data_ptr->getUniform (n_live_uniform);
        const auto                        live_uniform_name_ptr = in_program_data_ptr->getUniformName (n_live_uniform);
        const auto                        live_uniform_type_ptr = in_program_data_ptr->getUniformTType(n_live_uniform);
        OpenGL::ActiveUniformProperties live_uniform_props = OpenGL::ActiveUniformProperties();

        live_uniform_props.index 				= n_live_uniform;
        live_uniform_props.location 			= n_live_uniform;
        live_uniform_props.array_stride 		= live_uniform_object.arrayStride;
        live_uniform_props.is_row_major 		= live_uniform_type_ptr->getQualifier().layoutMatrix == glslang::TLayoutMatrix::ElmRowMajor;
        live_uniform_props.matrix_stride; /* TODO */
        live_uniform_props.name     			= live_uniform_name_ptr;
        live_uniform_props.size     			= in_program_data_ptr->getUniformArraySize(n_live_uniform);
        live_uniform_props.type     			= get_variable_type_for_glslang_type(*live_uniform_type_ptr);
        live_uniform_props.offset     			= in_program_data_ptr->getUniformBufferOffset(n_live_uniform);
        live_uniform_props.uniform_block_index = in_program_data_ptr->getUniformBlockIndex(n_live_uniform);
        live_uniform_props.binding_point 		= (live_uniform_type_ptr->getQualifier().layoutBinding < 0xFFFF) ? live_uniform_type_ptr->getQualifier().layoutBinding
        																												: live_uniform_props.binding_point; //in_program_data_ptr->getUniformBinding(n_live_uniform);

        {
        	if (strcmp(live_uniform_props.name.c_str(),
        			(VKGL_DEFAULT_UNIFORM_BLOCK_NAME ".") ) == 0)
        	{
        		live_uniform_props.name.erase(0,
        										strlen((VKGL_DEFAULT_UNIFORM_BLOCK_NAME ".") ) );
        	}
        	
        	{
            	restore_glsl_symbol_names(live_uniform_props.name);
        	}
        }
        
        result_ptr->active_uniform_max_length = std::max(result_ptr->active_uniform_max_length,
                                                           static_cast<uint32_t>(live_uniform_props.name.length() + 1) );

vkgl_printf("live_uniform_props.name = %s", live_uniform_props.name.c_str() );
        result_ptr->active_uniforms.push_back(live_uniform_props);

        vkgl_assert(result_ptr->active_uniform_by_name_map.find(live_uniform_props.name) == result_ptr->active_uniform_by_name_map.end() );
        result_ptr->active_uniform_by_name_map[live_uniform_props.name] = &result_ptr->active_uniforms.at(n_live_uniform);

    	/* Active ubs */
    	auto n_live_ub = live_uniform_props.uniform_block_index;
    	vkgl_assert(n_live_ub < n_live_ubs);
    	
    	if (live_uniform_props.uniform_block_index >= 0)
		{
            const auto                        live_uniform_block_name_ptr = in_program_data_ptr->getUniformBlockName (n_live_ub);
            const auto                        live_uniform_block_type_ptr = in_program_data_ptr->getUniformBlockTType(n_live_ub);
            const auto                        live_uniform_block_stages = in_program_data_ptr->getUniformStages(n_live_uniform);
            OpenGL::ActiveUniformBlock& 	live_uniform_block = result_ptr->active_uniform_blocks.at(n_live_ub);
    
            live_uniform_block.index 		= n_live_ub;
            live_uniform_block.binding_point = live_uniform_block_type_ptr->getQualifier().layoutBinding; //in_program_data_ptr->getUniformBlockBinding(n_live_ub);
            live_uniform_block.name     	= live_uniform_block_name_ptr;
            live_uniform_block.data_size     = in_program_data_ptr->getUniformBlockSize(n_live_ub);
            
            live_uniform_block.referenced_by_fs     = live_uniform_block_stages & EShLanguageMask::EShLangFragmentMask;
            live_uniform_block.referenced_by_gs     = live_uniform_block_stages & EShLanguageMask::EShLangGeometryMask;
            live_uniform_block.referenced_by_vs     = live_uniform_block_stages & EShLanguageMask::EShLangVertexMask;
    
        	{
            	if (strcmp(live_uniform_block.name.c_str(), 
            			VKGL_DEFAULT_UNIFORM_BLOCK_NAME) == 0)
            	{
            		live_uniform_props.is_default_uniform = true;
            	}
            	else
            	{
            		live_uniform_props.is_default_uniform = false;
            	}
            	
            	{
                	restore_glsl_symbol_names(live_uniform_block.name);
            	}
        	}
    
            result_ptr->active_uniform_block_max_name_length = std::max(result_ptr->active_uniform_block_max_name_length,
                                                               				static_cast<uint32_t>(live_uniform_block.name.length() + 1) );
    
    vkgl_printf("live_uniform_block.name = %s", live_uniform_block.name.c_str() );
            result_ptr->index_to_ub_and_uniform_index_pair[live_uniform_props.index] = UniformBlockAndUniformIndexPair(live_uniform_props.uniform_block_index,
            																													live_uniform_block.active_uniforms.size() );
            live_uniform_block.active_uniforms.push_back(live_uniform_props);
    
            result_ptr->active_uniform_block_by_name_map[live_uniform_block.name] = &live_uniform_block;
        }
        else
        {
	        result_ptr->index_to_ub_and_uniform_index_pair[live_uniform_props.index] = UniformBlockAndUniformIndexPair(live_uniform_props.uniform_block_index,
																													live_uniform_props.index);
        }
    }

    return result_ptr;
}

OpenGL::GeometryInputType OpenGL::VKSPIRVManager::get_geometry_input_type_for_layout_geometry(const glslang::TLayoutGeometry& in_layout_geometry) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::GeometryInputType result = OpenGL::GeometryInputType::Unknown;

    switch (in_layout_geometry)
    {
        case glslang::TLayoutGeometry::ElgNone:                                                                        break;
        case glslang::TLayoutGeometry::ElgLines:              result = OpenGL::GeometryInputType::Lines;               break;
        case glslang::TLayoutGeometry::ElgLinesAdjacency:     result = OpenGL::GeometryInputType::Lines_Adjacency;     break;
        case glslang::TLayoutGeometry::ElgPoints:             result = OpenGL::GeometryInputType::Points;              break;
        case glslang::TLayoutGeometry::ElgTriangles:          result = OpenGL::GeometryInputType::Triangles;           break;
        case glslang::TLayoutGeometry::ElgTrianglesAdjacency: result = OpenGL::GeometryInputType::Triangles_Adjacency; break;

        case glslang::TLayoutGeometry::ElgIsolines:
        case glslang::TLayoutGeometry::ElgLineStrip:
        case glslang::TLayoutGeometry::ElgQuads:
        case glslang::TLayoutGeometry::ElgTriangleStrip:
        {
            /* ?! */
            vkgl_assert_fail();

            break;
        }

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

OpenGL::GeometryOutputType OpenGL::VKSPIRVManager::get_geometry_output_type_for_layout_geometry(const glslang::TLayoutGeometry& in_layout_geometry) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::GeometryOutputType result = OpenGL::GeometryOutputType::Unknown;

    switch (in_layout_geometry)
    {
        case glslang::TLayoutGeometry::ElgNone:                                                               break;
        case glslang::TLayoutGeometry::ElgLineStrip:     result = OpenGL::GeometryOutputType::Line_Strip;     break;
        case glslang::TLayoutGeometry::ElgPoints:        result = OpenGL::GeometryOutputType::Points;         break;
        case glslang::TLayoutGeometry::ElgTriangleStrip: result = OpenGL::GeometryOutputType::Triangle_Strip; break;

        case glslang::TLayoutGeometry::ElgIsolines:
        case glslang::TLayoutGeometry::ElgLines:
        case glslang::TLayoutGeometry::ElgLinesAdjacency:
        case glslang::TLayoutGeometry::ElgQuads:
        case glslang::TLayoutGeometry::ElgTriangles:
        case glslang::TLayoutGeometry::ElgTrianglesAdjacency:
        {
            /* ?! */
            vkgl_assert_fail();

            break;
        }

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

bool OpenGL::VKSPIRVManager::get_program_link_status(const SPIRVBlobID& in_spirv_blob_id,
                                                     bool*              out_status_ptr,
                                                     const char**       out_link_log_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_spirv_blob_id_to_program_data_map.find(in_spirv_blob_id);

        if (iterator != m_spirv_blob_id_to_program_data_map.end() )
        {
            vkgl_assert(iterator->second->link_task_fence_ptr != nullptr);

            iterator->second->link_task_fence_ptr->wait();

            result            = true;
            if (out_status_ptr) { *out_status_ptr   = iterator->second->link_status; }
            if (out_link_log_ptr) { *out_link_log_ptr = iterator->second->link_log.c_str(); }
        }
    }
    m_mutex.unlock_shared();

    return result;
}

bool OpenGL::VKSPIRVManager::get_spirv_blob_id_for_glsl(const char*          in_glsl_ptr,
                                                        OpenGL::SPIRVBlobID* out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_glsl_to_shader_data_map.find(std::string(in_glsl_ptr) );

        if (iterator != m_glsl_to_shader_data_map.end() )
        {
            if (out_result_ptr) { *out_result_ptr = iterator->second->id; }
            result          = true;
        }
    }
    m_mutex.unlock_shared();

    return result;
}

bool OpenGL::VKSPIRVManager::get_spirv_blob_id_for_program_reference(const GLuint&             in_program_id,
                                                                     const OpenGL::TimeMarker& in_time_marker,
                                                                     OpenGL::SPIRVBlobID*      out_result_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_program_reference_to_program_data_map.find(std::pair<GLuint, OpenGL::TimeMarker>(in_program_id, in_time_marker) );

        if (iterator != m_program_reference_to_program_data_map.end() )
        {
            if (out_result_ptr) { *out_result_ptr = iterator->second->id; }
            result          = true;
        }
    }
    m_mutex.unlock_shared();

    return result;
}

bool OpenGL::VKSPIRVManager::get_shader_compilation_status(const SPIRVBlobID& in_spirv_blob_id,
                                                           bool*              out_status_ptr,
                                                           const char**       out_compilation_log_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_spirv_blob_id_to_shader_data_map.find(in_spirv_blob_id);

        if (iterator != m_spirv_blob_id_to_shader_data_map.end() )
        {
            vkgl_assert(iterator->second->compile_task_fence_ptr != nullptr);

            iterator->second->compile_task_fence_ptr->wait();

            result                   = true;
            if (out_status_ptr) 		{ *out_status_ptr          = iterator->second->compilation_status; }
            if (out_compilation_log_ptr) { *out_compilation_log_ptr = iterator->second->compilation_log.c_str(); }
        }
    }
    m_mutex.unlock_shared();

    return result;
}

bool OpenGL::VKSPIRVManager::get_shader_module_ptr(const SPIRVBlobID&        in_spirv_blob_id,
                                                   const OpenGL::ShaderType& in_shader_type,
                                                   Anvil::ShaderModule**     out_result_ptr_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_spirv_blob_id_to_program_data_map.find(in_spirv_blob_id);

        if (iterator != m_spirv_blob_id_to_program_data_map.end() )
        {
            vkgl_assert(iterator->second->link_task_fence_ptr != nullptr);

            iterator->second->link_task_fence_ptr->wait();

            result              = true;
            if (out_result_ptr_ptr) { *out_result_ptr_ptr = iterator->second->shader_module_ptrs[static_cast<uint32_t>(in_shader_type)].get(); }
        }
    }
    m_mutex.unlock_shared();

    return result;
}

bool OpenGL::VKSPIRVManager::get_spirv_blob(const SPIRVBlobID& in_spirv_blob_id,
                                            const uint8_t**    out_spirv_blob_ptr,
                                            uint32_t*          out_spirv_blob_size_bytes_ptr) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    m_mutex.lock_shared();
    {
        auto iterator = m_spirv_blob_id_to_shader_data_map.find(in_spirv_blob_id);

        if (iterator != m_spirv_blob_id_to_shader_data_map.end() )
        {
            vkgl_assert(iterator->second->compile_task_fence_ptr != nullptr);

            iterator->second->compile_task_fence_ptr->wait();

            vkgl_assert(iterator->second->spirv_blob.size() > 0);
            if (iterator->second->spirv_blob.size() > 0)
            {
                result                         = true;
                if (out_spirv_blob_ptr) 			{ *out_spirv_blob_ptr            = &iterator->second->spirv_blob.at(0); }
                if (out_spirv_blob_size_bytes_ptr) { *out_spirv_blob_size_bytes_ptr = static_cast<uint32_t>(iterator->second->spirv_blob.size() ); }
            }
        }
    }
    m_mutex.unlock_shared();

    return result;
}

OpenGL::VariableType OpenGL::VKSPIRVManager::get_variable_type_for_glslang_type(const glslang::TType& in_type) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::VariableType result = OpenGL::VariableType::Unknown;

    switch (in_type.getBasicType() )
    {
        case glslang::TBasicType::EbtAtomicUint:
        case glslang::TBasicType::EbtDouble:
        case glslang::TBasicType::EbtFloat16:
        case glslang::TBasicType::EbtInt8:
        case glslang::TBasicType::EbtInt16:
        case glslang::TBasicType::EbtInt64:
        case glslang::TBasicType::EbtUint8:
        case glslang::TBasicType::EbtUint16:
        case glslang::TBasicType::EbtUint64:
        case glslang::TBasicType::EbtVoid:
        {
            /* Computer says no */
            vkgl_assert_fail();

            break;
        }

        case glslang::TBasicType::EbtBool:
        {
            switch (in_type.getVectorSize() )
            {
                case 1: result = OpenGL::VariableType::Bool;  break;
                case 2: result = OpenGL::VariableType::Bvec2; break;
                case 3: result = OpenGL::VariableType::Bvec3; break;
                case 4: result = OpenGL::VariableType::Bvec4; break;

                default:
                {
                    vkgl_assert_fail();
                }
            }

            break;
        }

        case glslang::TBasicType::EbtFloat:
        {
            if (in_type.getVectorSize() ||
            	(in_type.getMatrixRows() && in_type.getMatrixCols() ) )
        	{
                switch (in_type.getVectorSize() )
                {
                    case 1: result = OpenGL::VariableType::Float; break;
                    case 2: result = OpenGL::VariableType::Vec2;  break;
                    case 3: result = OpenGL::VariableType::Vec3;  break;
                    case 4: result = OpenGL::VariableType::Vec4;  break;
                }

                switch (in_type.getMatrixCols() )
                {
                    case 2:
                    {
                        switch (in_type.getMatrixRows() )
                        {
                            case 2: result = OpenGL::VariableType::Mat2;  break;
                            case 3: result = OpenGL::VariableType::Mat2x3;  break;
                            case 4: result = OpenGL::VariableType::Mat2x4;  break;
                        }
                    }
                    case 3:
                    {
                        switch (in_type.getMatrixRows() )
                        {
                            case 2: result = OpenGL::VariableType::Mat3x2;  break;
                            case 3: result = OpenGL::VariableType::Mat3;  break;
                            case 4: result = OpenGL::VariableType::Mat3x4;  break;
                        }
                    }
                    case 4:
                    {
                        switch (in_type.getMatrixRows() )
                        {
                            case 2: result = OpenGL::VariableType::Mat4x2;  break;
                            case 3: result = OpenGL::VariableType::Mat4x3;  break;
                            case 4: result = OpenGL::VariableType::Mat4;  break;
                        }
                    }
                }
            }
            else
            {
                vkgl_assert_fail();
            }
            
            break;
        }

        case glslang::TBasicType::EbtInt:
        {
            switch (in_type.getVectorSize() )
            {
                case 1: result = OpenGL::VariableType::Int;  break;
                case 2: result = OpenGL::VariableType::Ivec2; break;
                case 3: result = OpenGL::VariableType::Ivec3; break;
                case 4: result = OpenGL::VariableType::Ivec4; break;

                default:
                {
                    vkgl_assert_fail();
                }
            }

            break;
        }

        case glslang::TBasicType::EbtSampler:
        {
            /* TODO */
            //vkgl_not_implemented();
            
            result = OpenGL::VariableType::Sampler2D; break;

            break;
        }

        case glslang::TBasicType::EbtUint:
        {
            switch (in_type.getVectorSize() )
            {
                case 1: result = OpenGL::VariableType::Uint;  break;
                case 2: result = OpenGL::VariableType::Uvec2; break;
                case 3: result = OpenGL::VariableType::Uvec3; break;
                case 4: result = OpenGL::VariableType::Uvec4; break;

                default:
                {
                    vkgl_assert_fail();
                }
            }

            break;
        }

        case glslang::TBasicType::EbtBlock:
        case glslang::TBasicType::EbtStruct:
        {
            /* todo */
            vkgl_not_implemented();

            break;
        }

        default:
        {
            vkgl_assert_fail();
        }
    }

    return result;
}

bool OpenGL::VKSPIRVManager::init()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    bool result = false;

    result = init_glslang_resources();
    if (!result)
    {
        vkgl_assert(result);

        goto end;
    }

end:
    return result;
}

bool OpenGL::VKSPIRVManager::init_glslang_resources()
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto device_ptr          = m_backend_ptr->get_device_ptr ();
    auto frontend_limits_ptr = m_frontend_ptr->get_limits_ptr();
    bool result              = false;

    m_glslang_resources_ptr.reset(new TBuiltInResource() );

    vkgl_assert(m_glslang_resources_ptr != nullptr);
    if (m_glslang_resources_ptr == nullptr)
    {
        goto end;
    }

    m_glslang_resources_ptr->maxLights                                   = VKGL_MAX_LIGHTS; /* pre-core profile stuff */
    m_glslang_resources_ptr->maxClipPlanes                               = frontend_limits_ptr->get_max_clip_distances();
    m_glslang_resources_ptr->maxTextureUnits                             = VKGL_MAX_TEXTURE_UNITS; /* pre-core profile stuff */
    m_glslang_resources_ptr->maxTextureCoords                            = VKGL_MAX_TEXTURE_COORDS; /* pre-core profile stuff */
    m_glslang_resources_ptr->maxVertexAttribs                            = frontend_limits_ptr->get_max_vertex_attribs                ();
    m_glslang_resources_ptr->maxVertexUniformComponents                  = frontend_limits_ptr->get_max_vertex_uniform_components     ();
    m_glslang_resources_ptr->maxVaryingFloats                            = frontend_limits_ptr->get_max_varying_components            ();
    m_glslang_resources_ptr->maxVertexTextureImageUnits                  = frontend_limits_ptr->get_max_vertex_texture_image_units    ();
    m_glslang_resources_ptr->maxCombinedTextureImageUnits                = frontend_limits_ptr->get_max_combined_texture_image_units  ();
    m_glslang_resources_ptr->maxTextureImageUnits                        = frontend_limits_ptr->get_max_texture_image_units           ();
    m_glslang_resources_ptr->maxFragmentUniformComponents                = frontend_limits_ptr->get_max_fragment_uniform_components   ();
    m_glslang_resources_ptr->maxDrawBuffers                              = frontend_limits_ptr->get_max_draw_buffers                  ();
    m_glslang_resources_ptr->maxVertexUniformVectors                     = frontend_limits_ptr->get_max_vertex_uniform_components     () / 4; /* magic number as per spec */
    m_glslang_resources_ptr->maxVaryingVectors                           = frontend_limits_ptr->get_max_varying_components            () / 4; /* magic number as per spec */
    m_glslang_resources_ptr->maxFragmentUniformVectors                   = frontend_limits_ptr->get_max_fragment_uniform_components   () / 4; /* magic number as per spec */
    m_glslang_resources_ptr->maxVertexOutputVectors                      = frontend_limits_ptr->get_max_vertex_output_components      () / 4; /* magic number as per spec */
    m_glslang_resources_ptr->maxFragmentInputVectors                     = frontend_limits_ptr->get_max_fragment_input_components     () / 4; /* magic number as per spec */
    m_glslang_resources_ptr->minProgramTexelOffset                       = frontend_limits_ptr->get_min_program_texel_offset          ();
    m_glslang_resources_ptr->maxProgramTexelOffset                       = frontend_limits_ptr->get_max_program_texel_offset          ();
    m_glslang_resources_ptr->maxClipDistances                            = frontend_limits_ptr->get_max_clip_distances                ();
    m_glslang_resources_ptr->maxComputeWorkGroupCountX                   = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_count      ()[0]; */
    m_glslang_resources_ptr->maxComputeWorkGroupCountY                   = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_count      ()[1]; */
    m_glslang_resources_ptr->maxComputeWorkGroupCountZ                   = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_count      ()[2]; */
    m_glslang_resources_ptr->maxComputeWorkGroupSizeX                    = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_size       ()[0]; */
    m_glslang_resources_ptr->maxComputeWorkGroupSizeY                    = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_size       ()[1]; */
    m_glslang_resources_ptr->maxComputeWorkGroupSizeZ                    = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_work_group_size       ()[2]; */
    m_glslang_resources_ptr->maxComputeUniformComponents                 = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_uniform_components    ();    */
    m_glslang_resources_ptr->maxComputeTextureImageUnits                 = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_texture_image_units   ();    */
    m_glslang_resources_ptr->maxComputeImageUniforms                     = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_image_uniforms        ();    */
    m_glslang_resources_ptr->maxComputeAtomicCounters                    = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_atomic_counters       ();    */
    m_glslang_resources_ptr->maxComputeAtomicCounterBuffers              = 0; /* No support for compute shaders in GL 3.2: frontend_limits_ptr->get_max_compute_atomic_counter_buffers();    */
    m_glslang_resources_ptr->maxVaryingComponents                        = frontend_limits_ptr->get_max_varying_components            ();
    m_glslang_resources_ptr->maxVertexOutputComponents                   = frontend_limits_ptr->get_max_vertex_output_components      ();
    m_glslang_resources_ptr->maxGeometryInputComponents                  = frontend_limits_ptr->get_max_geometry_input_components     ();
    m_glslang_resources_ptr->maxGeometryOutputComponents                 = frontend_limits_ptr->get_max_geometry_output_components    ();
    m_glslang_resources_ptr->maxFragmentInputComponents                  = frontend_limits_ptr->get_max_fragment_input_components     ();
    m_glslang_resources_ptr->maxImageUnits                               = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_image_units                              (); */
    m_glslang_resources_ptr->maxCombinedImageUnitsAndFragmentOutputs     = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_combined_image_units_and_fragment_outputs(); */
    m_glslang_resources_ptr->maxCombinedShaderOutputResources            = /* No support for SSBOs in GL 3.2:  frontend_limits_ptr->get_max_combined_shader_storage_blocks() + */
                                                                           /* No support for images in GL 3.2: frontend_limits_ptr->get_max_combined_image_uniforms       () + */
                                                                           frontend_limits_ptr->get_max_draw_buffers();
    m_glslang_resources_ptr->maxImageSamples                             = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_image_samples                 (); */
    m_glslang_resources_ptr->maxVertexImageUniforms                      = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_vertex_image_uniforms         (); */
    m_glslang_resources_ptr->maxTessControlImageUniforms                 = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_tess_control_image_uniforms   (); */
    m_glslang_resources_ptr->maxTessEvaluationImageUniforms              = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_image_uniforms(); */
    m_glslang_resources_ptr->maxGeometryImageUniforms                    = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_geometry_image_uniforms       (); */
    m_glslang_resources_ptr->maxFragmentImageUniforms                    = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_fragment_image_uniforms       (); */
    m_glslang_resources_ptr->maxCombinedImageUniforms                    = 0; /* No support for images in GL 3.2: frontend_limits_ptr->get_max_combined_image_uniforms       (); */
    m_glslang_resources_ptr->maxGeometryTextureImageUnits                = frontend_limits_ptr->get_max_geometry_texture_image_units    ();
    m_glslang_resources_ptr->maxGeometryOutputVertices                   = frontend_limits_ptr->get_max_geometry_output_vertices        ();
    m_glslang_resources_ptr->maxGeometryTotalOutputComponents            = frontend_limits_ptr->get_max_geometry_total_output_components();
    m_glslang_resources_ptr->maxGeometryUniformComponents                = frontend_limits_ptr->get_max_geometry_uniform_components     ();
    m_glslang_resources_ptr->maxGeometryVaryingComponents                = 0; /* ES stuff? */
    m_glslang_resources_ptr->maxTessControlInputComponents               = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_control_input_components       (); */
    m_glslang_resources_ptr->maxTessControlOutputComponents              = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_control_output_components      (); */
    m_glslang_resources_ptr->maxTessControlTextureImageUnits             = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_control_texture_image_units    (); */
    m_glslang_resources_ptr->maxTessControlUniformComponents             = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_control_uniform_components     (); */
    m_glslang_resources_ptr->maxTessControlTotalOutputComponents         = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_control_total_output_components(); */
    m_glslang_resources_ptr->maxTessEvaluationInputComponents            = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_input_components    (); */
    m_glslang_resources_ptr->maxTessEvaluationOutputComponents           = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_output_components   (); */
    m_glslang_resources_ptr->maxTessEvaluationTextureImageUnits          = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_texture_image_units (); */
    m_glslang_resources_ptr->maxTessEvaluationUniformComponents          = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_uniform_components  (); */
    m_glslang_resources_ptr->maxTessPatchComponents                      = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_patch_components               (); */
    m_glslang_resources_ptr->maxPatchVertices                            = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_patch_vertices                      (); */
    m_glslang_resources_ptr->maxTessGenLevel                             = 0; /* No support for tess shaders in GL 3.2: frontend_limits_ptr->get_max_tess_gen_level                      (); */
    m_glslang_resources_ptr->maxViewports                                = 1; /* No support for multiple viewports in GL 3.2 */
    m_glslang_resources_ptr->maxVertexAtomicCounters                     = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_vertex_atomic_counters                (); */
    m_glslang_resources_ptr->maxTessControlAtomicCounters                = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_tess_control_atomic_counters          (); */
    m_glslang_resources_ptr->maxTessEvaluationAtomicCounters             = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_atomic_counters       (); */
    m_glslang_resources_ptr->maxGeometryAtomicCounters                   = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_geometry_atomic_counters              (); */
    m_glslang_resources_ptr->maxFragmentAtomicCounters                   = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_fragment_atomic_counters              (); */
    m_glslang_resources_ptr->maxCombinedAtomicCounters                   = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_combined_atomic_counters              (); */
    m_glslang_resources_ptr->maxAtomicCounterBindings                    = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_atomic_counter_bindings               (); */
    m_glslang_resources_ptr->maxVertexAtomicCounterBuffers               = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_vertex_atomic_counter_buffers         (); */
    m_glslang_resources_ptr->maxTessControlAtomicCounterBuffers          = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_tess_control_atomic_counter_buffers   (); */
    m_glslang_resources_ptr->maxTessEvaluationAtomicCounterBuffers       = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_tess_evaluation_atomic_counter_buffers(); */
    m_glslang_resources_ptr->maxGeometryAtomicCounterBuffers             = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_geometry_atomic_counter_buffers       (); */
    m_glslang_resources_ptr->maxFragmentAtomicCounterBuffers             = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_fragment_atomic_counter_buffers       (); */
    m_glslang_resources_ptr->maxCombinedAtomicCounterBuffers             = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_combined_atomic_counter_buffers       (); */
    m_glslang_resources_ptr->maxAtomicCounterBufferSize                  = 0; /* No support for atomic counters in GL 3.2: frontend_limits_ptr->get_max_atomic_counter_buffer_size            (); */
    m_glslang_resources_ptr->maxTransformFeedbackBuffers                 = frontend_limits_ptr->get_max_transform_feedback_buffers               ();
    m_glslang_resources_ptr->maxTransformFeedbackInterleavedComponents   = frontend_limits_ptr->get_max_transform_feedback_interleaved_components();
    m_glslang_resources_ptr->maxCullDistances                            = 0; /* No support for ARB_cull_distance in GL3.2: frontend_limits_ptr->get_max_cull_distances                  (); */
    m_glslang_resources_ptr->maxCombinedClipAndCullDistances             = 0; /* No support for ARB_cull_distance in GL3.2: frontend_limits_ptr->get_max_combined_clip_and_cull_distances(); */
    m_glslang_resources_ptr->maxSamples                                  = frontend_limits_ptr->get_max_samples();
    m_glslang_resources_ptr->limits.nonInductiveForLoops                 = true;
    m_glslang_resources_ptr->limits.whileLoops                           = true;
    m_glslang_resources_ptr->limits.doWhileLoops                         = true;
    m_glslang_resources_ptr->limits.generalUniformIndexing               = true;
    m_glslang_resources_ptr->limits.generalAttributeMatrixVectorIndexing = true;
    m_glslang_resources_ptr->limits.generalVaryingIndexing               = true;
    m_glslang_resources_ptr->limits.generalSamplerIndexing               = (device_ptr->get_extension_info()->ext_descriptor_indexing() );
    m_glslang_resources_ptr->limits.generalVariableIndexing              = true;
    m_glslang_resources_ptr->limits.generalConstantMatrixVectorIndexing  = true;

    result = true;
end:
    return result;
}

void OpenGL::VKSPIRVManager::link_program(ProgramData* in_program_data_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    /* NOTE: This function is called back from one of the backend thread pool's threads */
    auto                               frontend_program_manager_ptr = m_frontend_ptr->get_program_manager_ptr();
    std::unique_ptr<glslang::TProgram> glslang_program_ptr;
    const auto                         program_id                   = in_program_data_ptr->program_reference_ptr->get_payload().id;
    const auto                         program_time_marker          = in_program_data_ptr->program_reference_ptr->get_payload().time_marker;

    glslang_program_ptr.reset(new glslang::TProgram() );
    vkgl_assert(glslang_program_ptr!= nullptr);

    for (const auto& current_shader_data_ptr : in_program_data_ptr->shader_ptrs)
    {
        glslang_program_ptr->addShader(current_shader_data_ptr->glslang_shader_ptr.get() );
    }

    /* NOTE: We do not support predefined bindings & locations specified via GL API calls just yet. */
    {
        const OpenGL::AttributeLocationBindingMap*    attribute_location_bindings_ptr  = nullptr;
        const OpenGL::FragDataLocationMap*            frag_data_location_mappings_ptr  = nullptr;
        const std::unordered_map<uint32_t, uint32_t>* ub_index_to_binding_mappings_ptr = nullptr;

        if (!frontend_program_manager_ptr->get_program_link_time_properties(program_id,
                                                                           &program_time_marker,
                                                                           &attribute_location_bindings_ptr,
                                                                           &frag_data_location_mappings_ptr,
                                                                           &ub_index_to_binding_mappings_ptr) )
        {
            vkgl_assert_fail();
        }

        vkgl_assert(attribute_location_bindings_ptr->size () == 0); /* TODO */
        vkgl_assert(frag_data_location_mappings_ptr->size () == 0); /* TODO */
        vkgl_assert(ub_index_to_binding_mappings_ptr->size() == 0); /* TODO */
    }

    /* Link the program and cache result SPIR-V blobs.. */
    in_program_data_ptr->link_status = glslang_program_ptr->link      (static_cast<EShMessages>(EShMsgDefault/* | EShMsgSpvRules*//* | EShMsgVulkanRules*/) );
    in_program_data_ptr->link_log    = glslang_program_ptr->getInfoLog();

	{
		restore_glsl_symbol_names(in_program_data_ptr->link_log);
	}
vkgl_printf(">>>>LINK_LOG>>>>\n%s\n>>>>>>>>", in_program_data_ptr->link_log.c_str() );
    if (!glslang_program_ptr->mapIO(nullptr, 
    									nullptr) ) //< TODO: Need to use app-specified data here
    {
        vkgl_assert_fail();
    }

    if (!glslang_program_ptr->buildReflection() )
    {
        vkgl_assert_fail();
    }

    if (in_program_data_ptr->link_status)
    {
        for (const auto& current_shader_data_ptr : in_program_data_ptr->shader_ptrs)
        {
            const auto            shader_type           = current_shader_data_ptr->type;
            const auto            intermediate_ptr      = glslang_program_ptr->getIntermediate(OpenGL::Utils::get_sh_language_for_opengl_shader_type(shader_type) );
            glslang::SpvOptions spv_options;
            std::vector<uint8_t>& result_spirv_blob_u8  = in_program_data_ptr->spirv_blobs[static_cast<uint32_t>(shader_type)];
            std::vector<uint32_t> result_spirv_blob_u32;

            glslang::GlslangToSpv(*intermediate_ptr,
                                  result_spirv_blob_u32,
                                  nullptr,
                                  &spv_options);

            if (result_spirv_blob_u32.size() == 0)
            {
                vkgl_assert_fail();
            }
            else
            {
                result_spirv_blob_u8.resize(result_spirv_blob_u32.size() * sizeof(uint32_t) );

                #if defined(_DEBUG)
                {
                    std::stringbuf spirv_out_str;
                    std::ostream spirv_out(&spirv_out_str);
                    
                    spv::Disassemble(spirv_out,
                    				result_spirv_blob_u32);
                    
                    vkgl_printf("spirv_out_str:\n%s\n", spirv_out_str.str().c_str() );
                }
                #endif

                memcpy(&result_spirv_blob_u8.at(0),
                       &result_spirv_blob_u32.at(0),
                        result_spirv_blob_u8.size() );
            }

            vkgl_assert(shader_type == ShaderType::Fragment ||
                        shader_type == ShaderType::Geometry ||
                        shader_type == ShaderType::Vertex);

            in_program_data_ptr->shader_module_ptrs[static_cast<uint32_t>(current_shader_data_ptr->type)] = Anvil::ShaderModule::create_from_spirv_blob(m_backend_ptr->get_device_ptr(),
                                                                                                                                                       &result_spirv_blob_u32.at(0),
                                                                                                                                                        static_cast<uint32_t>(result_spirv_blob_u32.size() ),
                                                                                                                                                        "",  /* in_opt_cs_entrypoint_name */
                                                                                                                                                        (shader_type == ShaderType::Fragment) ? current_shader_data_ptr->sm_entrypoint_name : "",
                                                                                                                                                        (shader_type == ShaderType::Geometry) ? current_shader_data_ptr->sm_entrypoint_name : "",
                                                                                                                                                        "",  /* in_opt_tc_entrypoint_name */
                                                                                                                                                        "",  /* in_opt_te_entrypoint_name */
                                                                                                                                                        (shader_type == ShaderType::Vertex) ? current_shader_data_ptr->sm_entrypoint_name : "");
            vkgl_assert(in_program_data_ptr->shader_module_ptrs[static_cast<uint32_t>(current_shader_data_ptr->type)] != nullptr);
        }
    }

    /* Create, fill and associate post-link data struct with the GL program */
    {
        auto post_link_data_ptr = create_post_link_data(glslang_program_ptr.get() );
        vkgl_assert(post_link_data_ptr != nullptr);

        frontend_program_manager_ptr->set_program_post_link_data_ptr(program_id,
                                                                    &program_time_marker,
                                                                     std::move(post_link_data_ptr) );
    }

    glslang_program_ptr->dumpReflection();

    in_program_data_ptr->need_rebuild_uniform_resources = true;

    /* All done, signal the fence we're done */
    in_program_data_ptr->link_task_fence_ptr->signal();

    /* NOTE: We do NOT cache the TProgram instance. It's not going to be needed afterwards */
    in_program_data_ptr->program_reference_ptr.reset();
}

void OpenGL::VKSPIRVManager::remove_unused_symbols(glslang::TIntermediate& in_intermediate) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
    	struct RemoveUnusedSymbolsTraverser : glslang::TIntermTraverser {
            virtual void visitSymbol(glslang::TIntermSymbol* in_symbol)
            {
            	if (!m_is_processing_functions)
            	{
            	
            	}
            	else
            	{
            	
            	}
            }

            RemoveUnusedSymbolsTraverser(glslang::TIntermediate& in_intermediate)
            	:TIntermTraverser				(),
            	m_is_processing_functions(true),
            	m_intermediate				(in_intermediate)
            {
            	/* Stub */
            }
            
            void set_is_processing_functions(bool in_is_processing_functions)
            {
            	m_is_processing_functions = in_is_processing_functions;
            }
            
            void do_remove(void)
            {
            	if (m_is_processing_functions)
            	{
            	
            	}
            	else
            	{
            	
            	}
            }
            
            bool 					m_is_processing_functions;
            glslang::TIntermediate& m_intermediate;
            std::unordered_set<std::string> m_used_function_names;
            std::unordered_set<std::string> m_used_variable_names;
        };
        
        RemoveUnusedSymbolsTraverser it(in_intermediate);
        auto 							tree_root = in_intermediate.getTreeRoot();
        
        it.set_is_processing_functions(true);
        tree_root->traverse(&it);
        
        it.set_is_processing_functions(false);
        tree_root->traverse(&it);
        
        it.do_remove();
    }
}

void OpenGL::VKSPIRVManager::restore_glsl_symbol_names(std::string& inout_glsl_code) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    static std::string from_vkgl_built_in_to_built_in_FIND_string 			= "(([^\\w]))vkgl_";
    static std::string from_vkgl_built_in_to_built_in_REPLACE_string 		= "$2";
    static std::string from__vkgl_custom_to_vkgl_custom_FIND_string 	= "((^\\w[_]*))_vkgl_";
    static std::string from__vkgl_custom_to_vkgl_custom_REPLACE_string = "$2vkgl_";
    
    /* restore the glsl symbol names that are modified in function OpenGL::VKSPIRVManager::patch_glsl_code
     * from "vkgl_(built-in)" to "(built-in)"
     * and from "_vkgl_(custom)" to "vkgl_(custom)".
     *
     */
	{
    	inout_glsl_code.insert(0,
							" ",
							strlen(" ") );
    	
		inout_glsl_code = regex_replace(inout_glsl_code,
										std::regex(from_vkgl_built_in_to_built_in_FIND_string),
										from_vkgl_built_in_to_built_in_REPLACE_string);
    	
    	inout_glsl_code = regex_replace(inout_glsl_code,
    									std::regex(from__vkgl_custom_to_vkgl_custom_FIND_string),
    									from__vkgl_custom_to_vkgl_custom_REPLACE_string);
    	
    	inout_glsl_code.erase(0,
							strlen(" ") );
	}
}

void OpenGL::VKSPIRVManager::patch_glsl_code(const ShaderData* in_shader_data_ptr,
                                             std::string&      inout_glsl_code) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    {
        auto& type = in_shader_data_ptr->type;
        auto& source = inout_glsl_code;
        
        struct shaderVersion
        {
        	const char * const version =
        		"#version 450 core" "\n";
        } shaderVersion;
        
        struct shaderExtensions
        {
        	const char * const extensions =
				"#extension GL_ARB_shading_language_420pack : enable" "\n"
				"#extension GL_ARB_separate_shader_objects : enable" "\n";
        } shaderExtensions;
        
    	const char * const shaderCompatibilityVertexFunctions = 
                "vec4 ftransform(void) {" "\n"
                "    return gl_ModelViewProjectionMatrix * gl_Vertex;" "\n"
                "}" "\n";
        
    	const char * const shaderCompatibilityFragmentFunctions = 
    			"" "\n";
    	
    	const char * const shaderCompatibilityCommonFunctions = 
    			"" "\n";
    	
    	struct shaderCompatibilityFragmentOuts
    	{
            const char * const gl_FragColor =
                "layout(location = 0) out mediump vec4 gl_FragColor;" "\n";
            const char * const gl_FragData =
                "layout(location = 0) out mediump vec4 gl_FragData[gl_MaxDrawBuffers];" "\n";
        } shaderCompatibilityFragmentOuts;
        
    	const char * const shaderCompatibilityAttributes = 
                "in vec4  gl_Color;" "\n"
                "in vec4  gl_SecondaryColor;" "\n"
                "in vec3  gl_Normal;" "\n"
                "in vec4  gl_Vertex;" "\n"
                "in vec4  gl_MultiTexCoord0;" "\n"
                "in vec4  gl_MultiTexCoord1;" "\n"
                "in vec4  gl_MultiTexCoord2;" "\n"
                "in vec4  gl_MultiTexCoord3;" "\n"
                "in vec4  gl_MultiTexCoord4;" "\n"
                "in vec4  gl_MultiTexCoord5;" "\n"
                "in vec4  gl_MultiTexCoord6;" "\n"
                "in vec4  gl_MultiTexCoord7;" "\n"
                "in float gl_FogCoord;" "\n";
        
    	const char * const shaderCompatibilityVaryings = 
                    "        vec4  gl_ClipVertex;" "\n"       // needs qualifier fixed later
                    "varying vec4  gl_FrontColor;" "\n"
                    "varying vec4  gl_BackColor;" "\n"
                    "varying vec4  gl_FrontSecondaryColor;" "\n"
                    "varying vec4  gl_BackSecondaryColor;" "\n"
                    "varying vec4  gl_TexCoord[gl_MaxTextureCoords];" "\n"
                    "varying float gl_FogFragCoord;" "\n";
        
    	const char * const shaderCompatibilityUniforms = 
        //
        // Matrix state. p. 31, 32, 37, 39, 40.
        //
            "uniform mat4  gl_ModelViewMatrix;" "\n"
            "uniform mat4  gl_ProjectionMatrix;" "\n"
            "uniform mat4  gl_ModelViewProjectionMatrix;" "\n"

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
            "uniform mat3  gl_NormalMatrix;" "\n"

            "uniform mat4  gl_ModelViewMatrixInverse;" "\n"
            "uniform mat4  gl_ProjectionMatrixInverse;" "\n"
            "uniform mat4  gl_ModelViewProjectionMatrixInverse;" "\n"

            "uniform mat4  gl_ModelViewMatrixTranspose;" "\n"
            "uniform mat4  gl_ProjectionMatrixTranspose;" "\n"
            "uniform mat4  gl_ModelViewProjectionMatrixTranspose;" "\n"

            "uniform mat4  gl_ModelViewMatrixInverseTranspose;" "\n"
            "uniform mat4  gl_ProjectionMatrixInverseTranspose;" "\n"
            "uniform mat4  gl_ModelViewProjectionMatrixInverseTranspose;" "\n"

            //
            // Normal scaling p. 39.
            //
            "uniform float gl_NormalScale;" "\n"

            //
            // Material State p. 50, 55.
            //
            "struct gl_MaterialParameters {" "\n"
                "vec4  emission;" "\n"    // Ecm
                "vec4  ambient;" "\n"     // Acm
                "vec4  diffuse;" "\n"     // Dcm
                "vec4  specular;" "\n"    // Scm
                "float shininess;" "\n"   // Srm
            "};" "\n"
            "uniform gl_MaterialParameters  gl_FrontMaterial;" "\n"
            "uniform gl_MaterialParameters  gl_BackMaterial;" "\n"

            //
            // Light State p 50, 53, 55.
            //
            "struct gl_LightSourceParameters {" "\n"
                "vec4  ambient;" "\n"             // Acli
                "vec4  diffuse;" "\n"             // Dcli
                "vec4  specular;" "\n"            // Scli
                "vec4  position;" "\n"            // Ppli
                "vec4  halfVector;" "\n"          // Derived: Hi
                "vec3  spotDirection;" "\n"       // Sdli
                "float spotExponent;" "\n"        // Srli
                "float spotCutoff;" "\n"          // Crli
                                                        // (range: [0.0,90.0], 180.0)
                "float spotCosCutoff;" "\n"       // Derived: cos(Crli)
                                                        // (range: [1.0,0.0],-1.0)
                "float constantAttenuation;" "\n" // K0
                "float linearAttenuation;" "\n"   // K1
                "float quadraticAttenuation;" "\n"// K2
            "};" "\n"

            "struct gl_LightModelParameters {" "\n"
                "vec4  ambient;" "\n"       // Acs
            "};" "\n"

            "uniform gl_LightModelParameters  gl_LightModel;" "\n"

            //
            // Derived state from products of light and material.
            //
            "struct gl_LightModelProducts {" "\n"
                "vec4  sceneColor;" "\n"     // Derived. Ecm + Acm * Acs
            "};" "\n"

            "uniform gl_LightModelProducts gl_FrontLightModelProduct;" "\n"
            "uniform gl_LightModelProducts gl_BackLightModelProduct;" "\n"

            "struct gl_LightProducts {" "\n"
                "vec4  ambient;" "\n"        // Acm * Acli
                "vec4  diffuse;" "\n"        // Dcm * Dcli
                "vec4  specular;" "\n"       // Scm * Scli
            "};" "\n"

            //
            // Fog p. 161
            //
            "struct gl_FogParameters {" "\n"
                "vec4  color;" "\n"
                "float density;" "\n"
                "float start;" "\n"
                "float end;" "\n"
                "float scale;" "\n"   //  1 / (gl_FogEnd - gl_FogStart)
            "};" "\n"

            "uniform gl_FogParameters gl_Fog;" "\n"
            
            //
            // Matrix state. p. 31, 32, 37, 39, 40.
            //
                        "uniform mat4  gl_TextureMatrix[gl_MaxTextureCoords];" "\n"

            //
            // Derived matrix state that provides inverse and transposed versions
            // of the matrices above.
            //
                        "uniform mat4  gl_TextureMatrixInverse[gl_MaxTextureCoords];" "\n"

                        "uniform mat4  gl_TextureMatrixTranspose[gl_MaxTextureCoords];" "\n"

                        "uniform mat4  gl_TextureMatrixInverseTranspose[gl_MaxTextureCoords];" "\n"

            //
            // Light State p 50, 53, 55.
            //
                        "uniform gl_LightSourceParameters  gl_LightSource[gl_MaxLights];" "\n"

            //
            // Derived state from products of light.
            //
                        "uniform gl_LightProducts gl_FrontLightProduct[gl_MaxLights];" "\n"
                        "uniform gl_LightProducts gl_BackLightProduct[gl_MaxLights];" "\n"

            //
            // Texture Environment and Generation, p. 152, p. 40-42.
            //
                        "uniform vec4  gl_TextureEnvColor[gl_MaxTextureImageUnits];" "\n"
                        "uniform vec4  gl_EyePlaneS[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_EyePlaneT[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_EyePlaneR[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_EyePlaneQ[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_ObjectPlaneS[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_ObjectPlaneT[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_ObjectPlaneR[gl_MaxTextureCoords];" "\n"
                        "uniform vec4  gl_ObjectPlaneQ[gl_MaxTextureCoords];" "\n";
        
        /* process header. */
        {
    	    std::string sourceHeader = "";
    	    {
        	    std::smatch results;
        	    
        	    {
            	    sourceHeader += std::string(shaderVersion.version);
                    sourceHeader += std::string(shaderExtensions.extensions);
                }
                
                {
                    if (type == OpenGL::ShaderType::Vertex)
                    {
                    	sourceHeader += std::string(shaderCompatibilityAttributes);
                    }
                    
                    if (type == OpenGL::ShaderType::Fragment)
                    {
                    	if (regex_search(source,
                    					results,
                    					std::regex("[^\\w]gl_FragColor[^\\w]") ) )
                    	{
                        	sourceHeader += std::string(shaderCompatibilityFragmentOuts.gl_FragColor);
                    	}
                    	
                    	if (regex_search(source,
                    					results,
                    					std::regex("[^\\w]gl_FragData[^\\w]") ) )
                    	{
                        	sourceHeader += std::string(shaderCompatibilityFragmentOuts.gl_FragData);
                    	}
                    }
                }
                
                {
                    sourceHeader += std::string(shaderCompatibilityUniforms);
                    sourceHeader += std::string(shaderCompatibilityVaryings);
                }
                
                {
                    if (type == OpenGL::ShaderType::Vertex)
                    {
                        sourceHeader += std::string(shaderCompatibilityVertexFunctions);
                    }
                    
                    if (type == OpenGL::ShaderType::Fragment)
                    {
                        sourceHeader += std::string(shaderCompatibilityFragmentFunctions);
                    }
                    
                    sourceHeader += std::string(shaderCompatibilityCommonFunctions);
                }
            }
        	
    	    // If #version is present
            size_t found = source.find("#version");
            if (found != std::string::npos)
            {
                size_t f1 = source.find("\n", found);
                source.replace(found,
                				(f1 - found),
                				sourceHeader);
            }
            else
            {
                source.insert(0,
                			sourceHeader);
            }
        }
        
        /* pre process */
        {
            if (type == OpenGL::ShaderType::Vertex)
            {
                /* convert GL to Vulkan depth range */
                {
                    // Find last "}"
                    size_t pos = source.rfind("}");
                
                    std::string GlToVkDepthRangeConversion = std::string("    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;" "\n");
                    source.insert(pos,
                    			GlToVkDepthRangeConversion);
                }
            }
        }
        
        {
        	/* vkgl_(custom) => _vkgl_(custom) */
        	{
            	source = regex_replace(source,
            							std::regex("(([^\\w][_]*))vkgl_"),
            							"$2_vkgl_");
        	}
        	
        	
        	/* (built-in) => vkgl_(built-in) */
        	{
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewMatrix))"),
            							"$2vkgl_$4"); // gl_ModelViewMatrix => vkgl_gl_ModelViewMatrix
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ProjectionMatrix))"),
            							"$2vkgl_$4"); // gl_ProjectionMatrix => vkgl_gl_ProjectionMatrix
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewProjectionMatrix))"),
            							"$2vkgl_$4"); // gl_ModelViewProjectionMatrix => vkgl_gl_ModelViewProjectionMatrix
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_NormalMatrix))"),
            							"$2vkgl_$4"); // gl_NormalMatrix => vkgl_gl_NormalMatrix
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewMatrixInverse))"),
            							"$2vkgl_$4"); // gl_ModelViewMatrixInverse => vkgl_gl_ModelViewMatrixInverse
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ProjectionMatrixInverse))"),
            							"$2vkgl_$4"); // gl_ProjectionMatrixInverse => vkgl_gl_ProjectionMatrixInverse
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewProjectionMatrixInverse))"),
            							"$2vkgl_$4"); // gl_ModelViewProjectionMatrixInverse => vkgl_gl_ModelViewProjectionMatrixInverse
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewMatrixTranspose))"),
            							"$2vkgl_$4"); // gl_ModelViewMatrixTranspose => vkgl_gl_ModelViewMatrixTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ProjectionMatrixTranspose))"),
            							"$2vkgl_$4"); // gl_ProjectionMatrixTranspose => vkgl_gl_ProjectionMatrixTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewProjectionMatrixTranspose))"),
            							"$2vkgl_$4"); // gl_ModelViewProjectionMatrixTranspose => vkgl_gl_ModelViewProjectionMatrixTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewMatrixInverseTranspose))"),
            							"$2vkgl_$4"); // gl_ModelViewMatrixInverseTranspose => vkgl_gl_ModelViewMatrixInverseTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ProjectionMatrixInverseTranspose))"),
            							"$2vkgl_$4"); // gl_ProjectionMatrixInverseTranspose => vkgl_gl_ProjectionMatrixInverseTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ModelViewProjectionMatrixInverseTranspose))"),
            							"$2vkgl_$4"); // gl_ModelViewProjectionMatrixInverseTranspose => vkgl_gl_ModelViewProjectionMatrixInverseTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_NormalScale))"),
            							"$2vkgl_$4"); // gl_NormalScale => vkgl_gl_NormalScale
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MaterialParameters))"),
            							"$2vkgl_$4"); // gl_MaterialParameters => vkgl_gl_MaterialParameters
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FrontMaterial))"),
            							"$2vkgl_$4"); // gl_FrontMaterial => vkgl_gl_FrontMaterial
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_BackMaterial))"),
            							"$2vkgl_$4"); // gl_BackMaterial => vkgl_gl_BackMaterial
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightModelParameters))"),
            							"$2vkgl_$4"); // gl_LightModelParameters => vkgl_gl_LightModelParameters
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightModel))"),
            							"$2vkgl_$4"); // gl_LightModel => vkgl_gl_LightModel
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightModelProducts))"),
            							"$2vkgl_$4"); // gl_LightModelProducts => vkgl_gl_LightModelProducts
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FrontLightModelProduct))"),
            							"$2vkgl_$4"); // gl_FrontLightModelProduct => vkgl_gl_FrontLightModelProduct
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_BackLightModelProduct))"),
            							"$2vkgl_$4"); // gl_BackLightModelProduct => vkgl_gl_BackLightModelProduct
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FogParameters))"),
            							"$2vkgl_$4"); // gl_FogParameters => vkgl_gl_FogParameters
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_Fog))"),
            							"$2vkgl_$4"); // gl_Fog => vkgl_gl_Fog
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TextureMatrix))"),
            							"$2vkgl_$4"); // gl_TextureMatrix => vkgl_gl_TextureMatrix
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TextureMatrixInverse))"),
            							"$2vkgl_$4"); // gl_TextureMatrixInverse => vkgl_gl_TextureMatrixInverse
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TextureMatrixTranspose))"),
            							"$2vkgl_$4"); // gl_TextureMatrixTranspose => vkgl_gl_TextureMatrixTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TextureMatrixInverseTranspose))"),
            							"$2vkgl_$4"); // gl_TextureMatrixInverseTranspose => vkgl_gl_TextureMatrixInverseTranspose
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightSourceParameters))"),
            							"$2vkgl_$4"); // gl_LightSourceParameters => vkgl_gl_LightSourceParameters
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightSource))"),
            							"$2vkgl_$4"); // gl_LightSource => vkgl_gl_LightSource
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_LightProducts))"),
            							"$2vkgl_$4"); // gl_LightProducts => vkgl_gl_LightProducts
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FrontLightProduct))"),
            							"$2vkgl_$4"); // gl_FrontLightProduct => vkgl_gl_FrontLightProduct
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_BackLightProduct))"),
            							"$2vkgl_$4"); // gl_BackLightProduct => vkgl_gl_BackLightProduct
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TextureEnvColor))"),
            							"$2vkgl_$4"); // gl_TextureEnvColor => vkgl_gl_TextureEnvColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_EyePlaneS))"),
            							"$2vkgl_$4"); // gl_EyePlaneS => vkgl_gl_EyePlaneS
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_EyePlaneT))"),
            							"$2vkgl_$4"); // gl_EyePlaneT => vkgl_gl_EyePlaneT
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_EyePlaneR))"),
            							"$2vkgl_$4"); // gl_EyePlaneR => vkgl_gl_EyePlaneR
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_EyePlaneQ))"),
            							"$2vkgl_$4"); // gl_EyePlaneQ => vkgl_gl_EyePlaneQ
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ObjectPlaneS))"),
            							"$2vkgl_$4"); // gl_ObjectPlaneS => vkgl_gl_ObjectPlaneS
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ObjectPlaneT))"),
            							"$2vkgl_$4"); // gl_ObjectPlaneT => vkgl_gl_ObjectPlaneT
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ObjectPlaneR))"),
            							"$2vkgl_$4"); // gl_ObjectPlaneR => vkgl_gl_ObjectPlaneR
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ObjectPlaneQ))"),
            							"$2vkgl_$4"); // gl_ObjectPlaneQ => vkgl_gl_ObjectPlaneQ
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_Color))"),
            							"$2vkgl_$4"); // gl_Color => vkgl_gl_Color
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_SecondaryColor))"),
            							"$2vkgl_$4"); // gl_SecondaryColor => vkgl_gl_SecondaryColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_Normal))"),
            							"$2vkgl_$4"); // gl_Normal => vkgl_gl_Normal
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_Vertex))"),
            							"$2vkgl_$4"); // gl_Vertex => vkgl_gl_Vertex
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord0))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord0 => vkgl_gl_MultiTexCoord0
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord1))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord1 => vkgl_gl_MultiTexCoord1
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord2))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord2 => vkgl_gl_MultiTexCoord2
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord3))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord3 => vkgl_gl_MultiTexCoord3
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord4))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord4 => vkgl_gl_MultiTexCoord4
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord5))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord5 => vkgl_gl_MultiTexCoord5
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord6))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord6 => vkgl_gl_MultiTexCoord6
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_MultiTexCoord7))"),
            							"$2vkgl_$4"); // gl_MultiTexCoord7 => vkgl_gl_MultiTexCoord7
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FogCoord))"),
            							"$2vkgl_$4"); // gl_FogCoord => vkgl_gl_FogCoord
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_ClipVertex))"),
            							"$2vkgl_$4"); // gl_ClipVertex => vkgl_gl_ClipVertex
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FrontColor))"),
            							"$2vkgl_$4"); // gl_FrontColor => vkgl_gl_FrontColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_BackColor))"),
            							"$2vkgl_$4"); // gl_BackColor => vkgl_gl_BackColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FrontSecondaryColor))"),
            							"$2vkgl_$4"); // gl_FrontSecondaryColor => vkgl_gl_FrontSecondaryColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_BackSecondaryColor))"),
            							"$2vkgl_$4"); // gl_BackSecondaryColor => vkgl_gl_BackSecondaryColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_TexCoord))"),
            							"$2vkgl_$4"); // gl_TexCoord => vkgl_gl_TexCoord
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FogFragCoord))"),
            							"$2vkgl_$4"); // gl_FogFragCoord => vkgl_gl_FogFragCoord
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FragColor))"),
            							"$2vkgl_$4"); // gl_FragColor => vkgl_gl_FragColor
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((gl_FragData))"),
            							"$2vkgl_$4"); // gl_FragData => vkgl_gl_FragData
            	
            	
            	
            	
            	
            	source = regex_replace(source,
            							std::regex("(([^\\w]))((ftransform[\\s]*\\())"),
            							"$2vkgl_$4"); // ftransform() => vkgl_ftransform()
        	}
        	
        	
        	
        	
        	
        	
        	source = regex_replace(source,
        							std::regex("(([^\\w]))(texture)[\\d]D([\\w]*[\\s]*\\()"),
        							"$2$3$4"); // texture2D() => texture()
        	source = regex_replace(source,
        							std::regex("(([^\\w]))(shadow)[\\d]D([\\w]*[\\s]*\\()"),
        							"$2texture$4"); // shadow2D() => texture()
        	
    	}
    	
    	{
            if (type == OpenGL::ShaderType::Vertex)
            {
                source = regex_replace(source,
            							std::regex("(([^\\w]))attribute(([^\\w]))"),
            							"$2in$4"); // attribute => in
                source = regex_replace(source,
            							std::regex("(([^\\w]))varying(([^\\w]))"),
            							"$2out$4"); // varying => out
            }
            
            if (type == OpenGL::ShaderType::Fragment)
            {
                source = regex_replace(source,
            							std::regex("(([^\\w]))varying(([^\\w]))"),
            							"$2in$4"); // varying => in
            }
        }
        
        vkgl_printf(">>>>SHADER SOURCE CODE>>>>\n%s\n>>>>>>>>", source.c_str() );
    }
}

bool OpenGL::VKSPIRVManager::build_uniform_resources(const SPIRVBlobID&        in_spirv_blob_id,
        												const OpenGL::PostLinkData* in_post_link_data_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	bool result = false;
	
	m_mutex.lock_shared();
	{
        auto 		frontend_state_manager_ptr = m_frontend_ptr->get_state_manager_ptr();
        auto 		frontend_buffer_manager_ptr = m_frontend_ptr->get_buffer_manager_ptr();
    	vkgl_assert(frontend_state_manager_ptr != nullptr);
    	vkgl_assert(frontend_buffer_manager_ptr != nullptr);
    	
    	OpenGL::VKSPIRVManager::ProgramData* program_data_ptr 	= nullptr;
    	std::vector<OpenGL::UniformResource>* uniform_resources_ptr = nullptr;
    	bool need_rebuild_uniform_resources 							= false;
    	
    	auto program_data_iterator = m_spirv_blob_id_to_program_data_map.find(in_spirv_blob_id);
    	if (program_data_iterator == m_spirv_blob_id_to_program_data_map.end() )
    	{
        	vkgl_assert(program_data_iterator != m_spirv_blob_id_to_program_data_map.end() );
        	goto end;
        }
        
    	program_data_ptr 				= program_data_iterator->second.get();
    	
    	program_data_ptr->link_task_fence_ptr->wait();
    	
    	uniform_resources_ptr 			= &program_data_ptr->uniform_resources;
    	need_rebuild_uniform_resources = program_data_ptr->need_rebuild_uniform_resources;
    	
    	if (need_rebuild_uniform_resources)
    	{
        	/* Create uniform buffer */
        	{
            	vkgl_assert(uniform_resources_ptr != nullptr);
            	vkgl_assert(in_post_link_data_ptr != nullptr);
            	
            	uint32_t n_bindings = 0;
            	{
            		for (auto& current_active_uniform : in_post_link_data_ptr->active_uniforms)
            		{
            			if (current_active_uniform.binding_point >= 0)
            			{
            				n_bindings ++;
            			}
            			else if (current_active_uniform.uniform_block_index >= 0)
            			{
            				auto& current_active_uniform_block = in_post_link_data_ptr->active_uniform_blocks.at(current_active_uniform.uniform_block_index);
            				
            				if (current_active_uniform_block.binding_point >= 0)
                			{
                				n_bindings ++;
                			}
                		}
                	}
                }
                
            	uniform_resources_ptr->clear();
            	uniform_resources_ptr->reserve(n_bindings);
            	{
            		for (int i = 0;
            				i < n_bindings;
            				i++)
            		{
            			uniform_resources_ptr->push_back(OpenGL::UniformResource() );
            		}
            		vkgl_assert(uniform_resources_ptr->size() == n_bindings);
            	}
            	
            	for (auto& current_active_uniform : in_post_link_data_ptr->active_uniforms)
            	{
            		uint32_t current_binding = UINT_MAX;
            		{
            			if (current_active_uniform.binding_point >= 0)
            			{
            				current_binding = current_active_uniform.binding_point;
            			}
            			else if (current_active_uniform.uniform_block_index >= 0)
            			{
            				continue;
                		}
                		else
                		{
                			vkgl_assert_fail();
                		}
                		vkgl_assert(current_binding < uniform_resources_ptr->size() );
                	}
            		
            		auto& uniform_resource = uniform_resources_ptr->at(current_binding);
            		auto& type 						= current_active_uniform.type;
            		
            		if (type == OpenGL::VariableType::Sampler2D)
            		{
            			uniform_resource.is_sampler 		= true;
            			uniform_resource.is_uniform_buffer = false;
            			
            			uniform_resource.binding		= current_binding;
            			
            			for (int i = 0;
            					i < current_active_uniform.size;
            					i++)
            			{
            				uniform_resource.samplers.push_back(OpenGL::UniformResource::SamplerInfo() );
            			}
            		}
            		else
            		{
            			continue;
            		}
            	}
            	
            	for (auto& current_active_uniform_block : in_post_link_data_ptr->active_uniform_blocks)
            	{
            		uint32_t current_binding = UINT_MAX;
            		{
        				current_binding = current_active_uniform_block.binding_point;
                		vkgl_assert(current_binding < uniform_resources_ptr->size() );
                	}
            		
            		auto& uniform_resource = uniform_resources_ptr->at(current_binding);
            		auto& type 						= current_active_uniform_block.active_uniforms.at(0).type;
            		
            		if (type == OpenGL::VariableType::Sampler2D)
            		{
            			continue;
            		}
            		else
            		{
            			uniform_resource.is_sampler 		= false;
            			uniform_resource.is_uniform_buffer = true;
            			
            			uniform_resource.binding 				= current_binding;
            			
            			{
                			uniform_resource.buffer_blocks.push_back(OpenGL::UniformResource::BufferBlockInfo() );
                			auto& new_buffer_block = uniform_resource.buffer_blocks.back();
                			
                			uint32_t buffer_size 						= current_active_uniform_block.data_size;
                			new_buffer_block.is_default_uniform_buffer = current_active_uniform_block.active_uniforms.at(0).is_default_uniform;
                			
                			for (auto& current_active_uniform : current_active_uniform_block.active_uniforms)
                			{
                    			new_buffer_block.buffers.push_back(OpenGL::UniformResource::BufferBlockInfo::BufferInfo() );
                    			auto& new_buffer = new_buffer_block.buffers.back();
                    			
                    			new_buffer.buffer_offset 			= current_active_uniform.offset;
                    			new_buffer.buffer_elements_num 	= current_active_uniform.size;
                    			new_buffer.buffer_element_size 	= OpenGL::Utils::get_n_bytes_for_variable_type(type);
                    		}
                			
                			/* Create buffer for the default uniform block. */
                			if (new_buffer_block.is_default_uniform_buffer)
                			{vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
                			vkgl_printf("buffer_size = %d", buffer_size);
                            	GLuint new_gl_uniform_buffer 	= 0;
                            	GLuint previous_gl_uniform_buffer = 0;
                            	if (frontend_state_manager_ptr->get_bound_buffer_object(OpenGL::BufferTarget::Uniform_Buffer) != nullptr)
                            	{
                            		previous_gl_uniform_buffer = frontend_state_manager_ptr->get_bound_buffer_object(OpenGL::BufferTarget::Uniform_Buffer)->get_payload().id;
                            	}
                            	
                            	{
                            	    glGenBuffers(1,
                            	    			&new_gl_uniform_buffer);
            		
                            		glBindBuffer(GL_UNIFORM_BUFFER,
                            					new_gl_uniform_buffer);
                            		
                            		glBufferData(GL_UNIFORM_BUFFER,
                        						buffer_size,
                        						nullptr,
                        						GL_DYNAMIC_DRAW);
                            		
                            		glBindBuffer(GL_UNIFORM_BUFFER,
                            					previous_gl_uniform_buffer);
                            	}
                            	
                            	new_buffer_block.gl_buffer_reference_ptr = frontend_buffer_manager_ptr->acquire_current_latest_snapshot_reference(new_gl_uniform_buffer);
                            	vkgl_assert(new_buffer_block.gl_buffer_reference_ptr != nullptr);
                			}
                			else
                			{
                				vkgl_not_implemented();
                			}
                		}
            		}
            	}
        	}
        	
        	/* Create descriptor set group */
        	{
            	Anvil::DescriptorSetGroupUniquePtr dsg_ptr;
            	
            	auto ds_create_info_ptrs = std::vector<Anvil::DescriptorSetCreateInfoUniquePtr>();
                auto descriptor_type = Anvil::DescriptorType::UNKNOWN;
                auto shader_stage_flag_bits = Anvil::ShaderStageFlagBits::VERTEX_BIT | Anvil::ShaderStageFlagBits::FRAGMENT_BIT | Anvil::ShaderStageFlagBits::GEOMETRY_BIT;
                
                {
                    ds_create_info_ptrs.push_back(Anvil::DescriptorSetCreateInfo::create() );
                }
            	
            	{
                	for (uint32_t n_uniform_resource = 0;
                				n_uniform_resource < uniform_resources_ptr->size();
                				++n_uniform_resource)
                	{
                		auto& current_uniform_resource = uniform_resources_ptr->at(n_uniform_resource);
                		
                		auto is_sampler = current_uniform_resource.is_sampler;
                		auto n_binding = current_uniform_resource.binding;
                		auto n_elements = 0;
                		
                		if (n_binding == UINT_MAX)
                		{
                    		continue;
                		}
                		
                		if (is_sampler)
                		{
                			descriptor_type = Anvil::DescriptorType::COMBINED_IMAGE_SAMPLER;
                			
                			n_elements = current_uniform_resource.samplers.size();
                		}
                		else
                		{
            		    	descriptor_type = Anvil::DescriptorType::UNIFORM_BUFFER;
            		    	
            		    	n_elements = current_uniform_resource.buffer_blocks.size();
                		}
                		
                        ds_create_info_ptrs[0]->add_binding(n_binding,
                                                             descriptor_type,
                                                             n_elements,
                                                             shader_stage_flag_bits);
                	}
                	
                	dsg_ptr = Anvil::DescriptorSetGroup::create(m_backend_ptr->get_device_ptr(),
                                                                  ds_create_info_ptrs);
        		}
        		
        		{
        		    auto                               								backend_buffer_manager_ptr   = m_backend_ptr->get_buffer_manager_ptr();
                	std::vector<Anvil::DescriptorSet::UniformBufferBindingElement> buffer_binding_items;
                	
                	for (uint32_t n_uniform_resource = 0;
                				n_uniform_resource < uniform_resources_ptr->size();
                				++n_uniform_resource)
                	{
                		auto& current_uniform_resource = uniform_resources_ptr->at(n_uniform_resource);
                		
                		auto& is_sampler = current_uniform_resource.is_sampler;
                		auto& n_binding = current_uniform_resource.binding;
                		
                		if (n_binding == UINT_MAX)
                		{
                    		continue;
                		}
                		
                		if (is_sampler)
                		{
                			continue;
                		}
                		else
                		{
                			for (int i = 0;
                					i < current_uniform_resource.buffer_blocks.size();
                					i++)
                			{
                            	auto& current_buffer_block = current_uniform_resource.buffer_blocks.at(i);
                                vkgl_assert(current_buffer_block.gl_buffer_reference_ptr != nullptr);
                                
                                auto& backend_buffer_reference_ptr = current_buffer_block.vk_buffer_reference_ptr;
                                auto& buffer_ptr 					= current_buffer_block.buffer_ptr;
                		    	auto buffer_size 					= 0;
                		    	auto buffer_offset 					= UINT_MAX;
                                
                                const auto& frontend_buffer_creation_time = current_buffer_block.gl_buffer_reference_ptr->get_payload().object_creation_time;
                                const auto& frontend_buffer_id            = current_buffer_block.gl_buffer_reference_ptr->get_payload().id;
                                const auto& frontend_buffer_snapshot_time = current_buffer_block.gl_buffer_reference_ptr->get_payload().time_marker;
                            
                                backend_buffer_reference_ptr = backend_buffer_manager_ptr->acquire_object(frontend_buffer_id,
                                                                                                          frontend_buffer_creation_time,
                                                                                                          frontend_buffer_snapshot_time);
                        
                                vkgl_assert(backend_buffer_reference_ptr != nullptr);
                                
                                buffer_ptr 				= backend_buffer_reference_ptr->get_payload().buffer_ptr;
                		    	vkgl_assert(buffer_ptr != nullptr);
                		    	buffer_size 			= buffer_ptr->get_create_info_ptr()->get_size();
                		    	buffer_offset 			= buffer_size * i;
                		    	
                		    	buffer_binding_items.push_back(Anvil::DescriptorSet::UniformBufferBindingElement(buffer_ptr,
                                                                                                                     buffer_offset,
                                                                                                                     buffer_size) );
            		    	}
            		    	
                			dsg_ptr->set_binding_array_items(0, /* in_n_set */
                												n_binding,
                												Anvil::BindingElementArrayRange(0,
                																			buffer_binding_items.size() ),
                												buffer_binding_items.data() );
                			
                			buffer_binding_items.clear();
                		}
                	}
        		}
        		
        		program_data_ptr->descriptor_set_group_ptr.reset();
        		program_data_ptr->descriptor_set_group_ptr = std::move(dsg_ptr);
        	}
        	
        	program_data_ptr->need_rebuild_uniform_resources = false;
    	}
	}
	m_mutex.unlock_shared();
	
	result = true;
end:
	return result;
}

std::vector<OpenGL::UniformResource>* OpenGL::VKSPIRVManager::get_uniform_resources(const SPIRVBlobID&        in_spirv_blob_id) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	std::vector<OpenGL::UniformResource>* result = nullptr;
	
	m_mutex.lock_shared();
	{
    	auto program_data_iterator = m_spirv_blob_id_to_program_data_map.find(in_spirv_blob_id);
    	
    	vkgl_assert(program_data_iterator != m_spirv_blob_id_to_program_data_map.end() );
    	if (program_data_iterator != m_spirv_blob_id_to_program_data_map.end() )
    	{
    		program_data_iterator->second->link_task_fence_ptr->wait();
    		
    		result = &program_data_iterator->second->uniform_resources;
    	}
	}
	m_mutex.unlock_shared();
	
	return result;
}

Anvil::DescriptorSetGroup* OpenGL::VKSPIRVManager::get_descriptor_set_group(const SPIRVBlobID&        in_spirv_blob_id) const
{
    FUN_ENTRY(DEBUG_DEPTH);
    
	Anvil::DescriptorSetGroup* result = nullptr;
	
	m_mutex.lock_shared();
	{
    	auto program_data_iterator = m_spirv_blob_id_to_program_data_map.find(in_spirv_blob_id);
    	
    	vkgl_assert(program_data_iterator != m_spirv_blob_id_to_program_data_map.end() );
    	if (program_data_iterator != m_spirv_blob_id_to_program_data_map.end() )
    	{
    		program_data_iterator->second->link_task_fence_ptr->wait();
    		
    		result = program_data_iterator->second->descriptor_set_group_ptr.get();
    	}
	}
	m_mutex.unlock_shared();
	
	return result;
}

OpenGL::SPIRVBlobID OpenGL::VKSPIRVManager::register_program(OpenGL::GLProgramReferenceUniquePtr in_program_reference_ptr)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::SPIRVBlobID result                       = UINT32_MAX;
    auto                program_frontend_manager_ptr = m_frontend_ptr->get_program_manager_ptr();
    auto                shader_frontend_manager_ptr  = m_frontend_ptr->get_shader_manager_ptr ();
    auto                thread_pool_ptr              = m_backend_ptr->get_thread_pool_ptr     ();

    const auto          program_id                   = in_program_reference_ptr->get_payload().id;
    const auto          program_timestamp            = in_program_reference_ptr->get_payload().time_marker;

    m_mutex.lock_unique();
    {
        ProgramDataUniquePtr     program_data_ptr     = ProgramDataUniquePtr(nullptr,
                                                                             std::default_delete<ProgramData>() );
        ProgramData*             program_data_raw_ptr = nullptr;
        std::vector<ShaderData*> shader_data_vec;

        /* 1. Obtain ptrs to ShaderData structures for all shaders attached to the program */
        {
            const auto attached_shader_reference_vec_ptr = program_frontend_manager_ptr->get_attached_shaders(program_id,
                                                                                                             &program_timestamp);

            vkgl_assert(attached_shader_reference_vec_ptr         != nullptr);
            vkgl_assert(attached_shader_reference_vec_ptr->size() >  0);

            for (const auto& current_shader_reference_ptr : *attached_shader_reference_vec_ptr)
            {
                const char* shader_glsl      = nullptr;
                const auto  shader_id        = current_shader_reference_ptr->get_payload().id;
                const auto  shader_timestamp = current_shader_reference_ptr->get_payload().time_marker;

                decltype(m_glsl_to_shader_data_map)::const_iterator shader_data_iterator;

                if (!shader_frontend_manager_ptr->get_shader_glsl(shader_id,
                                                                 &shader_timestamp,
                                                                 &shader_glsl) )
                {
                    vkgl_assert_fail();
                }
                else
                {
                    vkgl_assert(shader_glsl != nullptr);
                }

                shader_data_iterator = m_glsl_to_shader_data_map.find(std::string(shader_glsl) );
                vkgl_assert(shader_data_iterator != m_glsl_to_shader_data_map.end() );

                shader_data_vec.push_back(shader_data_iterator->second.get() );
            }
        }

        /* 2. Spawn a new entity to hold shader data */
        {
            SPIRVBlobID new_blob_id = static_cast<SPIRVBlobID>(++m_n_entities_registered);

            vkgl_assert(m_spirv_blob_id_to_program_data_map.find(new_blob_id) == m_spirv_blob_id_to_program_data_map.end() );

            program_data_ptr.reset(new ProgramData(new_blob_id,
                                                   shader_data_vec,
                                                   std::move(in_program_reference_ptr) )
            );
            vkgl_assert(program_data_ptr != nullptr);

            program_data_raw_ptr                                                                                          = program_data_ptr.get();
            m_program_reference_to_program_data_map[std::pair<GLuint, OpenGL::TimeMarker>(program_id, program_timestamp)] = program_data_raw_ptr;
            m_spirv_blob_id_to_program_data_map    [new_blob_id]                                                          = std::move(program_data_ptr);

            program_frontend_manager_ptr->set_program_backend_spirv_blob_id(program_id,
                                                                           &program_timestamp,
                                                                            new_blob_id);
        }

        /* 3. Wait until all shaders are compiled before submitting a link task to the thread pool.
         *
         * NOTE: This works because this function is always called from app's thread.
         * TODO: Do we need to implicitly submit compile shader tasks for shaders, for which glCompileShader() has not been invoked?
         */
        for (auto& current_shader_data_ptr : shader_data_vec)
        {
            current_shader_data_ptr->compile_task_fence_ptr->wait();
        }

        /* 4. Submit a new task to the thread pool, which we're going to use to actually perform the linking. */
        thread_pool_ptr->submit_task(std::bind(&OpenGL::VKSPIRVManager::link_program,
                                               this,
                                               program_data_raw_ptr)
        );
    }
    m_mutex.unlock_unique();

    return result;
}

OpenGL::SPIRVBlobID OpenGL::VKSPIRVManager::register_shader(const OpenGL::ShaderType& in_shader_type,
                                                            const char*               in_glsl)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    OpenGL::SPIRVBlobID result          = UINT32_MAX;
    auto                thread_pool_ptr = m_backend_ptr->get_thread_pool_ptr();

    m_mutex.lock_unique();
    {
        ShaderData* shader_data_raw_ptr = nullptr;

        vkgl_assert(m_glsl_to_shader_data_map.find(in_glsl) == m_glsl_to_shader_data_map.end() );

        /* 1. Spawn a new entity to hold shader data */
        {
            SPIRVBlobID         new_blob_id    = static_cast<SPIRVBlobID>(++m_n_entities_registered);
            ShaderDataUniquePtr shader_data_ptr;

            vkgl_assert(m_spirv_blob_id_to_shader_data_map.find(new_blob_id) == m_spirv_blob_id_to_shader_data_map.end() );

            shader_data_ptr.reset(new ShaderData(new_blob_id,
                                                 in_shader_type,
                                                 in_glsl)
            );
            vkgl_assert(shader_data_ptr != nullptr);

            shader_data_raw_ptr                             = shader_data_ptr.get();
            m_spirv_blob_id_to_shader_data_map[new_blob_id] = shader_data_raw_ptr;
            m_glsl_to_shader_data_map         [in_glsl]     = std::move(shader_data_ptr);

            result = new_blob_id;
        }

        /* 2. Submit a new task to the thread pool, which we're going to use to actually perform the GLSL->SPIRV "conversion". */
        thread_pool_ptr->submit_task(std::bind(&OpenGL::VKSPIRVManager::compile_shader,
                                               this,
                                               shader_data_raw_ptr)
        );
    }
    m_mutex.unlock_unique();

    return result;
}

void OpenGL::VKSPIRVManager::unregister_program(const GLuint& in_id)
{
    FUN_ENTRY(DEBUG_DEPTH);
    
    m_mutex.lock_unique();
    {
        std::vector<std::pair<GLuint, OpenGL::TimeMarker> > relevant_program_reference_map_keys;
        std::vector<SPIRVBlobID>                            relevant_spirv_blob_ids;

        for (const auto& current_program_reference_map_item : m_program_reference_to_program_data_map)
        {
            if (current_program_reference_map_item.first.first == in_id)
            {
                relevant_program_reference_map_keys.push_back(current_program_reference_map_item.first);
            }
        }

        for (const auto& current_spirv_blob_map_item : m_spirv_blob_id_to_program_data_map)
        {
            if (current_spirv_blob_map_item.second->program_id == in_id)
            {
                relevant_spirv_blob_ids.push_back(current_spirv_blob_map_item.first);
            }
        }

        for (const auto& current_program_reference_map_key : relevant_program_reference_map_keys)
        {
            m_program_reference_to_program_data_map.erase(current_program_reference_map_key);
        }

        /* Release the actual vk uniform buffers and descriptor set. */
        for (const auto& current_spirv_blob_id : relevant_spirv_blob_ids)
        {
        	auto program_data_iterator = m_spirv_blob_id_to_program_data_map.find(current_spirv_blob_id);
        	vkgl_assert(program_data_iterator != m_spirv_blob_id_to_program_data_map.end() );
        	auto program_data_ptr = program_data_iterator->second.get();
        	
        	program_data_ptr->uniform_resources.clear		();
        	program_data_ptr->descriptor_set_group_ptr.reset();
        }

        for (const auto& current_spirv_blob_id : relevant_spirv_blob_ids)
        {
            m_spirv_blob_id_to_program_data_map.erase(current_spirv_blob_id);
        }
    }
    m_mutex.unlock_unique();
}