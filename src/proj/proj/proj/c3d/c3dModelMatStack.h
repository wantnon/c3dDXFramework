

#ifndef __HelloOpenGL__c3dModelMatStack__
#define __HelloOpenGL__c3dModelMatStack__



#include <iostream>
#include <vector>
using namespace std;
#include "c3dMath.h"


class Cc3dModelMatStack{
public:
    static Cc3dModelMatStack*sharedModelMatStack();
    Cc3dModelMatStack(){
        m_stack.push_back(unitMat());//initial bottom element
    }

    virtual~Cc3dModelMatStack(){}
    void pushMatrix();
    void popMatrix();
    void loadIdentity();
    void loadMatrix(const Cc3dMatrix4&mat);
	void mulMatrix(const Cc3dMatrix4&mat);
    Cc3dMatrix4 getTopMat()const;

protected:
    vector<Cc3dMatrix4> m_stack;



};

#endif /* defined(__HelloOpenGL__c3dModelMatStack__) */



