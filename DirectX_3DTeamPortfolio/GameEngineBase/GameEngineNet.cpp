#include "PreCompile.h"
#include "GameEngineNet.h"

GameEngineNet::GameEngineNet() 
{
}

GameEngineNet::~GameEngineNet() 
{
	IsRun = false;
}

void GameEngineNet::RecvThreadFunction(SOCKET _Socket, GameEngineNet* _Net)
{
	char Data[1024] = { 0 };

	while (true == _Net->IsRun)
	{
		int Result = recv(_Socket, Data, sizeof(Data), 0);

		if (-1 == Result)
		{
			return;
		}

		// Á¢¼Ó ²÷±è
		if (SOCKET_ERROR == _Socket || INVALID_SOCKET == _Socket)
		{
			return;
		}

		_Net->RecvProcess(Data);
	}
}