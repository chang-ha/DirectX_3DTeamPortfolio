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