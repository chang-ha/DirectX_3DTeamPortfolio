cbuffer MergeInfo : register(b11)
{
    int MergeTargetCount = 0;
    int def1 = 0;
    int def2 = 0;
    int def3 = 0;
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
    float4 Target1 : SV_Target1;
    float4 Target2 : SV_Target2;
    float4 Target3 : SV_Target3;
    float4 Target4 : SV_Target4;
    float4 Target5 : SV_Target5;
    float4 Target6 : SV_Target6;
    float4 Target7 : SV_Target7;
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
    
    if (MergeTargetCount == 0)
    {
        OutPut.Target0 = Color;
    }
    
    if (MergeTargetCount == 3)
    {
        OutPut.Target3 = Color;
    }
    
    return OutPut;
}