

#ifndef __HelloCpp__c3dRCobj__

#define __HelloCpp__c3dRCobj__



#include <iostream>
#include <string>
using namespace std;
#include <assert.h>

class Cc3dRCobj//base class for reference-counting object
{

public:

    Cc3dRCobj(){
		m_retainCount=1;

    }

    virtual~Cc3dRCobj(){
		
    }

	void retain(){
		m_retainCount++;
	}
	void release(){
		assert(m_retainCount>=0);
		m_retainCount--;
		if(m_retainCount<=0){
			delete this;
		}

	}
 

public:
	int m_retainCount;

    

};

#endif /* defined(__HelloCpp__c3dRCobj__) */
