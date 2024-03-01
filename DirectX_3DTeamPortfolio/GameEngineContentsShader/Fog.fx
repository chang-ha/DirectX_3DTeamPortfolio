cbuffer FogInfo : register(b12)
{
    float4x4 CameraViewInverseMatrix;
    float4 FogColor; // 원하는 포그의 색상
    float FogMinHeight ; // 포그가 시작되는 거리
    float FogMaxHeight; // 포그가 오브젝트를 완전히 가리는 거리 
    float NoiseScale ; // 노이즈 텍스처 좌표의 스케일
    float NoiseOffset ; // 노이즈 텍스처 좌표 애니메이션을 위한 오프셋
    float NoiseIntensity ; // 노이즈 모듈레이션의 강도
    float WorldScale;
    float Def1;
    float Def3;
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

PixelOutPut Fog_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D SceneTex : register(t0);
SamplerState SceneTexSampler : register(s0);
Texture2D PosTex : register(t1);  // view 포지션
SamplerState PosTexSampler : register(s1);
//Texture2D NoiseTex : register(t2);  // view 포지션
//SamplerState NoiseTexSampler : register(s2);


float4 Fog_PS(PixelOutPut _Input) : SV_Target0
{
    
    float4 SceneColor = SceneTex.Sample(SceneTexSampler, _Input.TEXCOORD.xy);
    SceneColor.w = 1.0f;
    float4 viewPos = PosTex.Sample(PosTexSampler, _Input.TEXCOORD.xy);
    float Alpha = viewPos.a;
    viewPos.w = 1.0f;
    
    float heightFactor = 0.0f;
    
    float4 WorldPos = mul(viewPos, CameraViewInverseMatrix);
    
    if (Alpha == 0.0f)
    {
        //SceneColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
        //heightFactor = 1.0f;
        return FogColor;

    }
    else
    {
           
             
    //낮을 수록 포그 적용 안받음
        heightFactor = 1.f - saturate((WorldPos.y - FogMinHeight) / (FogMaxHeight - FogMinHeight));
    }
    
   
    
    
    
    //노이즈 텍스쳐 관련
    //float3 worldSpaceTexCoords = WorldPos.xyz / WorldScale;
    
    
    //if (heightFactor <= 0.0f)
    //{
    //    return SceneColor;
    //}
    
    //float2 noiseTexCoord = float2(worldSpaceTexCoords.x, worldSpaceTexCoords.y) * NoiseScale + float2(NoiseOffset, NoiseOffset);
    //float noiseValue = NoiseTex.Sample(NoiseTexSampler, noiseTexCoord).r;
    
    
    
    //heightFactor *= lerp(1.0f, noiseValue, NoiseIntensity);
    
    
    
    float4 Result = lerp(SceneColor, FogColor, heightFactor);
    
    
    Result.w = 1.0f;
 
    
    return Result;

}