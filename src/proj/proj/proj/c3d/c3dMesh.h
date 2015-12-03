



#ifndef __HelloCpp__c3dMesh__
#define __HelloCpp__c3dMesh__



#include <iostream>
using namespace std;
#include "c3dMath.h"
#include "c3dSimpleClasses.h"
#include "c3dComponent.h"
class Cc3dMesh:public Cc3dComponent
{

public:

    Cc3dMesh(){
		m_name="mesh";
	};

    virtual~Cc3dMesh(){};

public:
    vector<Cc3dVector4> m_positionList;
    vector<Cc3dVector2> m_texCoordList;
    vector<Cc3dVector4> m_normalList;
    vector<Cc3dVector4> m_colorList;
public:
    vector<Cc3dIDTriangle> m_IDtriList;
	vector<Cc3dIDLine> m_IDLineList;



};


void makeCube(Cc3dMesh*mesh,const Cc3dVector4&color=cc3dv4(1,1,1,1));
void makeAxis(Cc3dMesh*mesh,float L=1);
void makeSphere(Cc3dMesh*mesh,int nSlice,int nStack,const Cc3dVector4&color=cc3dv4(1,1,1,1));
void makeRectFrame(Cc3dMesh*mesh);

#endif /* defined(__HelloCpp__c3dMesh__) */