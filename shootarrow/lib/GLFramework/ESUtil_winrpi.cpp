#ifdef __unix__ 
#include "bcm_host.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include "ESUtil.h"


///
//  WinCreate()
//
//      Create Win32 instance and window
//
GLboolean WinCreate(ESContext *esContext, const char *title)
{
	int32_t success = 0;

	static EGL_DISPMANX_WINDOW_T nativewindow;

	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;


	uint32_t display_width;
	uint32_t display_height;

	// create an EGL window surface, passing context width/height
	success = graphics_get_display_size(0 /* LCD */, &display_width, &display_height);
	if ( success < 0 )
	{
		printf("x");
		return EGL_FALSE;
	}

	// You can hardcode the resolution here:
	display_width = 640;
	display_height = 480;

	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = display_width;
	dst_rect.height = display_height;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = display_width << 16;
	src_rect.height = display_height << 16;   

	dispman_display = vc_dispmanx_display_open( 0 /* LCD */);
	dispman_update = vc_dispmanx_update_start( 0 );

	dispman_element = vc_dispmanx_element_add ( dispman_update, dispman_display,
		0/*layer*/, &dst_rect, 0/*src*/,
		&src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, DISPMANX_NO_ROTATE);

	nativewindow.element = dispman_element;
	nativewindow.width = display_width;
	nativewindow.height = display_height;
	vc_dispmanx_update_submit_sync( dispman_update );

	esContext->hWnd = &nativewindow;

	return EGL_TRUE;
}

GLboolean userInterrupt(ESContext *esContext)
{   
	return GL_FALSE;
}


///
//  winLoop()
//
//      Start main windows loop
//
void WinLoop(ESContext *esContext)
{
	struct timeval t1, t2;
	struct timezone tz;
	float deltatime;
	float totaltime = 0.0f;
	unsigned int frames = 0;

	gettimeofday ( &t1 , &tz );

	while(userInterrupt(esContext) == GL_FALSE)
	{
		gettimeofday(&t2, &tz);
		deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
		t1 = t2;

		if (esContext->updateFunc != NULL)
			esContext->updateFunc(esContext, deltatime);
		if (esContext->drawFunc != NULL)
			esContext->drawFunc(esContext);

		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

		totaltime += deltatime;
		frames++;
		if (totaltime >  2.0f)
		{
			printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
			totaltime -= 2.0f;
			frames = 0;
		}
	}
}
#endif