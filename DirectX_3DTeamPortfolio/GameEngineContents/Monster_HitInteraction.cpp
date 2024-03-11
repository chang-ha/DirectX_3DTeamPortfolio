#include "PreCompile.h"
#include "Monster_HitInteraction.h"

#include "BaseActor.h"

Monster_HitInteraction::Monster_HitInteraction() 
{
}

Monster_HitInteraction::~Monster_HitInteraction() 
{
}

void Monster_HitInteraction::CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness /*= 0*/)
{
	ValidityCheck();
	
	std::function ColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("결과값이 잘못되어 있습니다.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				if (true == IsContain(pActor.get()))
				{
					continue;
				}

				const float4 ColPos = pCollision->Transform.GetWorldPosition();
				const float4 OtherPos = pCol->Transform.GetWorldPosition();
				const float4 DirVector = ColPos - OtherPos;
				Enum_DirectionXZ_Quat eDir = ContentsMath::ReturnXZDirectionToVector(DirVector);

				pActor->GetHit({ pParent, _iStiffness, eDir });
				RecordCollision(pActor.get());
			}
		};

	pCollision->Collision(_Order, ColEvent);
}

void Monster_HitInteraction::CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness /*= 0*/)
{
	ValidityCheck();

	std::function ColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("결과값이 잘못되어 있습니다.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				if (true == IsContain(pActor.get()))
				{
					continue;
				}

				pActor->GetHitToShield({ pParent, _iStiffness });
				RecordCollision(pActor.get());
			}
		};

	pCollision->Collision(_Order, ColEvent);
}