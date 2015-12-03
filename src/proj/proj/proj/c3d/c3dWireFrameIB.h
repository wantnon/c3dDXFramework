#ifndef _c3dWireFrameIB_H_
#define _c3dWireFrameIB_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dIBBase.h"
#include "c3dDX.h"

class Cc3dWireFrameIB:public Cc3dIBBase
{
public:
	Cc3dWireFrameIB(){	
		m_name="wireFrameIB";
		m_primitiveType=eLineList;
	}

	virtual~Cc3dWireFrameIB(){
	}

	void createIB();
	void updateIB();
	void update();


};





#endif