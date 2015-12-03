  #include "c3dIB.h"
#include "c3dNode.h"
#include "c3dScene.h"
#include "c3dMesh.h"

void Cc3dIB::createIB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	m_indexCount=0;
	if(m_primitiveType==eTriList){
		m_indexCount=mesh->m_IDtriList.size()*3;
	}else if(m_primitiveType==eLineList){
		m_indexCount=mesh->m_IDLineList.size()*2;
	}else{
		assert(false);
	}
	//create ib
	g_pd3dDevice->CreateIndexBuffer( m_indexCount * sizeof( WORD ),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		0);
}
void Cc3dIB::updateIB(){
	Cc3dNode*node=this->m_nodeRef;
	Cc3dMesh*mesh=(Cc3dMesh*)(node->getComponentByName("mesh"));
	WORD* indices = 0;
	m_pIB->Lock(0, 0, (void**)&indices, 0);
	if(m_primitiveType==eTriList){
		const int triCount=(int)mesh->m_IDtriList.size();
		for(int i=0;i<triCount;i++){
			const Cc3dIDTriangle&IDtri=mesh->m_IDtriList[i];
			indices[i*3]=IDtri.vID(0);
			indices[i*3+1]=IDtri.vID(1);
			indices[i*3+2]=IDtri.vID(2);

		}
	}else if(m_primitiveType==eLineList){
		const int lineCount=(int)mesh->m_IDLineList.size();
		for(int i=0;i<lineCount;i++){
			const Cc3dIDLine&IDline=mesh->m_IDLineList[i];
			indices[i*2]=IDline.vID(0);
			indices[i*2+1]=IDline.vID(1);

		}
	}else{
		assert(false);
	}
	m_pIB->Unlock();
}
void Cc3dIB::update(){
	if(m_isEnable==false)return;
	Cc3dMaterial*material=m_materialRef;
	Cc3dLightSource*lightSource=Cc3dScene::getInstance()->m_lightSource;
	assert(material);
	//update uniforms on client side
	material->m_effect->setUniform("g_diffuseL",lightSource->m_diffuse);
	material->m_effect->setUniform("g_ambientL",lightSource->m_ambient);
	material->m_effect->setUniform("g_lightDir",lightSource->m_dir.toV3());


}