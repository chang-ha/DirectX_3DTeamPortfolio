#pragma once
#include "GameEnginePacket.h"
#include "GameEngineDispatcher.h"
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

	virtual void SendPacket(std::shared_ptr<GameEnginePacket> _Packet) = 0;

	void SendPacket(SOCKET _Socket, std::shared_ptr<GameEnginePacket> _Packet);

	void Send(SOCKET _Socket, GameEngineSerializer& _Ser);
	void Send(SOCKET _Socket, const char* _DataPtr, int _Size);

	GameEngineDispatcher Dispatcher;

	std::mutex& GetRecvPacketLock()
	{
		return RecvPacketLock;
	}

	std::list<std::shared_ptr<GameEnginePacket>>& GetRecvPacket()
	{
		return RecvPacket;
	}

	void RecvPacketProcess();


protected:
	static void RecvThreadFunction(SOCKET _Socket, GameEngineNet* _Net);
	bool IsRun = true;

private:
	std::mutex RecvPacketLock;
	std::list<std::shared_ptr<GameEnginePacket>> RecvPacket;

};

