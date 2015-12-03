#include "c3dNode.h"
void Cc3dNode::rotate(const Cc3dVector4&axis,float A){
		Cc3dMatrix4 rotmat=calculateRotationMatrix(axis,cosf(A*M_PI/180),sinf(A*M_PI/180));
		m_RTmat=m_RTmat*rotmat;
	}
	void Cc3dNode::setScale(float scaleX,float scaleY,float scaleZ){
		m_scale.init(scaleX,scaleY,scaleZ,1);
	}
	void Cc3dNode::rotateInParent(const Cc3dVector4&axis,float A){
		Cc3dMatrix4 rotmat=calculateRotationMatrix(axis,sinf(A*M_PI/180),cosf(A*M_PI/180));
		m_RTmat=rotmat*m_RTmat;
	}
	void Cc3dNode::move(float dx,float dy,float dz){

		// RTmat    *   Tmat     =    RTmat'

		// a d g x     1 0 0 dx     a d g x+adx+ddy+gdz
		// b e h y  *  0 1 0 dy  =  b e h y+bdx+edy+hdz
		// c f i z     0 0 1 dz     c f i z+cdx+fdy+idz
		// 0 0 0 1     0 0 0  1     0 0 0 1

		float RTmat[16];
		memcpy(RTmat, m_RTmat.getArray(),sizeof(RTmat));
		RTmat[12]+=RTmat[0]*dx+RTmat[4]*dy+RTmat[8]*dz;
		RTmat[13]+=RTmat[1]*dx+RTmat[5]*dy+RTmat[9]*dz;
		RTmat[14]+=RTmat[2]*dx+RTmat[6]*dy+RTmat[10]*dz;

		m_RTmat.setAt(12, RTmat[12]);
		m_RTmat.setAt(13, RTmat[13]);
		m_RTmat.setAt(14, RTmat[14]);


	}



	void Cc3dNode::moveInParent(float dx,float dy,float dz){

		//  Tmat    *   RTmat   =   RTmat'

		// 1 0 0 dx    a d g x     a d g x+dx
		// 0 1 0 dy *  b e h y  =  b e h y+dy
		// 0 0 1 dz    c f i z     c f i z+dz
		// 0 0 0 1     0 0 0 1     0 0 0 1

		m_RTmat.setAt(12, m_RTmat.getAt(12)+dx);
		m_RTmat.setAt(13, m_RTmat.getAt(13)+dy);
		m_RTmat.setAt(14, m_RTmat.getAt(14)+dz);

	}

	void Cc3dNode::addChild(Cc3dNode*child){
		assert(child);
		assert(m_isAddedToScene);//if this node is not added to scene yet, do now allowed to add child for it
		assert(child->m_isAddedToScene==false);//a node can not be added to scene twice
		m_childList.push_back(child);
		
		
	}
	
	void Cc3dNode::removeChild(Cc3dNode*child){//do not allowed to remove child but not delete them. remove is delete! you can use change parent instead
		int index=findChild(child);
		if(index!=-1){
			m_childList.erase(m_childList.begin()+index);
			delete child;
		}
	}
	void Cc3dNode::changeParent(Cc3dNode*newParent){
		assert(false);//not implemented yet
	}
	Cc3dVector4 Cc3dNode::getPos(){
		Cc3dVector4 pos=Cc3dVector4(m_RTmat.getAt(12),m_RTmat.getAt(13),m_RTmat.getAt(14),1);
		return pos;
	}
	const Cc3dMatrix4 Cc3dNode::getRTSmat()const {
		//apply scale to RTmat
		Cc3dMatrix4 RTSmat;
		RTSmat=m_RTmat;
		RTSmat.setAt(0, RTSmat.getAt(0)*m_scale.x());
		RTSmat.setAt(1, RTSmat.getAt(1)*m_scale.x());
		RTSmat.setAt(2, RTSmat.getAt(2)*m_scale.x());

		RTSmat.setAt(4, RTSmat.getAt(4)*m_scale.y());
		RTSmat.setAt(5, RTSmat.getAt(5)*m_scale.y());
		RTSmat.setAt(6, RTSmat.getAt(6)*m_scale.y());

		RTSmat.setAt(8, RTSmat.getAt(8)*m_scale.z());
		RTSmat.setAt(9, RTSmat.getAt(9)*m_scale.z());
		RTSmat.setAt(10, RTSmat.getAt(10)*m_scale.z());
		return RTSmat;
	}

void Cc3dNode::update(){

		const int compoCount=(int)m_componentList.size();
		for(int i=0;i<compoCount;i++){
			Cc3dComponent*compo=m_componentList[i];
			compo->update();
		}

		
	}
void Cc3dNode::drawGizmos(){

		const int compoCount=(int)m_componentList.size();
		for(int i=0;i<compoCount;i++){
			Cc3dComponent*compo=m_componentList[i];
			compo->drawGizmos();
		}

		
	}
vector<Cc3dNode*> Cc3dNode::getAllNodesInSubTree()
//this node is included
{
		vector<Cc3dNode*> nodeList;//the result
		vector<Cc3dNode*> nodeStack;//for postorder traversal
		nodeStack.push_back(this);
		while(nodeStack.empty()==false){
			//pop out the back and add to nodeList
			Cc3dNode*node=nodeStack.back();
			nodeStack.pop_back();//pop_back() only erase the last element, see source code
			nodeList.push_back(node);
			//push all it's children to nodeStack
			const int childCount=(int)node->m_childList.size();
			for(int i=0;i<childCount;i++){
				Cc3dNode*child=node->m_childList[i];
				nodeStack.push_back(child);
			}
		}//got nodeList
		return nodeList;

}
vector<Cc3dComponent*> Cc3dNode::getAllComponentsInSubTree(){
	vector<Cc3dNode*> nodeList=this->getAllNodesInSubTree();
	vector<Cc3dComponent*> compoList;
	const int nodeCount=(int)nodeList.size();
	for(int i=0;i<nodeCount;i++){
		Cc3dNode*node=nodeList[i];
		const int compoCount=(int)node->m_componentList.size();
		for(int j=0;j<compoCount;j++){
			Cc3dComponent*compo=node->m_componentList[j];
			compoList.push_back(compo);
		}
	}
	return compoList;

}

void Cc3dNode::visitUpdate(){
		Cc3dModelMatStack::sharedModelMatStack()->pushMatrix();
		Cc3dModelMatStack::sharedModelMatStack()->mulMatrix(getRTSmat());
		
		m_cachedWorldMat=Cc3dModelMatStack::sharedModelMatStack()->getTopMat();

		//start all components
		const int compoCount=(int)m_componentList.size();
		for(int i=0;i<compoCount;i++){
			Cc3dComponent*compo=m_componentList[i];
			if(compo->m_isStarted==false){
				compo->start();
				compo->m_isStarted=true;
			}

		}

		//update self
		this->update();

		//draw gizoms
		this->drawGizmos();
	    

		//draw children
		const int nchild=(int)m_childList.size();
		if(nchild!=0){
			for(int i=0;i<nchild;i++){
				assert(m_childList[i]);
				m_childList[i]->visitUpdate();
			}
		}
		Cc3dModelMatStack::sharedModelMatStack()->popMatrix();
	}
Cc3dComponent*Cc3dNode::getComponentByName(const string&name){
		int comCount=m_componentList.size();
		for(int i=0;i<comCount;i++){
			Cc3dComponent*com=m_componentList[i];
			if(com->m_name==name){
				return com;
			}
		}
		return NULL;
	}
	void Cc3dNode::addComponent(Cc3dComponent*component){
		assert(component);
		assert(m_isAddedToScene==false);//do not support add component after the node is added to scene
		m_componentList.push_back(component);
		component->m_nodeRef=this;
		component->m_isStarted=false;
	}
	Cc3dNode*Cc3dNode::findChildByPath(const string&path){//path is like "xxx/xxx/../xxx"
		vector<string> pathSegList;
		const int len=(int)path.size();
		string buf;
		for(int i=0;i<len;i++){
			if(path[i]!='/'){
				buf+=path[i];
			}else{
				pathSegList.push_back(buf);
				buf.clear();
			}
		}
		if(buf.empty()==false)pathSegList.push_back(buf);//got pathSegList
		const int pathSegCount=(int)pathSegList.size();
		Cc3dNode*p=this;
		int pathSegIndex=0;
		while(pathSegIndex<pathSegCount){
			const string&pathSeg=pathSegList[pathSegIndex];
			p=p->findChildByName(pathSeg);
			if(p==NULL)return NULL;
			pathSegIndex++;
		}
		return p;
	
	}


	Cc3dNode*Cc3dNode::findChildByName(const string&name){
		const int childCount=(int)m_childList.size();
		for(int i=0;i<childCount;i++){
			Cc3dNode*_child=m_childList[i];
			if(_child->m_name==name){
				return _child;
			}
		}
		return NULL;
	
	}
	int Cc3dNode::findChild(Cc3dNode*child)//return child index
	{
		const int childCount=(int)m_childList.size();
		for(int i=0;i<childCount;i++){
			Cc3dNode*_child=m_childList[i];
			if(_child==child){
				return i;
			}
		}
		return -1;
	}