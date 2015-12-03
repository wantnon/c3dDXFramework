

float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

float4 g_tintColor=float4(1,1,1,1);

//output position must be float4, see: http://www.myexception.cn/program/1065001.html
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 mainColor  : COLOR0;     // main vertex color (note that COLOR0 is clamped from 0..1)
};



VS_OUTPUT RenderSceneVS( float3 vPos : POSITION, 
			 float4 vColor : COLOR0)
{
    VS_OUTPUT Output;

    Output.Position = mul(float4(vPos,1), g_mWorldViewProjection);
   
    Output.mainColor = vColor;  

    
  
    
    return Output;    
}



struct PS_OUTPUT
{
    float4 RGBColor : SV_TARGET;  // Pixel color, must be float4
};



PS_OUTPUT RenderScenePS( VS_OUTPUT In) 
{ 
    PS_OUTPUT Output;
    Output.RGBColor = In.mainColor*g_tintColor;


    return Output;
}



technique basicTech
{
    pass P0
    {          
        VertexShader = compile vs_2_0 RenderSceneVS();
        PixelShader  = compile ps_2_0 RenderScenePS(); // trivial pixel shader (could use FF instead if desired)
    }
}
