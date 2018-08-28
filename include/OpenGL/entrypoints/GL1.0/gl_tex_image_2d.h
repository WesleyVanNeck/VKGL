/* VKGL (c) 2018 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_GL_TEX_IMAGE_2D_H
#define VKGL_GL_TEX_IMAGE_2D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void VKGL_APIENTRY vkglTexImage2D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLsizei     height,
                                      GLint       border,
                                      GLenum      format,
                                      GLenum      type,
                                      const void* pixels);

    void vkglTexImage2D_with_validation(VKGL::Context* in_context_ptr,
                                        const GLenum&  in_target,
                                        const GLint&   in_level,
                                        const GLint&   in_internalformat,
                                        const GLsizei& in_width,
                                        const GLsizei& in_height,
                                        const GLint&   in_border,
                                        const GLenum&  in_format,
                                        const GLenum&  in_type,
                                        const void*    in_pixels_ptr);
}

#endif /* VKGL_GL_TEX_IMAGE_2D_H */