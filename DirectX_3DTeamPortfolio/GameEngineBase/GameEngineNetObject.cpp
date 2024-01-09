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