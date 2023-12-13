#include "RenderBase.fx"

// 노이즈 텍스처의 크기를 알아야 합니다.
Texture2D EngineNoise : register(t15);

static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

float4 GaussianSample(float2 _Uv)
{
    float4 vOutColor = (float4) 0.0f;
    
    // saturate(6.31211)
    // 1
    
    if (1.0f < _Uv.x)
    {
        _Uv.x = frac(_Uv.x);
    }
    else if (_Uv.x < 0.0f)
    {
        _Uv.x = 1.0f + frac(_Uv.x);
    }
    
    if (1.0f < _Uv.y)
    {
        _Uv.y = frac(_Uv.y);
    }
    else if (_Uv.y < 0.0f)
    {
        _Uv.y = 1.0f + frac(_Uv.y);
    }
    
    // 노이즈 텍스처의 크기를 곱해서 픽셀 xy위치를 구한다.
    int2 iUV = _Uv * float2(1024.0f, 1024.0f);

    iUV -= int2(2, 2);
    for (int j = 0; j < 5; ++j)
    {
        for (int i = 0; i < 5; ++i)
        {
            int2 idx = int2(iUV.y + i, iUV.x + j);
            vOutColor += EngineNoise[idx] * GaussianFilter[j][i];
        }
    }
    
    return vOutColor;
}

float4 RandomFloat4(int _Index, int ParticleMaxCount)
{
    float4 RandomVector = (float4) 0.0f;

    float2 UV = float2((float) _Index.x / ParticleMaxCount, 0.5f);
    // 매번 다은 UV가 나오겠죠?
    UV.x += AccDeltaTime;
    UV.y += sin((UV.x + AccDeltaTime) * 3.141592.r * 2.0f * 10.0f) * 0.5f;
    
    RandomVector = float4(GaussianSample(UV + float2(0.0f, 0.0f)).x, GaussianSample(UV + float2(0.1f, 0.0f)).x, GaussianSample(UV + float2(0.2f, 0.0f)).x, GaussianSample(UV + float2(0.3f, 0.0f)).x);
    return RandomVector;
}