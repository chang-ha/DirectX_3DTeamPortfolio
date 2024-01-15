
struct LightData
{
    float4x4 LightViewMatrix;
    float4x4 LightViewInverseMatrix;
    float4x4 LightProjectionMatrix;
    float4x4 LightProjectionInverseMatrix;
    float4x4 LightViewProjectionMatrix;
    float4x4 CameraViewInverseMatrix;
    float4 LightColor;
    float4 AmbientLight;
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
    float ShadowTargetSizeX;
    float ShadowTargetSizeY;
    float LightNear;
    float LightFar;
    float DifLightPower;
    float SpcLightPower;
    float AmbLightPower;
    float SpcPow;
    int LightType;
    float PointLightRange;
    int Temp2;
    int Temp3;
};

cbuffer LightDatas : register(b12)
{
    int LightCount;
    LightData AllLight[64];
};

float4 CalDiffuseLight(float4 _Normal, LightData _Data)
{
    // 0~1
    float4 ResultRatio = 0.0f;
    
    float4 N = float4(normalize(_Normal.xyz), 0.0f);
    float4 L = float4(normalize(_Data.ViewLightRevDir.xyz), 0.0f);
    
    ResultRatio.xyz = max(0.0f, dot(N.xyz, L.xyz));
    return ResultRatio * _Data.DifLightPower;
}

float4 CalSpacularLight(float4 _Pos, float4 _Normal, LightData _Data)
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
    ResultRatio.xyzw = pow(Result, _Data.SpcPow);
    
    return ResultRatio * _Data.SpcLightPower;
}



float4 CalAmbientLight(LightData _Data)
{
    return _Data.AmbientLight * _Data.AmbLightPower;
}

float4 NormalTexCalculate(Texture2D NormalTex, SamplerState Smp, float4 UV, float4 _Tangent, float4 _BiNormal, float4 _Normal)
{
    float4 TexNormal = NormalTex.Sample(Smp, UV.xy);
    
    // ���󿡴� ���������̶�°� ���
    // �븻�� ����Ѱ� �ؽ�ó�� ���鶧
    // +1 * 0.5f�� �Ѵٸ� �� �ع�����.
    // �װ� ������� �����ִ� ����
    TexNormal = TexNormal * 2.0f - 1.0f;
    TexNormal.w = 0.0f;
    TexNormal = normalize(TexNormal);
    // �׳� �ؽ�ó���� ������ normal ���� ȸ���ȵǾ���.
    
    
    float4 Result = (float4) 0.0f;
    
    // ���ο� ȸ������� ����� ����.
    // ź��Ʈ �����̽���� �θ���.
    float3x3 TangentSpace = float3x3(_Tangent.xyz, _BiNormal.xyz, _Normal.xyz);
    Result.xyz = mul(TexNormal.xyz, TangentSpace);
    
    return Result;

}

