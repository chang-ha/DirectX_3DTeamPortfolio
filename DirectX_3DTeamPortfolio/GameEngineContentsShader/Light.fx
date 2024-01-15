#include "../GameEngineCoreShader/Light.fx"



float4 CalSpacularLightContents(float4 _Pos, float4 _Normal, LightData _Data, float3 _SpecColor)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float3 N = normalize(_Normal.xyz);
    //float3 L = normalize(_Data.ViewLightRevDir.xyz);
    
    float3 L = (float4) 0;
    
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
    
    //�ݻ� ���� Reflection()
    float3 ReflectionN = normalize(2.0f * _Normal.xyz * dot(L.xyz, N.xyz) - L.xyz);
    
    float3 EyeL = normalize(_Data.CameraPosition.xyz - _Pos.xyz);
    
    float Result = max(0.0f, dot(ReflectionN.xyz, EyeL.xyz));
    
    float SpecIntensity = pow(Result, _Data.SpcPow);
   
    ResultRatio = float4(SpecIntensity * _SpecColor, 1.0f);
    
    return ResultRatio * _Data.SpcLightPower;
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
        // point , spot
        L.xyz = normalize(_Data.ViewLightPos.xyz - _Pos.xyz);
    }
    
    ResultRatio.xyz = max(0.0f, dot(N.xyz, L.xyz));
    return ResultRatio * _Data.DifLightPower;
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
