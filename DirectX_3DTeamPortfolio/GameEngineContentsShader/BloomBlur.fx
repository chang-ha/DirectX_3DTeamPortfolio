#include "RenderBase.fx"

#define GAU 13




static const float Weight[GAU] =
{
    0.0561, 0.1353, 0.278, 0.4868, 0.7261, 0.9231, 1, 0.9231, 0.7261, 0.4868, 0.278, 0.1353, 0.0561
};

static const float Total = 6.2108;



float4 GaussianBlur(Texture2D _Tex, SamplerState _Sampler, float2 _Scale, float2 _PixelUV)
{
    // _Scale 1280 720
    float2 PixelSize = float2(1.0f / _Scale.x, 1.0f / _Scale.y);
    float2 StartUV = _PixelUV.xy;  /*+ (-PixelSize * 6.0f);*/
    float2 CurUV = StartUV;
    float3 ResultX = (float4) 0.0f;
    float3 ResultY = (float4) 0.0f;
    
    
    // X축 블러 패스
    for (int X = -6; X < 6; ++X)
    {
        
        CurUV = StartUV + float2(PixelSize.x * X,0.0f );
        ResultX += _Tex.Sample(_Sampler, CurUV) * Weight[6 + X];
    }
    
    ResultX /= Total;
    // Y축 블러 패스
    for (int Y = -6; Y < 6; ++Y)
    {
        CurUV = StartUV + float2(0.0f, PixelSize.y * Y);
        ResultY += _Tex.Sample(_Sampler, CurUV) * Weight[6 + Y];
    }
    
    ResultY /= Total;
    float4 Result = float4(ResultY + ResultX, 1.0f);
    
    //Result.rgb = Result.rgb / Total;
    //Result.w = 1.0f;
 
    //for (int Y = 0; Y < GAUY; ++Y)
    //{
    //    for (int X = 0; X < GAUX; ++X)
    //    {
    //        Result += _Tex.Sample(_Sampler, CurUV) * Gau[Y][X];
    //        CurUV.x += PixelSize.x;
    //    }
        
    //    CurUV.x = StartUV.x;
    //    CurUV.y += PixelSize.y;
    //}
    
    return Result;
}





struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // 픽셀쉐이더에 보내느 ㄴ역
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};


PixelOutPut BloomBlur_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D BrightTex : register(t0);
SamplerState BrightTexSampler : register(s0);

// StructuredBuffer<float4> ArrScreenSize : register(t11);

float4 BloomBlur_PS(PixelOutPut _Input) : SV_Target0
{
    return GaussianBlur(BrightTex, BrightTexSampler, ScreenSize.xy, _Input.TEXCOORD.xy);
}