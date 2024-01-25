#include "Transform.fx"
#include "RenderBase.fx"
#include "Light.fx"

struct GameEngineVertex
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
    float4 POSITION : SV_Position;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;
};

PixelOutPut FBXStaticShaderDeferred_VS(GameEngineVertex _Input)
{
    // _Input 0.5 0.5
    
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는것
    PixelOutPut Result = (PixelOutPut)0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;

    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;


    Result.VIEWNORMAL = mul(_Input.NORMAL, WorldViewMatrix);
    
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    _Input.NORMAL.w = 0.0f;
    Result.VIEWNORMAL = mul(_Input.NORMAL, WorldViewMatrix);
    // Result.VIEWNORMAL = mul(_Input.NORMAL, WorldMatrix);
    Result.VIEWNORMAL.w = 0.0f;
    
    _Input.TANGENT.w = 0.0f;
    Result.VIEWTANGENT = mul(_Input.TANGENT, WorldViewMatrix);
    // Result.VIEWNORMAL = mul(_Input.NORMAL, WorldMatrix);
    Result.VIEWTANGENT.w = 0.0f;
    
    _Input.BINORMAL.w = 0.0f;
    Result.VIEWBINORMAL = mul(_Input.BINORMAL, WorldViewMatrix);
    // Result.VIEWNORMAL = mul(_Input.NORMAL, WorldMatrix);
    Result.VIEWBINORMAL.w = 0.0f;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    
    Result.TEXCOORD = _Input.TEXCOORD;
    
    return Result;
}

// b버퍼 14
// t텍스처 
// s샘플러 
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러와 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식등을 내부에서
// 사용해주는 용도가 있다.

// 우리 규칙

struct DeferrdOut
{
    float4 DifColor : SV_Target1;
    float4 PosColor : SV_Target2;
    float4 NorColor : SV_Target3;
};

Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);
Texture2D NormalTexture : register(t2);
SamplerState NormalTextureSAMPLER : register(s2);

DeferrdOut FBXStaticShaderDeferred_PS(PixelOutPut _Input)
{
    DeferrdOut Result = (DeferrdOut) 0.0f;
    float4 Color = BaseColor;
    if (0 != IsDiffuse)
    {
        Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    }
    Result.DifColor = Color;
    Result.PosColor = _Input.VIEWPOSITION;
    
    //if (0 != IsNormal)
    //{
    //    _Input.VIEWNORMAL = NormalTexCalculate(NormalTexture, NormalTextureSAMPLER, _Input.TEXCOORD, _Input.VIEWTANGENT, _Input.VIEWBINORMAL, _Input.VIEWNORMAL);
    //}
    
    Result.NorColor = _Input.VIEWNORMAL;
    Result.NorColor.w = 1.0f;
    
    return Result;
}