#pragma once
#include <atomic>
#include <map>
#include <mutex>
#include <list>
#include "GameEnginePacket.h"
#include "GameEngineDebug.h"

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

	static int CreateServerObjectID()
	{
		return ++ServerObjectID;
	}

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

private:
	static std::atomic<int> ServerObjectID;
	static std::mutex ObjectLock;
	static std::map<int, GameEngineNetObject*> AllNetObjects;

	int ObjectID = -1;

	ControllType Type = ControllType::None;

	std::list<std::shared_ptr<GameEnginePacket>> Packets;
};

