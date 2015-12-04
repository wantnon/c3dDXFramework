
//----begin yang chao
#include <tchar.h>//must put at the very top
#include <iostream>
using namespace std;
//----end yang chao

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )


#include "c3d/c3d.h"


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

	
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitScene()
//-----------------------------------------------------------------------------
HRESULT InitScene()
{
	//create font
	//g_pFont
	//ref: http://blog.csdn.net/kesalin/article/details/1820419
	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));
	fontDesc.Height         = 25;    
	fontDesc.Width          = 12;    
	fontDesc.Weight         = 500;   // 0(light) - 1000(bold)
	fontDesc.Italic         = false;   
	fontDesc.CharSet        = DEFAULT_CHARSET;
	fontDesc.OutputPrecision   = 0;              
	fontDesc.MipLevels       = D3DX_DEFAULT;          
	fontDesc.Quality        = 0;           
	fontDesc.PitchAndFamily = 0;           
	wcscpy(fontDesc.FaceName, _T("Times New Roman"));//strcpy wchar: http://blog.csdn.net/shiwei0124/article/details/4531651 
	D3DXCreateFontIndirect(g_pd3dDevice,&fontDesc,&g_pFont);
	//g_pSprite
	// Create a sprite to help batch calls when drawing many lines of text
    D3DXCreateSprite( g_pd3dDevice, &g_pSprite ) ;



    //cull face 
	//CCW is dx9's default value
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_CCW);// D3DCULL_NONE );


    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	//vertex declaration
	g_pd3dDevice->CreateVertexDeclaration(vertexDecl,&_vertexDecl);

	//set viewport
	D3DVIEWPORT9 viewport_dx={g_viewport.x(),g_viewport.y(),g_viewport.z(),g_viewport.w(),g_minZ,g_maxZ};  
	g_pd3dDevice->SetViewport(&viewport_dx);  

	

	//camera
	Cc3dScene::getInstance()->m_camera->init(g_viewport);
	Cc3dScene::getInstance()->m_camera->m_pos.init(0,2,-3,1);
	Cc3dScene::getInstance()->m_camera->m_center.init(0,0,0,1);
	//lightSource
	Cc3dScene::getInstance()->m_lightSource->m_dir.init(1,-1,0,0);
	Cc3dScene::getInstance()->m_lightSource->m_ambient.init(0.2,0.2,0.2,1);

	//texture
	Cc3dTexture*texture1=Cc3dTextureCache::getInstance()->add("box.bmp");
	Cc3dTexture*texture2=Cc3dTextureCache::getInstance()->add("basketballTex.bmp");


	//material
	Cc3dMaterial*mat_diffuse1=NULL;
	{
		Cc3dMaterial*material=new Cc3dMaterial();
		material->initWithEffectFile("shader/diffuse.fx","shader/diffuse.var");
		material->addTexture(texture1);
		material->m_effect->setSampler("g_mainTexture",texture1);
		Cc3dMaterialManager::getInstance()->m_materialList.push_back(material);
		mat_diffuse1=material;
	}
	Cc3dMaterial*mat_diffuse2=NULL;
	{
		Cc3dMaterial*material=new Cc3dMaterial();
		material->initWithEffectFile("shader/diffuse.fx","shader/diffuse.var");
		material->addTexture(texture2);
		material->m_effect->setSampler("g_mainTexture",texture2);
		Cc3dMaterialManager::getInstance()->m_materialList.push_back(material);
		mat_diffuse2=material;
	}
	Cc3dMaterial*mat_axis=NULL;
	{
		Cc3dMaterial*material=new Cc3dMaterial();
		material->initWithEffectFile("shader/color.fx","shader/color.var");
		Cc3dMaterialManager::getInstance()->m_materialList.push_back(material);
		mat_axis=material;
	}
	Cc3dMaterial*mat_color=NULL;
	{
		Cc3dMaterial*material=new Cc3dMaterial();
		material->initWithEffectFile("shader/color.fx","shader/color.var");
		material->m_effect->setUniform("g_tintColor",cc3dv4(1,1,0,1));
		Cc3dMaterialManager::getInstance()->m_materialList.push_back(material);
		mat_color=material;
	}
	
	Cc3dMaterial*mat_depthBias=NULL;
	{
		Cc3dMaterial*material=new Cc3dMaterial(); 
		material->initWithEffectFile("shader/diffuse.fx","shader/diffuse.var");
		material->addTexture(texture1);
		material->m_effect->setSampler("g_mainTexture",texture1);
		Cc3dMaterialManager::getInstance()->m_materialList.push_back(material);
		mat_depthBias=material;

		material->m_onRenderEnter=[](){
			//depth bias, ref: http://stackoverflow.com/questions/17199817/directx11-wireframe-z-fighting-help-or-why-d3d11-rasterizer-desc-depthbias-is-a
			g_pd3dDevice->SetRenderState(D3DRS_DEPTHBIAS,990000000 );
			g_pd3dDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,1);
		};
		material->m_onRenderLeave=[](){
			g_pd3dDevice->SetRenderState(D3DRS_DEPTHBIAS,0);
			g_pd3dDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,0);
		};
	}

	
	//node1
	Cc3dNode*node1=NULL;
	{
		//mesh
		Cc3dMesh*mesh=new Cc3dMesh();
		makeCube(mesh);
		//vb
		Cc3dVB*vb=new Cc3dVB();

		//ib
		Cc3dIB*ib=new Cc3dIB();
		Cc3dMaterialManager::getInstance()->connect(ib,mat_diffuse1);
	
		//node
		Cc3dNode*node=new Cc3dNode();
		node->m_name="node1";
		node->addComponent(mesh);
		node->addComponent(vb);
		node->addComponent(ib);

		vb->createVB();
		vb->updateVB();
	
		ib->createIB();
		ib->updateIB();

		node1=node;
	}
	//node2
	Cc3dNode*node2=NULL;
	{
		//mesh
		Cc3dMesh*mesh=new Cc3dMesh();
		makeSphere(mesh,30,30);
		//vb
		Cc3dVB*vb=new Cc3dVB();

		//ib
		Cc3dIB*ib=new Cc3dIB();
		Cc3dMaterialManager::getInstance()->connect(ib,mat_diffuse2);
	
		//node
		Cc3dNode*node=new Cc3dNode();
		node->m_name="node2";
		node->addComponent(mesh);
		node->addComponent(vb);
		node->addComponent(ib);


		vb->createVB();
		vb->updateVB();

		ib->createIB();
		ib->updateIB();
		
		
		node->moveInParent(1,0,0);

		node2=node;
	}
	//node3
	Cc3dNode*node3=NULL;
	{
		//vb
		Cc3dVB*vb=new Cc3dVB();
		//ib
		Cc3dIB*ib=new Cc3dIB();
		ib->m_primitiveType=eLineList;
		Cc3dMaterialManager::getInstance()->connect(ib,mat_axis);

		//mesh
		Cc3dMesh*mesh=new Cc3dMesh();
		makeAxis(mesh,3);
		
		//node
		Cc3dNode*node=new Cc3dNode();
		node->m_name="node3";
		node->addComponent(mesh);
		node->addComponent(vb);
		node->addComponent(ib);


		vb->createVB();
		vb->updateVB();

		ib->createIB();
		ib->updateIB();

		node3=node;
	}
	//node4
	Cc3dNode*node4=NULL;
	{
		//mesh
		Cc3dMesh*mesh=new Cc3dMesh();
		makeCube(mesh);
		//vb
		Cc3dVB*vb=new Cc3dVB();
		//ib
		Cc3dIB*ib=new Cc3dIB();
		Cc3dMaterialManager::getInstance()->connect(ib,mat_depthBias);

		//wireFrameRender
		Cc3dWireFrameIB*wireFrameIB=new Cc3dWireFrameIB();
		Cc3dMaterialManager::getInstance()->connect(wireFrameIB,mat_color);

		//node
		Cc3dNode*node=new Cc3dNode();
		node->m_name="node4";
		node->addComponent(mesh);
		node->addComponent(vb);
		node->addComponent(ib);
		node->addComponent(wireFrameIB);
			
		vb->createVB();
		vb->updateVB();

		ib->createIB();
		ib->updateIB();

		wireFrameIB->createIB();
		wireFrameIB->updateIB();

		node->rotate(cc3dv4(0,1,0,0),20);
		node->setScale(0.5,0.5,0.5);
		node->moveInParent(-1,0,0);

		node4=node;
	}
	//node5
	Cc3dNode*node5=NULL;
	{
		//screenLineRender
		Cc3dScreenLineRender*screenLineRender=new Cc3dScreenLineRender();
		const float margin=10;
		screenLineRender->m_posList.push_back(cc3dv2(0+margin,0+margin));
		screenLineRender->m_posList.push_back(cc3dv2(0+margin,g_viewport.w()-margin));
		screenLineRender->m_posList.push_back(cc3dv2(g_viewport.z()-margin,g_viewport.w()-margin));
		screenLineRender->m_posList.push_back(cc3dv2(g_viewport.z()-margin,0+margin));
		screenLineRender->m_posList.push_back(cc3dv2(0+margin,0+margin));
		//node
		Cc3dNode*node=new Cc3dNode();
		node->m_name="node5";
		node->addComponent(screenLineRender);

		node5=node;
	}
	
	//add to scene
	Cc3dScene::getInstance()->m_root->addChild(node1);
	Cc3dScene::getInstance()->m_root->addChild(node2);
	Cc3dScene::getInstance()->m_root->addChild(node3);
	Cc3dScene::getInstance()->m_root->addChild(node4);
	Cc3dScene::getInstance()->m_root->addChild(node5);



    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	//to do
	Cc3dScene::getInstance()->clean();

//------------------put at last
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();

	if(	g_pFont	!=NULL	)
		g_pFont->Release();
	if(g_pSprite!=NULL)
		g_pSprite->Release();
}

//-----------------------------------------------------------------------------
// RenderText()
//-----------------------------------------------------------------------------
VOID RenderText(HWND hWnd){
	g_pSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );

	RECT winRect;
	GetClientRect(hWnd,&winRect);

	RECT textRect;
	textRect.top=winRect.top;
	textRect.left=winRect.left;
	textRect.right=winRect.right;
	textRect.bottom=(winRect.top+winRect.bottom)*0.4;
	g_pFont->DrawText(g_pSprite,_T("array key: rotate"),-1,&textRect,DT_CENTER|DT_VCENTER,D3DCOLOR_XRGB(255, 255, 255));
	
	g_pSprite->End();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render(HWND hWnd)
{
    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB( 128, 128, 128 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

		
		//render scene
		Cc3dScene::getInstance()->render();
	
		//render text
		RenderText(hWnd);
			

        // End the scene
        g_pd3dDevice->EndScene();
		


    }

	

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	
	
}





//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
	case WM_MOUSEMOVE:
		{
			int xPos = LOWORD(lParam); 
			int yPos = HIWORD(lParam);
			g_mosPosFoe=g_mosPos;
			g_mosPos=Cc3dVector2(xPos,yPos);
			
			if(g_mosIsLDown){
				
				
			
				

			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int xPos = LOWORD(lParam); 
			int yPos = HIWORD(lParam);
		

			
			g_mosPosFoe=g_mosPos;
			g_mosPos=Cc3dVector2(xPos,yPos);
	
			g_mosIsLDown=true;

		


			////cout<<"mos:"<<xPos<<" "<<yPos<<endl;
		}
		break;
	case WM_LBUTTONUP:
		{
			int xPos = LOWORD(lParam); 
			int yPos = HIWORD(lParam);
	
			g_mosPosFoe=g_mosPos;
			g_mosPos=Cc3dVector2(xPos,yPos);

			g_mosIsLDown=false;

			

		
	
		}
		break;
	case WM_KEYDOWN:
		{
			//vk table ref: http://www.cnblogs.com/mr-wid/archive/2012/11/20/2779781.html
			switch(wParam)
			{
			case 65://a
				{
					
					
				}
				break;
			case 83://s
				{


				}
				break;
			case 87://w
				{



				}
				break;
			case 68://d
				{

				}

				break;
			case 81://q
				{


				}
				break;
			case 69://e
				{

				}
				break;
			case 78://n
				{

				}
				break;
			case 112://F1
				{
	

						
				}
				break;
			case 113://F2
				{


				}
				break;
			case VK_LEFT:
				{
					float dA=5;
					Cc3dScene::getInstance()->m_root->rotate(cc3dv4(0,1,0,0),dA);
				}
				break;
			case VK_RIGHT:
				{
					float dA=-5;
					Cc3dScene::getInstance()->m_root->rotate(cc3dv4(0,1,0,0),dA);
		
				}
				break;
			case VK_UP:
				{
					float dA=5;
					Cc3dScene::getInstance()->m_root->rotate(cc3dv4(1,0,0,0),dA);
				
				}
				break;
			case VK_DOWN:
				{
					float dA=-5;
					Cc3dScene::getInstance()->m_root->rotate(cc3dv4(1,0,0,0),dA);
			
				}
				break;
			}
		}
		break;
	case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		}
		break;
	}

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

 


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	//----begin yang chao
	//----create console
	AllocConsole();   // 建立控制台
    SetConsoleTitle(_T("Debug Output"));      // 设置控制台窗口标题
	// 重定向 STDIN
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONIN$", "r+t", stdin);
		if(eno!=0){//不成功
			MessageBox(NULL,_T("重定向stdin失败!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			exit(0);
		}
	}
	// 重定向STDOUT
	{
		FILE*fp;
		errno_t eno=freopen_s(&fp,"CONOUT$", "w+t", stdout);
		if(eno!=0){//不成功
			MessageBox(NULL,_T("重定向stdout失败!"),_T("error"),MB_OK|MB_ICONEXCLAMATION);
			exit(0);
		}
	
	}
	//----end yang chao


    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"c3d DX framework -- wantnon 2015-12-2",
                              WS_OVERLAPPEDWINDOW^WS_THICKFRAME, 100, 100, g_winWidth, g_winHeight,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the scene 
        if( SUCCEEDED( InitScene() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else{

                    Render(hWnd);
				}
            }
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



