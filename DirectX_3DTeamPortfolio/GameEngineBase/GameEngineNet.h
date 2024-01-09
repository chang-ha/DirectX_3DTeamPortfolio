#pragma once
#include "GameEnginePacket.h"
#include <memory>

// 설명 : // 서버 클라 가리지 않는다.
// 연결 1개
class GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNet();
	~GameEngineNet();

	// delete Function
	GameEngineNet(const GameEngineNet& _Other) = delete;
	GameEngineNet(GameEngineNet&& _Other) noexcept = delete;
	GameEngineNet& operator=(const GameEngineNet& _Other) = delete;
	GameEngineNet& operator=(GameEngineNet&& _Other) noexcept = delete;

	virtual void RecvProcess(char* _Data) = 0;

	void SendPacket(SOCKET _Socket, std::shared_ptr<GameEnginePacket> _Packet);

	void Send(SOCKET _Socket, GameEngineSerializer& _Ser);
	void Send(SOCKET _Socket, const char* _DataPtr, int _Size);

protected:
	static void RecvThreadFunction(SOCKET _Socket, GameEngineNet* _Net);
	bool IsRun = true;

private:
	int AtomicID;

};

