#include "Transform.fx"
#include "RenderBase.fx"

cbuffer FogWallInfo : register(b12)
{
    float frameTime;
    float scrollSpeeds1;
    float scrollSpeeds2;
    float scrollSpeeds3;
    float scales1;
    float scales2;
    float scales3;
    float padding;

    float4 distortion1;
    float4 distortion2;
    float4 distortion3;

    float distortionScale;
    float distortionBias;
    float perturbscale;
    float AlphaScale;
};

struct GameEngineVertex3D
{
    float4 POSITION : POSITION;
    float4 NORMAL : NORMAL;
    float4 TEXCOORD : TEXCOORD;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD0;
    float2 TEXCOORD1 : TEXCOORD1;
    float2 TEXCOORD2 : TEXCOORD2;
    float2 TEXCOORD3 : TEXCOORD3;
    float4 VIEWPOSITION : POSITION;
    //float4 WorldPOSITION : POSITION1;
    //float4 VIEWNORMAL : NORMAL;
    //float4 VIEWTANGENT : TANGENT;
    //float4 VIEWBINORMAL : BINORMAL;
};

PixelOutPut ContentsFogWallMesh_VS(GameEngineVertex3D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    // 노이즈 텍스쳐의 좌표를 크기 및 윗방향 스크롤 속도 값을 이용하여 계산합니다.
    
    Result.TEXCOORD1 = (_Input.TEXCOORD * scales1).xy;
    Result.TEXCOORD1.y = Result.TEXCOORD1.y + (frameTime * scrollSpeeds1);
    
    Result.TEXCOORD2 = (_Input.TEXCOORD * scales2).xy;
    Result.TEXCOORD2.y = Result.TEXCOORD2.y + (frameTime * scrollSpeeds2);
    
    Result.TEXCOORD3 = (_Input.TEXCOORD * scales3).xy;
    Result.TEXCOORD3.y = Result.TEXCOORD3.y + (frameTime * scrollSpeeds3);
    
    
    
    return Result;
}


struct PixelOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
};


Texture2D DiffuseTexture : register(t0);
SamplerState WrapSampler : register(s0);

SamplerState ClampSampler : register(s1);

PixelOut ContentsFogWallMesh_PS(PixelOutPut _Input)
{
    PixelOut Result = (PixelOut) 0.0f;
    
    float4 noise1;
    float4 noise2;
    float4 noise3;
    float4 finalNoise;
    float perturb;
    float2 noiseCoords;
    float4 FogColor;
   
    noise1 = DiffuseTexture.Sample(WrapSampler, _Input.TEXCOORD1.xy);
    noise2 = DiffuseTexture.Sample(WrapSampler, _Input.TEXCOORD2.xy);
    noise3 = DiffuseTexture.Sample(WrapSampler, _Input.TEXCOORD3.xy);

    // 노이즈 범위 늘리기
    noise1 = (noise1 - 0.5f) * 2.0f;
    noise2 = (noise2 - 0.5f) * 2.0f;
    noise3 = (noise3 - 0.5f) * 2.0f;
    
    noise1.xy = noise1.xy * distortion1.xy;
    noise2.xy = noise2.xy * distortion2.xy;
    noise3.xy = noise3.xy * distortion3.xy;
    
    finalNoise = noise1 + noise2 + noise3;
    
    ////_Input.TEXCOORD.y가 낮을 수록 불의 근원지에 가까울수록 왜곡현상 완화 
    //perturb = ((perturbscale - _Input.TEXCOORD.y) * distortionScale) + distortionBias;
    
    //perturb *= 0.001f;
    
    noiseCoords.xy = (finalNoise.xy) /*+ _Input.TEXCOORD.xy*/;
    
    FogColor = DiffuseTexture.Sample(ClampSampler, noiseCoords.xy).r - 0.1f;
    
    FogColor.z -= 0.1f;
    
    FogColor = saturate(FogColor);
    
    FogColor.a = 0.8f + (0.2f * FogColor.x);
    
    
    Result.DifColor = FogColor;
    Result.PosColor = _Input.VIEWPOSITION;
    
  
    return Result;
}