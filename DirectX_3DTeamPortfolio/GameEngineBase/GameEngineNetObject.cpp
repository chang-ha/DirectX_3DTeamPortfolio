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
	// ��Ʈ��ũ�� ����Ǵ� �༮���� �� ���� ��ϵǾ�������
	return AllNetObjects.contains(_ObjectId);
}

void GameEngineNetObject::InitNetObject(int _ObjectId, GameEngineNet* _Net)
{
	// ���� 1�� ������Ʈ��
	ObjectID = _ObjectId;
	std::lock_guard<std::mutex> Lock(ObjectLock);
	// ��Ʈ��ũ�� ����Ǵ� �༮���� �� ���� ��ϵǾ�������
	AllNetObjects.insert(std::pair<int, GameEngineNetObject*>(_ObjectId, this));

	Net = _Net;
}

void GameEngineNetObject::PushPacket(std::shared_ptr<GameEnginePacket> _Packet)
{
	Packets.push_back(_Packet);
}
