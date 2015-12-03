
#include "c3dFuncs.h"

static char buffer[1024]={0};//used for fscan string
string numberToStr(int n){//int to string
    char numbuf[128];
    sprintf(numbuf, "%i", n);//there is no itoa in xcode
    string numStr=numbuf;
    return numStr;
}
int charToNumber(char c){
	assert('0'<'9');
	assert(c>='0');
	assert(c<='9');
	return (c-'0');
}
int strToNumber(const string&numStr){
	int number=0;
	int len=(int)numStr.size();
	for(int i=0;i<len;i++){
		char c=numStr[i];
		int num=charToNumber(c);
		number*=10;
		number+=num;
	}//got number
	return number;
}
vector<string> divideStr(const string&str,const string&dividerChars){
	const int dividerCharCount=(int)dividerChars.size();
	vector<string> strList;
	string t_str;
	int len=(int)str.size();
	for(int i=0;i<len;i++){
		char c=str[i];
		bool cIsDividerCh=false;
		for(int j=0;j<dividerCharCount;j++){
			char divierCh=dividerChars[j];
			if(c==divierCh){
				cIsDividerCh=true;
				break;
			}
		}//got cIsDividerCh
		if(cIsDividerCh==false){
			t_str+=c;
		}else{
			strList.push_back(t_str);
			t_str.clear();
		}
	}
	if(t_str.empty()==false){
		strList.push_back(t_str);
	}//got strList;
	return strList;

}




Cc3dVector4 fscanVector4(FILE * fp){
	assert(fp);
	float arr[4];
	for(int i=0;i<4;i++){
		fscanf(fp,"%f",&arr[i]);
	}
	return Cc3dVector4(arr);
}
Cc3dVector4 fscanVector3(FILE * fp){
	assert(fp);
	float arr[3];
	for(int i=0;i<3;i++){
		fscanf(fp,"%f",&arr[i]);
	}
	return Cc3dVector4(arr);
}
Cc3dVector2 fscanVector2(FILE * fp){
	assert(fp);
	float arr[2];
	for(int i=0;i<2;i++){
		fscanf(fp,"%f",&arr[i]);
	}
	return Cc3dVector2(arr);
}
float fscanFloat(FILE * fp){
	assert(fp);
	float temp=0;
	fscanf(fp,"%f",&temp);
	return temp;

}
int fscanInt(FILE * fp){
	assert(fp);
	int temp=0;
	fscanf(fp,"%i",&temp);
	return temp;
}
string fscanStr(FILE*fp,const string&expectedStr){
	assert(fp);
	fscanf(fp,"%s",buffer);
	string str=buffer;
	if(expectedStr.empty()==false){
		assert(str==expectedStr);
	}
	return str;
}
string fscanOneQuotation(FILE * fp){
	assert(fp);
	string quoatation="";
	fscanf(fp,"%s",buffer);
	string beginStr=buffer;
	assert(beginStr[0]=='\"');
	quoatation+=beginStr;
	while(1){
		char endCh=quoatation[(int)quoatation.size()-1];
		if(endCh=='\"'){
			break;
		}
		fscanf(fp,"%s",buffer);
		string str=buffer;
		quoatation+=str;
		
	}//got quoatation
	return quoatation;

}

