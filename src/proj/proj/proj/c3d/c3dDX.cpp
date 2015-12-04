#include "c3dDX.h"

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
ID3DXFont*              g_pFont=NULL;
ID3DXSprite*            g_pSprite = NULL;       // Sprite for batching draw text calls
float g_minZ=0;
float g_maxZ=1;

D3DVERTEXELEMENT9 vertexDecl[]=
{
	{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,0},
	{0,12,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,0},
	{0,24,D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,0},
	{0,40,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0},
	D3DDECL_END()
};
IDirect3DVertexDeclaration9* _vertexDecl=NULL;