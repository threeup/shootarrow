#include "GLUtils.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>

GLUtils::GLUtils()
{
}


GLUtils::~GLUtils()
{
}

GLuint GLUtils::CreateSimpleTexture2D()
{
	// Texture object handle
	GLuint textureId;

	// 2x2 Image, 3 bytes per pixel (R, G, B)
	GLubyte pixels[4 * 3] =
	{
		255, 0, 0, // Red
		0, 255, 0, // Green
		0, 0, 255, // Blue
		255, 255, 0  // Yellow
	};

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return textureId;

}

GLuint GLUtils::LoadTexture(std::string fileName)
{
	int width,
		height;
	char *buffer = ESUtil::LoadTGA(fileName.c_str(), &width, &height);
	GLuint texId;

	if (buffer == NULL)
	{
		ESUtil::LogMessage("Error loading (%s) image.\n", fileName.c_str());
		return 0;
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	delete buffer;

	return texId;
}

GLuint GLUtils::LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			//esLogMessage("Error compiling shader:\n%s\n", infoLog);

			//free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}