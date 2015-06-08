#pragma once

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>
#include "../lib/GLFramework/ESUtil.h"

class GLUtils
{
public:
	GLUtils();
	~GLUtils();

	static GLuint LoadShader(GLenum type, const char *shaderSrc);
	static GLuint CreateSimpleTexture2D();
	static GLuint LoadTexture(std::string fileName);
};
