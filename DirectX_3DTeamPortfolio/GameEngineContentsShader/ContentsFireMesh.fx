#include "Transform.fx"
#include "RenderBase.fx"

cbuffer FireInfo : register(b12)
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
    float perturbscale ;
    float def2 = 0.0f;
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
    //float4 VIEWPOSITION : POSITION;
    //float4 WorldPOSITION : POSITION1;
    //float4 VIEWNORMAL : NORMAL;
    //float4 VIEWTANGENT : TANGENT;
    //float4 VIEWBINORMAL : BINORMAL;
};

PixelOutPut ContentsFireMesh_VS(GameEngineVertex3D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
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

Texture2D NoiseTexture : register(t1);
Texture2D AlphaTexture : register(t2);
SamplerState ClampSampler : register(s1);

PixelOut ContentsFireMesh_PS(PixelOutPut _Input)
{
    PixelOut Result = (PixelOut) 0.0f;
    
    float4 noise1;
    float4 noise2;
    float4 noise3;
    float4 finalNoise;
    float perturb;
    float2 noiseCoords;
    float4 fireColor;
    float4 alphaColor;
   
    noise1 = NoiseTexture.Sample(WrapSampler, _Input.TEXCOORD1.xy);
    noise2 = NoiseTexture.Sample(WrapSampler, _Input.TEXCOORD2.xy);
    noise3 = NoiseTexture.Sample(WrapSampler, _Input.TEXCOORD3.xy);

    // 노이즈 범위 늘리기
    noise1 = (noise1 - 0.5f) * 2.0f;
    noise2 = (noise2 - 0.5f) * 2.0f;
    noise3 = (noise3 - 0.5f) * 2.0f;
    
    noise1.xy = noise1.xy * distortion1.xy;
    noise2.xy = noise2.xy * distortion2.xy;
    noise3.xy = noise3.xy * distortion3.xy;
    
    finalNoise = noise1 + noise2 + noise3;
    
    //_Input.TEXCOORD.y가 낮을 수록 불의 근원지에 가까울수록 왜곡현상 완화 
    perturb = ((perturbscale - _Input.TEXCOORD.y) * distortionScale) + distortionBias;
    
    noiseCoords.xy = (finalNoise.xy * perturb) + _Input.TEXCOORD.xy;
    
    fireColor = DiffuseTexture.Sample(ClampSampler, noiseCoords.xy);
    
    
    alphaColor = AlphaTexture.Sample(ClampSampler, noiseCoords.xy);
    
    fireColor.a = alphaColor;
    
    Result.DifColor = fireColor;
    
  
    return Result;
}

//    texCoord.y -= time * 0.2; // 필요에 따라 속도를 조정합니다.
//    texCoord.x += sin(time + texCoord.y * 3.0) * 0.1; // 수평 왜곡
