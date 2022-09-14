// Compatibility OpenGL Over Core OpenGL

#include "OpenGL/entrypoints/gl_entry_points_pack.h"



#include "deps/glm/glm/glm.hpp"
#include "deps/glm/glm/ext.hpp"




#define NOT_IMPLEMENTED 			\
	vkgl_not_implemented();					\





inline bool ENABLED_GL_NO_ERROR(OpenGL::Context* in_context_ptr)
{
	return false;
}

inline void SET_GL_ERROR(OpenGL::IContextObjectManagers* in_context_ptr,
							GLenum in_gl_error)
{
	in_context_ptr->get_state_manager_ptr()->set_error(OpenGL::Utils::get_error_code_for_gl_enum(in_gl_error) );
}


// Compatibility API

/*
 * Miscellaneous
 */

void glClearIndex( GLfloat c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glAlphaFunc( GLenum func, GLclampf ref ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    fpe_state_ptr->alpha_test.alpha_func = func;
    fpe_state_ptr->alpha_test.alpha_ref = ref;

}

void glLineStipple( GLint factor, GLushort pattern ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPolygonStipple( const GLubyte *mask ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetPolygonStipple( GLubyte *mask ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEdgeFlag( GLboolean flag ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEdgeFlagv( const GLboolean *flag ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glClipPlane( GLenum plane, const GLdouble *equation ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetClipPlane( GLenum plane, GLdouble *equation ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glEnableClientState( GLenum cap ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    OpenGL::FpeState::FpeVertexArrays::FpeClientArray* vertex_array_ptr = nullptr;
    
    switch (cap)
    {
    	case GL_COLOR_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.color_array; break;
    	}
    	case GL_EDGE_FLAG_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.edge_flag_array; break;
    	}
    	case GL_FOG_COORD_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.fog_coord_array; break;
    	}
    	case GL_INDEX_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.index_array; break;
    	}
    	case GL_NORMAL_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.normal_array; break;
    	}
    	case GL_SECONDARY_COLOR_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.secondary_color_array; break;
    	}
    	case GL_TEXTURE_COORD_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.tex_coord_arrays.at(fpe_state_ptr->state.current_client_active_texture_unit); break;
    	}
    	case GL_VERTEX_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.vertex_array; break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }
    
    vertex_array_ptr->enabled = true;

}
  /* 1.1 */

void glDisableClientState( GLenum cap ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    OpenGL::FpeState::FpeVertexArrays::FpeClientArray* vertex_array_ptr = nullptr;
    
    switch (cap)
    {
    	case GL_COLOR_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.color_array; break;
    	}
    	case GL_EDGE_FLAG_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.edge_flag_array; break;
    	}
    	case GL_FOG_COORD_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.fog_coord_array; break;
    	}
    	case GL_INDEX_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.index_array; break;
    	}
    	case GL_NORMAL_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.normal_array; break;
    	}
    	case GL_SECONDARY_COLOR_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.secondary_color_array; break;
    	}
    	case GL_TEXTURE_COORD_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.tex_coord_arrays.at(fpe_state_ptr->state.current_client_active_texture_unit); break;
    	}
    	case GL_VERTEX_ARRAY:
    	{
    		vertex_array_ptr = &fpe_state_ptr->vertex_arrays.vertex_array; break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }
    
    vertex_array_ptr->enabled = false;

}
  /* 1.1 */



void glPushAttrib( GLbitfield mask ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPopAttrib( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glPushClientAttrib( GLbitfield mask ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}
  /* 1.1 */

void glPopClientAttrib( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}
  /* 1.1 */


GLint glRenderMode( GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED
    return 0;
}


/*
 * Depth Buffer
 */


/*
 * Accumulation Buffer
 */

void glClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glAccum( GLenum op, GLfloat value ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



/*
 * Transformation
 */

void glMatrixMode( GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto current_matrix_ptr_ptr = &fpe_state_ptr->state.current_bound_matrix_ptr;
    
    switch (mode)
    {
    	case GL_MODELVIEW:
    	{
    		*current_matrix_ptr_ptr = &fpe_state_ptr->matrices.gl_ModelViewMatrix;
    		
    		break;
    	}
    	case GL_PROJECTION:
    	{
    		*current_matrix_ptr_ptr = &fpe_state_ptr->matrices.gl_ProjectionMatrix;
    		
    		break;
    	}
    	case GL_TEXTURE:
    	{
    		*current_matrix_ptr_ptr = &fpe_state_ptr->matrices.gl_TextureMatrix.at(fpe_state_ptr->state.current_client_active_texture_unit);
    		
    		fpe_state_ptr->state.tex_matrix_enabled.at(fpe_state_ptr->state.current_client_active_texture_unit) = true;
    		
    		break;
    	}
    	case GL_COLOR:
    	{
    		vkgl_not_implemented();
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    glm::mat4 mat4 = glm::ortho(left, right, bottom, top, near_val, far_val);
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = mat4;

}

void glFrustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    glm::mat4 mat4 = glm::frustum(left, right, bottom, top, near_val, far_val);
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = mat4;

}

void glPushMatrix( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPopMatrix( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glLoadIdentity( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::mat4();

}

void glLoadMatrixd( const GLdouble *m ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GLfloat mf[16];
    for(int n = 0;
    		n < 16;
    		n++)
    {
    	mf[n] = (GLfloat)m[n];
    }
    
    glLoadMatrixf((const GLfloat *)mf);

}

void glLoadMatrixf( const GLfloat *m ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::mat4(m[0], m[1], m[2], m[3],
    															m[4], m[5], m[6], m[7],
    															m[8], m[9], m[10], m[11],
    															m[12], m[13], m[14], m[15]);

}

void glMultMatrixd( const GLdouble *m ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GLfloat mf[16];
    for(int n = 0;
    		n < 16;
    		n++)
    {
    	mf[n] = (GLfloat)m[n];
    }
    
    glMultMatrixf((const GLfloat *)mf);

}

void glMultMatrixf( const GLfloat *m ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glm::mat4 in_mat4 = glm::mat4(m[0], m[1], m[2], m[3],
									m[4], m[5], m[6], m[7],
									m[8], m[9], m[10], m[11],
									m[12], m[13], m[14], m[15]);
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    *fpe_state_ptr->state.current_bound_matrix_ptr *= in_mat4;

}

void glRotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glRotatef((GLfloat)angle, (GLfloat)x, (GLfloat)y, (GLfloat)z);

}

void glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    glm::mat4 mat4 = *fpe_state_ptr->state.current_bound_matrix_ptr;
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::rotate(mat4, angle, glm::vec3(x, y, x) );

}

void glScaled( GLdouble x, GLdouble y, GLdouble z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glScalef((GLfloat)x, (GLfloat)y, (GLfloat)z);

}

void glScalef( GLfloat x, GLfloat y, GLfloat z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    glm::mat4 mat4 = *fpe_state_ptr->state.current_bound_matrix_ptr;
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::scale(mat4, glm::vec3(x, y, x) );

}

void glTranslated( GLdouble x, GLdouble y, GLdouble z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);

}

void glTranslatef( GLfloat x, GLfloat y, GLfloat z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    glm::mat4 mat4 = *fpe_state_ptr->state.current_bound_matrix_ptr;
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::translate(mat4, glm::vec3(x, y, x) );

}



/*
 * Display Lists
 */

GLboolean glIsList( GLuint list ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED
    return GL_FALSE;
}

void glDeleteLists( GLuint list, GLsizei range ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

GLuint glGenLists( GLsizei range ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED
    return 0;
}

void glNewList( GLuint list, GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEndList( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glCallList( GLuint list ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glCallLists( GLsizei n, GLenum type, const GLvoid *lists ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glListBase( GLuint base ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



/*
 * Drawing Functions
 */

void glBegin( GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEnd( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glVertex2d( GLdouble x, GLdouble y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2f( GLfloat x, GLfloat y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2i( GLint x, GLint y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2s( GLshort x, GLshort y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3d( GLdouble x, GLdouble y, GLdouble z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3f( GLfloat x, GLfloat y, GLfloat z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3i( GLint x, GLint y, GLint z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3s( GLshort x, GLshort y, GLshort z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4i( GLint x, GLint y, GLint z, GLint w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex2sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex3sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glVertex4sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3i( GLint nx, GLint ny, GLint nz ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3s( GLshort nx, GLshort ny, GLshort nz ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3bv( const GLbyte *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glNormal3sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glIndexd( GLdouble c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexf( GLfloat c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexi( GLint c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexs( GLshort c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexub( GLubyte c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}
  /* 1.1 */

void glIndexdv( const GLdouble *c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexfv( const GLfloat *c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexiv( const GLint *c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexsv( const GLshort *c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glIndexubv( const GLubyte *c ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}
  /* 1.1 */

void glColor3b( GLbyte red, GLbyte green, GLbyte blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3d( GLdouble red, GLdouble green, GLdouble blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3f( GLfloat red, GLfloat green, GLfloat blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3i( GLint red, GLint green, GLint blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3s( GLshort red, GLshort green, GLshort blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3ub( GLubyte red, GLubyte green, GLubyte blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3ui( GLuint red, GLuint green, GLuint blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3us( GLushort red, GLushort green, GLushort blue ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4b( GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4d( GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4i( GLint red, GLint green, GLint blue, GLint alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4s( GLshort red, GLshort green, GLshort blue, GLshort alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4ui( GLuint red, GLuint green, GLuint blue, GLuint alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4us( GLushort red, GLushort green, GLushort blue, GLushort alpha ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glColor3bv( const GLbyte *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3ubv( const GLubyte *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3uiv( const GLuint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor3usv( const GLushort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4bv( const GLbyte *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4ubv( const GLubyte *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4uiv( const GLuint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColor4usv( const GLushort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glTexCoord1d( GLdouble s ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1f( GLfloat s ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1i( GLint s ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1s( GLshort s ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2d( GLdouble s, GLdouble t ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2f( GLfloat s, GLfloat t ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2i( GLint s, GLint t ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2s( GLshort s, GLshort t ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3d( GLdouble s, GLdouble t, GLdouble r ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3f( GLfloat s, GLfloat t, GLfloat r ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3i( GLint s, GLint t, GLint r ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3s( GLshort s, GLshort t, GLshort r ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4i( GLint s, GLint t, GLint r, GLint q ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord1sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord2sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord3sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexCoord4sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glRasterPos2d( GLdouble x, GLdouble y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2f( GLfloat x, GLfloat y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2i( GLint x, GLint y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2s( GLshort x, GLshort y ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3d( GLdouble x, GLdouble y, GLdouble z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3f( GLfloat x, GLfloat y, GLfloat z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3i( GLint x, GLint y, GLint z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3s( GLshort x, GLshort y, GLshort z ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4i( GLint x, GLint y, GLint z, GLint w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos2sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos3sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4dv( const GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4fv( const GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4iv( const GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRasterPos4sv( const GLshort *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRecti( GLint x1, GLint y1, GLint x2, GLint y2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glRectdv( const GLdouble *v1, const GLdouble *v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRectfv( const GLfloat *v1, const GLfloat *v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRectiv( const GLint *v1, const GLint *v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glRectsv( const GLshort *v1, const GLshort *v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



/*
 * Vertex Arrays  (1.1)
 */

void glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.vertex_array;
    
    vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glNormalPointer( GLenum type, GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.normal_array;
    
    //vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.color_array;
    
    vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glIndexPointer( GLenum type, GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.index_array;
    
    //vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.tex_coord_arrays.at(fpe_state_ptr->state.current_client_active_texture_unit);
    
    vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glEdgeFlagPointer( GLsizei stride, const GLvoid *ptr ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.edge_flag_array;
    
    //vertex_array_ptr->size = size;
    //vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = ptr;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glArrayElement( GLint i ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glInterleavedArrays( GLenum format, GLsizei stride, const GLvoid *pointer ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}


/*
 * Lighting
 */

void glShadeModel( GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glLightf( GLenum light, GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glLightfv(light, pname, &param);

}

void glLighti( GLenum light, GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glLightiv(light, pname, &param);

}

void glLightfv( GLenum light, GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto n_light = light - GL_LIGHT0;
    
    switch (pname)
    {
    	case GL_AMBIENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).ambient[i] = params[i];
    		
    		break;
    	}
    	case GL_DIFFUSE:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).diffuse[i] = params[i];
    		
    		break;
    	}
    	case GL_SPECULAR:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).specular[i] = params[i];
    		
    		break;
    	}
    	case GL_POSITION:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).position[i] = params[i];
    		
    		break;
    	}
    	case GL_SPOT_DIRECTION:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).spotDirection[i] = params[i];
    		
    		break;
    	}
    	case GL_SPOT_EXPONENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).spotExponent = std::clamp(*params, 0.0f, 180.0f);
    		
    		break;
    	}
    	case GL_SPOT_CUTOFF:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).spotCutoff = *params != 180.0f ? std::clamp(*params, 0.0f, 90.0f) : 180.0f;
    		
    		break;
    	}
    	case GL_CONSTANT_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).constantAttenuation = *params;
    		
    		break;
    	}
    	case GL_LINEAR_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).linearAttenuation = *params;
    		
    		break;
    	}
    	case GL_QUADRATIC_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).quadraticAttenuation = *params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glLightiv( GLenum light, GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto n_light = light - GL_LIGHT0;
    
    switch (pname)
    {
    	case GL_AMBIENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).ambient[i] = (params[i] / INT_MAX);
    		
    		break;
    	}
    	case GL_DIFFUSE:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).diffuse[i] = (params[i] / INT_MAX);
    		
    		break;
    	}
    	case GL_SPECULAR:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).specular[i] = (params[i] / INT_MAX);
    		
    		break;
    	}
    	case GL_POSITION:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).position[i] = params[i];
    		
    		break;
    	}
    	case GL_SPOT_DIRECTION:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).spotDirection[i] = params[i];
    		
    		break;
    	}
    	case GL_SPOT_EXPONENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightSource.at(n_light).spotExponent = std::clamp((GLfloat)*params, 0.0f, 180.0f);
    		
    		break;
    	}
    	case GL_SPOT_CUTOFF:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).spotCutoff = *params != 180.0f ? std::clamp((GLfloat)*params, 0.0f, 90.0f) : 180.0f;
    		
    		break;
    	}
    	case GL_CONSTANT_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).constantAttenuation = *params;
    		
    		break;
    	}
    	case GL_LINEAR_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).linearAttenuation = *params;
    		
    		break;
    	}
    	case GL_QUADRATIC_ATTENUATION:
    	{
    		fpe_state_ptr->light.gl_LightSource.at(n_light).quadraticAttenuation = *params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glGetLightfv( GLenum light, GLenum pname, GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetLightiv( GLenum light, GLenum pname, GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glLightModelf( GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glLightModelfv(pname, &param);

}

void glLightModeli( GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glLightModeliv(pname, &param);

}

void glLightModelfv( GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    switch (pname)
    {
    	case GL_LIGHT_MODEL_AMBIENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightModel.ambient[i] = params[i];
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_TWO_SIDE:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_LOCAL_VIEWER:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_COLOR_CONTROL:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glLightModeliv( GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    switch (pname)
    {
    	case GL_LIGHT_MODEL_AMBIENT:
    	{
    		for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_LightModel.ambient[i] = (params[i] / INT_MAX);
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_TWO_SIDE:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_LOCAL_VIEWER:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	case GL_LIGHT_MODEL_COLOR_CONTROL:
    	{
    		fpe_state_ptr->light.light_model_state.two_side = *params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glMaterialf( GLenum face, GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glMaterialfv(face, pname, &param);

}

void glMateriali( GLenum face, GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glMaterialiv(face, pname, &param);

}

void glMaterialfv( GLenum face, GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    if (face == GL_FRONT || face == GL_FRONT_AND_BACK)
	{
		switch (pname)
		{
			case GL_AMBIENT:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.ambient[i] = params[i];
				
				break;
			}
			case GL_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.diffuse[i] = params[i];
				
				break;
			}
			case GL_AMBIENT_AND_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.ambient[i] = params[i];
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.diffuse[i] = params[i];
				
				break;
			}
			case GL_SPECULAR:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.specular[i] = params[i];
				
				break;
			}
			case GL_EMISSION:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.emission[i] = params[i];
				
				break;
			}
			case GL_SHININESS:
			{
				fpe_state_ptr->light.gl_FrontMaterial.shininess = std::clamp(*params, 0.0f, 128.0f);
				
				break;
			}
			default:
        	{
        		vkgl_assert_fail();
        	}
        }
	}
	
    if (face == GL_BACK || face == GL_FRONT_AND_BACK)
	{
		switch (pname)
		{
			case GL_AMBIENT:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.ambient[i] = params[i];
				
				break;
			}
			case GL_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.diffuse[i] = params[i];
				
				break;
			}
			case GL_AMBIENT_AND_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.ambient[i] = params[i];
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.diffuse[i] = params[i];
				
				break;
			}
			case GL_SPECULAR:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.specular[i] = params[i];
				
				break;
			}
			case GL_EMISSION:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.emission[i] = params[i];
				
				break;
			}
			case GL_SHININESS:
			{
				fpe_state_ptr->light.gl_BackMaterial.shininess = std::clamp(*params, 0.0f, 128.0f);
				
				break;
			}
			default:
        	{
        		vkgl_assert_fail();
        	}
        }
	}

}

void glMaterialiv( GLenum face, GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    if (face == GL_FRONT || face == GL_FRONT_AND_BACK)
	{
		switch (pname)
		{
			case GL_AMBIENT:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.ambient[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.diffuse[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_AMBIENT_AND_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.ambient[i] = (params[i] / INT_MAX);
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.diffuse[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_SPECULAR:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.specular[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_EMISSION:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_FrontMaterial.emission[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_SHININESS:
			{
				fpe_state_ptr->light.gl_FrontMaterial.shininess = std::clamp((GLfloat)(*params / INT_MAX), 0.0f, 128.0f);
				
				break;
			}
			default:
        	{
        		vkgl_assert_fail();
        	}
        }
	}
	
    if (face == GL_BACK || face == GL_FRONT_AND_BACK)
	{
		switch (pname)
		{
			case GL_AMBIENT:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.ambient[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.diffuse[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_AMBIENT_AND_DIFFUSE:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.ambient[i] = (params[i] / INT_MAX);
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.diffuse[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_SPECULAR:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.specular[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_EMISSION:
			{
				for (int i = 0; i < 4; i++) fpe_state_ptr->light.gl_BackMaterial.emission[i] = (params[i] / INT_MAX);
				
				break;
			}
			case GL_SHININESS:
			{
				fpe_state_ptr->light.gl_BackMaterial.shininess = std::clamp((GLfloat)(*params / INT_MAX), 0.0f, 128.0f);
				
				break;
			}
			default:
        	{
        		vkgl_assert_fail();
        	}
        }
	}

}

void glGetMaterialfv( GLenum face, GLenum pname, GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetMaterialiv( GLenum face, GLenum pname, GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glColorMaterial( GLenum face, GLenum mode ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    if (face == GL_FRONT || face == GL_FRONT_AND_BACK)
	{
		fpe_state_ptr->light.front_material_state.mode = mode;
	}
    if (face == GL_BACK || face == GL_FRONT_AND_BACK)
	{
		fpe_state_ptr->light.back_material_state.mode = mode;
	}

}



/*
 * Raster functions
 */

void glPixelZoom( GLfloat xfactor, GLfloat yfactor ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPixelTransferf( GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPixelTransferi( GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPixelMapfv( GLenum map, GLsizei mapsize, const GLfloat *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPixelMapuiv( GLenum map, GLsizei mapsize, const GLuint *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPixelMapusv( GLenum map, GLsizei mapsize, const GLushort *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetPixelMapfv( GLenum map, GLfloat *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetPixelMapuiv( GLenum map, GLuint *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetPixelMapusv( GLenum map, GLushort *values ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glBitmap( GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glDrawPixels( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glCopyPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum type ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}


/*
 * Stenciling
 */



/*
 * Texture mapping
 */

void glTexGend( GLenum coord, GLenum pname, GLdouble param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexGenf( GLenum coord, GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexGeni( GLenum coord, GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexGendv( GLenum coord, GLenum pname, const GLdouble *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexGenfv( GLenum coord, GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glTexGeniv( GLenum coord, GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetTexGendv( GLenum coord, GLenum pname, GLdouble *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetTexGenfv( GLenum coord, GLenum pname, GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetTexGeniv( GLenum coord, GLenum pname, GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



void glTexEnvf( GLenum target, GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glTexEnvfv(target, pname, &param);

}

void glTexEnvi( GLenum target, GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glTexEnviv(target, pname, &param);

}

void glTexEnvfv( GLenum target, GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    if (target == GL_TEXTURE_ENV){
        switch(pname)
        {
            case GL_TEXTURE_ENV_COLOR:
            {
            	for (int i = 0; i < 4; i++) fpe_state_ptr->texture_env.texture_env_color.at(fpe_state_ptr->state.current_active_texture_unit)[i] = params[i];
            	
            	break;
            }
            default:
            {
            	vkgl_assert_fail();
            }
        }
    }

}

void glTexEnviv( GLenum target, GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    if (target == GL_TEXTURE_ENV){
        switch(pname)
        {
            case GL_TEXTURE_ENV_MODE:
            {
            	fpe_state_ptr->texture_env.texture_env_mode.at(fpe_state_ptr->state.current_active_texture_unit) = *params;
            	
            	break;
            }
            case GL_COMBINE_RGB:
            case GL_COMBINE_ALPHA:
            case GL_SOURCE0_RGB:
            case GL_OPERAND0_RGB:
            case GL_SOURCE0_ALPHA:
            case GL_OPERAND0_ALPHA:
            case GL_SOURCE1_RGB:
            case GL_OPERAND1_RGB:
            case GL_SOURCE1_ALPHA:
            case GL_OPERAND1_ALPHA:
            case GL_SOURCE2_RGB:
            case GL_OPERAND2_RGB:
            case GL_SOURCE2_ALPHA:
            case GL_OPERAND2_ALPHA:
            {
            	vkgl_not_implemented();
            	
            	break;
            }
            default:
            {
            	vkgl_assert_fail();
            }
        }
    }

}

void glGetTexEnvfv( GLenum target, GLenum pname, GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetTexEnviv( GLenum target, GLenum pname, GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}




/* 1.1 functions */

void glPrioritizeTextures( GLsizei n, const GLuint *textures, const GLclampf *priorities ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

GLboolean glAreTexturesResident( GLsizei n, const GLuint *textures, GLboolean *residences ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED
    return GL_FALSE;
}


/*
 * Evaluators
 */

void glMap1d( GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMap1f( GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMap2d( GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMap2f( GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetMapdv( GLenum target, GLenum query, GLdouble *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetMapfv( GLenum target, GLenum query, GLfloat *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glGetMapiv( GLenum target, GLenum query, GLint *v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord1d( GLdouble u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord1f( GLfloat u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord1dv( const GLdouble *u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord1fv( const GLfloat *u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord2d( GLdouble u, GLdouble v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord2f( GLfloat u, GLfloat v ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord2dv( const GLdouble *u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalCoord2fv( const GLfloat *u ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMapGrid1d( GLint un, GLdouble u1, GLdouble u2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMapGrid1f( GLint un, GLfloat u1, GLfloat u2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMapGrid2d( GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMapGrid2f( GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalPoint1( GLint i ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalPoint2( GLint i, GLint j ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalMesh1( GLenum mode, GLint i1, GLint i2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glEvalMesh2( GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2 ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



/*
 * Fog
 */

void glFogf( GLenum pname, GLfloat param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    switch (pname)
    {
    	case GL_FOG_MODE:
    	case GL_FOG_DENSITY:
    	case GL_FOG_START:
    	case GL_FOG_END:
    	case GL_FOG_INDEX:
    	case GL_FOG_COORD_SRC:
    	{
		    glFogfv(pname, &param);
		    
		    break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glFogi( GLenum pname, GLint param ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    switch (pname)
    {
    	case GL_FOG_MODE:
    	case GL_FOG_DENSITY:
    	case GL_FOG_START:
    	case GL_FOG_END:
    	case GL_FOG_INDEX:
    	case GL_FOG_COORD_SRC:
    	{
		    glFogiv(pname, &param);
		    
		    break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glFogfv( GLenum pname, const GLfloat *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto& fog = fpe_state_ptr->fog;
    
    switch (pname)
    {
    	case GL_FOG_MODE:
    	{
    		fog.mode = (GLint)*params;
    		
    		break;
    	}
    	case GL_FOG_DENSITY:
    	{
    		fog.density = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_START:
    	{
    		fog.start = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_END:
    	{
    		fog.end = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_INDEX:
    	{
    		fog.index = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_COLOR:
    	{
    		float color4[4] = {0.0f};
    		for (int i = 0;
    				i < 4;
    				i++)
    		{
    			color4[i] = std::clamp((float)params[i], 0.0f, 1.0f);
    			
    			fog.color[i] = color4[i];
    		}
    		
    		break;
    	}
    	case GL_FOG_COORD_SRC:
    	{
    		fog.coord_src = (GLint)*params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}

void glFogiv( GLenum pname, const GLint *params ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto& fog = fpe_state_ptr->fog;
    
    switch (pname)
    {
    	case GL_FOG_MODE:
    	{
    		fog.mode = (GLint)*params;
    		
    		break;
    	}
    	case GL_FOG_DENSITY:
    	{
    		fog.density = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_START:
    	{
    		fog.start = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_END:
    	{
    		fog.end = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_INDEX:
    	{
    		fog.index = (float)*params;
    		
    		break;
    	}
    	case GL_FOG_COLOR:
    	{
    		float color4[4] = {0.0f};
    		for (int i = 0;
    				i < 4;
    				i++)
    		{
    			color4[i] = std::clamp((float)(params[i] / INT_MAX), 0.0f, 1.0f);
    			
    			fog.color[i] = color4[i];
    		}
    		
    		break;
    	}
    	case GL_FOG_COORD_SRC:
    	{
    		fog.coord_src = (GLint)*params;
    		
    		break;
    	}
    	default:
    	{
    		vkgl_assert_fail();
    	}
    }

}



/*
 * Selection and Feedback
 */

void glFeedbackBuffer( GLsizei size, GLenum type, GLfloat *buffer ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPassThrough( GLfloat token ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSelectBuffer( GLsizei size, GLuint *buffer ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glInitNames( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glLoadName( GLuint name ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPushName( GLuint name ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glPopName( void ){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}




// GL_VERSION_1_3

void glClientActiveTexture (GLenum texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto n_texture = texture - GL_TEXTURE0;
    
    fpe_state_ptr->state.current_client_active_texture_unit = n_texture;

}

void glMultiTexCoord1d (GLenum target, GLdouble s){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1dv (GLenum target, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1f (GLenum target, GLfloat s){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1fv (GLenum target, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1i (GLenum target, GLint s){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1iv (GLenum target, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1s (GLenum target, GLshort s){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord1sv (GLenum target, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2d (GLenum target, GLdouble s, GLdouble t){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2dv (GLenum target, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2f (GLenum target, GLfloat s, GLfloat t){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2fv (GLenum target, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2i (GLenum target, GLint s, GLint t){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2iv (GLenum target, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2s (GLenum target, GLshort s, GLshort t){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord2sv (GLenum target, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3d (GLenum target, GLdouble s, GLdouble t, GLdouble r){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3dv (GLenum target, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3f (GLenum target, GLfloat s, GLfloat t, GLfloat r){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3fv (GLenum target, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3i (GLenum target, GLint s, GLint t, GLint r){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3iv (GLenum target, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3s (GLenum target, GLshort s, GLshort t, GLshort r){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord3sv (GLenum target, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4d (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4dv (GLenum target, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4fv (GLenum target, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4i (GLenum target, GLint s, GLint t, GLint r, GLint q){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4iv (GLenum target, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4s (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glMultiTexCoord4sv (GLenum target, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glLoadTransposeMatrixf (const GLfloat *m){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    *fpe_state_ptr->state.current_bound_matrix_ptr = glm::transpose(glm::mat4(m[0], m[1], m[2], m[3],
                    															m[4], m[5], m[6], m[7],
                    															m[8], m[9], m[10], m[11],
                    															m[12], m[13], m[14], m[15])
                    															);

}

void glLoadTransposeMatrixd (const GLdouble *m){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GLfloat mf[16];
    for(int n = 0;
    		n < 16;
    		n++)
    {
    	mf[n] = (GLfloat)m[n];
    }
    
    glLoadTransposeMatrixf((const GLfloat *)mf);

}

void glMultTransposeMatrixf (const GLfloat *m){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    glm::mat4 in_mat4 = glm::mat4(m[0], m[1], m[2], m[3],
									m[4], m[5], m[6], m[7],
									m[8], m[9], m[10], m[11],
									m[12], m[13], m[14], m[15]);
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    *fpe_state_ptr->state.current_bound_matrix_ptr *= glm::transpose(in_mat4);


}

void glMultTransposeMatrixd (const GLdouble *m){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GLfloat mf[16];
    for(int n = 0;
    		n < 16;
    		n++)
    {
    	mf[n] = (GLfloat)m[n];
    }
    
    glMultTransposeMatrixf((const GLfloat *)mf);

}



// GL_VERSION_1_4

void glFogCoordf (GLfloat coord){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glFogCoordfv (const GLfloat *coord){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glFogCoordd (GLdouble coord){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glFogCoorddv (const GLdouble *coord){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glFogCoordPointer (GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.fog_coord_array;
    
    //vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = pointer;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glSecondaryColor3b (GLbyte red, GLbyte green, GLbyte blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3bv (const GLbyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3d (GLdouble red, GLdouble green, GLdouble blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3dv (const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3f (GLfloat red, GLfloat green, GLfloat blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3fv (const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3i (GLint red, GLint green, GLint blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3iv (const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3s (GLshort red, GLshort green, GLshort blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3sv (const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3ub (GLubyte red, GLubyte green, GLubyte blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3ubv (const GLubyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3ui (GLuint red, GLuint green, GLuint blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3uiv (const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3us (GLushort red, GLushort green, GLushort blue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColor3usv (const GLushort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glSecondaryColorPointer (GLint size, GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    //NOT_IMPLEMENTED
    
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    auto vertex_array_ptr = &fpe_state_ptr->vertex_arrays.secondary_color_array;
    
    vertex_array_ptr->size = size;
    vertex_array_ptr->type = type;
    vertex_array_ptr->stride = stride;
    vertex_array_ptr->pointer = pointer;
    
	vertex_array_ptr->bound_buffer = fpe_state_ptr->state.current_bound_buffer;

}

void glWindowPos2d (GLdouble x, GLdouble y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2dv (const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2f (GLfloat x, GLfloat y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2fv (const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2i (GLint x, GLint y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2iv (const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2s (GLshort x, GLshort y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos2sv (const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3d (GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3dv (const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3f (GLfloat x, GLfloat y, GLfloat z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3fv (const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3i (GLint x, GLint y, GLint z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3iv (const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3s (GLshort x, GLshort y, GLshort z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}

void glWindowPos3sv (const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    NOT_IMPLEMENTED

}



// GL_VERSION_1_5



// Core API


// GL_VERSION_1_0

void glCullFace (GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCullFace (mode);
}

void glFrontFace (GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFrontFace (mode);
}

void glHint (GLenum target, GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglHint (target, mode);
}

void glLineWidth (GLfloat width){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglLineWidth (width);
}

void glPointSize (GLfloat size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPointSize (size);
}

void glPolygonMode (GLenum face, GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPolygonMode (face, mode);
}

void glScissor (GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglScissor (x, y, width, height);
}

void glTexParameterf (GLenum target, GLenum pname, GLfloat param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexParameterf (target, pname, param);
}

void glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexParameterfv (target, pname, params);
}

void glTexParameteri (GLenum target, GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

	switch (pname)
	{
		case GL_TEXTURE_WRAP_S:
		case GL_TEXTURE_WRAP_T:
		{
			switch (param)
			{
				case GL_CLAMP:
				{
					return OpenGL::vkglTexParameteri (target, pname, GL_CLAMP_TO_EDGE);
				}
			}
		}
	}

    return OpenGL::vkglTexParameteri (target, pname, param);
}

void glTexParameteriv (GLenum target, GLenum pname, const GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

	switch (pname)
	{
		case GL_TEXTURE_WRAP_S:
		case GL_TEXTURE_WRAP_T:
		{
			switch (*params)
			{
				case GL_CLAMP:
				{
					return OpenGL::vkglTexParameteri (target, pname, GL_CLAMP_TO_EDGE);
				}
			}
		}
	}

    return OpenGL::vkglTexParameteriv (target, pname, params);
}

void glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexImage1D (target, level, internalformat, width, border, format, type, pixels);
}

void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)

	if (!ENABLED_GL_NO_ERROR(in_context_p) )
	{
    	GLsizei max_texture_size = 0;
    	{
    		glGetIntegerv(GL_MAX_TEXTURE_SIZE,
    					&max_texture_size);
    	}
    		vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    		vkgl_printf("width = %d", width);
    		vkgl_printf("height = %d", height);
    		vkgl_printf("max_texture_size = %d", max_texture_size);
    	if (target == GL_PROXY_TEXTURE_2D ||
            target == GL_PROXY_TEXTURE_1D_ARRAY ||
            target == GL_PROXY_TEXTURE_RECTANGLE ||
            target == GL_PROXY_TEXTURE_CUBE_MAP)
    	{
    		if ((width <= 0 || width > max_texture_size) ||
    			(height <= 0 || height > max_texture_size) )
    		{
    			internalformat = 0;
    			width = 0;
    			height = 0;
    		}
    		
		    OpenGL::vkglTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);
		    
		    goto end;
    	}
    	
    	if (target != GL_TEXTURE_2D &&
            target != GL_TEXTURE_1D_ARRAY &&
            target != GL_TEXTURE_RECTANGLE &&
            target != GL_PROXY_TEXTURE_2D &&
            target != GL_PROXY_TEXTURE_1D_ARRAY &&
            target != GL_PROXY_TEXTURE_RECTANGLE &&
            target != GL_PROXY_TEXTURE_CUBE_MAP &&
            target != GL_TEXTURE_CUBE_MAP_POSITIVE_X &&
            target != GL_TEXTURE_CUBE_MAP_NEGATIVE_X &&
            target != GL_TEXTURE_CUBE_MAP_POSITIVE_Y &&
            target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y &&
            target != GL_TEXTURE_CUBE_MAP_POSITIVE_Z &&
            target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_ENUM);
    		goto end;
    	}
    	
    	if ((target >= GL_TEXTURE_CUBE_MAP_POSITIVE_X && target <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) &&
    		(width != height) )
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_ENUM);
    		goto end;
    	}
    	
    	if (type != GL_UNSIGNED_BYTE &&
            type != GL_BYTE &&
            type != GL_UNSIGNED_SHORT &&
            type != GL_SHORT &&
            type != GL_UNSIGNED_INT &&
            type != GL_INT &&
            type != GL_FLOAT &&
            type != GL_UNSIGNED_BYTE_3_3_2 &&
            type != GL_UNSIGNED_BYTE_2_3_3_REV &&
            type != GL_UNSIGNED_SHORT_5_6_5 &&
            type != GL_UNSIGNED_SHORT_5_6_5_REV &&
            type != GL_UNSIGNED_SHORT_4_4_4_4 &&
            type != GL_UNSIGNED_SHORT_4_4_4_4_REV &&
            type != GL_UNSIGNED_SHORT_5_5_5_1 &&
            type != GL_UNSIGNED_SHORT_1_5_5_5_REV &&
            type != GL_UNSIGNED_INT_8_8_8_8 &&
            type != GL_UNSIGNED_INT_8_8_8_8_REV &&
            type != GL_UNSIGNED_INT_10_10_10_2 &&
            type != GL_UNSIGNED_INT_2_10_10_10_REV)
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_ENUM);
    		goto end;
    	}
    	
    	if ((width <= 0 || width > max_texture_size) ||
    		(height <= 0 || height > max_texture_size) )
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_VALUE);
    		goto end;
    	}
    	
    	if (level < 0)
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_VALUE);
    		goto end;
    	}
    	
    	if (border != 0)
    	{
    		SET_GL_ERROR(in_context_p,
    						GL_INVALID_VALUE);
    		goto end;
    	}
	}

    OpenGL::vkglTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);

end:
	;
}

void glDrawBuffer (GLenum buf){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawBuffer (buf);
}

void glClear (GLbitfield mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClear (mask);
}

void glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearColor (red, green, blue, alpha);
}

void glClearStencil (GLint s){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearStencil (s);
}

void glClearDepth (GLdouble depth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearDepth (depth);
}

void glStencilMask (GLuint mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilMask (mask);
}

void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglColorMask (red, green, blue, alpha);
}

void glDepthMask (GLboolean flag){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthMask (flag);
}

void glDisable (GLenum cap){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    switch (cap)
    {
    	case GL_FOG:
    	{
    		fpe_state_ptr->state.fog_enabled = false;
    		
    		break;
    	}
    	case GL_LIGHTING:
    	{
    		fpe_state_ptr->state.lighting_enabled = false;
    		
    		break;
    	}
    	case GL_NORMALIZE:
    	{
    		fpe_state_ptr->state.normalize_enabled = false;
    		
    		break;
    	}
    	case GL_RESCALE_NORMAL:
    	{
    		fpe_state_ptr->state.rescale_normal_enabled = false;
    		
    		break;
    	}
    	case GL_ALPHA_TEST:
    	{
    		fpe_state_ptr->state.alpha_test_enabled = false;
    		
    		break;
    	}
    	case GL_COLOR_MATERIAL:
    	{
    		fpe_state_ptr->state.color_material_enabled = false;
    		
    		break;
    	}
    	case GL_TEXTURE_2D:
    	{
    		fpe_state_ptr->state.texture_unit_enabled.at(fpe_state_ptr->state.current_active_texture_unit) = false;
    		
    		break;
    	}
    	default:
    	{
        	if (cap >= GL_LIGHT0)
        	{
        		uint32_t n_light = std::clamp((int)(cap - GL_LIGHT0),
        									0,
        									(int)(fpe_state_ptr->state.light_enabled.size() ) );
        		
        		fpe_state_ptr->state.light_enabled.at(n_light) = false;
        	}
        	else
        	{
        	    OpenGL::vkglDisable (cap);
    	    }
    	}
    }
}

void glEnable (GLenum cap){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    
    switch (cap)
    {
    	case GL_FOG:
    	{
    		fpe_state_ptr->state.fog_enabled = true;
    		
    		break;
    	}
    	case GL_LIGHTING:
    	{
    		fpe_state_ptr->state.lighting_enabled = true;
    		
    		break;
    	}
    	case GL_NORMALIZE:
    	{
    		fpe_state_ptr->state.normalize_enabled = true;
    		
    		break;
    	}
    	case GL_RESCALE_NORMAL:
    	{
    		fpe_state_ptr->state.rescale_normal_enabled = true;
    		
    		break;
    	}
    	case GL_ALPHA_TEST:
    	{
    		fpe_state_ptr->state.alpha_test_enabled = true;
    		
    		break;
    	}
    	case GL_COLOR_MATERIAL:
    	{
    		fpe_state_ptr->state.color_material_enabled = true;
    		
    		break;
    	}
    	case GL_TEXTURE_2D:
    	{
    		fpe_state_ptr->state.texture_unit_enabled.at(fpe_state_ptr->state.current_active_texture_unit) = true;
    		
    		break;
    	}
    	default:
    	{
        	if (cap >= GL_LIGHT0)
        	{
        		uint32_t n_light = std::clamp((int)(cap - GL_LIGHT0),
        									0,
        									(int)(fpe_state_ptr->state.light_enabled.size() ) );
        		
        		fpe_state_ptr->state.light_enabled.at(n_light) = true;
        	}
        	else
        	{
        	    OpenGL::vkglEnable (cap);
    	    }
    	}
    }
}

void glFinish (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFinish ();
}

void glFlush (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFlush ();
}

void glBlendFunc (GLenum sfactor, GLenum dfactor){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendFunc (sfactor, dfactor);
}

void glLogicOp (GLenum opcode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglLogicOp (opcode);
}

void glStencilFunc (GLenum func, GLint ref, GLuint mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilFunc (func, ref, mask);
}

void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilOp (fail, zfail, zpass);
}

void glDepthFunc (GLenum func){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthFunc (func);
}

void glPixelStoref (GLenum pname, GLfloat param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPixelStoref (pname, param);
}

void glPixelStorei (GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPixelStorei (pname, param);
}

void glReadBuffer (GLenum src){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglReadBuffer (src);
}

void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglReadPixels (x, y, width, height, format, type, pixels);
}

void glGetBooleanv (GLenum pname, GLboolean *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBooleanv (pname, data);
}

void glGetDoublev (GLenum pname, GLdouble *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetDoublev (pname, data);
}

GLenum glGetError (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetError ();
}

void glGetFloatv (GLenum pname, GLfloat *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFloatv (pname, data);
}

void glGetIntegerv (GLenum pname, GLint *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    switch (pname)
    {
    	case GL_MAX_TEXTURE_COORDS:		*data = VKGL_MAX_TEXTURE_COORDS; break;
    	case GL_MAX_TEXTURE_UNITS:		*data = VKGL_MAX_TEXTURE_UNITS; break;
    	case GL_MAX_LIGHTS:				*data = VKGL_MAX_LIGHTS; break;
    	
    	default:
    	{
    	    OpenGL::vkglGetIntegerv (pname, data);
    	}
    }
}

const GLubyte *glGetString (GLenum name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetString (name);
}

void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexImage (target, level, format, type, pixels);
}

void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexParameterfv (target, pname, params);
}

void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexParameteriv (target, pname, params);
}

void glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexLevelParameterfv (target, level, pname, params);
}

void glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexLevelParameteriv (target, level, pname, params);
}

GLboolean glIsEnabled (GLenum cap){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    GLboolean result = GL_FALSE;
    
    switch (cap)
    {
    	case GL_FOG:
    	{
    		result = fpe_state_ptr->state.fog_enabled;
    		
    		break;
    	}
    	case GL_LIGHTING:
    	{
    		result = fpe_state_ptr->state.lighting_enabled;
    		
    		break;
    	}
    	case GL_NORMALIZE:
    	{
    		result = fpe_state_ptr->state.normalize_enabled;
    		
    		break;
    	}
    	case GL_RESCALE_NORMAL:
    	{
    		result = fpe_state_ptr->state.rescale_normal_enabled;
    		
    		break;
    	}
    	case GL_ALPHA_TEST:
    	{
    		result = fpe_state_ptr->state.alpha_test_enabled;
    		
    		break;
    	}
    	case GL_COLOR_MATERIAL:
    	{
    		result = fpe_state_ptr->state.color_material_enabled;
    		
    		break;
    	}
    	case GL_TEXTURE_2D:
    	{
    		result = fpe_state_ptr->state.texture_unit_enabled.at(fpe_state_ptr->state.current_active_texture_unit);
    		
    		break;
    	}
    	default:
    	{
        	if (cap >= GL_LIGHT0)
        	{
        		uint32_t n_light = std::clamp((int)(cap - GL_LIGHT0),
        									0,
        									(int)(fpe_state_ptr->state.light_enabled.size() ) );
        		
        		result = fpe_state_ptr->state.light_enabled.at(n_light);
        	}
        	else
        	{
        	    result = OpenGL::vkglIsEnabled (cap);
    	    }
    	}
    }
    
    return result;
}

void glDepthRange (GLdouble n, GLdouble f){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthRange (n, f);
}

void glViewport (GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglViewport (x, y, width, height);
}



// GL_VERSION_1_1

void glDrawArrays (GLenum mode, GLint first, GLsizei count){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    bool result = false;vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    
    const auto current_bound_buffer = fpe_state_ptr->state.current_bound_buffer;
    const auto current_bound_program = fpe_state_ptr->state.current_bound_program;
    const auto current_bound_vao = fpe_state_ptr->state.current_bound_vao;
    
    auto fpe_program 			= current_bound_program;
    
    result = fpe_manager_ptr->update_fpe_vertex_buffers(first + count);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    vkgl_assert(result != false);
    
    if (fpe_program == 0)
    {vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    	fpe_program = fpe_manager_ptr->get_fpe_program();vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    	vkgl_assert(fpe_program != 0);
    
        OpenGL::vkglUseProgram(fpe_program);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    }
    
    result = fpe_manager_ptr->update_fpe_uniform_resources(fpe_program);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    vkgl_assert(result != false);
    
    result = fpe_manager_ptr->begin_fpe_vao(fpe_program);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    vkgl_assert(result != false);
	
    OpenGL::vkglDrawArrays (mode, first, count);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    
    result = fpe_manager_ptr->end_fpe_vao(fpe_program);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
    vkgl_assert(result != false);
    
    OpenGL::vkglUseProgram(current_bound_program);vkgl_printf("line = %d file = %s", __LINE__, __FILE__);
}

void glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    bool result = false;
    
    const auto current_bound_buffer = fpe_state_ptr->state.current_bound_buffer;
    const auto current_bound_program = fpe_state_ptr->state.current_bound_program;
    const auto current_bound_vao = fpe_state_ptr->state.current_bound_vao;
    
    auto fpe_program 			= current_bound_program;
    
    if (fpe_program == 0)
    {
    	fpe_program = fpe_manager_ptr->get_fpe_program();
    	vkgl_assert(fpe_program != 0);
    
        OpenGL::vkglUseProgram(fpe_program);
    }
    
    result = fpe_manager_ptr->update_fpe_uniform_resources(fpe_program);
    vkgl_assert(result != false);
    
    result = fpe_manager_ptr->update_fpe_vertex_buffers(count);
    vkgl_assert(result != false);
    
    result = fpe_manager_ptr->begin_fpe_vao(fpe_program);
    vkgl_assert(result != false);
	
    OpenGL::vkglDrawElements (mode, count, type, indices);
    
    result = fpe_manager_ptr->end_fpe_vao(fpe_program);
    vkgl_assert(result != false);
    
    OpenGL::vkglUseProgram(current_bound_program);
}

void glGetPointerv (GLenum pname, void **params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetPointerv (pname, params);
}

void glPolygonOffset (GLfloat factor, GLfloat units){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPolygonOffset (factor, units);
}

void glCopyTexImage1D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTexImage1D (target, level, internalformat, x, y, width, border);
}

void glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTexImage2D (target, level, internalformat, x, y, width, height, border);
}

void glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTexSubImage1D (target, level, xoffset, x, y, width);
}

void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height);
}

void glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexSubImage1D (target, level, xoffset, width, format, type, pixels);
}

void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void glBindTexture (GLenum target, GLuint texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindTexture (target, texture);
}

void glDeleteTextures (GLsizei n, const GLuint *textures){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteTextures (n, textures);
}

void glGenTextures (GLsizei n, GLuint *textures){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenTextures (n, textures);
}

GLboolean glIsTexture (GLuint texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsTexture (texture);
}



// GL_VERSION_1_2

void glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    bool result = false;
    
    const auto current_bound_buffer = fpe_state_ptr->state.current_bound_buffer;
    const auto current_bound_program = fpe_state_ptr->state.current_bound_program;
    const auto current_bound_vao = fpe_state_ptr->state.current_bound_vao;
    
    auto fpe_program 			= current_bound_program;
    
    if (fpe_program == 0)
    {
    	fpe_program = fpe_manager_ptr->get_fpe_program();
    	vkgl_assert(fpe_program != 0);
    
        OpenGL::vkglUseProgram(fpe_program);
    }
    
    result = fpe_manager_ptr->update_fpe_uniform_resources(fpe_program);
    vkgl_assert(result != false);
    
    result = fpe_manager_ptr->update_fpe_vertex_buffers(count);
    vkgl_assert(result != false);
    
    result = fpe_manager_ptr->begin_fpe_vao(fpe_program);
    vkgl_assert(result != false);
	
    OpenGL::vkglDrawRangeElements (mode, start, end, count, type, indices);
    
    result = fpe_manager_ptr->end_fpe_vao(fpe_program);
    vkgl_assert(result != false);
    
    OpenGL::vkglUseProgram(current_bound_program);
}

void glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexImage3D (target, level, internalformat, width, height, depth, border, format, type, pixels);
}

void glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTexSubImage3D (target, level, xoffset, yoffset, zoffset, x, y, width, height);
}



// GL_VERSION_1_3

void glActiveTexture (GLenum texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    fpe_state_ptr->state.current_active_texture_unit = texture;

    return OpenGL::vkglActiveTexture (texture);
}

void glSampleCoverage (GLfloat value, GLboolean invert){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSampleCoverage (value, invert);
}

void glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexImage3D (target, level, internalformat, width, height, depth, border, imageSize, data);
}

void glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexImage2D (target, level, internalformat, width, height, border, imageSize, data);
}

void glCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexImage1D (target, level, internalformat, width, border, imageSize, data);
}

void glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexSubImage3D (target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void glCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTexSubImage1D (target, level, xoffset, width, format, imageSize, data);
}

void glGetCompressedTexImage (GLenum target, GLint level, void *img){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetCompressedTexImage (target, level, img);
}



// GL_VERSION_1_4

void glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendFuncSeparate (sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void glMultiDrawArrays (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawArrays (mode, first, count, drawcount);
}

void glMultiDrawElements (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawElements (mode, count, type, indices, drawcount);
}

void glPointParameterf (GLenum pname, GLfloat param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPointParameterf (pname, param);
}

void glPointParameterfv (GLenum pname, const GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPointParameterfv (pname, params);
}

void glPointParameteri (GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPointParameteri (pname, param);
}

void glPointParameteriv (GLenum pname, const GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPointParameteriv (pname, params);
}

void glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendColor (red, green, blue, alpha);
}

void glBlendEquation (GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendEquation (mode);
}



// GL_VERSION_1_5

void glGenQueries (GLsizei n, GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenQueries (n, ids);
}

void glDeleteQueries (GLsizei n, const GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteQueries (n, ids);
}

GLboolean glIsQuery (GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsQuery (id);
}

void glBeginQuery (GLenum target, GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBeginQuery (target, id);
}

void glEndQuery (GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEndQuery (target);
}

void glGetQueryiv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryiv (target, pname, params);
}

void glGetQueryObjectiv (GLuint id, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryObjectiv (id, pname, params);
}

void glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryObjectuiv (id, pname, params);
}

void glBindBuffer (GLenum target, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    switch (target)
    {
    	case GL_ARRAY_BUFFER:
    	{
            fpe_state_ptr->state.current_bound_buffer 		= buffer;
            
            break;
        }
    }
    
    return OpenGL::vkglBindBuffer (target, buffer);
}

void glDeleteBuffers (GLsizei n, const GLuint *buffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteBuffers (n, buffers);
}

void glGenBuffers (GLsizei n, GLuint *buffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenBuffers (n, buffers);
}

GLboolean glIsBuffer (GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsBuffer (buffer);
}

void glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBufferData (target, size, data, usage);
}

void glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBufferSubData (target, offset, size, data);
}

void glGetBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBufferSubData (target, offset, size, data);
}

void *glMapBuffer (GLenum target, GLenum access){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMapBuffer (target, access);
}

GLboolean glUnmapBuffer (GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUnmapBuffer (target);
}

void glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBufferParameteriv (target, pname, params);
}

void glGetBufferPointerv (GLenum target, GLenum pname, void **params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBufferPointerv (target, pname, params);
}



// GL_VERSION_2_0

void glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendEquationSeparate (modeRGB, modeAlpha);
}

void glDrawBuffers (GLsizei n, const GLenum *bufs){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawBuffers (n, bufs);
}

void glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilOpSeparate (face, sfail, dpfail, dppass);
}

void glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilFuncSeparate (face, func, ref, mask);
}

void glStencilMaskSeparate (GLenum face, GLuint mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglStencilMaskSeparate (face, mask);
}

void glAttachShader (GLuint program, GLuint shader){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglAttachShader (program, shader);
}

void glBindAttribLocation (GLuint program, GLuint index, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindAttribLocation (program, index, name);
}

void glCompileShader (GLuint shader){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompileShader (shader);
}

GLuint glCreateProgram (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateProgram ();
}

GLuint glCreateShader (GLenum type){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateShader (type);
}

void glDeleteProgram (GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

	GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    OpenGL::vkglDeleteProgram (program);
    
    auto result	= fpe_manager_ptr->delete_program_state(program);
    vkgl_assert(result);
}

void glDeleteShader (GLuint shader){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteShader (shader);
}

void glDetachShader (GLuint program, GLuint shader){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDetachShader (program, shader);
}

void glDisableVertexAttribArray (GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDisableVertexAttribArray (index);
}

void glEnableVertexAttribArray (GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEnableVertexAttribArray (index);
}

void glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveAttrib (program, index, bufSize, length, size, type, name);
}

void glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveUniform (program, index, bufSize, length, size, type, name);
}

void glGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetAttachedShaders (program, maxCount, count, shaders);
}

GLint glGetAttribLocation (GLuint program, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetAttribLocation (program, name);
}

void glGetProgramiv (GLuint program, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramiv (program, pname, params);
}

void glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramInfoLog (program, bufSize, length, infoLog);
}

void glGetShaderiv (GLuint shader, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetShaderiv (shader, pname, params);
}

void glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetShaderInfoLog (shader, bufSize, length, infoLog);
}

void glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetShaderSource (shader, bufSize, length, source);
}

GLint glGetUniformLocation (GLuint program, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformLocation (program, name);
}

void glGetUniformfv (GLuint program, GLint location, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformfv (program, location, params);
}

void glGetUniformiv (GLuint program, GLint location, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformiv (program, location, params);
}

void glGetVertexAttribdv (GLuint index, GLenum pname, GLdouble *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribdv (index, pname, params);
}

void glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribfv (index, pname, params);
}

void glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribiv (index, pname, params);
}

void glGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribPointerv (index, pname, pointer);
}

GLboolean glIsProgram (GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsProgram (program);
}

GLboolean glIsShader (GLuint shader){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsShader (shader);
}

void glLinkProgram (GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

	GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    OpenGL::vkglLinkProgram (program);
    
    auto result	= fpe_manager_ptr->create_program_state(program);
    vkgl_assert(result);
}

void glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglShaderSource (shader, count, string, length);
}

void glUseProgram (GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    
	GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    fpe_state_ptr->state.current_bound_program 		= program;
    
    return OpenGL::vkglUseProgram (program);
}

void glUniform1f (GLint location, GLfloat v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1f (location, v0);
}

void glUniform2f (GLint location, GLfloat v0, GLfloat v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2f (location, v0, v1);
}

void glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3f (location, v0, v1, v2);
}

void glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4f (location, v0, v1, v2, v3);
}

void glUniform1i (GLint location, GLint v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1i (location, v0);
}

void glUniform2i (GLint location, GLint v0, GLint v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2i (location, v0, v1);
}

void glUniform3i (GLint location, GLint v0, GLint v1, GLint v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3i (location, v0, v1, v2);
}

void glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4i (location, v0, v1, v2, v3);
}

void glUniform1fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1fv (location, count, value);
}

void glUniform2fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2fv (location, count, value);
}

void glUniform3fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3fv (location, count, value);
}

void glUniform4fv (GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4fv (location, count, value);
}

void glUniform1iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1iv (location, count, value);
}

void glUniform2iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2iv (location, count, value);
}

void glUniform3iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3iv (location, count, value);
}

void glUniform4iv (GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4iv (location, count, value);
}

void glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2fv (location, count, transpose, value);
}

void glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3fv (location, count, transpose, value);
}

void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4fv (location, count, transpose, value);
}

void glValidateProgram (GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglValidateProgram (program);
}

void glVertexAttrib1d (GLuint index, GLdouble x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1d (index, x);
}

void glVertexAttrib1dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1dv (index, v);
}

void glVertexAttrib1f (GLuint index, GLfloat x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1f (index, x);
}

void glVertexAttrib1fv (GLuint index, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1fv (index, v);
}

void glVertexAttrib1s (GLuint index, GLshort x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1s (index, x);
}

void glVertexAttrib1sv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib1sv (index, v);
}

void glVertexAttrib2d (GLuint index, GLdouble x, GLdouble y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2d (index, x, y);
}

void glVertexAttrib2dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2dv (index, v);
}

void glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2f (index, x, y);
}

void glVertexAttrib2fv (GLuint index, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2fv (index, v);
}

void glVertexAttrib2s (GLuint index, GLshort x, GLshort y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2s (index, x, y);
}

void glVertexAttrib2sv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib2sv (index, v);
}

void glVertexAttrib3d (GLuint index, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3d (index, x, y, z);
}

void glVertexAttrib3dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3dv (index, v);
}

void glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3f (index, x, y, z);
}

void glVertexAttrib3fv (GLuint index, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3fv (index, v);
}

void glVertexAttrib3s (GLuint index, GLshort x, GLshort y, GLshort z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3s (index, x, y, z);
}

void glVertexAttrib3sv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib3sv (index, v);
}

void glVertexAttrib4Nbv (GLuint index, const GLbyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nbv (index, v);
}

void glVertexAttrib4Niv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Niv (index, v);
}

void glVertexAttrib4Nsv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nsv (index, v);
}

void glVertexAttrib4Nub (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nub (index, x, y, z, w);
}

void glVertexAttrib4Nubv (GLuint index, const GLubyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nubv (index, v);
}

void glVertexAttrib4Nuiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nuiv (index, v);
}

void glVertexAttrib4Nusv (GLuint index, const GLushort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4Nusv (index, v);
}

void glVertexAttrib4bv (GLuint index, const GLbyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4bv (index, v);
}

void glVertexAttrib4d (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4d (index, x, y, z, w);
}

void glVertexAttrib4dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4dv (index, v);
}

void glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4f (index, x, y, z, w);
}

void glVertexAttrib4fv (GLuint index, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4fv (index, v);
}

void glVertexAttrib4iv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4iv (index, v);
}

void glVertexAttrib4s (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4s (index, x, y, z, w);
}

void glVertexAttrib4sv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4sv (index, v);
}

void glVertexAttrib4ubv (GLuint index, const GLubyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4ubv (index, v);
}

void glVertexAttrib4uiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4uiv (index, v);
}

void glVertexAttrib4usv (GLuint index, const GLushort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttrib4usv (index, v);
}

void glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribPointer (index, size, type, normalized, stride, pointer);
}



// GL_VERSION_2_1

void glUniformMatrix2x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2x3fv (location, count, transpose, value);
}

void glUniformMatrix3x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3x2fv (location, count, transpose, value);
}

void glUniformMatrix2x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2x4fv (location, count, transpose, value);
}

void glUniformMatrix4x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4x2fv (location, count, transpose, value);
}

void glUniformMatrix3x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3x4fv (location, count, transpose, value);
}

void glUniformMatrix4x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4x3fv (location, count, transpose, value);
}



// GL_VERSION_3_0

void glColorMaski (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglColorMaski (index, r, g, b, a);
}

void glGetBooleani_v (GLenum target, GLuint index, GLboolean *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBooleani_v (target, index, data);
}

void glGetIntegeri_v (GLenum target, GLuint index, GLint *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetIntegeri_v (target, index, data);
}

void glEnablei (GLenum target, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEnablei (target, index);
}

void glDisablei (GLenum target, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDisablei (target, index);
}

GLboolean glIsEnabledi (GLenum target, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsEnabledi (target, index);
}

void glBeginTransformFeedback (GLenum primitiveMode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBeginTransformFeedback (primitiveMode);
}

void glEndTransformFeedback (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEndTransformFeedback ();
}

void glBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindBufferRange (target, index, buffer, offset, size);
}

void glBindBufferBase (GLenum target, GLuint index, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindBufferBase (target, index, buffer);
}

void glTransformFeedbackVaryings (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTransformFeedbackVaryings (program, count, varyings, bufferMode);
}

void glGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTransformFeedbackVarying (program, index, bufSize, length, size, type, name);
}

void glClampColor (GLenum target, GLenum clamp){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClampColor (target, clamp);
}

void glBeginConditionalRender (GLuint id, GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBeginConditionalRender (id, mode);
}

void glEndConditionalRender (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEndConditionalRender ();
}

void glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribIPointer (index, size, type, stride, pointer);
}

void glGetVertexAttribIiv (GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribIiv (index, pname, params);
}

void glGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribIuiv (index, pname, params);
}

void glVertexAttribI1i (GLuint index, GLint x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI1i (index, x);
}

void glVertexAttribI2i (GLuint index, GLint x, GLint y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI2i (index, x, y);
}

void glVertexAttribI3i (GLuint index, GLint x, GLint y, GLint z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI3i (index, x, y, z);
}

void glVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4i (index, x, y, z, w);
}

void glVertexAttribI1ui (GLuint index, GLuint x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI1ui (index, x);
}

void glVertexAttribI2ui (GLuint index, GLuint x, GLuint y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI2ui (index, x, y);
}

void glVertexAttribI3ui (GLuint index, GLuint x, GLuint y, GLuint z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI3ui (index, x, y, z);
}

void glVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4ui (index, x, y, z, w);
}

void glVertexAttribI1iv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI1iv (index, v);
}

void glVertexAttribI2iv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI2iv (index, v);
}

void glVertexAttribI3iv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI3iv (index, v);
}

void glVertexAttribI4iv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4iv (index, v);
}

void glVertexAttribI1uiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI1uiv (index, v);
}

void glVertexAttribI2uiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI2uiv (index, v);
}

void glVertexAttribI3uiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI3uiv (index, v);
}

void glVertexAttribI4uiv (GLuint index, const GLuint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4uiv (index, v);
}

void glVertexAttribI4bv (GLuint index, const GLbyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4bv (index, v);
}

void glVertexAttribI4sv (GLuint index, const GLshort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4sv (index, v);
}

void glVertexAttribI4ubv (GLuint index, const GLubyte *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4ubv (index, v);
}

void glVertexAttribI4usv (GLuint index, const GLushort *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribI4usv (index, v);
}

void glGetUniformuiv (GLuint program, GLint location, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformuiv (program, location, params);
}

void glBindFragDataLocation (GLuint program, GLuint color, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindFragDataLocation (program, color, name);
}

GLint glGetFragDataLocation (GLuint program, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFragDataLocation (program, name);
}

void glUniform1ui (GLint location, GLuint v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1ui (location, v0);
}

void glUniform2ui (GLint location, GLuint v0, GLuint v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2ui (location, v0, v1);
}

void glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3ui (location, v0, v1, v2);
}

void glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4ui (location, v0, v1, v2, v3);
}

void glUniform1uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1uiv (location, count, value);
}

void glUniform2uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2uiv (location, count, value);
}

void glUniform3uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3uiv (location, count, value);
}

void glUniform4uiv (GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4uiv (location, count, value);
}

void glTexParameterIiv (GLenum target, GLenum pname, const GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexParameterIiv (target, pname, params);
}

void glTexParameterIuiv (GLenum target, GLenum pname, const GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexParameterIuiv (target, pname, params);
}

void glGetTexParameterIiv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexParameterIiv (target, pname, params);
}

void glGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTexParameterIuiv (target, pname, params);
}

void glClearBufferiv (GLenum buffer, GLint drawbuffer, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferiv (buffer, drawbuffer, value);
}

void glClearBufferuiv (GLenum buffer, GLint drawbuffer, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferuiv (buffer, drawbuffer, value);
}

void glClearBufferfv (GLenum buffer, GLint drawbuffer, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferfv (buffer, drawbuffer, value);
}

void glClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferfi (buffer, drawbuffer, depth, stencil);
}

const GLubyte *glGetStringi (GLenum name, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetStringi (name, index);
}

GLboolean glIsRenderbuffer (GLuint renderbuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsRenderbuffer (renderbuffer);
}

void glBindRenderbuffer (GLenum target, GLuint renderbuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindRenderbuffer (target, renderbuffer);
}

void glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteRenderbuffers (n, renderbuffers);
}

void glGenRenderbuffers (GLsizei n, GLuint *renderbuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenRenderbuffers (n, renderbuffers);
}

void glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglRenderbufferStorage (target, internalformat, width, height);
}

void glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetRenderbufferParameteriv (target, pname, params);
}

GLboolean glIsFramebuffer (GLuint framebuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsFramebuffer (framebuffer);
}

void glBindFramebuffer (GLenum target, GLuint framebuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindFramebuffer (target, framebuffer);
}

void glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteFramebuffers (n, framebuffers);
}

void glGenFramebuffers (GLsizei n, GLuint *framebuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenFramebuffers (n, framebuffers);
}

GLenum glCheckFramebufferStatus (GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCheckFramebufferStatus (target);
}

void glFramebufferTexture1D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferTexture1D (target, attachment, textarget, texture, level);
}

void glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferTexture2D (target, attachment, textarget, texture, level);
}

void glFramebufferTexture3D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferTexture3D (target, attachment, textarget, texture, level, zoffset);
}

void glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferRenderbuffer (target, attachment, renderbuffertarget, renderbuffer);
}

void glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFramebufferAttachmentParameteriv (target, attachment, pname, params);
}

void glGenerateMipmap (GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenerateMipmap (target);
}

void glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlitFramebuffer (srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglRenderbufferStorageMultisample (target, samples, internalformat, width, height);
}

void glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferTextureLayer (target, attachment, texture, level, layer);
}

void *glMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMapBufferRange (target, offset, length, access);
}

void glFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFlushMappedBufferRange (target, offset, length);
}

void glBindVertexArray (GLuint array){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    
	GET_CONTEXT(in_context_p)
    OpenGL::IContextObjectManagers* frontend_object_managers_ptr = in_context_p;
    
    auto fpe_manager_ptr = frontend_object_managers_ptr->get_compatibility_manager_ptr();
    vkgl_assert(fpe_manager_ptr != nullptr);
    
    auto fpe_state_ptr		= fpe_manager_ptr->get_fpe_state();
    
    fpe_state_ptr->state.current_bound_vao 		= array;

    return OpenGL::vkglBindVertexArray (array);
}

void glDeleteVertexArrays (GLsizei n, const GLuint *arrays){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteVertexArrays (n, arrays);
}

void glGenVertexArrays (GLsizei n, GLuint *arrays){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenVertexArrays (n, arrays);
}

GLboolean glIsVertexArray (GLuint array){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsVertexArray (array);
}




// GL_VERSION_3_1

void glDrawArraysInstanced (GLenum mode, GLint first, GLsizei count, GLsizei instancecount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawArraysInstanced (mode, first, count, instancecount);
}

void glDrawElementsInstanced (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsInstanced (mode, count, type, indices, instancecount);
}

void glTexBuffer (GLenum target, GLenum internalformat, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexBuffer (target, internalformat, buffer);
}

void glPrimitiveRestartIndex (GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPrimitiveRestartIndex (index);
}

void glCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyBufferSubData (readTarget, writeTarget, readOffset, writeOffset, size);
}

void glGetUniformIndices (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformIndices (program, uniformCount, uniformNames, uniformIndices);
}

void glGetActiveUniformsiv (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveUniformsiv (program, uniformCount, uniformIndices, pname, params);
}

void glGetActiveUniformName (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveUniformName (program, uniformIndex, bufSize, length, uniformName);
}

GLuint glGetUniformBlockIndex (GLuint program, const GLchar *uniformBlockName){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformBlockIndex (program, uniformBlockName);
}

void glGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveUniformBlockiv (program, uniformBlockIndex, pname, params);
}

void glGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveUniformBlockName (program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void glUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformBlockBinding (program, uniformBlockIndex, uniformBlockBinding);
}




// GL_VERSION_3_2

void glDrawElementsBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsBaseVertex (mode, count, type, indices, basevertex);
}

void glDrawRangeElementsBaseVertex (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawRangeElementsBaseVertex (mode, start, end, count, type, indices, basevertex);
}

void glDrawElementsInstancedBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsInstancedBaseVertex (mode, count, type, indices, instancecount, basevertex);
}

void glMultiDrawElementsBaseVertex (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawElementsBaseVertex (mode, count, type, indices, drawcount, basevertex);
}

void glProvokingVertex (GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProvokingVertex (mode);
}

GLsync glFenceSync (GLenum condition, GLbitfield flags){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFenceSync (condition, flags);
}

GLboolean glIsSync (GLsync sync){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsSync (sync);
}

void glDeleteSync (GLsync sync){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteSync (sync);
}

GLenum glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClientWaitSync (sync, flags, timeout);
}

void glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglWaitSync (sync, flags, timeout);
}

void glGetInteger64v (GLenum pname, GLint64 *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetInteger64v (pname, data);
}

void glGetSynciv (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSynciv (sync, pname, bufSize, length, values);
}

void glGetInteger64i_v (GLenum target, GLuint index, GLint64 *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetInteger64i_v (target, index, data);
}

void glGetBufferParameteri64v (GLenum target, GLenum pname, GLint64 *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetBufferParameteri64v (target, pname, params);
}

void glFramebufferTexture (GLenum target, GLenum attachment, GLuint texture, GLint level){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferTexture (target, attachment, texture, level);
}

void glTexImage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexImage2DMultisample (target, samples, internalformat, width, height, fixedsamplelocations);
}

void glTexImage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexImage3DMultisample (target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void glGetMultisamplefv (GLenum pname, GLuint index, GLfloat *val){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetMultisamplefv (pname, index, val);
}

void glSampleMaski (GLuint maskNumber, GLbitfield mask){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSampleMaski (maskNumber, mask);
}


/*

// GL_VERSION_3_3

void glBindFragDataLocationIndexed (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindFragDataLocationIndexed (program, colorNumber, index, name);
}

GLint glGetFragDataIndex (GLuint program, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFragDataIndex (program, name);
}

void glGenSamplers (GLsizei count, GLuint *samplers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenSamplers (count, samplers);
}

void glDeleteSamplers (GLsizei count, const GLuint *samplers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteSamplers (count, samplers);
}

GLboolean glIsSampler (GLuint sampler){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsSampler (sampler);
}

void glBindSampler (GLuint unit, GLuint sampler){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindSampler (unit, sampler);
}

void glSamplerParameteri (GLuint sampler, GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameteri (sampler, pname, param);
}

void glSamplerParameteriv (GLuint sampler, GLenum pname, const GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameteriv (sampler, pname, param);
}

void glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameterf (sampler, pname, param);
}

void glSamplerParameterfv (GLuint sampler, GLenum pname, const GLfloat *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameterfv (sampler, pname, param);
}

void glSamplerParameterIiv (GLuint sampler, GLenum pname, const GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameterIiv (sampler, pname, param);
}

void glSamplerParameterIuiv (GLuint sampler, GLenum pname, const GLuint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSamplerParameterIuiv (sampler, pname, param);
}

void glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSamplerParameteriv (sampler, pname, params);
}

void glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSamplerParameterIiv (sampler, pname, params);
}

void glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSamplerParameterfv (sampler, pname, params);
}

void glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSamplerParameterIuiv (sampler, pname, params);
}

void glQueryCounter (GLuint id, GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglQueryCounter (id, target);
}

void glGetQueryObjecti64v (GLuint id, GLenum pname, GLint64 *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryObjecti64v (id, pname, params);
}

void glGetQueryObjectui64v (GLuint id, GLenum pname, GLuint64 *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryObjectui64v (id, pname, params);
}

void glVertexAttribDivisor (GLuint index, GLuint divisor){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribDivisor (index, divisor);
}

void glVertexAttribP1ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP1ui (index, type, normalized, value);
}

void glVertexAttribP1uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP1uiv (index, type, normalized, value);
}

void glVertexAttribP2ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP2ui (index, type, normalized, value);
}

void glVertexAttribP2uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP2uiv (index, type, normalized, value);
}

void glVertexAttribP3ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP3ui (index, type, normalized, value);
}

void glVertexAttribP3uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP3uiv (index, type, normalized, value);
}

void glVertexAttribP4ui (GLuint index, GLenum type, GLboolean normalized, GLuint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP4ui (index, type, normalized, value);
}

void glVertexAttribP4uiv (GLuint index, GLenum type, GLboolean normalized, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribP4uiv (index, type, normalized, value);
}




// GL_VERSION_4_0

void glMinSampleShading (GLfloat value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMinSampleShading (value);
}

void glBlendEquationi (GLuint buf, GLenum mode){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendEquationi (buf, mode);
}

void glBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendEquationSeparatei (buf, modeRGB, modeAlpha);
}

void glBlendFunci (GLuint buf, GLenum src, GLenum dst){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendFunci (buf, src, dst);
}

void glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlendFuncSeparatei (buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void glDrawArraysIndirect (GLenum mode, const void *indirect){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawArraysIndirect (mode, indirect);
}

void glDrawElementsIndirect (GLenum mode, GLenum type, const void *indirect){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsIndirect (mode, type, indirect);
}

void glUniform1d (GLint location, GLdouble x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1d (location, x);
}

void glUniform2d (GLint location, GLdouble x, GLdouble y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2d (location, x, y);
}

void glUniform3d (GLint location, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3d (location, x, y, z);
}

void glUniform4d (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4d (location, x, y, z, w);
}

void glUniform1dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform1dv (location, count, value);
}

void glUniform2dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform2dv (location, count, value);
}

void glUniform3dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform3dv (location, count, value);
}

void glUniform4dv (GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniform4dv (location, count, value);
}

void glUniformMatrix2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2dv (location, count, transpose, value);
}

void glUniformMatrix3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3dv (location, count, transpose, value);
}

void glUniformMatrix4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4dv (location, count, transpose, value);
}

void glUniformMatrix2x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2x3dv (location, count, transpose, value);
}

void glUniformMatrix2x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix2x4dv (location, count, transpose, value);
}

void glUniformMatrix3x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3x2dv (location, count, transpose, value);
}

void glUniformMatrix3x4dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix3x4dv (location, count, transpose, value);
}

void glUniformMatrix4x2dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4x2dv (location, count, transpose, value);
}

void glUniformMatrix4x3dv (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformMatrix4x3dv (location, count, transpose, value);
}

void glGetUniformdv (GLuint program, GLint location, GLdouble *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformdv (program, location, params);
}

GLint glGetSubroutineUniformLocation (GLuint program, GLenum shadertype, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSubroutineUniformLocation (program, shadertype, name);
}

GLuint glGetSubroutineIndex (GLuint program, GLenum shadertype, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetSubroutineIndex (program, shadertype, name);
}

void glGetActiveSubroutineUniformiv (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveSubroutineUniformiv (program, shadertype, index, pname, values);
}

void glGetActiveSubroutineUniformName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveSubroutineUniformName (program, shadertype, index, bufsize, length, name);
}

void glGetActiveSubroutineName (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveSubroutineName (program, shadertype, index, bufsize, length, name);
}

void glUniformSubroutinesuiv (GLenum shadertype, GLsizei count, const GLuint *indices){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUniformSubroutinesuiv (shadertype, count, indices);
}

void glGetUniformSubroutineuiv (GLenum shadertype, GLint location, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetUniformSubroutineuiv (shadertype, location, params);
}

void glGetProgramStageiv (GLuint program, GLenum shadertype, GLenum pname, GLint *values){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramStageiv (program, shadertype, pname, values);
}

void glPatchParameteri (GLenum pname, GLint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPatchParameteri (pname, value);
}

void glPatchParameterfv (GLenum pname, const GLfloat *values){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPatchParameterfv (pname, values);
}

void glBindTransformFeedback (GLenum target, GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindTransformFeedback (target, id);
}

void glDeleteTransformFeedbacks (GLsizei n, const GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteTransformFeedbacks (n, ids);
}

void glGenTransformFeedbacks (GLsizei n, GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenTransformFeedbacks (n, ids);
}

GLboolean glIsTransformFeedback (GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsTransformFeedback (id);
}

void glPauseTransformFeedback (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPauseTransformFeedback (void);
}

void glResumeTransformFeedback (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglResumeTransformFeedback (void);
}

void glDrawTransformFeedback (GLenum mode, GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawTransformFeedback (mode, id);
}

void glDrawTransformFeedbackStream (GLenum mode, GLuint id, GLuint stream){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawTransformFeedbackStream (mode, id, stream);
}

void glBeginQueryIndexed (GLenum target, GLuint index, GLuint id){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBeginQueryIndexed (target, index, id);
}

void glEndQueryIndexed (GLenum target, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEndQueryIndexed (target, index);
}

void glGetQueryIndexediv (GLenum target, GLuint index, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryIndexediv (target, index, pname, params);
}




// GL_VERSION_4_1

void glReleaseShaderCompiler (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglReleaseShaderCompiler (void);
}

void glShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglShaderBinary (count, shaders, binaryformat, binary, length);
}

void glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetShaderPrecisionFormat (shadertype, precisiontype, range, precision);
}

void glDepthRangef (GLfloat n, GLfloat f){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthRangef (n, f);
}

void glClearDepthf (GLfloat d){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearDepthf (d);
}

void glGetProgramBinary (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramBinary (program, bufSize, length, binaryFormat, binary);
}

void glProgramBinary (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramBinary (program, binaryFormat, binary, length);
}

void glProgramParameteri (GLuint program, GLenum pname, GLint value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramParameteri (program, pname, value);
}

void glUseProgramStages (GLuint pipeline, GLbitfield stages, GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUseProgramStages (pipeline, stages, program);
}

void glActiveShaderProgram (GLuint pipeline, GLuint program){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglActiveShaderProgram (pipeline, program);
}

GLuint glCreateShaderProgramv (GLenum type, GLsizei count, const GLchar *const*strings){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateShaderProgramv (type, count, strings);
}

void glBindProgramPipeline (GLuint pipeline){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindProgramPipeline (pipeline);
}

void glDeleteProgramPipelines (GLsizei n, const GLuint *pipelines){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDeleteProgramPipelines (n, pipelines);
}

void glGenProgramPipelines (GLsizei n, GLuint *pipelines){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenProgramPipelines (n, pipelines);
}

GLboolean glIsProgramPipeline (GLuint pipeline){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglIsProgramPipeline (pipeline);
}

void glGetProgramPipelineiv (GLuint pipeline, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramPipelineiv (pipeline, pname, params);
}

void glProgramUniform1i (GLuint program, GLint location, GLint v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1i (program, location, v0);
}

void glProgramUniform1iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1iv (program, location, count, value);
}

void glProgramUniform1f (GLuint program, GLint location, GLfloat v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1f (program, location, v0);
}

void glProgramUniform1fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1fv (program, location, count, value);
}

void glProgramUniform1d (GLuint program, GLint location, GLdouble v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1d (program, location, v0);
}

void glProgramUniform1dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1dv (program, location, count, value);
}

void glProgramUniform1ui (GLuint program, GLint location, GLuint v0){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1ui (program, location, v0);
}

void glProgramUniform1uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform1uiv (program, location, count, value);
}

void glProgramUniform2i (GLuint program, GLint location, GLint v0, GLint v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2i (program, location, v0, v1);
}

void glProgramUniform2iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2iv (program, location, count, value);
}

void glProgramUniform2f (GLuint program, GLint location, GLfloat v0, GLfloat v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2f (program, location, v0, v1);
}

void glProgramUniform2fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2fv (program, location, count, value);
}

void glProgramUniform2d (GLuint program, GLint location, GLdouble v0, GLdouble v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2d (program, location, v0, v1);
}

void glProgramUniform2dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2dv (program, location, count, value);
}

void glProgramUniform2ui (GLuint program, GLint location, GLuint v0, GLuint v1){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2ui (program, location, v0, v1);
}

void glProgramUniform2uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform2uiv (program, location, count, value);
}

void glProgramUniform3i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3i (program, location, v0, v1, v2);
}

void glProgramUniform3iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3iv (program, location, count, value);
}

void glProgramUniform3f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3f (program, location, v0, v1, v2);
}

void glProgramUniform3fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3fv (program, location, count, value);
}

void glProgramUniform3d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3d (program, location, v0, v1, v2);
}

void glProgramUniform3dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3dv (program, location, count, value);
}

void glProgramUniform3ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3ui (program, location, v0, v1, v2);
}

void glProgramUniform3uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform3uiv (program, location, count, value);
}

void glProgramUniform4i (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4i (program, location, v0, v1, v2, v3);
}

void glProgramUniform4iv (GLuint program, GLint location, GLsizei count, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4iv (program, location, count, value);
}

void glProgramUniform4f (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4f (program, location, v0, v1, v2, v3);
}

void glProgramUniform4fv (GLuint program, GLint location, GLsizei count, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4fv (program, location, count, value);
}

void glProgramUniform4d (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4d (program, location, v0, v1, v2, v3);
}

void glProgramUniform4dv (GLuint program, GLint location, GLsizei count, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4dv (program, location, count, value);
}

void glProgramUniform4ui (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4ui (program, location, v0, v1, v2, v3);
}

void glProgramUniform4uiv (GLuint program, GLint location, GLsizei count, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniform4uiv (program, location, count, value);
}

void glProgramUniformMatrix2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix2x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2x3fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3x2fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix2x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2x4fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4x2fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4x2fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3x4fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3x4fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4x3fv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4x3fv (program, location, count, transpose, value);
}

void glProgramUniformMatrix2x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2x3dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3x2dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix2x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix2x4dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4x2dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4x2dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix3x4dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix3x4dv (program, location, count, transpose, value);
}

void glProgramUniformMatrix4x3dv (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglProgramUniformMatrix4x3dv (program, location, count, transpose, value);
}

void glValidateProgramPipeline (GLuint pipeline){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglValidateProgramPipeline (pipeline);
}

void glGetProgramPipelineInfoLog (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramPipelineInfoLog (pipeline, bufSize, length, infoLog);
}

void glVertexAttribL1d (GLuint index, GLdouble x){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL1d (index, x);
}

void glVertexAttribL2d (GLuint index, GLdouble x, GLdouble y){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL2d (index, x, y);
}

void glVertexAttribL3d (GLuint index, GLdouble x, GLdouble y, GLdouble z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL3d (index, x, y, z);
}

void glVertexAttribL4d (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL4d (index, x, y, z, w);
}

void glVertexAttribL1dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL1dv (index, v);
}

void glVertexAttribL2dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL2dv (index, v);
}

void glVertexAttribL3dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL3dv (index, v);
}

void glVertexAttribL4dv (GLuint index, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribL4dv (index, v);
}

void glVertexAttribLPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribLPointer (index, size, type, stride, pointer);
}

void glGetVertexAttribLdv (GLuint index, GLenum pname, GLdouble *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexAttribLdv (index, pname, params);
}

void glViewportArrayv (GLuint first, GLsizei count, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglViewportArrayv (first, count, v);
}

void glViewportIndexedf (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglViewportIndexedf (index, x, y, w, h);
}

void glViewportIndexedfv (GLuint index, const GLfloat *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglViewportIndexedfv (index, v);
}

void glScissorArrayv (GLuint first, GLsizei count, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglScissorArrayv (first, count, v);
}

void glScissorIndexed (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglScissorIndexed (index, left, bottom, width, height);
}

void glScissorIndexedv (GLuint index, const GLint *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglScissorIndexedv (index, v);
}

void glDepthRangeArrayv (GLuint first, GLsizei count, const GLdouble *v){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthRangeArrayv (first, count, v);
}

void glDepthRangeIndexed (GLuint index, GLdouble n, GLdouble f){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDepthRangeIndexed (index, n, f);
}

void glGetFloati_v (GLenum target, GLuint index, GLfloat *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFloati_v (target, index, data);
}

void glGetDoublei_v (GLenum target, GLuint index, GLdouble *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetDoublei_v (target, index, data);
}




// GL_VERSION_4_2

void glDrawArraysInstancedBaseInstance (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawArraysInstancedBaseInstance (mode, first, count, instancecount, baseinstance);
}

void glDrawElementsInstancedBaseInstance (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsInstancedBaseInstance (mode, count, type, indices, instancecount, baseinstance);
}

void glDrawElementsInstancedBaseVertexBaseInstance (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawElementsInstancedBaseVertexBaseInstance (mode, count, type, indices, instancecount, basevertex, baseinstance);
}

void glGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetInternalformativ (target, internalformat, pname, bufSize, params);
}

void glGetActiveAtomicCounterBufferiv (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetActiveAtomicCounterBufferiv (program, bufferIndex, pname, params);
}

void glBindImageTexture (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindImageTexture (unit, texture, level, layered, layer, access, format);
}

void glMemoryBarrier (GLbitfield barriers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMemoryBarrier (barriers);
}

void glTexStorage1D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexStorage1D (target, levels, internalformat, width);
}

void glTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexStorage2D (target, levels, internalformat, width, height);
}

void glTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexStorage3D (target, levels, internalformat, width, height, depth);
}

void glDrawTransformFeedbackInstanced (GLenum mode, GLuint id, GLsizei instancecount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawTransformFeedbackInstanced (mode, id, instancecount);
}

void glDrawTransformFeedbackStreamInstanced (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDrawTransformFeedbackStreamInstanced (mode, id, stream, instancecount);
}




// GL_VERSION_4_3

void glClearBufferData (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferData (target, internalformat, format, type, data);
}

void glClearBufferSubData (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearBufferSubData (target, internalformat, offset, size, format, type, data);
}

void glDispatchCompute (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDispatchCompute (num_groups_x, num_groups_y, num_groups_z);
}

void glDispatchComputeIndirect (GLintptr indirect){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDispatchComputeIndirect (indirect);
}

void glCopyImageSubData (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyImageSubData (srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void glFramebufferParameteri (GLenum target, GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFramebufferParameteri (target, pname, param);
}

void glGetFramebufferParameteriv (GLenum target, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetFramebufferParameteriv (target, pname, params);
}

void glGetInternalformati64v (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetInternalformati64v (target, internalformat, pname, bufSize, params);
}

void glInvalidateTexSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateTexSubImage (texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

void glInvalidateTexImage (GLuint texture, GLint level){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateTexImage (texture, level);
}

void glInvalidateBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateBufferSubData (buffer, offset, length);
}

void glInvalidateBufferData (GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateBufferData (buffer);
}

void glInvalidateFramebuffer (GLenum target, GLsizei numAttachments, const GLenum *attachments){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateFramebuffer (target, numAttachments, attachments);
}

void glInvalidateSubFramebuffer (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateSubFramebuffer (target, numAttachments, attachments, x, y, width, height);
}

void glMultiDrawArraysIndirect (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawArraysIndirect (mode, indirect, drawcount, stride);
}

void glMultiDrawElementsIndirect (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawElementsIndirect (mode, type, indirect, drawcount, stride);
}

void glGetProgramInterfaceiv (GLuint program, GLenum programInterface, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramInterfaceiv (program, programInterface, pname, params);
}

GLuint glGetProgramResourceIndex (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramResourceIndex (program, programInterface, name);
}

void glGetProgramResourceName (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramResourceName (program, programInterface, index, bufSize, length, name);
}

void glGetProgramResourceiv (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramResourceiv (program, programInterface, index, propCount, props, bufSize, length, params);
}

GLint glGetProgramResourceLocation (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramResourceLocation (program, programInterface, name);
}

GLint glGetProgramResourceLocationIndex (GLuint program, GLenum programInterface, const GLchar *name){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetProgramResourceLocationIndex (program, programInterface, name);
}

void glShaderStorageBlockBinding (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglShaderStorageBlockBinding (program, storageBlockIndex, storageBlockBinding);
}

void glTexBufferRange (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexBufferRange (target, internalformat, buffer, offset, size);
}

void glTexStorage2DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexStorage2DMultisample (target, samples, internalformat, width, height, fixedsamplelocations);
}

void glTexStorage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTexStorage3DMultisample (target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void glTextureView (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureView (texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

void glBindVertexBuffer (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindVertexBuffer (bindingindex, buffer, offset, stride);
}

void glVertexAttribFormat (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribFormat (attribindex, size, type, normalized, relativeoffset);
}

void glVertexAttribIFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribIFormat (attribindex, size, type, relativeoffset);
}

void glVertexAttribLFormat (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribLFormat (attribindex, size, type, relativeoffset);
}

void glVertexAttribBinding (GLuint attribindex, GLuint bindingindex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexAttribBinding (attribindex, bindingindex);
}

void glVertexBindingDivisor (GLuint bindingindex, GLuint divisor){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexBindingDivisor (bindingindex, divisor);
}

void glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDebugMessageControl (source, type, severity, count, ids, enabled);
}

void glDebugMessageInsert (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDebugMessageInsert (source, type, id, severity, length, buf);
}

void glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDebugMessageCallback (callback, userParam);
}

GLuint glGetDebugMessageLog (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetDebugMessageLog (count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

void glPushDebugGroup (GLenum source, GLuint id, GLsizei length, const GLchar *message){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPushDebugGroup (source, id, length, message);
}

void glPopDebugGroup (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPopDebugGroup (void);
}

void glObjectLabel (GLenum identifier, GLuint name, GLsizei length, const GLchar *label){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglObjectLabel (identifier, name, length, label);
}

void glGetObjectLabel (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetObjectLabel (identifier, name, bufSize, length, label);
}

void glObjectPtrLabel (const void *ptr, GLsizei length, const GLchar *label){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglObjectPtrLabel (ptr, length, label);
}

void glGetObjectPtrLabel (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetObjectPtrLabel (ptr, bufSize, length, label);
}




// GL_VERSION_4_4

void glBufferStorage (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBufferStorage (target, size, data, flags);
}

void glClearTexImage (GLuint texture, GLint level, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearTexImage (texture, level, format, type, data);
}

void glClearTexSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearTexSubImage (texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
}

void glBindBuffersBase (GLenum target, GLuint first, GLsizei count, const GLuint *buffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindBuffersBase (target, first, count, buffers);
}

void glBindBuffersRange (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindBuffersRange (target, first, count, buffers, offsets, sizes);
}

void glBindTextures (GLuint first, GLsizei count, const GLuint *textures){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindTextures (first, count, textures);
}

void glBindSamplers (GLuint first, GLsizei count, const GLuint *samplers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindSamplers (first, count, samplers);
}

void glBindImageTextures (GLuint first, GLsizei count, const GLuint *textures){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindImageTextures (first, count, textures);
}

void glBindVertexBuffers (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindVertexBuffers (first, count, buffers, offsets, strides);
}




// GL_VERSION_4_5

void glClipControl (GLenum origin, GLenum depth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClipControl (origin, depth);
}

void glCreateTransformFeedbacks (GLsizei n, GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateTransformFeedbacks (n, ids);
}

void glTransformFeedbackBufferBase (GLuint xfb, GLuint index, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTransformFeedbackBufferBase (xfb, index, buffer);
}

void glTransformFeedbackBufferRange (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTransformFeedbackBufferRange (xfb, index, buffer, offset, size);
}

void glGetTransformFeedbackiv (GLuint xfb, GLenum pname, GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTransformFeedbackiv (xfb, pname, param);
}

void glGetTransformFeedbacki_v (GLuint xfb, GLenum pname, GLuint index, GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTransformFeedbacki_v (xfb, pname, index, param);
}

void glGetTransformFeedbacki64_v (GLuint xfb, GLenum pname, GLuint index, GLint64 *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTransformFeedbacki64_v (xfb, pname, index, param);
}

void glCreateBuffers (GLsizei n, GLuint *buffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateBuffers (n, buffers);
}

void glNamedBufferStorage (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedBufferStorage (buffer, size, data, flags);
}

void glNamedBufferData (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedBufferData (buffer, size, data, usage);
}

void glNamedBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedBufferSubData (buffer, offset, size, data);
}

void glCopyNamedBufferSubData (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyNamedBufferSubData (readBuffer, writeBuffer, readOffset, writeOffset, size);
}

void glClearNamedBufferData (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedBufferData (buffer, internalformat, format, type, data);
}

void glClearNamedBufferSubData (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedBufferSubData (buffer, internalformat, offset, size, format, type, data);
}

void *glMapNamedBuffer (GLuint buffer, GLenum access){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMapNamedBuffer (buffer, access);
}

void *glMapNamedBufferRange (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMapNamedBufferRange (buffer, offset, length, access);
}

GLboolean glUnmapNamedBuffer (GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglUnmapNamedBuffer (buffer);
}

void glFlushMappedNamedBufferRange (GLuint buffer, GLintptr offset, GLsizeiptr length){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglFlushMappedNamedBufferRange (buffer, offset, length);
}

void glGetNamedBufferParameteriv (GLuint buffer, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedBufferParameteriv (buffer, pname, params);
}

void glGetNamedBufferParameteri64v (GLuint buffer, GLenum pname, GLint64 *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedBufferParameteri64v (buffer, pname, params);
}

void glGetNamedBufferPointerv (GLuint buffer, GLenum pname, void **params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedBufferPointerv (buffer, pname, params);
}

void glGetNamedBufferSubData (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedBufferSubData (buffer, offset, size, data);
}

void glCreateFramebuffers (GLsizei n, GLuint *framebuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateFramebuffers (n, framebuffers);
}

void glNamedFramebufferRenderbuffer (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferRenderbuffer (framebuffer, attachment, renderbuffertarget, renderbuffer);
}

void glNamedFramebufferParameteri (GLuint framebuffer, GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferParameteri (framebuffer, pname, param);
}

void glNamedFramebufferTexture (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferTexture (framebuffer, attachment, texture, level);
}

void glNamedFramebufferTextureLayer (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferTextureLayer (framebuffer, attachment, texture, level, layer);
}

void glNamedFramebufferDrawBuffer (GLuint framebuffer, GLenum buf){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferDrawBuffer (framebuffer, buf);
}

void glNamedFramebufferDrawBuffers (GLuint framebuffer, GLsizei n, const GLenum *bufs){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferDrawBuffers (framebuffer, n, bufs);
}

void glNamedFramebufferReadBuffer (GLuint framebuffer, GLenum src){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedFramebufferReadBuffer (framebuffer, src);
}

void glInvalidateNamedFramebufferData (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateNamedFramebufferData (framebuffer, numAttachments, attachments);
}

void glInvalidateNamedFramebufferSubData (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglInvalidateNamedFramebufferSubData (framebuffer, numAttachments, attachments, x, y, width, height);
}

void glClearNamedFramebufferiv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedFramebufferiv (framebuffer, buffer, drawbuffer, value);
}

void glClearNamedFramebufferuiv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedFramebufferuiv (framebuffer, buffer, drawbuffer, value);
}

void glClearNamedFramebufferfv (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedFramebufferfv (framebuffer, buffer, drawbuffer, value);
}

void glClearNamedFramebufferfi (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglClearNamedFramebufferfi (framebuffer, buffer, drawbuffer, depth, stencil);
}

void glBlitNamedFramebuffer (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBlitNamedFramebuffer (readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

GLenum glCheckNamedFramebufferStatus (GLuint framebuffer, GLenum target){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCheckNamedFramebufferStatus (framebuffer, target);
}

void glGetNamedFramebufferParameteriv (GLuint framebuffer, GLenum pname, GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedFramebufferParameteriv (framebuffer, pname, param);
}

void glGetNamedFramebufferAttachmentParameteriv (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedFramebufferAttachmentParameteriv (framebuffer, attachment, pname, params);
}

void glCreateRenderbuffers (GLsizei n, GLuint *renderbuffers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateRenderbuffers (n, renderbuffers);
}

void glNamedRenderbufferStorage (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedRenderbufferStorage (renderbuffer, internalformat, width, height);
}

void glNamedRenderbufferStorageMultisample (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglNamedRenderbufferStorageMultisample (renderbuffer, samples, internalformat, width, height);
}

void glGetNamedRenderbufferParameteriv (GLuint renderbuffer, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetNamedRenderbufferParameteriv (renderbuffer, pname, params);
}

void glCreateTextures (GLenum target, GLsizei n, GLuint *textures){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateTextures (target, n, textures);
}

void glTextureBuffer (GLuint texture, GLenum internalformat, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureBuffer (texture, internalformat, buffer);
}

void glTextureBufferRange (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureBufferRange (texture, internalformat, buffer, offset, size);
}

void glTextureStorage1D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureStorage1D (texture, levels, internalformat, width);
}

void glTextureStorage2D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureStorage2D (texture, levels, internalformat, width, height);
}

void glTextureStorage3D (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureStorage3D (texture, levels, internalformat, width, height, depth);
}

void glTextureStorage2DMultisample (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureStorage2DMultisample (texture, samples, internalformat, width, height, fixedsamplelocations);
}

void glTextureStorage3DMultisample (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureStorage3DMultisample (texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void glTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureSubImage1D (texture, level, xoffset, width, format, type, pixels);
}

void glTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureSubImage2D (texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

void glTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureSubImage3D (texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void glCompressedTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTextureSubImage1D (texture, level, xoffset, width, format, imageSize, data);
}

void glCompressedTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTextureSubImage2D (texture, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void glCompressedTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCompressedTextureSubImage3D (texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void glCopyTextureSubImage1D (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTextureSubImage1D (texture, level, xoffset, x, y, width);
}

void glCopyTextureSubImage2D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTextureSubImage2D (texture, level, xoffset, yoffset, x, y, width, height);
}

void glCopyTextureSubImage3D (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCopyTextureSubImage3D (texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void glTextureParameterf (GLuint texture, GLenum pname, GLfloat param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameterf (texture, pname, param);
}

void glTextureParameterfv (GLuint texture, GLenum pname, const GLfloat *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameterfv (texture, pname, param);
}

void glTextureParameteri (GLuint texture, GLenum pname, GLint param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameteri (texture, pname, param);
}

void glTextureParameterIiv (GLuint texture, GLenum pname, const GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameterIiv (texture, pname, params);
}

void glTextureParameterIuiv (GLuint texture, GLenum pname, const GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameterIuiv (texture, pname, params);
}

void glTextureParameteriv (GLuint texture, GLenum pname, const GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureParameteriv (texture, pname, param);
}

void glGenerateTextureMipmap (GLuint texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGenerateTextureMipmap (texture);
}

void glBindTextureUnit (GLuint unit, GLuint texture){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglBindTextureUnit (unit, texture);
}

void glGetTextureImage (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureImage (texture, level, format, type, bufSize, pixels);
}

void glGetCompressedTextureImage (GLuint texture, GLint level, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetCompressedTextureImage (texture, level, bufSize, pixels);
}

void glGetTextureLevelParameterfv (GLuint texture, GLint level, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureLevelParameterfv (texture, level, pname, params);
}

void glGetTextureLevelParameteriv (GLuint texture, GLint level, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureLevelParameteriv (texture, level, pname, params);
}

void glGetTextureParameterfv (GLuint texture, GLenum pname, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureParameterfv (texture, pname, params);
}

void glGetTextureParameterIiv (GLuint texture, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureParameterIiv (texture, pname, params);
}

void glGetTextureParameterIuiv (GLuint texture, GLenum pname, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureParameterIuiv (texture, pname, params);
}

void glGetTextureParameteriv (GLuint texture, GLenum pname, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureParameteriv (texture, pname, params);
}

void glCreateVertexArrays (GLsizei n, GLuint *arrays){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateVertexArrays (n, arrays);
}

void glDisableVertexArrayAttrib (GLuint vaobj, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglDisableVertexArrayAttrib (vaobj, index);
}

void glEnableVertexArrayAttrib (GLuint vaobj, GLuint index){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglEnableVertexArrayAttrib (vaobj, index);
}

void glVertexArrayElementBuffer (GLuint vaobj, GLuint buffer){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayElementBuffer (vaobj, buffer);
}

void glVertexArrayVertexBuffer (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayVertexBuffer (vaobj, bindingindex, buffer, offset, stride);
}

void glVertexArrayVertexBuffers (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayVertexBuffers (vaobj, first, count, buffers, offsets, strides);
}

void glVertexArrayAttribBinding (GLuint vaobj, GLuint attribindex, GLuint bindingindex){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayAttribBinding (vaobj, attribindex, bindingindex);
}

void glVertexArrayAttribFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayAttribFormat (vaobj, attribindex, size, type, normalized, relativeoffset);
}

void glVertexArrayAttribIFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayAttribIFormat (vaobj, attribindex, size, type, relativeoffset);
}

void glVertexArrayAttribLFormat (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayAttribLFormat (vaobj, attribindex, size, type, relativeoffset);
}

void glVertexArrayBindingDivisor (GLuint vaobj, GLuint bindingindex, GLuint divisor){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglVertexArrayBindingDivisor (vaobj, bindingindex, divisor);
}

void glGetVertexArrayiv (GLuint vaobj, GLenum pname, GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexArrayiv (vaobj, pname, param);
}

void glGetVertexArrayIndexediv (GLuint vaobj, GLuint index, GLenum pname, GLint *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexArrayIndexediv (vaobj, index, pname, param);
}

void glGetVertexArrayIndexed64iv (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetVertexArrayIndexed64iv (vaobj, index, pname, param);
}

void glCreateSamplers (GLsizei n, GLuint *samplers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateSamplers (n, samplers);
}

void glCreateProgramPipelines (GLsizei n, GLuint *pipelines){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateProgramPipelines (n, pipelines);
}

void glCreateQueries (GLenum target, GLsizei n, GLuint *ids){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglCreateQueries (target, n, ids);
}

void glGetQueryBufferObjecti64v (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryBufferObjecti64v (id, buffer, pname, offset);
}

void glGetQueryBufferObjectiv (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryBufferObjectiv (id, buffer, pname, offset);
}

void glGetQueryBufferObjectui64v (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryBufferObjectui64v (id, buffer, pname, offset);
}

void glGetQueryBufferObjectuiv (GLuint id, GLuint buffer, GLenum pname, GLintptr offset){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetQueryBufferObjectuiv (id, buffer, pname, offset);
}

void glMemoryBarrierByRegion (GLbitfield barriers){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMemoryBarrierByRegion (barriers);
}

void glGetTextureSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetTextureSubImage (texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}

void glGetCompressedTextureSubImage (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetCompressedTextureSubImage (texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

GLenum glGetGraphicsResetStatus (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetGraphicsResetStatus (void);
}

void glGetnCompressedTexImage (GLenum target, GLint lod, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnCompressedTexImage (target, lod, bufSize, pixels);
}

void glGetnTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnTexImage (target, level, format, type, bufSize, pixels);
}

void glGetnUniformdv (GLuint program, GLint location, GLsizei bufSize, GLdouble *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnUniformdv (program, location, bufSize, params);
}

void glGetnUniformfv (GLuint program, GLint location, GLsizei bufSize, GLfloat *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnUniformfv (program, location, bufSize, params);
}

void glGetnUniformiv (GLuint program, GLint location, GLsizei bufSize, GLint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnUniformiv (program, location, bufSize, params);
}

void glGetnUniformuiv (GLuint program, GLint location, GLsizei bufSize, GLuint *params){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglGetnUniformuiv (program, location, bufSize, params);
}

void glReadnPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglReadnPixels (x, y, width, height, format, type, bufSize, data);
}

void glTextureBarrier (void){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglTextureBarrier (void);
}




// GL_VERSION_4_6

void glSpecializeShader (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglSpecializeShader (shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
}

void glMultiDrawArraysIndirectCount (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawArraysIndirectCount (mode, indirect, drawcount, maxdrawcount, stride);
}

void glMultiDrawElementsIndirectCount (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglMultiDrawElementsIndirectCount (mode, type, indirect, drawcount, maxdrawcount, stride);
}

void glPolygonOffsetClamp (GLfloat factor, GLfloat units, GLfloat clamp){
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);

    return OpenGL::vkglPolygonOffsetClamp (factor, units, clamp);
}




*/


