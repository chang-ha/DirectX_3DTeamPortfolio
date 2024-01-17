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

	GameEngineSerializer Ser;
	unsigned int PacketType = -1;
	unsigned int PacketSize = -1;

	while (true == _Net->IsRun)
	{
		int Result = recv(_Socket, Data, sizeof(Data), 0);

		if (-1 == Result)
		{
			_Net->Disconnect(_Socket);
			return;
		}

		// 접속 끊김
		if (SOCKET_ERROR == _Socket || INVALID_SOCKET == _Socket)
		{
			return;
		}

		Ser.Write(Data, Result);

		if (8 > Ser.GetWriteOffset())
		{
			continue;
		}

		if (-1 == PacketSize)
		{
			{
				// size     type
				// [][][][] [][][][]
				int* Ptr = Ser.GetDataPtr<int*>();
				PacketSize = Ptr[0];
			}

			{
				// size     type
				// [][][][] [][][][]
				int* Ptr = Ser.GetDataPtr<int*>();
				PacketType = Ptr[1];
			}
		}

		if (PacketSize > Ser.GetWriteOffset())
		{
			continue;
		}

		while (true)
		{
			std::shared_ptr<GameEnginePacket> Packet = _Net->Dispatcher.ConvertPacket(PacketType, Ser);

			if (nullptr != Packet)
			{
				std::lock_guard<std::mutex> Lock(_Net->RecvPacketLock);
				_Net->RecvPacket.push_back(Packet);
			}
			else
			{
				MsgBoxAssert("패킷 컨버전에 실패했습니다.");
			}

			if (Ser.GetWriteOffset() == Ser.GetReadOffset())
			{
				Ser.Reset();
				PacketType = -1;
				PacketSize = -1;
				break;
			}

			//  받은양 100              20
			if (Ser.GetWriteOffset() > Ser.GetReadOffset())
			{
				//           80
				unsigned int RemainSize = static_cast<unsigned int>(Ser.GetWriteOffset() - Ser.GetReadOffset());

				if (8 > RemainSize)
				{
					break;
				}

				{
					int* Ptr = Ser.GetDataPtr<int*>();
					PacketSize = Ptr[0];
				}

				{
					int* Ptr = Ser.GetDataPtr<int*>();
					PacketType = Ptr[1];
				}

				//     10           30
				if (RemainSize > PacketSize)
				{
					continue;
				}

				//     10           30
				Ser.ClearReadData();
			}
		}

		_Net->RecvProcess(Data);
	}
}

void GameEngineNet::SendPacket(std::shared_ptr<GameEnginePacket> _Packet)
{

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

void GameEngineNet::RecvPacketProcess()
{
	std::lock_guard<std::mutex> Lock(RecvPacketLock);

	for (std::shared_ptr<GameEnginePacket> _Packet : RecvPacket)
	{
		Dispatcher.ProcessPacket(_Packet);
	}

	RecvPacket.clear();
}