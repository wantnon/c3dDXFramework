

#include "c3dCamera.h"


Cc3dMatrix4 Cc3dCamera::calculateViewMat()const {


    Cc3dMatrix4 ret;

    ret=::calculateViewMatrix(m_pos, m_center, m_up);


    return ret;

    

};
Cc3dMatrix4 Cc3dCamera::calculateViewMat_dx()const {


    Cc3dMatrix4 ret;

    ret=::calculateViewMatrix_dx_colMajor(m_pos, m_center, m_up);


    return ret;

    

};

Cc3dMatrix4 Cc3dCamera::calculateViewMatInverse()const {

    Cc3dMatrix4 ret;


     ret=::calculateViewMatrixInverse(m_pos, m_center, m_up);

 

    return ret;

}

Cc3dMatrix4 Cc3dCamera::calculateProjectionMat()const {

    Cc3dMatrix4 projectionMat;

    switch (m_projectionMode) {

        case ec3dPerspectiveMode:

            projectionMat=::calculatePerspectiveProjectionMatrix(m_fovy, m_aspect, m_zNear, m_zFar);

            break;

        case ec3dOrthographicMode:

            projectionMat=::calculateOrthoProjectionMatrix(m_xmin, m_xmax, m_ymin, m_ymax, m_zNear, m_zFar);

            break;

        default:

            assert(false);

            break;

    }

    return projectionMat;

}

Cc3dMatrix4 Cc3dCamera::calculateViewportMat_dx()const{
	const float x=m_viewport.x();
	const float y=m_viewport.y();
	const float w=m_viewport.z();
	const float h=m_viewport.w();
	Cc3dMatrix4 viewportMat=::calculateViewportMatrix_dx_colMajor(x,y,w,h);
	return viewportMat;
}
Cc3dVector4 Cc3dCamera::unProjectPointFromScreenSpaceToWorldSpace_dx(const Cc3dVector4&posInScreenSpace)const{
	assert(posInScreenSpace.w()==1);
	const Cc3dMatrix4&projMat=calculateProjectionMat_dx();
	const Cc3dMatrix4&viewMat=calculateViewMat_dx();
	const Cc3dMatrix4&viewportMat=calculateViewportMat_dx();
	Cc3dMatrix4 invMat=inverse(viewportMat*projMat*viewMat);
	Cc3dVector4 posInWorldSpace=invMat*posInScreenSpace;
	posInWorldSpace.persDiv();
	return posInWorldSpace;
}
Cc3dVector4 Cc3dCamera::unProjectPointFromScreenSpaceToCameraSpace_dx(const Cc3dVector4&posInScreenSpace)const{
	assert(posInScreenSpace.w()==1);
	const Cc3dMatrix4&projMat=calculateProjectionMat_dx();
	const Cc3dMatrix4&viewMat=calculateViewMat_dx();
	const Cc3dMatrix4&viewportMat=calculateViewportMat_dx();
	Cc3dMatrix4 invMat=inverse(viewportMat*projMat);
	Cc3dVector4 posInCameraSpace=invMat*posInScreenSpace;
	posInCameraSpace.persDiv();
	return posInCameraSpace;
}
Cc3dMatrix4 Cc3dCamera::calculateProjectionMat_dx()const {

    Cc3dMatrix4 projectionMat;

    switch (m_projectionMode) {

        case ec3dPerspectiveMode:

            projectionMat=::calculatePerspectiveProjectionMatrix_dx_colMajor(m_fovy, m_aspect, m_zNear, m_zFar);

            break;

        case ec3dOrthographicMode:
			assert(false);//not implemented yet
			//ref: http://blog.csdn.net/zhanghua1816/article/details/23121735
         
            break;

		case ec3dObliquePerspectiveMode:
			
			projectionMat=::calculateObliquePerspectiveProjMat_dx_colMajor(m_xmin,m_xmax,m_ymin,m_ymax,m_zNear,m_zFar);

			break;

        default:

            assert(false);

            break;

    }

    return projectionMat;


}


void Cc3dCamera::rotate(const Cc3dVector4&axis,float cosA,float sinA){
	Cc3dMatrix4 viewMat=calculateViewMat();
	Cc3dMatrix4 modelMatOfCamera=inverse(viewMat);
	Cc3dMatrix4 rotMat=calculateRotationMatrix(axis,cosA,sinA);
	Cc3dMatrix4 newModelMatOfCamera=modelMatOfCamera*rotMat;
	Cc3dVector4 up=cc3dv4(newModelMatOfCamera.getAt(4),newModelMatOfCamera.getAt(5),newModelMatOfCamera.getAt(6),newModelMatOfCamera.getAt(7));
	Cc3dVector4 dir=cc3dv4(newModelMatOfCamera.getAt(8),newModelMatOfCamera.getAt(9),newModelMatOfCamera.getAt(10),newModelMatOfCamera.getAt(11))*(-1);
	Cc3dVector4 eyepos=cc3dv4(newModelMatOfCamera.getAt(12),newModelMatOfCamera.getAt(13),newModelMatOfCamera.getAt(14),newModelMatOfCamera.getAt(15));
	up.setw(0);
	dir.setw(0);
	eyepos.setw(1);
	//update camera
	m_pos=eyepos;
	m_center=m_pos+dir;
	m_up=up;

}