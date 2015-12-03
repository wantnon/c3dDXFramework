
#ifndef __HelloCpp__c3dGLMath__
#define __HelloCpp__c3dGLMath__

//这个文件里很多函数是没用的，还没来得及删。

#include <iostream>
using namespace std;
#include "c3dMath.h"

//OpenGL transform pipline: http://user.qzone.qq.com/350479720/blog/1310060277
//Basic 3D Math: Matrices: http://www.matrix44.net/cms/notes/opengl-3d-graphics/basic-3d-math-matrices
//ref to kmMat4PerspectiveProjection and kmMat4OrthographicProjection

Cc3dMatrix4 calculateViewMatrixInverse(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);
Cc3dMatrix4 calculateViewMatrixInverse_dx_colMajor(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);

Cc3dMatrix4 calculateViewMatrix(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);
Cc3dMatrix4 calculateViewMatrix_dx_colMajor(const Cc3dVector4&eyePos,const Cc3dVector4&center,const Cc3dVector4&up);

Cc3dMatrix4 calculateViewportMatrix_dx_colMajor(float x0,float y0,float w,float h);

Cc3dMatrix4 calculateObliquePerspectiveProjMat_dx_colMajor(float left,float right,float bottom,float top,float near,float far);

Cc3dMatrix4 calculateRotationMatrix(const Cc3dVector4&axis,float cosA,float sinA);

Cc3dMatrix4 calculateTranslateMatrix(const Cc3dVector4&translate);

Cc3dMatrix4 calculateScaleMatrix(float kx,float ky,float kz);



Cc3dMatrix4 calculatePerspectiveProjectionMatrix(float fovy,float aspect,float zNear,float zFar);
Cc3dMatrix4 calculatePerspectiveProjectionMatrix_dx_colMajor(float fovy,float aspect,float zNear,float zFar);
Cc3dMatrix4 calculateOrthoProjectionMatrix(float left,float right,float bottom,float top,float zNear,float zFar);



Cc3dVector4 convertFromScreenSpaceToWorldSpace(const Cc3dVector4&winPos,

                                                 const Cc3dMatrix4&projMat,

                                                 const Cc3dMatrix4&viewMat,

                                                 const float viewport[4]);

bool isLine3dIntersectWithTriangle3d(const Cc3dVector4&start,const Cc3dVector4&dir,

                                     const Cc3dVector4&p0,const Cc3dVector4&p1,const Cc3dVector4&p2);

Cc3dVector4 getIntersectPointOfLine3dIntersectWithPlane3d(const Cc3dVector4&start,const Cc3dVector4&dir,

                                     const Cc3dVector4&p,const Cc3dVector4&norm);

float calculate3dTriangleArea(const Cc3dVector4&v1,const Cc3dVector4&v2,const Cc3dVector4&v3);

#endif /* defined(__HelloCpp__c3dGLMath__) */
