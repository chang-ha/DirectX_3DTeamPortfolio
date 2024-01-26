#include "Light.fx"

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

PixelOutPut DeferredRender_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DifColorTex : register(t0);
Texture2D DifLightTex : register(t1);
Texture2D SpcLightTex : register(t2);
Texture2D AmbLightTex : register(t3);
Texture2D ShadowTex : register(t4);
SamplerState POINTWRAP : register(s0);

float4 DeferredRender_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Result = (float4) 0;
    
    float4 DifColor = DifColorTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    
    if (0 >= DifColor.a)
    {
        clip(-1);
    }
    
    float4 DifLight = DifLightTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 SpcLight = SpcLightTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 AmbLight = AmbLightTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Shadow = ShadowTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    
    float A = DifColor.w;
    Result.xyz = DifColor.xyz * (DifLight.xyz + SpcLight.xyz + AmbLight.xyz);
    
    if (0.0f < Shadow.x)
    {
        Result.xyz *= 0.2f;
    }
    
    Result.a = 1.0f;
    
    return Result;
}