struct AniMat
{
    float4x4 Mat;
};

//                 80바이트 500 
StructuredBuffer<AniMat> ArrAniMationMatrix : register(t7);

// 실제 
void Skinning(inout float4 _Pos, float4 _Weight, int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalPos = (float4) 0.0f;
    _Pos.w = 1.0f;
    
    for (int i = 0; i < 4; ++i)
    {
        // 2 3 10
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalPos += _Weight[i] * mul(_Pos, Mat.Mat);
    }
    
    _Pos = CalPos;
    _Pos.w = 1.0f;
}

void SkinningNormal(inout float4 _Normal, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalNormal = (float4) 0.0f;
    // 1로 맞추려는 행동.
    // _Weight[3] = 1.0f - _Weight[0] - _Weight[1] - _Weight[2];
    
    _Normal.w = 0.0f;
    
    for (int i = 0; i < 4; ++i)
    {
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalNormal += _Weight[i] * mul(_Normal, Mat.Mat);
    }
    
    _Normal = CalNormal;
    _Normal.xyz = normalize(_Normal.xyz);
    _Normal.w = 0.0f;

}
    
void SkinningNormal(inout float4 _Normal, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalNormal = (float4) 0.0f;
    // 1로 맞추려는 행동.
    // _Weight[3] = 1.0f - _Weight[0] - _Weight[1] - _Weight[2];
    
    _Normal.w = 0.0f;
    
    for (int i = 0; i < 4; ++i)
    {
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalNormal.xyz += _Weight[i] * mul(_Normal, Mat.Mat);
    }
    
    _Normal = CalNormal;
    _Normal.xyz = normalize(_Normal.xyz);
    _Normal.w = 0.0f;

}