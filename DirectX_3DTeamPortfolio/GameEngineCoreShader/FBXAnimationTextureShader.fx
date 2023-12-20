#include "Transform.fx"
#include "FBXAnimation.fx"
#include "RenderBase.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    // 픽셀쉐이더에 보내느 ㄴ역
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut FBXTextureShader_VS(GameEngineVertex2D _Input)
{
    // _Input 0.5 0.5
    
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는것
    PixelOutPut Result = (PixelOutPut)0;
    _Input.POSITION.w = 1.0f;
    
    if (0 != IsAnimation)
    {
        Skinning(_Input.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    }
    
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

// SV_Target0
// SV_Target1
// SV_Target2
// SV_Target3
// SV_Target4

Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);

PixelOut FBXTextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut)0.0f;
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    Color.a = 1;
    
    if (0 < Target0)
    {
        Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        Result.Color3 = Color;
    }
    
    return Result;
}