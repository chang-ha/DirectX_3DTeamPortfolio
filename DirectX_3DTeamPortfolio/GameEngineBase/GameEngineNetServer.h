#pragma once
#include "GameEngineNet.h"
#include "GameEngineThread.h"

// Ό³Έν :
class GameEngineNetServer : public GameEngineNet
{
public:
	// constrcuter destructer
	GameEngineNetServer();
	~GameEngineNetServer();

	// delete Function
	GameEngineNetServer(const GameEngineNetServer& _Other) = delete;
	GameEngineNetServer(GameEngineNetServer&& _Other) noexcept = delete;
	GameEngineNetServer& operator=(const GameEngineNetServer& _Other) = delete;
	GameEngineNetServer& operator=(GameEngineNetServer&& _Other) noexcept = delete;

	void ServerOpen(short Port, int _BackLog);
protected:

private:
	int BackLog = 0;
	SOCKET AcceptSocket = 0;

	GameEngineThread Thread;
	static void AcceptThread(SOCKET _AcceptSocket, GameEngineNetServer* _Net);
};

