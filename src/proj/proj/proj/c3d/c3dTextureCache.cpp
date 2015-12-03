


#include "c3dTextureCache.h"
static Cc3dTextureCache*s_textureCache=NULL;
Cc3dTextureCache*Cc3dTextureCache::getInstance(){
	if(s_textureCache==NULL){
		s_textureCache=new Cc3dTextureCache();
	}
	return s_textureCache;

}


Cc3dTexture* Cc3dTextureCache::add(Cc3dTexture*p){
		assert(p);
		m_list.push_back(p);
		return p;
	}
	Cc3dTexture* Cc3dTextureCache::add(const string&fileName){
		Cc3dTexture*p=new Cc3dTexture();
		p->initWithFile(fileName);
		add(p);
		return p;
	}
	void Cc3dTextureCache::removeUnused(){
		vector<Cc3dTexture*> list;
		const int count=m_list.size();
		for(int i=0;i<count;i++){
			Cc3dTexture*p=m_list[i];
			if(p->m_retainCount<=1){
				delete p;
			}else{
				list.push_back(p);
			}
		}
		m_list=list;
	}
	Cc3dTexture*Cc3dTextureCache::getByFileName(const string&fileName)const {
		const int count=m_list.size();
		for(int i=0;i<count;i++){
			Cc3dTexture*p=m_list[i];
			if(p->m_fileName==fileName){
				return p;
			}
		}
		return NULL;
	}