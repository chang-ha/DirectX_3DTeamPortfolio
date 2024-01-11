#pragma once
#include "GameEngineNet.h"
#include "GameEngineThread.h"

// Ό³Έν :
class GameEngineNetClient : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetClient();
	~GameEngineNetClient();

	// delete Function
	GameEngineNetClient(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient(GameEngineNetClient&& _Other) noexcept = delete;
	GameEngineNetClient& operator=(const GameEngineNetClient& _Other) = delete;
	GameEngineNetClient& operator=(GameEngineNetClient&& _Other) noexcept = delete;

	void Disconnect(SOCKET _Socket);

	bool Connect(const std::string& _IP, unsigned short _Port);

	void RecvProcess(char* _Data) override;

	void SendPacket(std::shared_ptr<GameEnginePacket> _Packet) override;

protected:

private:
	SOCKET ClientSocket = 0;

	GameEngineThread RecvThread;

};