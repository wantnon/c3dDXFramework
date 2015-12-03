#ifndef _c3dVB_H_
#define _c3dVB_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dComponent.h"
#include "c3dMesh.h"
#include "c3dDX.h"

class Cc3dVB:public Cc3dComponent{
public:
	Cc3dVB(){	
		m_name="vb";
		m_pVB=NULL;
		m_vertexCount=0;

	}

	virtual~Cc3dVB(){
		if( m_pVB != NULL )m_pVB->Release();

	}
	
	void createVB();
	void updateVB();

public:
	IDirect3DVertexBuffer9* m_pVB; 
	int m_vertexCount;


};





#endif