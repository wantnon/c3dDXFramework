

#include "c3dMaterial.h"

#include "c3dNode.h"
#include "c3dScene.h"
void Cc3dMaterial::initWithEffectFile(const string&effectFileName,const string&effectVarFileName){
		m_effect=new Cc3dEffect();
		m_effect->initWithFile(effectFileName,effectVarFileName);
		
		
	}
	void Cc3dMaterial::addTexture(Cc3dTexture*p){
		assert(p);
		m_textureList.push_back(p);
		p->retain();
	}
	void Cc3dMaterial::setTexture(int index,Cc3dTexture*p){
		assert(p);
		assert(index>=0&&index<(int)m_textureList.size());
		m_textureList[index]->release();
		m_textureList[index]=p;
		p->retain();
	}
void Cc3dMaterial::render(){
		if(m_onRenderEnter){
			m_onRenderEnter();
		}
	
		Cc3dCamera*camera=Cc3dScene::getInstance()->m_camera;
		

		//----apply textures
		int samplerCount=(int)m_effect->m_samplerList.size();
		for(int i=0;i<samplerCount;i++){
			const Cc3dSampler&sampler=m_effect->m_samplerList[i];
			if(sampler.m_textureRef){
				m_effect->m_pEffect->SetTexture(sampler.m_name.c_str(),sampler.m_textureRef->m_pTexture);
			}
		}
	

		//----calculate PV matrix
		Cc3dMatrix4 veiwMat=camera->calculateViewMat_dx();//instead of use D3DXMatrixLookAtLH, we calculate viewMat by ourself
		Cc3dMatrix4 projMat=camera->calculateProjectionMat_dx();//instead of use D3DXMatrixPerspectiveFovLH, we calculate projMat by ourself
		Cc3dMatrix4 PV=projMat*veiwMat;

		//----Apply the technique contained in the effect 
		if(m_effectTechnique.empty()==false){
			m_effect->m_pEffect->SetTechnique( m_effectTechnique.c_str() ) ;
			UINT iPass, cPasses;
			m_effect->m_pEffect->Begin( &cPasses, 0 );
			//----draw ibs
			const int ibCount=(int)m_ibList.size();
			for(int i=0;i<ibCount;i++){
				Cc3dIBBase*ib=m_ibList[i];
				//----set and apply matrix
				Cc3dMatrix4 modelMat=ib->m_nodeRef->m_cachedWorldMat;
				Cc3dMatrix4 PVM=PV*modelMat;
				m_effect->setUniform("g_mWorldViewProjection",PVM);
				m_effect->setUniform("g_mWorld",modelMat);
				m_effect->applyAllDirtyUniforms();
				//----draw passes
				for( iPass = 0; iPass < cPasses; iPass++ )
				{
					m_effect->m_pEffect->BeginPass( iPass ) ;
					// The effect interface queues up the changes and performs them 
					// with the CommitChanges call. You do not need to call CommitChanges if 
					// you are not setting any parameters between the BeginPass and EndPass.
					// V( g_pEffect->CommitChanges() );

					// Render the buffer contents with the applied technique
					{	
						Cc3dVB*VB=(Cc3dVB*)ib->m_nodeRef->getComponentByName("vb");
						g_pd3dDevice->SetStreamSource( 0, VB->m_pVB, 0, sizeof( CUSTOMVERTEX ) );
						g_pd3dDevice->SetIndices(ib->m_pIB);
						g_pd3dDevice->SetVertexDeclaration(_vertexDecl);
						_D3DPRIMITIVETYPE primitiveType=primitiveTypeToD3DPrimitiveType(ib->m_primitiveType);
						int primitveCount=0;
						if(ib->m_primitiveType==eTriList){
							primitveCount=ib->m_indexCount/3;
						}else if(ib->m_primitiveType==eLineList){
							primitveCount=ib->m_indexCount/2;
						}else{
							assert(false);
						}
						g_pd3dDevice->DrawIndexedPrimitive(primitiveType, 0, 0, VB->m_vertexCount, 0, primitveCount);
					}

					m_effect->m_pEffect->EndPass() ;

				}

			}
			
			m_effect->m_pEffect->End() ;
		}

		if(m_onRenderLeave){
			m_onRenderLeave();
			
			
		}

	

		
}

