#ifndef ESCOMMON__H__
#define ESCOMMON__H__

#include <GLES2/gl2.h>
#include <EGL/egl.h>

/*
 *  Macros
 */
#define ESCALLBACK
#define ESEXPORT __attribute__((visibility ("default")))
#define PI (3.1415926535897932384626433832795f)

/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2 
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

#ifndef FALSE
#   define FALSE 0
#endif
#ifndef TRUE
#   define TRUE 1
#endif

struct ESMatrix
{
    GLfloat   m[4][4];
};

struct ESContext
{
   /// Put your user data here...
   void*       userData;

   /// Window width
   GLint       width;

   /// Window height
   GLint       height;

   /// Window handle
   EGLNativeWindowType  hWnd;

   /// EGL display
   EGLDisplay  eglDisplay;
      
   /// EGL context
   EGLContext  eglContext;

   /// EGL surface
   EGLSurface  eglSurface;

   /// Callbacks
   void (ESCALLBACK *drawFunc)(ESContext *);
   void (ESCALLBACK *keyFunc)(ESContext *, unsigned char, int, int);
   void (ESCALLBACK *updateFunc)(ESContext *, float deltaTime);
};

#endif //ESCOMMON__H__
