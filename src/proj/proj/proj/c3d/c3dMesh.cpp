


#include "c3dMesh.h"
 



void makeAxis(Cc3dMesh*mesh,float L){
	assert(mesh);
	assert(mesh->m_positionList.empty());
	vector<Cc3dVector4> posList;
	vector<Cc3dIDLine> IDLineList;
	vector<Cc3dVector4> normList;
	vector<Cc3dVector4> colorList;
	vector<Cc3dVector2> texCoordList;
	//x
	{
		posList.push_back(cc3dv4(0,0,0,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(L,0,0,1));int vid1=posList.size()-1;
		normList.push_back(cc3dv4(0,0,0,0));
		normList.push_back(cc3dv4(0,0,0,0));
		colorList.push_back(cc3dv4(1,0,0,0));
		colorList.push_back(cc3dv4(1,0,0,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		IDLineList.push_back(Cc3dIDLine(vid0,vid1));
	}
	//y
	{
		posList.push_back(cc3dv4(0,0,0,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(0,L,0,1));int vid1=posList.size()-1;
		normList.push_back(cc3dv4(0,0,0,0));
		normList.push_back(cc3dv4(0,0,0,0));
		colorList.push_back(cc3dv4(0,1,0,0));
		colorList.push_back(cc3dv4(0,1,0,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		IDLineList.push_back(Cc3dIDLine(vid0,vid1));

	}
	//z
	{
		posList.push_back(cc3dv4(0,0,0,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(0,0,L,1));int vid1=posList.size()-1;
		normList.push_back(cc3dv4(0,0,0,0));
		normList.push_back(cc3dv4(0,0,0,0));
		colorList.push_back(cc3dv4(0,0,1,0));
		colorList.push_back(cc3dv4(0,0,1,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(0,0));
		IDLineList.push_back(Cc3dIDLine(vid0,vid1));
	}


	//----assign to mesh
	mesh->m_positionList=posList;
	mesh->m_IDLineList=IDLineList;
	mesh->m_normalList=normList;
	mesh->m_colorList=colorList;
	mesh->m_texCoordList=texCoordList;

}
void makeRectFrame(Cc3dMesh*mesh){
	assert(mesh);
	assert(mesh->m_positionList.empty());
	vector<Cc3dVector4> posList;
	vector<Cc3dIDLine> IDLineList;
	vector<Cc3dVector4> normList;
	vector<Cc3dVector4> colorList;
	vector<Cc3dVector2> texCoordList;
	const float d=1;
	Cc3dVector4 LU=cc3dv4(-d,d,0,1);
	Cc3dVector4 LD=cc3dv4(-d,-d,0,1);
	Cc3dVector4 RD=cc3dv4(d,-d,0,1);
	Cc3dVector4 RU=cc3dv4(d,d,0,1);


	posList.push_back(LU);//v0
	posList.push_back(LD);//v1
	posList.push_back(RD);//v2
	posList.push_back(RU);//v3
	normList.push_back(cc3dv4(0,0,0,0));
	normList.push_back(cc3dv4(0,0,0,0));
	normList.push_back(cc3dv4(0,0,0,0));
	normList.push_back(cc3dv4(0,0,0,0));
	colorList.push_back(cc3dv4(1,0,0,0));
	colorList.push_back(cc3dv4(1,0,0,0));
	colorList.push_back(cc3dv4(1,0,0,0));
	colorList.push_back(cc3dv4(1,0,0,0));
	texCoordList.push_back(Cc3dVector2(0,0));
	texCoordList.push_back(Cc3dVector2(0,0));
	texCoordList.push_back(Cc3dVector2(0,0));
	texCoordList.push_back(Cc3dVector2(0,0));

	IDLineList.push_back(Cc3dIDLine(0,1));
	IDLineList.push_back(Cc3dIDLine(1,2));
	IDLineList.push_back(Cc3dIDLine(2,3));
	IDLineList.push_back(Cc3dIDLine(3,0));


	//----assign to mesh
	mesh->m_positionList=posList;
	mesh->m_IDLineList=IDLineList;
	mesh->m_normalList=normList;
	mesh->m_colorList=colorList;
	mesh->m_texCoordList=texCoordList;
}
void makeCube(Cc3dMesh*mesh,const Cc3dVector4&color){
	assert(mesh);
	assert(mesh->m_positionList.empty());
	const float L=1;
	const float d=L/2;
	vector<Cc3dVector4> posList;
	vector<Cc3dIDTriangle> IDtriList;
	vector<Cc3dVector4> normList;
	vector<Cc3dVector4> colorList;
	vector<Cc3dVector2> texCoordList;
	//front face
	{
		posList.push_back(cc3dv4(-d,-d,+d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(+d,-d,+d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,+d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(-d,+d,+d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(0,0,1,0));
		normList.push_back(cc3dv4(0,0,1,0));
		normList.push_back(cc3dv4(0,0,1,0));
		normList.push_back(cc3dv4(0,0,1,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));
	}
	//back face
	{
		posList.push_back(cc3dv4(-d,-d,-d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(-d,+d,-d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,-d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(+d,-d,-d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(0,0,-1,0));
		normList.push_back(cc3dv4(0,0,-1,0));
		normList.push_back(cc3dv4(0,0,-1,0));
		normList.push_back(cc3dv4(0,0,-1,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));
	}
	//left face
	{
		posList.push_back(cc3dv4(-d,-d,+d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(-d,+d,+d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(-d,+d,-d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(-d,-d,-d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(-1,0,0,0));
		normList.push_back(cc3dv4(-1,0,0,0));
		normList.push_back(cc3dv4(-1,0,0,0));
		normList.push_back(cc3dv4(-1,0,0,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));

	}
	//right face
	{
		posList.push_back(cc3dv4(+d,-d,+d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(+d,-d,-d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,-d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,+d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(1,0,0,0));
		normList.push_back(cc3dv4(1,0,0,0));
		normList.push_back(cc3dv4(1,0,0,0));
		normList.push_back(cc3dv4(1,0,0,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));

	}
	//up face
	{
		posList.push_back(cc3dv4(-d,+d,+d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,+d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(+d,+d,-d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(-d,+d,-d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(0,1,0,0));
		normList.push_back(cc3dv4(0,1,0,0));
		normList.push_back(cc3dv4(0,1,0,0));
		normList.push_back(cc3dv4(0,1,0,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));

	}
	//dn face
	{
		posList.push_back(cc3dv4(-d,-d,+d,1));int vid0=posList.size()-1;
		posList.push_back(cc3dv4(-d,-d,-d,1));int vid1=posList.size()-1;
		posList.push_back(cc3dv4(+d,-d,-d,1));int vid2=posList.size()-1;
		posList.push_back(cc3dv4(+d,-d,+d,1));int vid3=posList.size()-1;
		normList.push_back(cc3dv4(0,-1,0,0));
		normList.push_back(cc3dv4(0,-1,0,0));
		normList.push_back(cc3dv4(0,-1,0,0));
		normList.push_back(cc3dv4(0,-1,0,0));
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		colorList.push_back(color);
		texCoordList.push_back(Cc3dVector2(0,0));
		texCoordList.push_back(Cc3dVector2(1,0));
		texCoordList.push_back(Cc3dVector2(1,1));
		texCoordList.push_back(Cc3dVector2(0,1));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid1,vid2));
		IDtriList.push_back(Cc3dIDTriangle(vid0,vid2,vid3));

	}//*/


	//----assign to mesh
	mesh->m_positionList=posList;
	mesh->m_IDtriList=IDtriList;
	mesh->m_normalList=normList;
	mesh->m_colorList=colorList;
	mesh->m_texCoordList=texCoordList;

}


void makeSphere(Cc3dMesh*mesh,int nSlice,int nStack,const Cc3dVector4&color){
	assert(mesh);
	assert(mesh->m_positionList.empty());

	const float r=0.5;



    float dA=360.0/nSlice;

    float dB=180.0/nStack;

    const float PIDIV180=M_PI/180;

    vector<Cc3dVector4> positionList;

    vector<Cc3dVector2> texCoordList;

    vector<Cc3dVector4> normalList;

    vector<Cc3dVector4> colorList;


    vector<Cc3dIDTriangle> IDtriList;


    //generate positionList, texCoordList, normalList, colorList

    for(int i=0;i<=nStack;i++){

        float B=-90+i*dB;

        float y=r*sinf(B*PIDIV180);

        float cosB=cosf(B*PIDIV180);

        for (int j=0; j<=nSlice; j++) {

            float A=j*dA;

            float R=r*cosB;

            float x=R*cosf(A*PIDIV180);

            float z=R*sinf(A*PIDIV180);

            Cc3dVector4 position(x,y,z,1);

            float s=(float)j/nSlice+0.25;

            float t=1-(float)i/nStack;

            Cc3dVector2 texCoord(s,t);

            Cc3dVector4 normal=normalize(cc3dv4(position.x(), position.y(), position.z(), 0));



            positionList.push_back(position);

            texCoordList.push_back(texCoord);

            normalList.push_back(normal);

            colorList.push_back(color);

			



        }

    }

    //generate IDtriList

    for(int i=0;i<nStack;i++){

        for(int j=0;j<nSlice;j++){

            int vID_rd=(nSlice+1)*i+j;

            int vID_ld=vID_rd+1;

            int vID_lu=vID_ld+(nSlice+1);

            int vID_ru=vID_lu-1;

            Cc3dIDTriangle IDtri0(vID_ld,vID_rd,vID_ru);

            Cc3dIDTriangle IDtri1(vID_ld,vID_ru,vID_lu);

            IDtriList.push_back(IDtri0);

            IDtriList.push_back(IDtri1);

        }

    }

	//----assign to subMeshData
	mesh->m_positionList=positionList;
	mesh->m_IDtriList=IDtriList;
	mesh->m_normalList=normalList;
	mesh->m_colorList=colorList;
	mesh->m_texCoordList=texCoordList;


}