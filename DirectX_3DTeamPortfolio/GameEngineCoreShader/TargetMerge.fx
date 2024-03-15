//cbuffer MergeInfo : register(b11)
//{
//    int MergeTargetCount = 0;
//    int def1 = 0;
//    int def2 = 0;
//    int def3 = 0;
//};

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

PixelOutPut TargetMerge_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

struct PSOutPut
{
    float4 Target0 : SV_Target0;
    
};

PSOutPut TargetMerge_PS(PixelOutPut _Input)
{
    PSOutPut OutPut = (PSOutPut) 0;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    if (Color.r >= 1.0f)
    {
        Color.r = 1.0f;
    }
    
    if (Color.g >= 1.0f)
    {
        Color.g = 1.0f;
    }
    
    if (Color.b >= 1.0f)
    {
        Color.b = 1.0f;
    }
    
    if (Color.a >= 1.0f)
    {
        Color.a = 1.0f;
    }
    
   
    OutPut.Target0 = Color;
    
    
  
    
    return OutPut;
}