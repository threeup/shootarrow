/*
 * ESUtil.c
 *
 *    A utility library for OpenGL ES.  This library provides a
 *    basic common framework for the example applications in the
 *    OpenGL ES 2.0 Programming Guide.
 */

#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "bcm_host.h"
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "ESUtil.h"
#include "ESUtil_win.h"



///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
	EGLContext* eglContext, EGLSurface* eglSurface,
	EGLint attribList[])
{
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
#ifdef _WIN32
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
#endif
#ifdef __unix__
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
#endif
	

	// Get Display
#ifdef __unix__
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif
#ifdef _WIN32
	display = eglGetDisplay(GetDC(hWnd)); 
#endif
	if (display == EGL_NO_DISPLAY)
	{
		return EGL_FALSE;
	}

	// Initialize EGL
	if (!eglInitialize(display, &majorVersion, &minorVersion))
	{
		return EGL_FALSE;
	}

	// Get configs
	if (!eglGetConfigs(display, NULL, 0, &numConfigs))
	{
		return EGL_FALSE;
	}

	// Choose config
	if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
	{
		return EGL_FALSE;
	}

	// Create a surface
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
	if (surface == EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	// Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if (context == EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	}

	// Make the context current
	if (!eglMakeCurrent(display, surface, surface, context))
	{
		return EGL_FALSE;
	}

	*eglDisplay = display;
	*eglSurface = surface;
	*eglContext = context;
	return EGL_TRUE;
}

void ESUtil::InitContext(ESContext *esContext)
{
#ifdef __unix__
   bcm_host_init();
#endif
   if (esContext != NULL) {
      memset(esContext, 0, sizeof(ESContext));
   }
}

GLboolean ESUtil::CreateMainWindow(ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags)
{
   EGLint attribList[] = {
       EGL_RED_SIZE,       5,
       EGL_GREEN_SIZE,     6,
       EGL_BLUE_SIZE,      5,
       EGL_ALPHA_SIZE,     (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
       EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
       EGL_NONE
   };

   if (esContext == NULL) {
      return GL_FALSE;
   }

   esContext->width = width;
   esContext->height = height;

   if(!WinCreate(esContext, title))
   {
	   printf("Unable to create Window");
	   return GL_FALSE;
   }


   if (!CreateEGLContext(esContext->hWnd,
	   &esContext->eglDisplay,
	   &esContext->eglContext,
	   &esContext->eglSurface,
	   attribList))
   {
	   return GL_FALSE;
   }


   return GL_TRUE;
}

void ESUtil::MainLoop(ESContext *esContext)
{
    float deltatime = 1;
    
	
	WinLoop(esContext);
}	

void ESUtil::RegisterDrawFunc(ESContext *esContext, void (ESCALLBACK *drawFunc)(ESContext*))
{
   esContext->drawFunc = drawFunc;
}

void ESUtil::RegisterUpdateFunc(ESContext *esContext, void (ESCALLBACK *updateFunc)(ESContext*, float))
{
   esContext->updateFunc = updateFunc;
}

void ESUtil::RegisterKeyFunc(ESContext *esContext,
                               void (ESCALLBACK *keyFunc)(ESContext*, unsigned char, int, int))
{
   esContext->keyFunc = keyFunc;
}

void ESUtil::LogMessage(const char *formatStr, ...)
{
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);

#ifdef _WIN32
    vsprintf_s(buf, formatStr, params);
#endif
#ifdef __unix__
	vsprintf(buf, formatStr, params);
#endif
    printf("%s", buf);

    va_end(params);
}

char* ESUtil::LoadTGA(const char *fileName, int *width, int *height)
{
    char *buffer = NULL;
    FILE *f;
    unsigned char tgaheader[12];
    unsigned char attributes[6];
    unsigned int imagesize;

#ifdef _WIN32
    fopen_s(&f, fileName, "rb");
#endif
#ifdef __unix__
	f = fopen(fileName, "rb");
#endif
    if (f == NULL) return NULL;

    if (fread(&tgaheader, sizeof(tgaheader), 1, f) == 0) {
        fclose(f);
        return NULL;
    }

    if (fread(attributes, sizeof(attributes), 1, f) == 0) {
        fclose(f);
        return 0;
    }

    *width = attributes[1] * 256 + attributes[0];
    *height = attributes[3] * 256 + attributes[2];
    imagesize = attributes[4] / 8 * (*width) * (*height);
    buffer = (char*)malloc(imagesize);
    if (buffer == NULL) {
        fclose(f);
        return 0;
    }

    if (fread(buffer, 1, imagesize, f) != imagesize) {
        free(buffer);
        return NULL;
    }

    fclose(f);

    return buffer;
}
