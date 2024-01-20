#include "Light.fx"

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

PixelOutPut ContentsDeferredRender_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut)0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DifColorTex : register(t0);
Texture2D PositionTex : register(t1);
Texture2D NormalTex : register(t2);
Texture2D SpecularTex : register(t3);
Texture2D HBAOTex : register(t4); 
SamplerState POINTWRAP : register(s0);

struct DeferredRenderOutPut
{
    float4 DeferredColor : SV_Target0;  //통합
    float4 DifColor : SV_Target1; // 알베도 색깔
    float4 DifLight : SV_Target2; // 나머지는 그 빛만
    float4 SpcLight : SV_Target3;
    float4 AmbLight : SV_Target4;  //HBAOlight
};

DeferredRenderOutPut ContentsDeferredRender_PS(PixelOutPut _Input)
{
    DeferredRenderOutPut Result = (DeferredRenderOutPut)0;

    float4 Color = DifColorTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Pos = PositionTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Normal = NormalTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
	float3 SpecularColor = SpecularTex.Sample(POINTWRAP, _Input.TEXCOORD.xy).rgb;
    float3 HBAOTexColor = HBAOTex.Sample(POINTWRAP, _Input.TEXCOORD.xy).rgb;

    if (0.0f >= Color.a)
    {
        clip(-1);
    }

   
    
    
    
	float4 DiffuseRatio = (float4) 0.0f;
	float4 SpacularRatio = (float4) 0.0f;
	float4 AmbientRatio = (float4) 0.0f;
    
	
	float constantAttenuation = 1.0f;
	float linearAttenuation = 0.0014;
	float quadraticAttenuation = 0.000007;
       
	for (int i = 0; i < LightCount; ++i)
	{
		float LightPower = 1.0f;
           
           
		if (0 != AllLight[i].LightType)
		{
			float Distance = length(AllLight[i].ViewLightPos.xyz - Pos.xyz);
               
			float attenuation = 1.0 / (constantAttenuation + linearAttenuation * Distance + quadraticAttenuation * Distance * Distance);
			LightPower = attenuation;
		}
           
           
		
			DiffuseRatio += CalDiffuseLightContents(Normal, Pos, AllLight[i]) * LightPower;
			SpacularRatio += CalSpacularLightContents(Pos, Normal, AllLight[i], SpecularColor) * LightPower;
			AmbientRatio += CalAmbientLight(AllLight[i]) * LightPower;
		
	}
       
	//Color.xyz = Color.xyz * (DiffuseRatio.xyz + SpacularRatio.xyz + AmbientRatio.xyz);
	
    
    
	Result.DifColor = Color;
	Result.DifColor.w = 1.0f;
	Result.DifLight = DiffuseRatio;
    Result.DifLight.w = 1.0f;
	Result.SpcLight = CalSpacularLightContents(Pos, Normal, AllLight[0], SpecularColor);
    //Result.AmbLight.xyz = Result.DifColor.xyz * (DiffuseRatio.xyz + SpacularRatio.xyz + AmbientRatio.xyz);
    Result.AmbLight.xyz = HBAOTexColor;
    Result.AmbLight.w = 1.0f;

	//float A = Result.DifColor.w;
    Result.DeferredColor.xyz = (Result.DifColor.xyz * (DiffuseRatio.xyz + SpacularRatio.xyz + AmbientRatio.xyz)) * HBAOTexColor;
	Result.DeferredColor.a = 1.0f;
    
	
    

    return Result;
}