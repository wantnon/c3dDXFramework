

#ifndef __HelloCpp__c3dMaterial_H_
#define __HelloCpp__c3dMaterial_H_


#include <iostream>
#include <string>
#include <functional>
using namespace std;

#include "c3dMath.h"
#include "c3dEffect.h"
#include "c3dTexture.h"
#include "c3dDX.h"
#include "c3dIBBase.h"
#include "c3dVB.h"
class Cc3dMaterial
{
public:
    Cc3dMaterial(){
		m_effect=NULL;
		m_effectTechnique="basicTech";
       
		m_onRenderEnter=nullptr;
		m_onRenderLeave=nullptr;
    }

 
	virtual~Cc3dMaterial(){
		const int textureCount=(int)m_textureList.size();
		for(int i=0;i<textureCount;i++){
			m_textureList[i]->release();
		}
		if(m_effect)delete m_effect;


    }
	void initWithEffectFile(const string&effectFileName,const string&effectVarFileName);
	void addTexture(Cc3dTexture*p);
	void setTexture(int index,Cc3dTexture*p);
	void render();
public:
	vector<Cc3dTexture*> m_textureList;//one material may have multi textures
	Cc3dEffect*m_effect;//shader program
	string m_effectTechnique;

	vector<Cc3dIBBase*> m_ibList;//ibs who render with this material

	std::function<void ()> m_onRenderEnter;//call back func implement by user, when start render this material, use it to set render states
	std::function<void ()> m_onRenderLeave;//call back func implement by user, when end render this material, use it to recover render states
	
};

#endif 
