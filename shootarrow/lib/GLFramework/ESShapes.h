#ifndef ESSHAPES__H__
#define ESSHAPES__H__

#include "ESCommon.h"

class ESShapes
{
public:
    /*
     * \brief Generates geometry for a sphere.  Allocates memory for the vertex data and stores 
     *        the results in the arrays.  Generate index list for a TRIANGLE_STRIP
     * \param numSlices The number of slices in the sphere
     * \param vertices If not NULL, will contain array of float3 positions
     * \param normals If not NULL, will contain array of float3 normals
     * \param texCoords If not NULL, will contain array of float2 texCoords
     * \param indices If not NULL, will contain the array of indices for the triangle strip
     * \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
     *         if it is not NULL ) as a GL_TRIANGLE_STRIP
     */
    static int GenSphere(int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                           GLfloat **texCoords, GLuint **indices);

    /*
     * \brief Generates geometry for a cube.  Allocates memory for the vertex data and stores 
     *        the results in the arrays.  Generate index list for a TRIANGLES
     * \param scale The size of the cube, use 1.0 for a unit cube.
     * \param vertices If not NULL, will contain array of float3 positions
     * \param normals If not NULL, will contain array of float3 normals
     * \param texCoords If not NULL, will contain array of float2 texCoords
     * \param indices If not NULL, will contain the array of indices for the triangle strip
     * \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
     *         if it is not NULL ) as a GL_TRIANGLE_STRIP
     */
    static int GenCube(float scale, GLfloat **vertices, GLfloat **normals,
                         GLfloat **texCoords, GLuint **indices);
};

#endif //ESSHAPES__H__
