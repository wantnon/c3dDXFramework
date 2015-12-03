

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------

float4x4 g_mWorld;                  // World matrix for object
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

texture g_mainTexture;              // Color texture for mesh
float3 g_lightDir;

float4 g_diffuseM=float4(0.8,0.8,0.8,1);
float4 g_ambientM=float4(1,1,1,1);
float4 g_diffuseL;
float4 g_ambientL;

float4 g_tintColor=float4(1,1,1,1);


//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler MeshTextureSampler = 
sampler_state
{
    Texture = <g_mainTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------
//output position must be float4, see: http://www.myexception.cn/program/1065001.html
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 mainColor  : COLOR0;     // main vertex color (note that COLOR0 is clamped from 0..1)
    float2 TextureUV  : TEXCOORD0;  // vertex texture coords 
};


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT RenderSceneVS( float3 vPos : POSITION, 
                         float3 vNormal : NORMAL,
						 float4 vColor : COLOR0,
                         float2 vTexCoord0 : TEXCOORD0 )
{
    VS_OUTPUT Output;
    float3 vNormalWorldSpace;
   

    // Transform the position from object space to homogeneous projection space
    Output.Position = mul(float4(vPos,1), g_mWorldViewProjection);
    
    // Transform the normal from object space to world space    
    vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld)); // normal (world space)
    
	// Compute simple directional lighting equation



        
	float4 diffuseColor=g_diffuseL*g_diffuseM* max(0,dot(vNormalWorldSpace, -g_lightDir));
	float4 ambientColor=g_ambientL*g_ambientM;

    Output.mainColor = (diffuseColor +ambientColor)*vColor;   
        
    Output.mainColor.a = 1.0f; 

    
    // Just copy the texture coordinate through 

    Output.TextureUV = vTexCoord0; 
  
    
    return Output;    
}


//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 RGBColor : SV_TARGET;  // Pixel color, must be float4
};


//--------------------------------------------------------------------------------------
// This shader outputs the pixel's color by modulating the texture's
//       color with diffuse material color
//--------------------------------------------------------------------------------------
PS_OUTPUT RenderScenePS( VS_OUTPUT In) 
{ 
    PS_OUTPUT Output;

    // Lookup mesh texture and modulate it with diffuse
    Output.RGBColor = tex2D(MeshTextureSampler, In.TextureUV) * In.mainColor *g_tintColor;


    return Output;
}


//--------------------------------------------------------------------------------------
// Renders scene to render target
//--------------------------------------------------------------------------------------
technique basicTech
{
    pass P0
    {          
        VertexShader = compile vs_2_0 RenderSceneVS();
        PixelShader  = compile ps_2_0 RenderScenePS(); // trivial pixel shader (could use FF instead if desired)
    }
}
