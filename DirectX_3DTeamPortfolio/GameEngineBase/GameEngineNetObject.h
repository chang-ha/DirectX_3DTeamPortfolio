#pragma once
#include <atomic>
#include <map>
#include <mutex>
#include <list>
#include "GameEnginePacket.h"
#include "GameEngineDebug.h"
#include "GameEngineNet.h"

enum class ControllType
{
	None,
	Net,
	Play,
};

// 설명 : 서버가 조작하는 오브젝트들은 다 이거 상속받아야 한다.
class GameEngineNetObject
{
public:
	// constructer destructer
	GameEngineNetObject();
	~GameEngineNetObject();

	// delete Function
	GameEngineNetObject(const GameEngineNetObject& _Other) = delete;
	GameEngineNetObject(GameEngineNetObject&& _Other) noexcept = delete;
	GameEngineNetObject& operator = (const GameEngineNetObject& _Other) = delete;
	GameEngineNetObject& operator = (GameEngineNetObject&& _Other) noexcept = delete;
	
	static bool IsNetObject(int _ObjectId);

	static void PushNetObjectPacket(std::shared_ptr<GameEnginePacket> _Packet)
	{
		int Id = _Packet->GetObjectID();

		if (false == AllNetObjects.contains(Id))
		{
			MsgBoxAssert("존재하지 않는 오브젝트에 패킷이 날아왔습니다.");
		}

		AllNetObjects[Id]->PushPacket(_Packet);
	}


	static int CreateServerObjectID()
	{
		return ++ServerObjectID;
	}

	void PushPacket(std::shared_ptr<GameEnginePacket> _Packet);

	int GetPacketCount()
	{
		if (Type == ControllType::None)
		{
			MsgBoxAssert("컨트롤 설정이 되어있지 않은 오브젝트입니다.");
		}

		return static_cast<int>(Packets.size());
	}

	std::shared_ptr<GameEnginePacket> PopPacket()
	{
		if (Type == ControllType::None)
		{
			MsgBoxAssert("컨트롤 설정이 되어있지 않은 오브젝트입니다.");
		}

		std::shared_ptr<GameEnginePacket> Packet = Packets.front();
		Packets.pop_front();

		return Packet;
	}

	ControllType GetControllType()
	{
		if (Type == ControllType::None)
		{
			MsgBoxAssert("컨트롤 설정이 되어있지 않은 오브젝트입니다.");
		}

		return Type;
	}

	void SetObjectID(int _ObjectID)
	{
		ObjectID = _ObjectID;
	}

	void SetContorllType(ControllType _Type)
	{
		Type = _Type;
	}

	void InitNetObject(int _ObjectId, GameEngineNet* _Net);

private:
	static std::atomic<int> ServerObjectID;
	static std::mutex ObjectLock;
	static std::map<int, GameEngineNetObject*> AllNetObjects;

	GameEngineNet* Net = nullptr;

	int ObjectID = -1;

	ControllType Type = ControllType::None;

	std::list<std::shared_ptr<GameEnginePacket>> Packets;
};

