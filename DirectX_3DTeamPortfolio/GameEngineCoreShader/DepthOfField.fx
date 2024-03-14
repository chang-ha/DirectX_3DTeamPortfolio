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


PixelOutPut DepthOfField_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
Texture2D BlurTex : register(t1);
Texture2D PosTex : register(t2);
SamplerState DiffuseTexSampler : register(s0);

#define FocalPlane 800.0f
#define MaxBlurSize 5000.0f
#define MinBlurSize 2000.0f

float4 DepthOfField_PS(PixelOutPut _Input) : SV_Target0
{
    float3 Result = (float4) 0;
    
    float3 viewSpacePos = PosTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy).rgb;
    
    float viewSpaceDepth = viewSpacePos.z;
    
    float COC = (FocalPlane - viewSpaceDepth);
    
    //크면 더 멀리 있다는 뜻
    if (COC < 0.0f)
    {
        COC /= MaxBlurSize;
    }
    else
    {
        COC /= MinBlurSize;
    }
    
    COC = abs(COC);
    
    COC = saturate(COC);
    
    
    float3 colorSharp = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy).rgb;
   
    float3 colorBlur = BlurTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy).rgb;
    
    Result = lerp(colorSharp, colorBlur, COC);
    
   
    return float4(Result, 1.0f);
}