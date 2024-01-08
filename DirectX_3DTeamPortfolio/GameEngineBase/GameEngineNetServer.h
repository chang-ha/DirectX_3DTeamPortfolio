#pragma once
#include "GameEngineNet.h"
#include "GameEngineThread.h"
#include <memory>
#include <map>
#include "GameEngineDebug.h"

// ���� :
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

	void SetAcceptCallBack(std::function<void(SOCKET _Client, GameEngineNetServer* Server, int _ID)> _CallBack)
	{
		if (nullptr == _CallBack)
		{
			MsgBoxAssert("����ִ� �ݹ��� �־�����ϴ�.");
		}

		AcceptCallBack = _CallBack;
	}

protected:
	void RecvProcess(char* _Data) override;

private:
	int BackLog = 0;

	// ���� ������
	SOCKET AcceptSocket = 0;

	std::atomic<int> SOCKETID = 0;

	std::mutex UserLock;
	std::map<int, SOCKET> Users;

	std::function<void(SOCKET _Client, GameEngineNetServer* _Server, int _ID)> AcceptCallBack;

	std::vector<std::shared_ptr<GameEngineThread>> ServerRecvThreads;

	GameEngineThread Thread;
	static void AcceptThread(SOCKET _AcceptSocket, GameEngineNetServer* _Net);
};

