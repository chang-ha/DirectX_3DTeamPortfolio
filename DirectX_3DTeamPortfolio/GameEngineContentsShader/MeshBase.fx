#include "Transform.fx"
#include "RenderBase.fx"

struct GameEngineVertex3D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};



void Mesh_VS_Update(inout GameEngineVertex3D _Input,inout PixelOutPut _Result)
{
    //PixelOutPut Result = (PixelOutPut) 0;
    
    _Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    _Result.TEXCOORD = _Input.TEXCOORD;
    
    //return _Result;
}


struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target1;
    float4 Color3 : SV_Target1;
    float4 Color4 : SV_Target1;
    float4 Color5 : SV_Target1;
    float4 Color6 : SV_Target1;
    float4 Color7 : SV_Target1;
};



Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);

void Mesh_PS_Update(inout PixelOutPut _Input, inout PixelOut _Result)
{
    
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    Color.a = 1;
    
    if (0 < Target0)
    {
        _Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        _Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        _Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        _Result.Color3 = Color;
    }
}