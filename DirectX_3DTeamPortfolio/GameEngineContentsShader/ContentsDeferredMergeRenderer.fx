

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

PixelOutPut ContentsDeferredMergeRender_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut)0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DifColorTex : register(t0);
Texture2D DifLightTex : register(t1);
Texture2D SpcLightTex : register(t2);
Texture2D AmbLightTex : register(t3);
Texture2D ShadowTex : register(t4);
Texture2D SpecularTex : register(t5);
Texture2D HBAOTex : register(t6);
Texture2D PBRTex : register(t7);
SamplerState POINTClamp : register(s0);
SamplerState LINEARClamp : register(s1);



float4 ContentsDeferredMergeRender_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Result = (float4) 0;
    
    
    float4 DifColor = DifColorTex.Sample(POINTClamp, _Input.TEXCOORD.xy);
    if (DifColor.w <= 0.0f)
    {
        clip(-1);
    }
    
    DifColor.xyz = pow(DifColor.xyz, 2.2f); //gamma
    
    float4 DifLight = DifLightTex.Sample(POINTClamp, _Input.TEXCOORD.xy);
    float4 SpcLight = SpcLightTex.Sample(POINTClamp, _Input.TEXCOORD.xy);
    float4 AmbLight = AmbLightTex.Sample(POINTClamp, _Input.TEXCOORD.xy);
    float4 Shadow = ShadowTex.Sample(LINEARClamp, _Input.TEXCOORD.xy);
    float4 PBR = PBRTex.Sample(POINTClamp, _Input.TEXCOORD.xy);
    float3 SpecularColor = SpecularTex.Sample(POINTClamp, _Input.TEXCOORD.xy).rgb;
    float3 HBAOTexColor = HBAOTex.Sample(LINEARClamp, _Input.TEXCOORD.xy).rgb;
    
    
    //SpcLight.xyz *= SpecularColor;
    
    //float A = DifColor.w;
    Result.xyz = PBR.xyz;
    //Result.xyz = DifColor.xyz * (DifLight.xyz + SpcLight.xyz );

    
    if (0.0f < Shadow.x)
    {
        Result.xyz *= (1.0f - Shadow.x);
        //Result.xyz *= 0.1f;
    }
    
    Result.xyz += DifColor.xyz * AmbLight.xyz;
    
    Result.xyz *= HBAOTexColor;
    Result.xyz = pow(Result.xyz, 1.0f / 2.2f);
    Result.a = 1.0f;
    
    return Result;
}