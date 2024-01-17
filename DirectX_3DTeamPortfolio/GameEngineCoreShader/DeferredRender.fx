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
Texture2D PositionTex : register(t1);
Texture2D NormalTex : register(t2);
SamplerState POINTWRAP : register(s0);

struct DeferredRenderOutPut
{
    float4 DeferredColor : SV_Target0;
    float4 DifColor : SV_Target1;
    float4 DifLight : SV_Target2;
    float4 SpcLight : SV_Target3;
    float4 AmbLight : SV_Target4;
};

DeferredRenderOutPut DeferredRender_PS(PixelOutPut _Input)
{
    DeferredRenderOutPut Result = (DeferredRenderOutPut) 0;
    
    float4 Color = DifColorTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Pos = PositionTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Normal = NormalTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    Result.DifColor = Color;
    Result.DifLight = CalDiffuseLight(Normal, AllLight[0]);
    Result.SpcLight = CalSpacularLight(Pos, Normal, AllLight[0]);
    Result.AmbLight = CalAmbientLight(AllLight[0]);
    
    
    float A = Result.DifColor.w;
    Result.DeferredColor.xyz = Result.DifColor.xyz * (Result.DifLight.xyz + Result.SpcLight.xyz + Result.AmbLight.xyz);
    Result.DeferredColor.a = 1.0f;
    
    return Result;
}