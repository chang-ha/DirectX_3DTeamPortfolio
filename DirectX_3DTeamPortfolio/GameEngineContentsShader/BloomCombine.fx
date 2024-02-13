
struct GameEngineVertex3D
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


PixelOutPut BloomCombine_VS(GameEngineVertex3D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
Texture2D BlurTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);
SamplerState BlurTexSampler : register(s1);

float4 BloomCombine_PS(PixelOutPut _Input) : SV_Target0
{
    
    const float gamma = 2.2;
    
    float3 Result = (float4) 0.0f;
    
    float3 BlurColor = pow(BlurTex.Sample(BlurTexSampler, _Input.TEXCOORD.xy).rgb, gamma);
    
    float3 Color = pow(DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy).rgb, gamma);
    
    Result = Color + BlurColor;
    
    Result = pow(Result, 1 / gamma);
    
    //// tone mapping
    //float3 ToneMap = float3(1.0f, 1.0f, 1.0f) - exp(-Color * 1.0f);
    //ToneMap = pow(ToneMap, float3(1.0f / gamma));
    
    //Result = float4(ToneMap, 1.0f);
    
    return float4(Result, 1.0f);
}