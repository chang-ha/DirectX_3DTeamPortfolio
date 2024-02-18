cbuffer FogInfo : register(b12)
{
    float4x4 CameraViewInverseMatrix;
    float4 FogColor; // 원하는 포그의 색상
    float FogMinHeight ; // 포그가 시작되는 거리
    float FogMaxHeight; // 포그가 오브젝트를 완전히 가리는 거리 
    float Def1;
    float Def2;
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


float4 Fog_PS(PixelOutPut _Input) : SV_Target0
{
    
    float4 SceneColor = SceneTex.Sample(SceneTexSampler, _Input.TEXCOORD.xy);
    float4 viewPos = PosTex.Sample(PosTexSampler, _Input.TEXCOORD.xy);
    
   
        if (viewPos.a == 0.0f)
        {
            return FogColor;
        }
    
    
    float4 WorldPos = mul(viewPos, CameraViewInverseMatrix);
    
    float heightFactor = saturate((WorldPos.y - FogMinHeight) / (FogMaxHeight - FogMinHeight));
    
    
 
    
    return lerp(FogColor, SceneColor, heightFactor);

}