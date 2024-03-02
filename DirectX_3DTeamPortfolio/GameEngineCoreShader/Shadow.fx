#include "FBXAnimation.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 ShadowPos : POSITION;
};

cbuffer ShadowAniInfo : register(b5)
{
    int IsShadowAnimation;
    int Temp0;
    int Temp1;
    int Temp2;
    float4x4 WorldViewProjectionMatrix;
};

Output Shadow_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;

    if (IsShadowAnimation != 0)
    {
        Skinning(InputPos, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
        InputPos.w = 1.0f;
    }

    // WorldViewProjectionMatrix ���� worldViewProjection
    // POSITION : SV_POSITION ViewPort����� �����Ͷ������� �Ѿ�� �ڵ����� ��������
    // ���忡���� ����� ���� ���Ѵٴ´°�.
    NewOutPut.POSITION = mul(InputPos, WorldViewProjectionMatrix);
    
    // ����Ʈ�� �������� �ȵǴϱ�.
    NewOutPut.ShadowPos = NewOutPut.POSITION;
    NewOutPut.ShadowPos.w = 1.0f;

    
    return NewOutPut;
}

void Shadow_PS(Output _Input) //: SV_Target0
{
    //return float4(max(0.0f, _Input.ShadowPos.z / _Input.ShadowPos.w), 0.0f, 0.0f, 1.0f);
}