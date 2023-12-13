#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() 
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
}

void GameEngineVertexBuffer::ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount)
{
	VertexSize = static_cast<UINT>(_VertexSize);
	VertexCount = static_cast<UINT>(_VertexCount);

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	// 버퍼는 방금전에 말했듯이 
	// 무슨 용도로 쓸거야?
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(VertexSize * VertexCount);

	// 안바꿈
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	// ID3D11Buffer* Arr[1];

	if (nullptr == Buffer)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
	}


	// 버텍스버퍼를 여러개 넣어줄수 있다.
	GameEngineCore::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
}