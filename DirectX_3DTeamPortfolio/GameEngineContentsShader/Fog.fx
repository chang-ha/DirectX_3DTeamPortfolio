cbuffer FogInfo : register(b12)
{
    float4x4 CameraViewInverseMatrix;
    float4 FogColor; // ���ϴ� ������ ����
    float FogMinHeight ; // ���װ� ���۵Ǵ� �Ÿ�
    float FogMaxHeight; // ���װ� ������Ʈ�� ������ ������ �Ÿ� 
    float NoiseScale ; // ������ �ؽ�ó ��ǥ�� ������
    float NoiseOffset ; // ������ �ؽ�ó ��ǥ �ִϸ��̼��� ���� ������
    float NoiseIntensity ; // ������ ��ⷹ�̼��� ����
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
    // �ȼ����̴��� ������ ����
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
Texture2D PosTex : register(t1);  // view ������
SamplerState PosTexSampler : register(s1);
//Texture2D NoiseTex : register(t2);  // view ������
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
           
             
    //���� ���� ���� ���� �ȹ���
        heightFactor = 1.f - saturate((WorldPos.y - FogMinHeight) / (FogMaxHeight - FogMinHeight));
    }
    
   
    
    
    
    //������ �ؽ��� ����
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