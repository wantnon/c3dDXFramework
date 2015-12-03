

#ifndef __HelloCpp__c3dTexture__
#define __HelloCpp__c3dTexture__



#include <iostream>
#include <string>
using namespace std;


#include "c3dDefine.h"
#include "c3dDX.h"
#include "c3dRCobj.h"
//texture is reference-counting object, can be shared between materials
class Cc3dTexture:public Cc3dRCobj
{
public:
    Cc3dTexture(){
		m_pTexture=NULL;
    }

    virtual~Cc3dTexture(){
		if( m_pTexture != NULL )m_pTexture->Release();
    }

	void initWithFile(const string&fileName);

public:
	IDirect3DTexture9*      m_pTexture ;
	string m_fileName;
    

};

#endif /* defined(__HelloCpp__c3dTexture__) */
