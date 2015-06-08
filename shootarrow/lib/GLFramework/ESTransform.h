#ifndef ESTRANSFORM__H__
#define ESTRANSFORM__H__

#include "ESCommon.h"

class ESTransform
{
public:
    /*
     * \brief multiply matrix specified by result with a scaling matrix and return new matrix in result
     * \param result Specifies the input matrix.  Scaled matrix is returned in result.
     * \param sx, sy, sz Scale factors along the x, y and z axes respectively
     */
    void Scale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);

    /*
     * \brief multiply matrix specified by result with a translation matrix and return new matrix in result
     * \param result Specifies the input matrix.  Translated matrix is returned in result.
     * \param tx, ty, tz Scale factors along the x, y and z axes respectively
     */
    void Translate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);

    /*
     * \brief multiply matrix specified by result with a rotation matrix and return new matrix in result
     * \param result Specifies the input matrix.  Rotated matrix is returned in result.
     * \param angle Specifies the angle of rotation, in degrees.
     * \param x, y, z Specify the x, y and z coordinates of a vector, respectively
     */
    void Rotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

    /*
     * \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
     * \param result Specifies the input matrix.  new matrix is returned in result.
     * \param left, right Coordinates for the left and right vertical clipping planes
     * \param bottom, top Coordinates for the bottom and top horizontal clipping planes
     * \param nearZ, farZ Distances to the near and far depth clipping planes.  Both distances must be positive.
     */
    void Frustum(ESMatrix *result, GLfloat left, GLfloat right, GLfloat bottom,
                   GLfloat top, GLfloat nearZ, GLfloat farZ);

    /*
     * \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
     * \param result Specifies the input matrix.  new matrix is returned in result.
     * \param fovy Field of view y angle in degrees
     * \param aspect Aspect ratio of screen
     * \param nearZ Near plane distance
     * \param farZ Far plane distance
     */
    void Perspective(ESMatrix *result, GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ);

    /*
     * \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
     * \param result Specifies the input matrix.  new matrix is returned in result.
     * \param left, right Coordinates for the left and right vertical clipping planes
     * \param bottom, top Coordinates for the bottom and top horizontal clipping planes
     * \param nearZ, farZ Distances to the near and far depth clipping planes.  These values are negative if plane is behind the viewer
     */
    void Ortho(ESMatrix *result, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top,
                 GLfloat nearZ, GLfloat farZ);

    /*
     * \brief perform the following operation - result matrix = srcA matrix * srcB matrix
     * \param result Returns multiplied matrix
     * \param srcA, srcB Input matrices to be multiplied
     */
    void MatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);

    /*
     * \brief return an indentity matrix 
     * \param result returns identity matrix
     */
    void MatrixLoadIdentity(ESMatrix *result);
};

#endif //ESTRANSFORM__H__
