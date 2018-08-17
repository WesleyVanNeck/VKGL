/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1ui.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLint&   in_location,
                     const GLuint&  in_v0)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

VKGL_API void VKGL_APIENTRY glUniform1ui(GLint  location,
                                         GLuint v0)
{
    const auto& dispatch_table_ptr = g_dispatch_table_ptr;

    dispatch_table_ptr->pGLUniform1ui(dispatch_table_ptr->bound_context_ptr,
                                      location,
                                      v0);
}

void vkglUniform1ui_execute(VKGL::Context* in_context_ptr,
                            const GLint&   in_location,
                            const GLuint&  in_v0)
{
    in_context_ptr->set_uniform(in_location,
                                VKGL::GetSetArgumentType::Unsigned_Int,
                                1,
                               &in_v0);
}

void vkglUniform1ui_with_validation(VKGL::Context* in_context_ptr,
                                   const GLint&    in_location,
                                   const GLuint&   in_v0)
{
    if (validate(in_context_ptr,
                 in_location,
                 in_v0) )
    {
        vkglUniform1ui_execute(in_context_ptr,
                               in_location,
                               in_v0);
    }
}
