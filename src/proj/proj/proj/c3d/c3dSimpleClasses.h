#ifndef _c3dSimpleClasses_H_
#define _c3dSimpleClasses_H_
#include "c3dMath.h"



class Cc3dIDTriangle 
{
public:

    Cc3dIDTriangle(){
        initMembers();
    }

    ~Cc3dIDTriangle(){
    }

    Cc3dIDTriangle(int ID0,int ID1,int ID2);
    const short*getArray()const {return m_array;}
    void init(int ID0,int ID1,int ID2);
    short vID(int i)const;
    void setVID(int i,short vID);
protected:
    void initMembers();
protected:
    short m_array[3];

};




class Cc3dIDLine 
{
public:
    Cc3dIDLine(){
        initMembers();
    }
    ~Cc3dIDLine(){
    }
    Cc3dIDLine(int ID0,int ID1);
    const short*getArray()const {return m_array;}
    void init(int ID0,int ID1);
    short vID(int i)const;
    void setVID(int i,short vID);
protected:
    void initMembers();
protected:
    short m_array[2];
};



#endif