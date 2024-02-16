#include "MeshBase_Header.fx"


PixelOutPut ContentsStaticAlphaMesh_VS(GameEngineVertex3D _Input)
{
    
    PixelOutPut Result = (PixelOutPut) 0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    
    Mesh_VS_Update(_Input, Result);
    
    return Result;
}



struct PixelOut
{
    float4 DifColor : SV_Target0;
};


Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);

PixelOut ContentsStaticAlphaMesh_PS(PixelOutPut _Input) 
{
    PixelOut Result = (PixelOut) 0.0f;
   
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    
   

    Result.DifColor = Color;
    
  
    return Result;
}