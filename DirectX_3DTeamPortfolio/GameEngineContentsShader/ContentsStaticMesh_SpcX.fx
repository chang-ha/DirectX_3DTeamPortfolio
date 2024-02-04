#include "MeshBase_SpcX.fx"



PixelOutPut ContentsStaticMesh_SpcX_VS(GameEngineVertex3D _Input)
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





DeferrdOut ContentsStaticMesh_SpcX_PS(PixelOutPut _Input)
{
	DeferrdOut Result = (DeferrdOut) 0.0f;
  
	Mesh_PS_Update(_Input, Result);
    
	return Result;
}