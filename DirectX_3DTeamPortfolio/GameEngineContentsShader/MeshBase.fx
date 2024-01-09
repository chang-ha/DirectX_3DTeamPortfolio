#include "Transform.fx"
#include "RenderBase.fx"
#include "Light.fx"

struct GameEngineVertex3D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 NORMAL : NORMAL;
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
};



void Mesh_VS_Update(inout GameEngineVertex3D _Input,inout PixelOutPut Result)
{
    //PixelOutPut Result = (PixelOutPut) 0;
    
    float4 InputPos = _Input.POSITION;
    InputPos.w = 1.0f;
    
    float4 InputNormal = _Input.NORMAL;
    InputNormal.w = 0.0f;
    
    Result.VIEWPOSITION = mul(InputPos, WorldViewMatrix);
    // Result.VIEWPOSITION = mul(_Input.NORMAL, WorldMatrix);
    Result.VIEWPOSITION.w = 1.0f;
    
    _Input.NORMAL.w = 0.0f;
    Result.VIEWNORMAL = mul(InputNormal, WorldViewMatrix);
    // Result.VIEWNORMAL = mul(_Input.NORMAL, WorldMatrix);
    Result.VIEWNORMAL.w = 0.0f;
    
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

void Mesh_PS_Update(inout PixelOutPut _Input, inout PixelOut _Result)
{
    //PixelOut Result = (PixelOut) 0.0f;
    float4 Color = DiffuseTexture.Sample(DiffuseTextureSampler, _Input.TEXCOORD.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
   // Color.a = 1;
    
    float4 DiffuseRatio = (float4) 0.0f;
    float4 AmbientRatio = (float4) 0.0f;
    
    if (1 == IsLight)
    {
        
        for (int i = 0; i < LightCount; ++i)
        {
            float LightPower = 1.0f;
            
            if (0 != AllLight[i].LightType)
            {
                float Distance = length(AllLight[i].ViewLightPos.xyz - _Input.VIEWPOSITION.xyz);
            
                float FallOffStart = AllLight[i].PointLightRange * 0.2f;
                float FallOffEnd = AllLight[i].PointLightRange;
                        
                LightPower *= saturate((FallOffEnd - Distance) / (FallOffEnd - FallOffStart));
            }
            
            
            DiffuseRatio += CalDiffuseLight(_Input.VIEWNORMAL, _Input.VIEWPOSITION, AllLight[i]);
            AmbientRatio += CalSpacularLight(_Input.VIEWPOSITION, _Input.VIEWNORMAL, AllLight[i]);
            AmbientRatio += CalAmbientLight(AllLight[i]);
        }
        
        float A = Color.w;
        Color.xyz = Color.xyz * (DiffuseRatio.xyz + AmbientRatio.xyz);
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