
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


PixelOutPut BloomBright_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 BloomBright_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Result = (float4) 0.0f;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    float Brightness = dot(Color.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    
    
    if (Brightness > 1.0f)
    {
        Result = float4(Color.rgb, 1.0f);
    }
    else
    {
        Result = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    return Result;
}