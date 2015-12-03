

#ifndef __HelloCpp__c3dCamera__
#define __HelloCpp__c3dCamera__


#include <iostream>
using namespace std;
#include "c3dGLMath.h"


enum ec3dCameraProjMode{
    ec3dOrthographicMode = 0,
    ec3dPerspectiveMode,
	ec3dObliquePerspectiveMode,
};
class Cc3dCamera
{
public:

    Cc3dCamera(){}
	void init(const Cc3dVector4&viewport){
		m_viewport=viewport;
		const float w=viewport.z();
		const float h=viewport.w();

		m_fovy=60;
        m_aspect=w/h;
        m_zNear=0.5;
        m_zFar=150;//1500;

	    m_ymin=-1;
	    m_ymax=1;
		m_xmin=-1*m_aspect;
	    m_xmax=1*m_aspect;

        m_projectionMode=ec3dPerspectiveMode;

		m_up=cc3dv4(0,1,0,0);
	}

    virtual ~Cc3dCamera(){}
    Cc3dMatrix4 calculateViewMat()const;
	Cc3dMatrix4 calculateViewMat_dx()const;
    Cc3dMatrix4 calculateViewMatInverse()const;
    Cc3dMatrix4 calculateProjectionMat()const;
    Cc3dMatrix4 calculateProjectionMat_dx()const;
	Cc3dMatrix4 calculateViewportMat_dx()const;
	Cc3dVector4 unProjectPointFromScreenSpaceToWorldSpace_dx(const Cc3dVector4&posInScreenSpace)const;
	Cc3dVector4 unProjectPointFromScreenSpaceToCameraSpace_dx(const Cc3dVector4&posInScreenSpace)const;
	void rotate(const Cc3dVector4&axis,float cosA,float sinA);
public:
    ec3dCameraProjMode m_projectionMode;
    float m_fovy;
    float m_aspect;
    float m_zNear;
    float m_zFar;
public://camera space range for OrthographicMode and ObliquePerspectiveMode
	float m_xmin;
	float m_xmax;
	float m_ymin;
	float m_ymax;
public:
	Cc3dVector4 m_center;
	Cc3dVector4 m_up;
	Cc3dVector4 m_pos;
	Cc3dVector4 m_viewport;//note, dx'viewport is OAtLU, opengl's viewport is OAtLD
};

#endif /* defined(__HelloCpp__c3dCamera__) */
