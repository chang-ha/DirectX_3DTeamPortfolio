#include "Transform.fx"
#include "RenderBase.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
};


struct PixelOutPut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_POSITION;
};

PixelOutPut FBXColorShader_VS(GameEngineVertex2D _Input)
{
    // _Input 0.5 0.5
    
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ°�
    PixelOutPut Result = (PixelOutPut)0;
    
    // ���� ���ϴ� ���� �̾ȿ� �־��ټ� �־�� �Ѵ�.
    
    _Input.POSITION.w = 1.0f;
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    return Result;
}

// b���� 14
// t�ؽ�ó 
// s���÷� 
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.

// �츮 ��Ģ

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target1;
    float4 Color3 : SV_Target1;
    float4 Color4 : SV_Target1;
    float4 Color5 : SV_Target1;
    float4 Color6 : SV_Target1;
    float4 Color7 : SV_Target1;
};

// SV_Target0
// SV_Target1
// SV_Target2
// SV_Target3
// SV_Target4

PixelOut FBXColorShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut)0.0f;
    float4 Color = BaseColor;
    Color.a = 1;
    
    if (0 < Target0)
    {
        Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        Result.Color3 = Color;
    }
    
    return Result;
}