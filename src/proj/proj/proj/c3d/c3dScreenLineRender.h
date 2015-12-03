#ifndef _c3dScreenLineRender_H_
#define _c3dScreenLineRender_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dComponent.h"
#include "c3dDX.h"
#include "c3dMath.h"
#include "c3dFuncs.h"
class Cc3dScreenLineRender:public Cc3dComponent{
public:
	Cc3dScreenLineRender(){	
		m_name="screenLineRender";
		m_pLine=NULL;

		D3DXCreateLine(g_pd3dDevice, &m_pLine);
		m_color.init(1,1,1,1);
	}

	virtual~Cc3dScreenLineRender(){
		if (m_pLine != NULL)  m_pLine->Release(); 

	}
	void drawGizmos(){
		if(m_isEnable==false)return;
		//conver to D3DXVECTOR2
		vector<D3DXVECTOR2> posList;
		const int posCount=(int)m_posList.size();
		for(int i=0;i<posCount;i++){
			const Cc3dVector2&pos=m_posList[i];
			posList.push_back(D3DXVECTOR2(pos.x(),pos.y()));
		}
		
		//draw
		if(posList.empty()==false){
			m_pLine->SetWidth(1.f);  
			m_pLine->SetAntialias(TRUE);  
			int r=max(min(m_color.r()*255,255),0);
			int g=max(min(m_color.g()*255,255),0);
			int b=max(min(m_color.b()*255,255),0);
			int a=max(min(m_color.a()*255,255),0);
			m_pLine->Draw(&posList[0], (int)posList.size(), RGBAToHexARGB(r,g,b,a));
		}
	}

public:

	LPD3DXLINE m_pLine; 
	vector<Cc3dVector2> m_posList;//note: positions are in viewport space (not screen space)
	Cc3dVector4 m_color;
};
#endif