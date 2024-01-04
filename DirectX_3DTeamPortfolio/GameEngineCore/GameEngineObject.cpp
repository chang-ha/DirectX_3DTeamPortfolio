#include "PreCompile.h"
#include "GameEngineObject.h"

GameEngineObject::GameEngineObject() 
{
}

GameEngineObject::~GameEngineObject() 
{
}




void GameEngineObject::AllLevelStart(class GameEngineLevel* _PrevLevel)
{
	LevelStart(_PrevLevel);

	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->LevelStart(_PrevLevel);
		}
	}
}
void GameEngineObject::AllLevelEnd(class GameEngineLevel* _NextLevel)
{
	LevelEnd(_NextLevel);

	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->LevelEnd(_NextLevel);
		}
	}
}

void GameEngineObject::AllRelease()
{
	Release();

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for ( std::shared_ptr<GameEngineObject> Object : Group)
		{
			Object->IsDeathValue = true;
			Object->Parent = nullptr;
			Object->AllRelease();
		}
	}
}


void GameEngineObject::AllReleaseCheck()
{
	if (true == IsDeath())
	{
		AllRelease();
		return;
	}

	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineObject>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineObject>>::iterator End = Group.end();

		for (; Start != End;)
		{
			if (false == (*Start)->IsDeath())
			{
				(*Start)->AllReleaseCheck();
				++Start;
				continue;
			}

			Start = Group.erase(Start);
		}
	}

}

void GameEngineObject::AllUpdate(float _Delta)
{
	Update(_Delta);

	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->AddLiveTime(_Delta);
			_Child->Update(_Delta);
		}
	}
}



void GameEngineObject::SetParent(GameEngineObject* _Parent, int _Order /*= 0*/)
{
	// 기존에 내가 부모를 가지고 있었다면
	if (nullptr != Parent)
	{
		Parent->Childs[GetOrder()].remove(shared_from_this());
	}

	SetOrder(_Order);
	Parent = _Parent;
	Parent->Childs[_Order].push_back(shared_from_this());
	Transform.SetParent(_Parent->Transform);
}