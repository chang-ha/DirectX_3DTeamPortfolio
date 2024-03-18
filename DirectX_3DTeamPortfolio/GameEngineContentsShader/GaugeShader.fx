#include "../GameEngineCoreShader/Transform.fx"
#include "../GameEngineCoreShader/RenderBase.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut GaugeShader_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    return Result;
}

cbuffer GaugeInfo : register(b3)
{
    float Gauge;
    int FromLeft;
    int Temp0;
    int Temp1;
};


Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 GaugeShader_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
  
    float GaugeRatio = Gauge; // 0 ~ 1
    if (0 != FromLeft) // 오른쪽부터 줄어들때
    {
        GaugeRatio *= -1.0f;
        GaugeRatio += 1.0f;
        
        if (_Input.TEXCOORD.x < GaugeRatio)
        {
            discard;
        }
    }
    else
    {
        if (_Input.TEXCOORD.x > GaugeRatio)
        {
            discard;
        }
    }
    
    if (0.0f >= Color.a)
    {
        discard;
    }
    
    return Color;
}

