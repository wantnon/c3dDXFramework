#ifndef _c3dScene_H_
#define _c3dScene_H_
#include "c3dNode.h"
#include "c3dCamera.h"
#include "c3dTextureCache.h"
#include "c3dLightSource.h"
#include "c3dMaterialManager.h"

class Cc3dScene{
public:
	Cc3dScene(){
		m_root=NULL;
		m_camera=NULL;
		m_lightSource=NULL;
	}
	virtual~Cc3dScene(){
		if(m_root)delete m_root;
		if(m_camera)delete m_camera;
		if(m_lightSource)delete m_lightSource;
	}
	void clean(){
		delete m_root;
		m_root=new Cc3dNode();
		m_root->m_isAddedToScene=true;
	}
	void render(){
		//visit update
		m_root->visitUpdate();//world marix have cached in nodes
		//draw all materials
		Cc3dMaterialManager::getInstance()->render();
	}
	void init(){
		m_root=new Cc3dNode();
		m_root->m_name="GameRoot";
		m_root->m_isAddedToScene=true;
		m_camera=new Cc3dCamera();
		m_lightSource=new Cc3dLightSource();
	}
	static Cc3dScene*getInstance();
	
public:
	Cc3dNode*m_root;//root node of the scene
	Cc3dCamera*m_camera;
	Cc3dLightSource*m_lightSource;//currently only support one lightSource, need improvement
};

#endif