#pragma once
#include "GameEngineResources.h"

// 설명 : 버퍼계열들은 모두다 동일한 인터페이스를 사용하고
// 의미는 그래픽카드에게 n바이트의 공간을 할당하고 그에 대한 접근권한을 달라고.

class GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	// delete Function
	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&& _Other) noexcept = delete;

protected:
	D3D11_BUFFER_DESC BufferInfo = {0};
	// 모든 버퍼들은 그 용도가 무엇이건 나오는 인터페이스는 버퍼로 동일되다.
	ID3D11Buffer* Buffer = nullptr;

	void BufferRelease();

private:

};

