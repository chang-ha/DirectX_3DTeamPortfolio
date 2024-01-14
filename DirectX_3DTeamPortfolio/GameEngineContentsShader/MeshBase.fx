#include "Transform.fx"
#include "RenderBase.fx"
#include "Light.fx"

struct GameEngineVertex3D
{
    float4 POSITION : POSITION;
    float4 NORMAL : NORMAL;
    float4 TEXCOORD : TEXCOORD;
    float4 TANGENT : TANGENT;
    float4 BINORMAL : BINORMAL;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};


struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 VIEWPOSITION : POSITION;
    float4 VIEWNORMAL : NORMAL;
    float4 VIEWTANGENT : TANGENT;
    float4 VIEWBINORMAL : BINORMAL;
};



void Mesh_VS_Update(inout GameEngineVertex3D _Input,inout PixelOutPut Result)
{
    //PixelOutPut Result = (PixelOutPut) 0;
    
    _Input.POSITION.w = 1.0f;
    Result.VIEWPOSITION = mul(_Input.POSITION, WorldViewMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    _Input.NORMAL.w = 0.0f;
    Result.VIEWNORMAL = mul(_Input.NORMAL, WorldViewMatrix);
    Result.VIEWNORMAL.w = 0.0f;
    
    _Input.TANGENT.w = 0.0f;
    Result.VIEWTANGENT = mul(_Input.TANGENT, WorldViewMatrix);
    Result.VIEWTANGENT.w = 0.0f;
    
    _Input.BINORMAL.w = 0.0f;
    Result.VIEWBINORMAL = mul(_Input.BINORMAL, WorldViewMatrix);
    Result.VIEWBINORMAL.w = 0.0f;
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    Result.TEXCOORD = _Input.TEXCOORD;
    
    //return _Result;
}


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



Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseTextureSampler : register(s0);
Texture2D NormalTexture : register(t2);
SamplerState NormalTextureSAMPLER : register(s2);

void Mesh_PS_Update(inout PixelOutPut _Input, inout PixelOut _Result)
{
    //PixelOut Result = (PixelOut) 0.0f;
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    if (0 != IsNormal)
    {
        _Input.VIEWNORMAL = NormalTexCalculate(NormalTexture, NormalTextureSAMPLER, _Input.TEXCOORD, _Input.VIEWTANGENT, _Input.VIEWBINORMAL, _Input.VIEWNORMAL);
    }
    
    
    
    float4 DiffuseRatio = (float4) 0.0f;
    float4 SpacularRatio = (float4) 0.0f;
    float4 AmbientRatio = (float4) 0.0f;
    
    if (1 == IsLight)
    {
        float constantAttenuation = 1.0f;
        float linearAttenuation = 0.0014;
        float quadraticAttenuation = 0.000007;
        
        for (int i = 0; i < LightCount; ++i)
        {
            float LightPower = 1.0f;
            
            
            if (0 != AllLight[i].LightType)
            {
                float Distance = length(AllLight[i].ViewLightPos.xyz - _Input.VIEWPOSITION.xyz);
                
                float attenuation = 1.0 / (constantAttenuation + linearAttenuation * Distance + quadraticAttenuation * Distance * Distance);
            
                //float FallOffStart = AllLight[i].PointLightRange * 0.2f;
                //float FallOffEnd = AllLight[i].PointLightRange;
                        
                LightPower = attenuation;
            }
            
            //float3 diffuse = max(dot(normalize(input.NormalWS), normalize(toLight)), 0.0) * materialDiffuse.rgb * lightIntensity;
            //float3 specular = /* ...specular calculation... */;

            //float3 finalColor = ambient + diffuse + specular;
            
            if (0.0f < LightPower)
            {
                
                DiffuseRatio += CalDiffuseLight(_Input.VIEWNORMAL, _Input.VIEWPOSITION, AllLight[i]) * LightPower;
                SpacularRatio += CalSpacularLight(_Input.VIEWPOSITION, _Input.VIEWNORMAL, AllLight[i]) * LightPower;
                AmbientRatio += CalAmbientLight(AllLight[i]) * LightPower;
            }
        }
        
        float A = Color.w;
        Color.xyz = Color.xyz * (DiffuseRatio.xyz + SpacularRatio.xyz + AmbientRatio.xyz);
        Color.a = A;
    }
    
    
    if (0 < Target0)
    {
        _Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        _Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        _Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        _Result.Color3 = Color;
    }
}