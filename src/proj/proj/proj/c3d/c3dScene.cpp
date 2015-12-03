#include "c3dScene.h"
static Cc3dScene*s_scene=NULL;
Cc3dScene*Cc3dScene::getInstance(){
	if(s_scene==NULL){
		s_scene=new Cc3dScene();
		s_scene->init();
	}
	return s_scene;
}