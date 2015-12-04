#ifndef _c3dIBBase_H_
#define _c3dIBBase_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dComponent.h"
#include "c3dDX.h"

enum ePrimitiveType{
	eTriList=0,
	eLineList,
};
inline _D3DPRIMITIVETYPE primitiveTypeToD3DPrimitiveType(ePrimitiveType type){
	switch(type){
	case eTriList:
		return D3DPT_TRIANGLELIST;
		break;
	case eLineList:
		return D3DPT_LINELIST;
		break;
	default:
		assert(false);
		break;
	}


}
class Cc3dMaterial;
class Cc3dIBBase:public Cc3dComponent{
public:
	Cc3dIBBase(){	
		m_name="ibBase";
		m_primitiveType=eTriList;
		m_pIB=NULL;
		m_indexCount=0;
		m_materialRef=NULL;

	}

	virtual~Cc3dIBBase(){
		if( m_pIB != NULL )m_pIB->Release();

	}
	
	virtual void createIB(){};
	virtual void updateIB(){};
public:
	IDirect3DIndexBuffer9*	m_pIB;
	int m_indexCount;
	ePrimitiveType m_primitiveType;
	Cc3dMaterial*m_materialRef;//use which material to render this ib
};





#endif