

#ifndef __HelloCpp__c3dTextureCache__
#define __HelloCpp__c3dTextureCache__



#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "c3dDX.h"
#include "c3dTexture.h"
class Cc3dTextureCache
{
public:
    Cc3dTextureCache(){
    }

    virtual~Cc3dTextureCache(){
		const int count=m_list.size();
		for(int i=0;i<count;i++){
			delete m_list[i];
		}
    }
	static Cc3dTextureCache*getInstance();

	Cc3dTexture* add(Cc3dTexture*p);
	Cc3dTexture* add(const string&fileName);
	void removeUnused();
	Cc3dTexture*getByFileName(const string&fileName)const;
protected:
	vector<Cc3dTexture*>      m_list ;

    

};

#endif /* defined(__HelloCpp__c3dTextureCache__) */
