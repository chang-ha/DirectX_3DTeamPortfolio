#include "PreCompile.h"
#include "Interaction_Sword.h"

#include "BaseActor.h"
#include "BoneSocketCollision.h"

Interaction_Sword::Interaction_Sword() 
{
}

Interaction_Sword::~Interaction_Sword() 
{
}


void Interaction_Sword::On()
{
	GameEngineObjectBase::On();

	for (GameEngineCollision* pCol : Collisions)
	{
		pCol->On();
	}
}

void Interaction_Sword::Off()
{
	GameEngineObjectBase::Off();

	for (GameEngineCollision* pCol : Collisions)
	{
		pCol->Off();
	}
}

void Interaction_Sword::Init(const std::vector<GameEngineCollision*>& _pCols)
{
	Collisions.reserve(_pCols.size());

	for (int i = 0; i < static_cast<int>(_pCols.size()); i++)
	{
		GameEngineCollision* pCol = _pCols[i];
		if (nullptr == pCol)
		{
			MsgBoxAssert("존재하지 않는 충돌체를 자료구조에 삽입하려 했습니다.");
			return;
		}

		Collisions.push_back(pCol);
	}
}

void Interaction_Sword::Collision(Enum_CollisionOrder _Order, std::function<void(std::vector<GameEngineCollision*>& _Other)> _CallBack)
{
	for (size_t i = 0; i < Collisions.size(); i++)
	{
		GameEngineCollision* pCol = Collisions[i];
		if (nullptr == pCol)
		{
			MsgBoxAssert("존재하지 않는 충돌체입니다.");
			return;
		}

		if (true == pCol->Collision(_Order, _CallBack))
		{
			break;
		}
	}
}

void Interaction_Sword::RecordCollision(BaseActor* _pActor)
{
	HitRecord.insert(_pActor);
}

bool Interaction_Sword::IsContain(BaseActor* _pActor) const
{
	if (HitRecord.contains(_pActor))
	{
		return true;
	}

	return false;
}

void Interaction_Sword::ResetRecord()
{
	HitRecord.clear();
}

void Interaction_Sword::Release()
{
	Collisions.clear();
	HitRecord.clear();
}