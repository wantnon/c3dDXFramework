


#ifndef __HelloCpp__c3dComponent__
#define __HelloCpp__c3dComponent__
#include <string>
#include <algorithm>
using namespace std;

class Cc3dNode;//no need to include "c3dNode.h", just declare Cc3dNode is OK!
class Cc3dComponent{
public:
	Cc3dComponent(){
		m_nodeRef=NULL;

		m_isStarted=false;
		m_isEnable=true;
	};
	virtual~Cc3dComponent(){}
	virtual void start(){}
	virtual void update(){}
	virtual void drawGizmos(){}

	
public:
	string m_name;
	Cc3dNode*m_nodeRef;

	bool m_isStarted;
	bool m_isEnable;
};

#endif /* defined(__HelloCpp__c3dComponent__) */