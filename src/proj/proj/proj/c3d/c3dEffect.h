



#ifndef __HelloCpp__c3dEffect__

#define __HelloCpp__c3dEffect__



#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "c3dDX.h"
#include "c3dRCobj.h"
#include "c3dDefine.h"
#include "DXUT.h"
#include "c3dFuncs.h"
#include "c3dTexture.h"
enum eSamplerType{
	eST_texture=0,
};
enum eUnifoType{
	eUT_float=0,
	eUT_float2,
	eUT_float3,
	eUT_float4,
	eUT_float4x4,
};

class Cc3dSampler{
public:
	Cc3dSampler(){
		m_type=eST_texture;
		m_textureRef=NULL;
	}
public:
	string m_name;
	eSamplerType m_type; 
	Cc3dTexture*m_textureRef;

};

class Cc3dUniform{

public:
	Cc3dUniform(){
		m_inited=false;
		m_isDirty=false;
		m_inited=false;
		m_type=(eUnifoType)0;
	}

	
	float getFloat()const ;
	Cc3dVector2 getV2()const ;
	Cc3dVector3 getV3()const ;
	Cc3dVector4 getV4()const ;
	Cc3dMatrix4 getM4()const ;
	void set(float x);
	void set(const Cc3dVector2&v);
	void set(const Cc3dVector3&v);
	void set(const Cc3dVector4&v);
	void set(const Cc3dMatrix4&m);
	
public:
	string m_name;
	eUnifoType m_type; 
	bool m_isDirty;
	bool m_inited;
	vector<float> m_floatList;
	vector<bool> m_boolList;
	vector<int> m_intList;


};

//effect (or shader program) is not shared between materials, each material holds it's own effect object
class Cc3dEffect
{

public:

    Cc3dEffect(){
		m_pEffect = NULL;
    }

    virtual~Cc3dEffect(){
		if( m_pEffect != NULL )m_pEffect->Release();
    }
	void initWithFile(const string&effectFileName,const string&effectVarFileName);
	void setUniform(const string&unifoName,float x);
	void setUniform(const string&unifoName,const Cc3dVector2&v2);
	void setUniform(const string&unifoName,const Cc3dVector3&v3);
	void setUniform(const string&unifoName,const Cc3dVector4&v4);
	void setUniform(const string&unifoName,const Cc3dMatrix4&m4);
	void setSampler(const string&samplerName,Cc3dTexture*texture);
	Cc3dSampler*getpSamplerByName(const string&samplerName);
	Cc3dUniform*getpUnifomByName(const string&unifoName);
	void applyAllDirtyUniforms();
protected:
	void applyUniformIfDirty(Cc3dUniform&unifo);
	void applyUniform(const Cc3dUniform&unifo);
	void readEffectVarFileAndGenUniformList(const string&fileName);
	eSamplerType strToSamplerType(const string&str);
	eUnifoType strToUnifoType(const string&str);
public:
	string m_fileName;
    ID3DXEffect*                m_pEffect;
	vector<Cc3dUniform> m_uniformList;
	vector<Cc3dSampler> m_samplerList;


};

#endif /* defined(__HelloCpp__c3dEffect__) */
