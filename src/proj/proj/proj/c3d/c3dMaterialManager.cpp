#include "c3dMaterialManager.h"
static Cc3dMaterialManager*s_materialManager=NULL;
Cc3dMaterialManager*Cc3dMaterialManager::getInstance(){
	if(s_materialManager==NULL){
		s_materialManager=new Cc3dMaterialManager();
	}
	return s_materialManager;
}


void Cc3dMaterialManager::render(){
		const int materialCount=m_materialList.size();
		for(int i=0;i<materialCount;i++){
			Cc3dMaterial*material=m_materialList[i];
			material->render();
		}


	}
	void Cc3dMaterialManager::connect(Cc3dIBBase*ib,Cc3dMaterial*material){
		assert(material);
		assert(ib);
		assert(ib->m_materialRef==NULL);
		ib->m_materialRef=material;
		material->m_ibList.push_back(ib);
		
	}
	void Cc3dMaterialManager::disconnect(Cc3dIBBase*ib,Cc3dMaterial*material){
		assert(ib);
		assert(material);
		assert(material==ib->m_materialRef);
		ib->m_materialRef=NULL;
		bool isFind=false;
		const int ibCount=(int)material->m_ibList.size();
		for(int i=0;i<ibCount;i++){
			Cc3dIBBase*_ib=material->m_ibList[i];
			if(_ib==ib){
				isFind=true;
				material->m_ibList.erase(material->m_ibList.begin()+i);
				break;
			}
		}//got isFind
		assert(isFind);
	}