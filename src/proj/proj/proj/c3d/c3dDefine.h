

#ifndef __HelloCpp__c3dDefine__
#define __HelloCpp__c3dDefine__

#include <iostream>
#include <string>
using namespace std;
#include <stdarg.h>

#define cc3dv4(x,y,z,w) Cc3dVector4(x,y,z,w)

#define cc3dv2(x,y) Cc3dVector2(x,y)


const float M_PI=3.1415926;
const float M_INF=0.5*(numeric_limits<float>::max)();
const float M_INF_int=0.5*(numeric_limits<int>::max)();
#define MAX_WCSTR_LEN 512



static const int maxC3dLogLen = 16*1024;// The max length of c3dLog message.
void c3dLog(const char * pszFormat, ...);

#define C3DLOG(format, ...)      c3dLog(format, ##__VA_ARGS__)
#endif /* defined(__HelloCpp__c3dDefine__) */