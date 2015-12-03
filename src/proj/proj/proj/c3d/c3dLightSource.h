


#ifndef __HelloCpp__c3dLightSource__
#define __HelloCpp__c3dLightSource__



#include <iostream>
using namespace std;
#include "c3dMath.h"



class Cc3dLightSource
{
public:
    Cc3dLightSource(){
        //the default values are ref from <<OpenGL Programming Guide>> sixth edition
        m_ambient.init(0, 0, 0, 1);
        m_diffuse.init(1, 1, 1, 1);
        m_specular.init(1, 1, 1, 1);
		m_dir.init(1,-1,0,0);
    }

    virtual~Cc3dLightSource(){
    }

public:
    Cc3dVector4 m_ambient;
    Cc3dVector4 m_diffuse;
    Cc3dVector4 m_specular;
    Cc3dVector4 m_pos;
	Cc3dVector4 m_dir;
};

#endif /* defined(__HelloCpp__c3dLightSource__) */
