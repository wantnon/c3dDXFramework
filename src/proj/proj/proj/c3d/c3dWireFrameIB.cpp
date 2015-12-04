#include "c3dWireFrameIB.h"
#include "c3dNode.h"
#include "c3dScene.h"
#include "c3dMesh.h"

void Cc3dWireFrameIB::createIB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	m_indexCount=mesh->m_IDtriList.size()*6;
	
	//create ib
	g_pd3dDevice->CreateIndexBuffer( m_indexCount * sizeof( WORD ),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		0);
}
void Cc3dWireFrameIB::updateIB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	WORD* indices = 0;
	m_pIB->Lock(0, 0, (void**)&indices, 0);

	const int triCount=(int)mesh->m_IDtriList.size();
	for(int i=0;i<triCount;i++){
		const Cc3dIDTriangle&IDtri=mesh->m_IDtriList[i];
		indices[i*6]=IDtri.vID(0);
		indices[i*6+1]=IDtri.vID(1);
		indices[i*6+2]=IDtri.vID(1);
		indices[i*6+3]=IDtri.vID(2);
		indices[i*6+4]=IDtri.vID(2);
		indices[i*6+5]=IDtri.vID(0);
	}

	m_pIB->Unlock();
}
