#include "MeshBase.fx"



PixelOutPut ContentsStaticMesh_VS(GameEngineVertex3D _Input)
{
    
    PixelOutPut Result = (PixelOutPut) 0;
    _Input.POSITION.w = 1.0f;
    _Input.NORMAL.w = 0.0f;
    
    
    Mesh_VS_Update(_Input, Result);
    
    return Result;
}

// b���� 14
// t�ؽ�ó 
// s���÷� 
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.





PixelOut ContentsStaticMesh_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut) 0.0f;
  
    Mesh_PS_Update(_Input, Result);
    
    return Result;
}