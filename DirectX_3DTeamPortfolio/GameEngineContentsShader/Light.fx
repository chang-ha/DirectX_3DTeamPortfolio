#include "../GameEngineCoreShader/Light.fx"

#define PI 3.14159265358979323846264338327950288419716939937510f

float4 CalSpacularLightContents(float4 _Pos, float4 _Normal, LightData _Data/*, float3 _SpecColor*/)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float3 N = normalize(_Normal.xyz);
    //float3 L = normalize(_Data.ViewLightRevDir.xyz);
    
    float Roughness = _Normal.w;
    
    float3 L = (float3) 0;
    
    if (0 == _Data.LightType)
    {
        // directional
        L.xyz = normalize(_Data.ViewLightRevDir.xyz);
    }
    else
    {
        // point , spot
        L.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    float3 EyeL = normalize(_Data.CameraPosition.xyz - _Pos.xyz);
    
    
    
    //นÝป็ บคลอ Reflection()
    float3 ReflectionN = normalize(2.0f * _Normal.xyz * dot(L.xyz, N.xyz) - L.xyz);
    
    
    float Result = max(0.0f, dot(ReflectionN.xyz, EyeL.xyz));
    
    ResultRatio.xyzw = pow(Result, _Data.SpcPow);
    
    
    return ResultRatio * _Data.LightColor * _Data.SpcLightPower;
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
}\

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
        // point , spot
        lightDir.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    float3 viewDir = normalize(_Data.CameraPosition.xyz - _Pos.xyz);
    float3 halfwayVec = normalize(viewDir + lightDir);
    
    float NdotL = max(dot(Normal, lightDir), 0.0);
    float NdotV = max(dot(Normal, viewDir), 0.0);
    //float NdotH = max(dot(_Normal.xyz, H), 0.0);
    float VdotH = max(dot(viewDir, halfwayVec), 0.0);
    
    
    // Fresnel term using Schlick's approximation
    float3 F = FresnelSchlick(VdotH, F0);
    
    float D = NormalDistributionGGXTR(Normal, halfwayVec, _Roughness);


    float G = GeometrySmith(Normal, viewDir, lightDir, _Roughness);
    
    
    
    //float WoDotN = (dot(viewDir, _Normal.xyz));
    //float WiDotN = (dot(lightDir, _Normal.xyz));


    
    float3 specular = D * F * G / ((4 * NdotV * NdotL) + 0.001f);
    
    float3 kS = F;
    float3 kD = 1.0f - kS;
    kD *= 1.0 - _Metalness;
    
    ResultRatio.xyz = ((kD * _Albedo ) + specular) * NdotL;
    ResultRatio.w = 1.0f;
    //ResultRatio = float4(specular, 1.0f);
    
    
    
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
    return ResultRatio * _Data.LightColor * _Data.DifLightPower;
}





//float4 PS(VertexOut input) : SV_Target
//{
//    // ...

//    // Sample the specular map using the texture coordinates of the pixel/vertex.
//    float3 specColor = SpecularMap.Sample(Samp, input.TexCoord).rgb;

//    // Calculate the lighting (for simplicity, let's assume a directional light).
//    float3 normal = normalize(input.Normal);
//    float3 lightDir = normalize(LightDirection);
//    float3 viewDir = normalize(ViewDirection - input.Position);
    
//    // Compute the reflection vector based on the light direction and surface normal
//    float3 reflectDir = reflect(-lightDir, normal);
    
//    // Compute the specular contribution using the Blinn-Phong reflection model
//    float specPower = 256.0; // Specular power or shininess coefficient
//    float specIntensity = pow(max(dot(viewDir, reflectDir), 0.0), specPower);

//    // Apply the sampled specular color to the intensity.
//    float3 specular = specIntensity * specColor;

//    // Combine with other lighting components (ambient and diffuse)
//    float3 ambient = AmbientIntensity;
//    float3 diffuse = max(dot(normal, lightDir), 0.0) * DiffuseColor;

//    float3 finalColor = ambient + diffuse + specular;

//    // Output final color
//    return float4(finalColor, 1.0);
//}
