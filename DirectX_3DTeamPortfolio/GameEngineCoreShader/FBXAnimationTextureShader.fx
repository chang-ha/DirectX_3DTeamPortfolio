#include "Transform.fx"
#include "FBXAnimation.fx"
#include "RenderBase.fx"
#include "Light.fx"

struct GameEngineVertex
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_POSITION;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut FBXTextureShader_VS(GameEngineVertex _Input)
{
    // _Input 0.5 0.5
    
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ°�
    PixelOutPut Result = (PixelOutPut)0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    if (0 != IsAnimation)
    {
        Skinning(_Input.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
        SkinningNormal(_Input.NORMAL, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    }
    
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;


    Result.VIEWNORMAL = mul(_Input.NORMAL, WorldViewMatrix);
    
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
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
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
    float4 Color4 : SV_Target4;
    float4 Color5 : SV_Target5;
    float4 Color6 : SV_Target6;
    float4 Color7 : SV_Target7;
};

Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);

PixelOut FBXTextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut)0.0f;
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    // Color.a = 1;
    
    float4 DiffuseRatio = (float4) 0.0f;
    float4 SpacularRatio = (float4) 0.0f;
    float4 AmbientRatio = (float4) 0.0f;
        if (1 == IsLight)
    {
        for (int i = 0; i < LightCount; ++i)
        {
            DiffuseRatio += CalDiffuseLight(_Input.VIEWNORMAL, AllLight[i]);
            SpacularRatio += CalSpacularLight(_Input.VIEWPOSITION, _Input.VIEWNORMAL, AllLight[i]);
            AmbientRatio += CalAmbientLight(AllLight[i]);
        }
        
        float A = Color.w;
        Color.xyz = Color.xyz * (DiffuseRatio.xyz + SpacularRatio.xyz + AmbientRatio.xyz);
        Color.a = A;
    }

    
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