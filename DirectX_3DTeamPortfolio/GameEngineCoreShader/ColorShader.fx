#include "Transform.fx"
#include "RenderBase.fx"

float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    // mul¿∫ mutiply
    return mul(pos, WorldViewProjectionMatrix);
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    // 1280 x 720 x 1280 x 720
    // for
    
    return BaseColor;
}