#ifndef _funcs_H_
#define _funcs_H_
#include <string>
#include <iostream>
using namespace std;

#include "c3dMath.h"
#include "c3dSimpleClasses.h"
#include <d3dx9.h>
string numberToStr(int n);
int strToNumber(const string&numStr);
int charToNumber(char c);
vector<string> divideStr(const string&str,const string&dividerChars);
Cc3dVector4 fscanVector4(FILE * fp);
Cc3dVector4 fscanVector3(FILE * fp);
Cc3dVector2 fscanVector2(FILE * fp);
float fscanFloat(FILE * fp);
int fscanInt(FILE * fp);
string fscanStr(FILE*fp,const string&expectedStr="");
string fscanOneQuotation(FILE * fp);

inline DWORD RGBAToHexARGB(unsigned char r,unsigned char g,unsigned char b,unsigned char a){
	//ref: http://www.cnblogs.com/wantnon/p/4968268.html
	DWORD rs=(r<<16)|(g<<8)|b|(a<<24);
	return rs;
}

inline void float16ToD3Dmat4(D3DXMATRIXA16&d3dmat,const float m[16]){
	d3dmat._11=m[0]; d3dmat._12=m[1]; d3dmat._13=m[2]; d3dmat._14=m[3];
	d3dmat._21=m[4]; d3dmat._22=m[5]; d3dmat._23=m[6]; d3dmat._24=m[7];
	d3dmat._31=m[8]; d3dmat._32=m[9]; d3dmat._33=m[10]; d3dmat._34=m[11];
	d3dmat._41=m[12]; d3dmat._42=m[13]; d3dmat._43=m[14]; d3dmat._44=m[15];
}

inline Cc3dMatrix4 D3Dmat4ToC3dMat4(D3DXMATRIXA16&d3dmat){
	return Cc3dMatrix4(
	d3dmat._11, d3dmat._12, d3dmat._13, d3dmat._14,
	d3dmat._21, d3dmat._22, d3dmat._23, d3dmat._24,
	d3dmat._31, d3dmat._32, d3dmat._33, d3dmat._34,
	d3dmat._41, d3dmat._42, d3dmat._43, d3dmat._44);
}
inline bool isListEqual(const vector<float>&list,const float arr[],int n){
	if((int)list.size()!=n)return false;
	for(int i=0;i<n;i++){
		if(list[i]!=arr[i])return false;
	}
	return true;

}

#endif