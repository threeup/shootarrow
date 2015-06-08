// esUtil_win.h
//
//   API-neutral interface for creating windows.  Implementation needs to be provided per-platform.

#ifndef ESUTIL_WIN_H
#define ESUTIL_WIN_H

#include "ESCommon.h"
	///
	//  WinCreate()
	//
	//      Create Win32 instance and window
	//
	GLboolean WinCreate(ESContext *esContext, const char *title);

	///
	//  WinLoop()
	//
	//      Start main windows loop
	//
	void WinLoop(ESContext *esContext);

	///
	//  WinTGALoad()
	//    
	//      TGA loader win32 implementation
	//
	//int WinTGALoad(const char *fileName, char **buffer, int *width, int *height);

#endif // ESUTIL_WIN_H