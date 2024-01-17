#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEnginePacket.h>

// 설명 : 오브젝트의 애니메이션 생성
class ObjectPacket : public GameEnginePacket
{
public:
	// constructer destructer
	ObjectPacket();
	~ObjectPacket();

	// delete Function
	ObjectPacket(const ObjectPacket& _Other) = delete;
	ObjectPacket(ObjectPacket&& _Other) noexcept = delete;
	ObjectPacket& operator = (const ObjectPacket& _Other) = delete;
	ObjectPacket& operator = (ObjectPacket&& _Other) noexcept = delete;

protected:

private:
	float4 Pos;
};

