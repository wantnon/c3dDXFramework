


#include "c3dEffect.h"

float Cc3dUniform::getFloat()const {
		assert(m_type==eUT_float);
		if(m_inited){
			return m_floatList[0];
		}else{
			return 0;
		}
	}
	Cc3dVector2 Cc3dUniform::getV2()const {
		assert(m_type==eUT_float2);
		if(m_inited){
			return Cc3dVector2(m_floatList[0],m_floatList[1]);
		}else{
			return Cc3dVector2();
		}
	}
	Cc3dVector3 Cc3dUniform::getV3()const {
		assert(m_type==eUT_float3);
		if(m_inited){
			return Cc3dVector3(m_floatList[0],m_floatList[1],m_floatList[2]);
		}else{
			return Cc3dVector3();
		}
	}
	Cc3dVector4 Cc3dUniform::getV4()const {
		assert(m_type==eUT_float4);
		if(m_inited){
			return Cc3dVector4(m_floatList[0],m_floatList[1],m_floatList[2],m_floatList[3]);
		}else{
			return Cc3dVector4();
		}
	}
	Cc3dMatrix4 Cc3dUniform::getM4()const {
		assert(m_type==eUT_float4x4);
		if(m_inited){
			return Cc3dMatrix4(m_floatList[0],m_floatList[1],m_floatList[2],m_floatList[3],
				m_floatList[4],m_floatList[5],m_floatList[6],m_floatList[7],
				m_floatList[8],m_floatList[9],m_floatList[10],m_floatList[11],
				m_floatList[12],m_floatList[13],m_floatList[14],m_floatList[15]);
		}else{
			return Cc3dMatrix4();
		}
	}
	
	void Cc3dUniform::set(float x){
		assert(m_type==eUT_float);
		if((int)m_floatList.size()!=1||x!=m_floatList[0]){
			m_floatList.resize(1);
			m_floatList[0]=x;
			m_isDirty=true;
		}
		if(m_inited==false){
			m_inited=true;
			m_isDirty=true;
		}
	}
	void Cc3dUniform::set(const Cc3dVector2&v){
		assert(m_type==eUT_float2);
		if(isListEqual(m_floatList,v.getArray(),v.getArrayLen())==false){
			m_floatList=v.convertToVector();
			m_isDirty=true;
		}
		if(m_inited==false){
			m_inited=true;
			m_isDirty=true;
		}
	}
	void Cc3dUniform::set(const Cc3dVector3&v){
		assert(m_type==eUT_float3);
		if(isListEqual(m_floatList,v.getArray(),v.getArrayLen())==false){
			m_floatList=v.convertToVector();
			m_isDirty=true;
		}
		if(m_inited==false){
			m_inited=true;
			m_isDirty=true;
		}
	}
	void Cc3dUniform::set(const Cc3dVector4&v){
		assert(m_type==eUT_float4);
		if(isListEqual(m_floatList,v.getArray(),v.getArrayLen())==false){
			m_floatList=v.convertToVector();
			m_isDirty=true;
		}
		if(m_inited==false){
			m_inited=true;
			m_isDirty=true;
		}
	}
	void Cc3dUniform::set(const Cc3dMatrix4&m){
		assert(m_type==eUT_float4x4);
		if(isListEqual(m_floatList,m.getArray(),m.getArrayLen())==false){
			m_floatList=m.convertToVector();
			m_isDirty=true;
		}
		if(m_inited==false){
			m_inited=true;
			m_isDirty=true;
		}
	}




//------------------------------------------------------------------------------------------

	void Cc3dEffect::initWithFile(const string&effectFileName,const string&effectVarFileName){

		
		WCHAR wcstr[MAX_WCSTR_LEN];
		MultiByteToWideChar(0,0,effectFileName.c_str(),-1,wcstr,MAX_WCSTR_LEN);
		// If this fails, there should be debug output as to 
		// why the .fx file failed to compile
		D3DXCreateEffectFromFile( g_pd3dDevice, wcstr, NULL, NULL, D3DXSHADER_DEBUG, NULL, &m_pEffect, NULL );
		assert(m_pEffect);
		readEffectVarFileAndGenUniformList(effectVarFileName);
	}
	void Cc3dEffect::setUniform(const string&unifoName,float x){
		Cc3dUniform*p=getpUnifomByName(unifoName);
		if(p)p->set(x);
	}
	void Cc3dEffect::setUniform(const string&unifoName,const Cc3dVector2&v2){
		Cc3dUniform*p=getpUnifomByName(unifoName);
		if(p)p->set(v2);
	}
	void Cc3dEffect::setUniform(const string&unifoName,const Cc3dVector3&v3){
		Cc3dUniform*p=getpUnifomByName(unifoName);
		if(p)p->set(v3);
	}
	void Cc3dEffect::setUniform(const string&unifoName,const Cc3dVector4&v4){
		Cc3dUniform*p=getpUnifomByName(unifoName);
		if(p)p->set(v4);
	}
	void Cc3dEffect::setUniform(const string&unifoName,const Cc3dMatrix4&m4){
		Cc3dUniform*p=getpUnifomByName(unifoName);
		if(p)p->set(m4);
	}
	void Cc3dEffect::setSampler(const string&samplerName,Cc3dTexture*texture){
		Cc3dSampler*p=getpSamplerByName(samplerName);
		if(p)p->m_textureRef=texture;
	}
	Cc3dSampler*Cc3dEffect::getpSamplerByName(const string&samplerName){
		const int count=(int)m_samplerList.size();
		for(int i=0;i<count;i++){
			Cc3dSampler&sampler=m_samplerList[i];
			if(sampler.m_name==samplerName){
				return &sampler;
			}
		}
		return NULL;
	}

	Cc3dUniform*Cc3dEffect::getpUnifomByName(const string&unifoName){
		const int unifoCount=(int)m_uniformList.size();
		for(int i=0;i<unifoCount;i++){
			Cc3dUniform&unifo=m_uniformList[i];
			if(unifo.m_name==unifoName){
				return &unifo;
			}
		}
		return NULL;
	}
	
	
	void Cc3dEffect::applyAllDirtyUniforms(){
		const int unifoCount=(int)m_uniformList.size();
		for(int i=0;i<unifoCount;i++){
			Cc3dUniform&unifo=m_uniformList[i];
			if(unifo.m_isDirty){//optim
				applyUniform(unifo);
				unifo.m_isDirty=false;//m_isDirty consumed
			}
		}
	}
	
	void Cc3dEffect::applyUniformIfDirty(Cc3dUniform&unifo){
		if(unifo.m_isDirty){
			applyUniform(unifo);
			unifo.m_isDirty=false;//m_isDirty consumed
		}
	}

	void Cc3dEffect::applyUniform(const Cc3dUniform&unifo)
	//shader can preserve uniform value even though it is unbinded and bind again
	//ref: https://www.opengl.org/discussion_boards/showthread.php/185522-glUniform-values-are-preserved-when-shader-is-uninstalled
	//and ref: http://www.opengpu.org/bbs/forum.php?mod=viewthread&tid=17637
	{
		eUnifoType type=unifo.m_type;
		string name=unifo.m_name;
		switch(type){

		case eUT_float:
			m_pEffect->SetFloat( name.c_str(),unifo.getFloat());
			break;
		case eUT_float2:
			m_pEffect->SetValue( name.c_str(), unifo.getV2().getArray(), sizeof( D3DXVECTOR2 ) );
			break;
		case eUT_float3:
			m_pEffect->SetValue( name.c_str(), unifo.getV3().getArray(), sizeof( D3DXVECTOR3 ) );
			break;
		case eUT_float4:
			m_pEffect->SetValue( name.c_str(), unifo.getV4().getArray(), sizeof( D3DXVECTOR4 ) );
			break;
		case eUT_float4x4:
			m_pEffect->SetMatrix( name.c_str(), &D3DXMATRIXA16(unifo.getM4().getArray()));
			break;
		default:
			assert(false);
			break;
		}
		
	}
	void Cc3dEffect::readEffectVarFileAndGenUniformList(const string&fileName){

		//------------------full path of file
		string fileFullPath=fileName;
		//open file
		FILE  *fp=NULL;
		fp=fopen(fileFullPath.c_str(),"r");// write
		if(fp==NULL){
			cout<<"Open "<<fileFullPath<<" failed!"<<endl;
			assert(false);
		}
		//------------------read file
		fscanStr(fp,"uniform:");
		while(1){
			string type=fscanStr(fp);
			if(type=="end")break;
			string name=fscanStr(fp);
			eUnifoType eType=strToUnifoType(type);
			Cc3dUniform unifo;
			unifo.m_name=name;
			unifo.m_type=eType;
			m_uniformList.push_back(unifo);
		}
		fscanStr(fp,"sampler:");
		while(1){
			string type=fscanStr(fp);
			if(type=="end")break;
			string name=fscanStr(fp);
			eSamplerType eType=strToSamplerType(type);
			Cc3dSampler sampler;
			sampler.m_name=name;
			sampler.m_type=eType;
			m_samplerList.push_back(sampler);
		}

		//--------------------------close file
		fclose(fp);
	}
	eSamplerType Cc3dEffect::strToSamplerType(const string&str){
		eSamplerType type=(eSamplerType)0;
		if(str=="texture"){
			type=eST_texture;
		}else{
			assert(false);
		}
		return type;
	}
	eUnifoType Cc3dEffect::strToUnifoType(const string&str){
		eUnifoType type=(eUnifoType)0;
		if(str=="float"){
			type = eUT_float;
		}else if(str=="float2"){
			type = eUT_float2;
		}else if(str=="float3"){
			type = eUT_float3;
		}else if(str=="float4"){
			type = eUT_float4;
		}else if(str=="float4x4"){
			type = eUT_float4x4;
		}else{
			assert(false);
		}
		return type;
	
	}