#include "PreCompile.h"
#include "GameEngineNetObject.h"

std::atomic<int> GameEngineNetObject::ServerObjectID = -1;
std::mutex GameEngineNetObject::ObjectLock;
std::map<int, GameEngineNetObject*> GameEngineNetObject::AllNetObjects;


GameEngineNetObject::GameEngineNetObject()
{
}

GameEngineNetObject::~GameEngineNetObject()
{
}

bool GameEngineNetObject::IsNetObject(int _ObjectId)
{
	// std::lock_guard<std::mutex> Lock(ObjectLock);
	// 네트워크로 제어되는 녀석들은 다 여기 등록되어있으니
	return AllNetObjects.contains(_ObjectId);
}

void GameEngineNetObject::InitNetObject(int _ObjectId, GameEngineNet* _Net)
{
	// 나는 1번 오브젝트다
	ObjectID = _ObjectId;
	std::lock_guard<std::mutex> Lock(ObjectLock);
	// 네트워크로 제어되는 녀석들은 다 여기 등록되어있으니
	AllNetObjects.insert(std::pair<int, GameEngineNetObject*>(_ObjectId, this));

	Net = _Net;
}

void GameEngineNetObject::PushPacket(std::shared_ptr<GameEnginePacket> _Packet)
{
	Packets.push_back(_Packet);
}
