#include "PreCompile.h"
#include "GameEngineNet.h"
#include "GameEngineBase/GameEngineSerializer.h"

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

void GameEngineNet::SendPacket(SOCKET _Socket, std::shared_ptr<GameEnginePacket> _Packet)
{

	GameEngineSerializer Ser;
	_Packet->SerializePacket(Ser);
	Send(_Socket, Ser);
	// send(_Socket, );
}

void GameEngineNet::Send(SOCKET _Socket, GameEngineSerializer& _Ser)
{
	Send(_Socket, _Ser.GetDataPtr<const char*>(), _Ser.GetWriteOffsetInt());
}

void GameEngineNet::Send(SOCKET _Socket, const char* _DataPtr, int _Size)
{
	send(_Socket, _DataPtr, _Size, 0);
}