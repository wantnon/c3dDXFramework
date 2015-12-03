

#include "c3dTexture.h"
void Cc3dTexture::initWithFile(const string&fileName){
		m_fileName=fileName;
		// Use D3DX to create a texture from a file based image
		WCHAR wcstr[MAX_WCSTR_LEN];
		MultiByteToWideChar(0,0,fileName.c_str(),-1,wcstr,MAX_WCSTR_LEN);
		D3DXCreateTextureFromFile( g_pd3dDevice, wcstr, &m_pTexture );
		assert(m_pTexture);
	}