#ifndef ESSHADER__H__
#define ESSHADER__H__

#include "ESCommon.h"

class ESShader
{
public:
    /*
     * \brief Load a shader, check for compile errors, print error messages to output log
     * \param type Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
     * \param shaderSrc Shader source string
     * \return A new shader object on success, 0 on failure
     */
    GLuint LoadShader(GLenum type, const char *shaderSrc);

    /*
     * \brief Load a vertex and fragment shader, create a program object, link program.
     *        Errors output to log.
     * \param vertShaderSrc Vertex shader source code
     * \param fragShaderSrc Fragment shader source code
     * \return A new program object linked with the vertex/fragment shader pair, 0 on failure
     */
    GLuint LoadProgram(const char *vertShaderSrc, const char *fragShaderSrc);
};

#endif //ESSHADER__H__
