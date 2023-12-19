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
    
