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
			MsgBoxAssert("존재하지 않는 충돌체를 반환하려했습니다.");
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
	ValidityCheck();
	HitRecord.insert(_pActor);
	pCollision->SetCollisionColor(float4::GREEN);
}

bool HitInteraction::IsContain(BaseActor* _pActor) const
{
	return HitRecord.contains(_pActor);
}

void HitInteraction::ResetRecord()
{
	ValidityCheck();
	HitRecord.clear();
	pCollision->SetCollisionColor(float4::RED);
}

void HitInteraction::Release()
{
	pCollision = nullptr;
	HitRecord.clear();
}