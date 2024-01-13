
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


PixelOutPut BloomBright_VS(GameEngineVertex3D _Input)
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

float4 BloomBright_PS(PixelOutPut _Input) : SV_Target0
{
    
    const float gamma = 2.2;
    
    float4 Result = (float4) 0.0f;
    
    float3 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy).rgb;
    
    float3 BlurColor = BlurTex.Sample(BlurTexSampler, _Input.TEXCOORD.xy).rgb;
    
    Color += BlurColor; // additive blending
    
    
    // tone mapping
    float3 ToneMap = float3(1.0f, 1.0f, 1.0f) - exp(-Color * 1.0f);
    ToneMap = pow(ToneMap, float3(1.0f / gamma));
    
    Result = float4(ToneMap, 1.0f);
    
    return Result;
}