#include "Transform.fx"
#include "RenderBase.fx"
#include "Normal.fx"

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
    // 픽셀쉐이더에 보내느 ㄴ역
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;
    float4 WorldPOSITION : POSITION1;
};



void Mesh_VS_Update(inout GameEngineVertex3D _Input, inout PixelOutPut Result)
{
    //PixelOutPut Result = (PixelOutPut) 0;
    
    _Input.POSITION.w = 1.0f;
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    Result.WorldPOSITION = mul(_Input.POSITION, WorldMatrix);
    Result.WorldPOSITION.w = 1.0f;
    
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
    Result.TEXCOORD = _Input.TEXCOORD * TEXCOORDMult; // 특수 맵 텍스쳐용 
    
    //return _Result;
}

struct DeferrdOut
{
    float4 DifColor : SV_Target1;
    float4 PosColor : SV_Target2;
    float4 NorColor : SV_Target3;
    float4 SpcColor : SV_Target4;
    float4 MatColor : SV_Target5;
    //float4 WorldPosColor : SV_Target6;
};



Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);

void Mesh_PS_Update(inout PixelOutPut _Input, inout DeferrdOut _Result)
{
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    
    
    if (AlphaValue > 0.0f || AlphaValue > 1.0f)
    {
        if (AlphaValue >= Color.a)
        {
            clip(-1);
        }
    }
     
    Color.w = 1.0f;    
    _Result.DifColor = Color;
    _Result.PosColor = _Input.VIEWPOSITION;    
    //_Result.WorldPosColor = _Input.WorldPOSITION;
           
    _Result.SpcColor = float4(0.006f, 0.006f, 0.004f, 1.f);
     
       
    _Result.NorColor = _Input.VIEWNORMAL;   
    _Result.NorColor.w = 1.f;
    
    
    if (Roughness < 0.0f)
    {
        _Result.MatColor.x = 0.5f; //Roughness
    }
    else
    {
        _Result.MatColor.x = Roughness;
    }
    
    if (Metalic < 0.0f)
    {
        _Result.MatColor.y = 0.0f; //Metalic
    }
    else
    {
        _Result.MatColor.y = Metalic;
    }
    _Result.MatColor.z = 1.0f;
    
    _Result.MatColor.w = 1.0f;
    
}