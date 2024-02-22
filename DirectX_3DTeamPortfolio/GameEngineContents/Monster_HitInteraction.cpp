#include "PreCompile.h"
#include "Monster_HitInteraction.h"

#include "BaseActor.h"

Monster_HitInteraction::Monster_HitInteraction() 
{
}

Monster_HitInteraction::~Monster_HitInteraction() 
{
}

void Monster_HitInteraction::CollisionToBody(Enum_CollisionOrder _Order)
{
	ValidityCheck();
	
	std::function ColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("������� �߸��Ǿ� �ֽ��ϴ�.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
					return;
				}

				if (true == IsContain(pActor.get()))
				{
					continue;
				}

				pActor->GetHit({ pParent });
				RecordCollision(pActor.get());
			}
		};

	pCollision->Collision(_Order, ColEvent);
}

void Monster_HitInteraction::CollisionToShield(Enum_CollisionOrder _Order)
{
	ValidityCheck();

	std::function ColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("������� �߸��Ǿ� �ֽ��ϴ�.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
					return;
				}

				if (true == IsContain(pActor.get()))
				{
					continue;
				}

				RecordCollision(pActor.get());
				pActor->GetHitToShield({ pParent });
			}
		};

	pCollision->Collision(_Order, ColEvent);
}