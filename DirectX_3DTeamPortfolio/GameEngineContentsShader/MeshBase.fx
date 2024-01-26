#include "Transform.fx"
#include "RenderBase.fx"
#include "Light.fx"

struct GameEngineVertex3D
{
    float4 POSITION : POSITION;
    float4 NORMAL : NORMAL;
    float4 TEXCOORD : TEXCOORD;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;
};



void Mesh_VS_Update(inout GameEngineVertex3D _Input,inout PixelOutPut Result)
{
    //PixelOutPut Result = (PixelOutPut) 0;
    
    _Input.POSITION.w = 1.0f;
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    _Input.NORMAL.w = 0.0f;
    Result.VIEWNORMAL = mul(_Input.NORMAL, WorldViewMatrix);
    Result.VIEWNORMAL.w = 0.0f;
    
    _Input.TANGENT.w = 0.0f;
    Result.VIEWTANGENT = mul(_Input.TANGENT, WorldViewMatrix);
    Result.VIEWTANGENT.w = 0.0f;
    
    _Input.BINORMAL.w = 0.0f;
    Result.VIEWBINORMAL = mul(_Input.BINORMAL, WorldViewMatrix);
    Result.VIEWBINORMAL.w = 0.0f;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
    //return _Result;
}


struct DeferrdOut
{
    float4 DifColor : SV_Target1;
    float4 PosColor : SV_Target2;
    float4 NorColor : SV_Target3;
    float4 SpcColor : SV_Target4;
};



Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);
Texture2D NormalTexture : register(t2);
SamplerState NormalTextureSAMPLER : register(s2);
Texture2D SpecularTexture : register(t3);
SamplerState SpecularTextureSAMPLER : register(s3);

void Mesh_PS_Update(inout PixelOutPut _Input, inout DeferrdOut _Result)
{
    //PixelOut Result = (PixelOut) 0.0f;
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    
    
    
    //if (0.7f >= Color.a)
    //{
    //    //clip(-1);
    //}
     
    Color.w = 1.0f;
    
    _Result.DifColor = Color;
    _Result.PosColor = _Input.VIEWPOSITION;
   ///_Result.SpcColor = float4(SpecularColor, 1.0f);
    
    
    if(0 != IsSpecular)
    {
        _Result.DifColor.w = float4(SpecularTexture.Sample(SpecularTextureSAMPLER, _Input.TEXCOORD.xy).rgb, 1.0f).x;
        _Result.SpcColor = float4(1.f, 0.f, 0.f, 1.f);
    }
    else
    {
        //_Result.SpcColor = float4(1.f, 1.f, 1.f,1.f);
        _Result.SpcColor = float4(0.f, 0.f, 1.f,1.f);

    }
    
    
    
    if (0 != IsNormal)
    {
        _Result.NorColor = -NormalTexCalculate(NormalTexture, NormalTextureSAMPLER, _Input.TEXCOORD, _Input.VIEWTANGENT, _Input.VIEWBINORMAL, _Input.VIEWNORMAL);
    }
    else
    {
        _Result.NorColor = _Input.VIEWNORMAL;
    }
    
    
   
    _Result.NorColor.w = 1.0f;
    
}