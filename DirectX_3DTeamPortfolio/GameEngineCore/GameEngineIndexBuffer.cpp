#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer() 
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer() 
{
}


void GameEngineIndexBuffer::ResCreate(const void* _Data, size_t _IndexCount)
{
	IndexCount = static_cast<UINT>(_IndexCount);

	// 버퍼는 방금전에 말했듯이 
	// 무슨 용도로 쓸거야?
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(IndexSize * IndexCount);

	// 안바꿈
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	// ID3D11Buffer* Arr[1];

	if (nullptr == Buffer)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
	}


	// 버텍스버퍼를 여러개 넣어줄수 있다.
	GameEngineCore::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}