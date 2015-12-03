#ifndef _c3dMaterialManager_H_
#define _c3dMaterialManager_H_
#include <vector>
using namespace std;
#include "c3dNode.h"
#include "c3dMaterial.h"

class Cc3dMaterialManager{
public:
	Cc3dMaterialManager(){
	}
	virtual~Cc3dMaterialManager(){
		
	}
	void render();
	void connect(Cc3dIBBase*ib,Cc3dMaterial*material);//connect material with ib
	void disconnect(Cc3dIBBase*ib,Cc3dMaterial*material);//disconnect material with ib
	
	static Cc3dMaterialManager*getInstance();
public:
	vector<Cc3dMaterial*> m_materialList;
};

#endif