/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformiv.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLuint&  in_program,
                     const GLint&   in_location,
                     GLint*         out_params_ptr)
{
    bool result = false;

    // ..

    result = true;
    return result;
}

VKGL_API void VKGL_APIENTRY glGetUniformiv(GLuint program,
                                           GLint  location,
                                           GLint* params)
{
    const auto& dispatch_table_ptr = g_dispatch_table_ptr;

    dispatch_table_ptr->pGLGetUniformiv(dispatch_table_ptr->bound_context_ptr,
                                        program,
                                        location,
                                        params);
}

void vkglGetUniformiv_execute(VKGL::Context* in_context_ptr,
                              const GLuint&  in_program,
                              const GLint&   in_location,
                              GLint*         out_params_ptr)
{
    in_context_ptr->get_uniform_value(in_program,
                                      in_location,
                                      VKGL::GetSetArgumentType::Int,
                                      out_params_ptr);
}

void vkglGetUniformiv_with_validation(VKGL::Context* in_context_ptr,
                                      const GLuint&  in_program,
                                      const GLint&   in_location,
                                      GLint*         out_params_ptr)
{
    if (validate(in_context_ptr,
                 in_program,
                 in_location,
                 out_params_ptr) )
    {
        vkglGetUniformiv_execute(in_context_ptr,
                                 in_program,
                                 in_location,
                                 out_params_ptr);
    }
}
