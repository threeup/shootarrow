/*
 * \file ESUtil.h
 * \brief A utility library for OpenGL ES.  This library provides a
 *        basic common framework for the example applications in the
 *        OpenGL ES 2.0 Programming Guide.
 */

#ifndef ESUTIL__H__
#define ESUTIL__H__

#include "ESCommon.h"

class ESUtil
{
public:
    /*
     * \brief Initialize ES framework context.  This must be called before calling any other functions.
     * \param esContext Application context
     */
    void InitContext(ESContext *esContext);

    /*
     * \brief Create a window with the specified parameters
     * \param esContext Application context
     * \param title Name for title bar of window
     * \param width Width in pixels of window to create
     * \param height Height in pixels of window to create
     * \param flags Bitfield for the window creation flags 
     *         ES_WINDOW_RGB     - specifies that the color buffer should have R,G,B channels
     *         ES_WINDOW_ALPHA   - specifies that the color buffer should have alpha
     *         ES_WINDOW_DEPTH   - specifies that a depth buffer should be created
     *         ES_WINDOW_STENCIL - specifies that a stencil buffer should be created
     *         ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
     * \return GL_TRUE if window creation is succesful, GL_FALSE otherwise
     */
    GLboolean CreateMainWindow(ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags);

    /*
     * \brief Start the main loop for the OpenGL ES application
     * \param esContext Application context
     */
    void MainLoop(ESContext *esContext);

    /*
     * \brief Register a draw callback function to be used to render each frame
     * \param esContext Application context
     * \param drawFunc Draw callback function that will be used to render the scene
     */
    void RegisterDrawFunc(ESContext *esContext, void (ESCALLBACK *drawFunc)(ESContext*));

    /*
     * \brief Register an update callback function to be used to update on each time step
     * \param esContext Application context
     * \param updateFunc Update callback function that will be used to render the scene
     */
    void RegisterUpdateFunc(ESContext *esContext, void (ESCALLBACK *updateFunc)(ESContext*, float));

    /*
     * \brief Register an keyboard input processing callback function
     * \param esContext Application context
     * \param keyFunc Key callback function for application processing of keyboard input
     */
    void RegisterKeyFunc(ESContext *esContext,
                           void (ESCALLBACK *drawFunc)(ESContext*, unsigned char, int, int));

    /*
     * \brief Log a message to the debug output for the platform
     * \param formatStr Format string for error log.  
     */
    static void LogMessage(const char *formatStr, ...);

    /*
     * \brief Loads a 24-bit TGA image from a file
     * \param fileName Name of the file on disk
     * \param width Width of loaded image in pixels
     * \param height Height of loaded image in pixels
     *  \return Pointer to loaded image.  NULL on failure. 
     */
    static char* LoadTGA(const char *fileName, int *width, int *height);
};

#endif // ESUTIL__H__
