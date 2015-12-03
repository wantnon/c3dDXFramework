#include "c3dModelMatStack.h"



#include "c3dModelMatStack.h"

static Cc3dModelMatStack*modelMatStack=NULL;

Cc3dModelMatStack* Cc3dModelMatStack::sharedModelMatStack(){

    if(modelMatStack==NULL){

        modelMatStack=new Cc3dModelMatStack();

    }

    return modelMatStack;

}



void Cc3dModelMatStack::pushMatrix(){
        assert(m_stack.empty()==false);
        Cc3dMatrix4 topMat=m_stack[(int)m_stack.size()-1];//copy top mat
        m_stack.push_back(topMat);
    }

    void Cc3dModelMatStack::popMatrix(){
        assert(m_stack.empty()==false);
        int n=(int)m_stack.size();
        m_stack.resize(n-1);
        assert((int)m_stack.size()!=0);//m_stack at least have one element (the inital element)
    }

    void Cc3dModelMatStack::mulMatrix(const Cc3dMatrix4&mat){
        assert(m_stack.empty()==false);
        int n=(int)m_stack.size();
        Cc3dMatrix4 topMat=m_stack[(int)m_stack.size()-1];
        Cc3dMatrix4 newTopMat=topMat*mat;
        //use newTopMat replace top mat
        m_stack[(int)m_stack.size()-1]=newTopMat;
        assert(n==(int)m_stack.size());//m_stack size should not change
    }

    void Cc3dModelMatStack::loadIdentity(){
        assert(m_stack.empty()==false);
        m_stack[(int)m_stack.size()-1]=unitMat();
    }

    void Cc3dModelMatStack::loadMatrix(const Cc3dMatrix4&mat){
        assert(m_stack.empty()==false);
        m_stack[(int)m_stack.size()-1]=mat;
    }

    Cc3dMatrix4 Cc3dModelMatStack::getTopMat()const{
        assert(m_stack.empty()==false);
        return m_stack[(int)m_stack.size()-1];
    }