#include "MeshBase.fx"



PixelOutPut ContentsStaticMesh_VS(GameEngineVertex3D _Input)
{
    
    PixelOutPut Result = (PixelOutPut) 0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    
    Mesh_VS_Update(_Input, Result);
    
    return Result;
}

// b버퍼 14
// t텍스처 
// s샘플러 
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러와 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식등을 내부에서
// 사용해주는 용도가 있다.





PixelOut ContentsStaticMesh_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut) 0.0f;
  
    Mesh_PS_Update(_Input, Result);
    
    return Result;
}