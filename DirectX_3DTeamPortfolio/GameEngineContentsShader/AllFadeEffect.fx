
struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut AllFadeEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

cbuffer FadeInfo : register(b0)
{
    float4 FadeColor;
    float Ratio;
    float Temp0;
    float Temp1;
    float Temp2;
};

Texture2D FadeTex : register(t0);
SamplerState FadeTexSampler : register(s0);

float4 AllFadeEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 TexColor = FadeTex.Sample(FadeTexSampler, _Input.TEXCOORD.xy);
    TexColor.w = 1.0f;
    TexColor.xyz *= (1.0f - Ratio);
    return TexColor;
}