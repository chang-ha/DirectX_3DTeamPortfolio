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
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWPOSITION : POSITION;
    float4 WorldPOSITION : POSITION1;
    float4 VIEWNORMAL : NORMAL;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;    
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
    Result.TEXCOORD = _Input.TEXCOORD;
    
    //return _Result;
}


