#include "PreCompile.h"
#include "HitInteraction.h"

#include "BaseActor.h"
#include "BoneSocketCollision.h"

HitInteraction::HitInteraction() 
{
}

HitInteraction::~HitInteraction() 
{
}


void HitInteraction::On()
{
	GameEngineObjectBase::On();
	ValidityCheck();
	pCollision->On();
}

void HitInteraction::Off()
{
	GameEngineObjectBase::Off();
	ValidityCheck();
	pCollision->Off();
}

void HitInteraction::ValidityCheck(std::string_view _MSG)
{
	if (nullptr == pCollision 
		|| nullptr == pParent)
	{
		if (_MSG.empty())
		{
			MsgBoxAssert("�������� �ʴ� �浹ü�� ��ȯ�Ϸ��߽��ϴ�.");
		}
		else
		{
			MsgBoxAssert(_MSG.data());
		}
	}
}

void HitInteraction::Init(BaseActor* _pParent, GameEngineCollision* _pCol)
{
	pCollision = _pCol;
	pParent = _pParent;

	ValidityCheck();
}

void HitInteraction::RecordCollision(BaseActor* _pActor)
{
	HitRecord.insert(_pActor);
}

bool HitInteraction::IsContain(BaseActor* _pActor) const
{
	return HitRecord.contains(_pActor);
}

void HitInteraction::ResetRecord()
{
	HitRecord.clear();
}

void HitInteraction::Release()
{
	pCollision = nullptr;
	HitRecord.clear();
}