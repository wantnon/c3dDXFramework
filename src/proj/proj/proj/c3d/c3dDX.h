#ifndef _c3dDX_H_
#define _c3dDX_H_
#include <d3dx9.h>
#include <vector>
using namespace std;
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

extern LPDIRECT3D9             g_pD3D ;
extern LPDIRECT3DDEVICE9       g_pd3dDevice ;
extern ID3DXFont*              g_pFont;
extern ID3DXSprite*            g_pSprite; 

extern float g_minZ;
extern float g_maxZ;

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DXVECTOR3 normal; //normal
    D3DXVECTOR4 color;    // The color
    FLOAT tu, tv;   // The texture coordinates

};

extern D3DVERTEXELEMENT9 vertexDecl[];
extern IDirect3DVertexDeclaration9* _vertexDecl;

#endif