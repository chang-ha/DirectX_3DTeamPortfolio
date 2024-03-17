#include "../GameEngineCoreShader/Light.fx"

#define PI 3.14159265358979323846264338327950288419716939937510f

float3 Fresnel(float3 EyeDir, float3 HalfVec, float3 F0)
{
    return F0 + (1.0f - F0) * pow(1.0f - max(dot(EyeDir, HalfVec), 0.0f), 5.0f);
}

float4 CalSpacularLightContents(float4 _Pos, float4 _Normal, LightData _Data, float3 _SpecColor)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float3 N = normalize(_Normal.xyz);
    //float3 L = normalize(_Data.ViewLightRevDir.xyz);
    
    
    float3 L = (float3) 0;
    
    if (0 == _Data.LightType)
    {
        // directional
        L.xyz = normalize(_Data.ViewLightRevDir.xyz);
    }
    else
    {
        // point 
        L.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    float3 EyeL = normalize(_Data.CameraPosition.xyz - _Pos.xyz);
    float3 H = normalize(L + EyeL);
    float fresnelTerm = Fresnel(EyeL, H, _SpecColor);
    
    //นÝป็ บคลอ Reflection()
    float3 ReflectionN = normalize(2.0f * _Normal.xyz * dot(L.xyz, N.xyz) - L.xyz);
    
    
    float specAngle = max(0.0f, dot(ReflectionN.xyz, EyeL.xyz));
    //float specPowerGradient = lerp(_Data.SpcPow + 15.0f, _Data.SpcPow, specAngle);
    //float Fresnel = pow(1.0f - specAngle, 5.0f);
    
    ResultRatio.xyzw = pow(specAngle, _Data.SpcPow) * fresnelTerm;
    
    
    return ResultRatio * _Data.LightColor * _Data.SpcLightPower * _Data.LightPower;
}


float NormalDistributionGGXTR(float3 n, float3 h, float a)
{
    float a2 = a * a;
    float NdotH = saturate(dot(n, h));
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = PI * denom * denom;

    return nom / denom;
}



float GeometrySchlickGGX(float NdotV, float roughness)  // k is a remapping of roughness based on direct lighting or IBL lighting
{
    float r = roughness + 1.0f;
    float k = (r * r) / 8.0f;

    //float k = (roughness * roughness) / 2.0f;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k;

    return nom / denom;
}
  
float GeometrySmith(float3 n, float3 v, float3 l, float k)
{
    //  Geometry Obstruction
    float NdotV = saturate(dot(n, v));
    //  Geometry Shadowing
    float NdotL = saturate(dot(n, l));

    float ggx2 = GeometrySchlickGGX(NdotV, k);
    float ggx1 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

//float GeometrySchlickGGX(float NdotV, float roughness)  // k is a remapping of roughness based on direct lighting or IBL lighting
//{
//    float r = roughness + 1.0f;
//    float k = (r * r) / 8.0f;

//    //float k = (roughness * roughness) / 2.0f;

//    float nom = NdotV;
//    float denom = NdotV * (1.0f - k) + k;

//    return nom / denom;
//}
  
//float GeometrySmith(float NdotV, float NdotL, float k)
//{
//    float ggx1 = GeometrySchlickGGX(NdotV, k);
//    float ggx2 = GeometrySchlickGGX(NdotL, k);

//    return ggx1 * ggx2;
//}

float3 FresnelSchlick(float cosTheta, float3 R0)
{
    return (R0 + (1.0f - R0) * pow(1.0 - cosTheta, 5.0f));
}

float4 CalSpacularLightContentsBRDF(float4 _Pos, float4 _Normal, float3 _Albedo, float _Metalness, float _Roughness, LightData _Data /*, float3 _SpecColor*/)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float3 Normal = normalize(_Normal.xyz);
    //float3 L = normalize(_Data.ViewLightRevDir.xyz);
    
    
    
    
    float3 F0 = float3(0.04f, 0.04f, 0.04f);
    F0 = lerp(F0, _Albedo, _Metalness); // Assuming albedo.x as base reflectivity for simplicity
    
    float3 lightDir = (float3) 0;
    
    if (0 == _Data.LightType)
    {
        // directional
        lightDir.xyz = normalize(_Data.ViewLightRevDir.xyz);
    }
    else
    {
        // point 
        lightDir.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    float3 viewDir = normalize(_Data.CameraPosition.xyz - _Pos.xyz);
    float3 halfwayVec = normalize(viewDir + lightDir);
    
    float NdotL = saturate(dot(Normal, lightDir));
    float NdotV = saturate(dot(Normal, viewDir));
    //float NdotH = max(dot(_Normal.xyz, H), 0.0);
    float VdotH = max(dot(viewDir, halfwayVec), 0.0);
    
    
    // Fresnel term using Schlick's approximation
    float3 F = FresnelSchlick(VdotH, F0);
    
    float D = NormalDistributionGGXTR(Normal, halfwayVec, _Roughness);


    float G = GeometrySmith(Normal, viewDir, lightDir, _Roughness);
    
    
    


    
    float3 specular = D * F * G / ((4 * NdotV * NdotL) + 0.001f);
    
    float3 kS = F;
    float3 kD = 1.0f - kS;
    kD *= 1.0 - _Metalness;
    
    //ResultRatio.xyz = ((kD * _Albedo ) + specular) * NdotL;
    ResultRatio.xyz = (_Albedo + specular) * NdotL;
    ResultRatio.w = 1.0f;
    
    
    
    return ResultRatio * _Data.LightColor * _Data.LightPower;
}





float4 CalDiffuseLightContents(float4 _Normal, float4 _Pos, LightData _Data)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float4 N = float4(normalize(_Normal.xyz), 0.0f);
    float4 L = (float4) 0;
    
    if (0 == _Data.LightType)
    {
        // directional
        L.xyz = normalize(_Data.ViewLightRevDir.xyz);
    }
    else
    {
        // point 
        L.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    
    ResultRatio.xyzw = max(0.0f, dot(N.xyz, L.xyz));
    return ResultRatio * _Data.LightColor * _Data.DifLightPower * _Data.LightPower;
}






