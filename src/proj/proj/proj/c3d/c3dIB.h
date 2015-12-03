#ifndef _c3dIB_H_
#define _c3dIB_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dIBBase.h"
#include "c3dDX.h"
class Cc3dIB:public Cc3dIBBase{
public:
	Cc3dIB(){	
		m_name="ib";
		m_primitiveType=eTriList;

	}

	virtual~Cc3dIB(){

	}
	void createIB();
	void updateIB();
	void update();


};





#endif