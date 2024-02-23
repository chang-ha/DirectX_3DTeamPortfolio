#include "Light.fx"

cbuffer CameraBaseInfo : register(b2)
{
    float SizeX;
    float SizeY;
    float Temp0;
    float Temp1;
};


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

PixelOutPut ContentsDeferredLightRender_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    
    
    return Result;
}

Texture2D PositionTex : register(t0);
Texture2D NormalTex : register(t1); //w는 roughness 
Texture2D ShadowTex : register(t2);
Texture2D DiffuseTexture : register(t3);
Texture2D MaterialTexture : register(t4);
SamplerState POINTWRAP : register(s0);
SamplerState LINEARClamp : register(s1);
SamplerComparisonState CompareSampler : register(s2);

struct DeferredRenderOutPut
{
    // float4 DeferredColor : SV_Target0;
    // float4 DifColor : SV_Target0;
    float4 DifLight : SV_Target0;
    float4 SpcLight : SV_Target1;
    float4 AmbLight : SV_Target2;
    float4 LightColor : SV_Target3;
    float4 Shadow : SV_Target4;
    float4 PBRLight : SV_Target5;
};

DeferredRenderOutPut ContentsDeferredLightRender_PS(PixelOutPut _Input)
{
    DeferredRenderOutPut Result = (DeferredRenderOutPut) 0;
    
    // float4 Color = DifColorTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Pos = PositionTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Normal = NormalTex.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Albedo = DiffuseTexture.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    float4 Material = MaterialTexture.Sample(POINTWRAP, _Input.TEXCOORD.xy);
    Albedo.xyz = pow(Albedo.xyz, 2.2f); //gamma
    
    
    float Roughness = Material.x;
    float Metalic = Material.y;
    
    
 
    
    if (0.0f >= Pos.a)
    {
        clip(-1);
    }
    
    float4 DiffuseRatio = (float4) 0.0f;
    float4 SpacularRatio = (float4) 0.0f;
    float4 AmbientRatio = (float4) 0.0f;
    
	
    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.0014;
    float quadraticAttenuation = 0.000007;
    
    float LightPower = 1.0f;
    
    if (0 != LightDataValue.LightType)
    {
        float Distance = length(LightDataValue.ViewLightPos.xyz - Pos.xyz);
             
        float attenuation = 1.0 / (constantAttenuation + linearAttenuation * Distance + quadraticAttenuation * Distance * Distance);
        LightPower = attenuation;
    }
    
    //Result.DifColor = Color;
    Result.DifLight = CalDiffuseLightContents(Normal, Pos, LightDataValue) * LightPower;
    Result.DifLight.w = 1.0f;
    
    Result.SpcLight = CalSpacularLightContents(Pos, Normal,LightDataValue) * LightPower;
    Result.SpcLight.w = 1.0f;
    
    Result.PBRLight = CalSpacularLightContentsBRDF(Pos, Normal, Albedo.xyz, Metalic, Roughness, LightDataValue) * LightPower;
    Result.PBRLight.w = 1.0f;
    
  
    Result.AmbLight = CalAmbientLight(LightDataValue);
    
    

  
    
    // 빛마다 그림자를 계산하는 방식을 다르게 해야하하기 때문이다.
    
 
 
    if (0 <= Result.DifLight.x)
    {
           
         // PCF를 위한 오프셋
        float2 texelSize = 1.0f / float2(LightDataValue.ShadowTargetSizeX, LightDataValue.ShadowTargetSizeY);
    
        float2 offsets[9] =
        {
            float2(-texelSize.x, texelSize.y), float2(0, texelSize.y), float2(texelSize.x, texelSize.y),
        float2(-texelSize.x, 0), float2(0, 0), float2(texelSize.x, 0),
        float2(-texelSize.x, -texelSize.y), float2(0, -texelSize.y), float2(texelSize.x, -texelSize.y)
        };
    
        // 빛이 드는 곳이라는 것.
        // Pos 카메라의 View공간에 존재하는 Pos
        float4 WorldPos = Pos;
        WorldPos.w = 1.0f;
        WorldPos = mul(WorldPos, LightDataValue.CameraViewInverseMatrix);
        WorldPos.w = 1.0f;
        
        // 월드 세상으로 왔다.
        
        // 이 월드 포스를 빛의 공간으로 보냅니다.
        // 빛의 공간으로 보내려고 하는거에요.
        float4 LightPos = mul(WorldPos, LightDataValue.LightViewProjectionMatrix);
        
        // 그런데 놀랍게도.
        float3 LightProjection = LightPos.xyz / LightPos.w;
        float CurrentDepth = LightProjection.z;
        float2 ShadowUV = float2(LightProjection.x * 0.5f + 0.5f, LightProjection.y * -0.5f + 0.5f);
        //float fShadowDepth = ShadowTex.SampleCmpLevelZero(CompareSampler, ShadowUV, CurrentDepth - 0.01f);
        //float fShadowDepth = ShadowTex.Sample(POINTWRAP, ShadowUV).r;
        // xy는 뭐로 압축됬나요? => -1 ~ 1사이의 공간으로 간거죠? 직교투영
        // LightProjection.z

        
       
        
        if ( 0.01f > ShadowUV.x && 0.999f < ShadowUV.x
           && 0.01f > ShadowUV.y && 0.999f < ShadowUV.y)
        {
            Result.Shadow = 1.0f;
        }
        else
        {
            float shadow = 0.0f;
            
            [unroll]
            for (int i = 0; i < 9; ++i)
            {
                float fShadowDepth = ShadowTex.Sample(POINTWRAP, ShadowUV + offsets[i]).r;
            
            
            
            if (
                fShadowDepth >= 0.0f && LightProjection.z >= (fShadowDepth + 0.001f)
             )
                {
            
                    shadow += 1.0f;
                }
            }
            
            shadow /= 9.0f;
            
            Result.Shadow = shadow;

        }
        
        
        

        
        
        //if (
        //    fShadowDepth >= 0.0f
        //    && 0.01f < ShadowUV.x && 0.999f > ShadowUV.x
        //    && 0.01f < ShadowUV.y && 0.999f > ShadowUV.y
        //    && LightProjection.z >= (fShadowDepth + 0.001f)
        //    )
        
        //if (
        //   fShadowDepth >= 0.0f
        //   && 0.01f < ShadowUV.x && 0.999f > ShadowUV.x
        //   && 0.01f < ShadowUV.y && 0.999f > ShadowUV.y
        //   && LightProjection.z >= (fShadowDepth + 0.001f)
        //     )
        //{
            
        //    Result.Shadow = 0.1f;
        //    //Result.DifLight = 0.0f;
        //    //Result.SpcLight = 0.0f;
        //    // 그림자
        //}
        
    }
    
 
    Result.LightColor = (Result.DifLight + Result.SpcLight + Result.AmbLight);
    
    // 최종컬러는 빛이 여러겨개 적용되서 들어가야 한다.
    //float A = Result.DifColor.w;
    //Result.DeferredColor.xyz = Result.DifColor.xyz * (Result.DifLight.xyz + Result.SpcLight.xyz + Result.AmbLight.xyz);
    //Result.DeferredColor.a = 1.0f;
    
    return Result;
}