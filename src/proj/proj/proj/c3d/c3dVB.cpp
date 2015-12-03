  #include "c3dVB.h"
#include "c3dNode.h"

void Cc3dVB::createVB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	m_vertexCount=mesh->m_positionList.size();
	//create vb
	g_pd3dDevice->CreateVertexBuffer( m_vertexCount * sizeof( CUSTOMVERTEX ),
		0, 0,
		D3DPOOL_DEFAULT, &m_pVB, NULL )  ;
}
void Cc3dVB::updateVB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	CUSTOMVERTEX* pVertices;
	m_pVB->Lock( 0, 0, ( void** )&pVertices, 0 ) ;
	for(int i=0;i<m_vertexCount;i++){
		const Cc3dVector4&pos=mesh->m_positionList[i];
		const Cc3dVector2&uv=mesh->m_texCoordList[i];
		const Cc3dVector4&color=mesh->m_colorList[i];
		const Cc3dVector4&normal=mesh->m_normalList[i];
		pVertices[i].position=D3DXVECTOR3( pos.x(), pos.y(), pos.z() );
		pVertices[i].normal=D3DXVECTOR3( normal.x(), normal.y(), normal.z() );
		pVertices[i].color=D3DXVECTOR4(color.r(),color.g(),color.b(),color.a());
		pVertices[i].tu=uv.x();
		pVertices[i].tv=uv.y();
	}
	m_pVB->Unlock();

}
