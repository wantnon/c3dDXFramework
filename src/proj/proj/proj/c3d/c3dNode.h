#ifndef _c3dNode_H_
#define _c3dNode_H_
#include <vector>
using namespace std;
#include <assert.h>
#include "c3dGLMath.h"
#include "c3dModelMatStack.h"
#include "c3dComponent.h"
#include "c3dDX.h" 
#include "c3dFuncs.h"


class Cc3dNode//to keep component-based, Cc3dNode should be a final class, do not inherit from it
{
public:
	Cc3dNode(){
		m_RTmat=unitMat();
		m_scale=cc3dv4(1,1,1,1);
		m_name="GameNode";
		m_isAddedToScene=false;
	}
	virtual ~Cc3dNode(){
		//when this node deleted, should delete all child... this cause a recursion process
		const int childCount=(int)m_childList.size();
		for(int i=0;i<childCount;i++){
			Cc3dNode*child=m_childList[i];
			assert(child);
			delete child;
		}
	}
	void setScale(float scaleX,float scaleY,float scaleZ);
	void rotate(const Cc3dVector4&axis,float A);
	void rotateInParent(const Cc3dVector4&axis,float A);
	void move(float dx,float dy,float dz);
	void moveInParent(float dx,float dy,float dz);
	Cc3dVector4 getPos();
	const Cc3dMatrix4 getRTSmat()const ;

	void addChild(Cc3dNode*child);
	void removeChild(Cc3dNode*child);
	void changeParent(Cc3dNode*newParent);
	Cc3dNode*findChildByPath(const string&path);
	vector<Cc3dNode*> getAllNodesInSubTree();

	void addComponent(Cc3dComponent*component);
	Cc3dComponent*getComponentByName(const string&name);
	vector<Cc3dComponent*> getAllComponentsInSubTree();

	void visitUpdate();
	void update();
	void drawGizmos();
private:
	Cc3dNode*findChildByName(const string&name);
	int findChild(Cc3dNode*child);
public:
	string m_name;
	Cc3dVector4 m_scale;
	Cc3dMatrix4 m_RTmat;//rotate & translate
	vector<Cc3dNode*> m_childList;
	vector<Cc3dComponent*> m_componentList;
	bool m_isAddedToScene;//when have time, should change this member to Cc3dNode* m_parent
public:
	Cc3dMatrix4 m_cachedWorldMat;//after visitUpdate the subtree, world matrix cached in this member
};

#endif