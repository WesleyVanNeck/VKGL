/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_hint.h"
#include "OpenGL/context.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

static bool validate(VKGL::Context* in_context_ptr,
                     const GLenum&  in_target,
                     const GLenum&  in_mode)
{
    bool result = false;

    // ..

    result = true;
    return result;
}


void VKGL_APIENTRY OpenGL::vkglHint(GLenum target,
                                    GLenum mode)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    dispatch_table_ptr->pGLHint(dispatch_table_ptr->bound_context_ptr,
                                target,
                                mode);
}

static void vkglHint_execute(VKGL::Context* in_context_ptr,
                             const GLenum&  in_target,
                             const GLenum&  in_mode)
{
    const auto mode_vkgl   = VKGL::Utils::get_hint_mode_for_gl_enum  (in_mode);
    const auto target_vkgl = VKGL::Utils::get_hint_target_for_gl_enum(in_target);

    in_context_ptr->set_hint(target_vkgl,
                             mode_vkgl);
}

void OpenGL::vkglHint_with_validation(VKGL::Context* in_context_ptr,
                                      const GLenum&  in_target,
                                      const GLenum&  in_mode)
{
    if (validate(in_context_ptr,
                 in_target,
                 in_mode) )
    {
        vkglHint_execute(in_context_ptr,
                         in_target,
                         in_mode);
    }
}