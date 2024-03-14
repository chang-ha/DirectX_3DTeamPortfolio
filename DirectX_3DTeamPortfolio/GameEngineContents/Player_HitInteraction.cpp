#include "PreCompile.h"
#include "Player_HitInteraction.h"
#include "BaseActor.h"

Player_HitInteraction::Player_HitInteraction()
{
}

Player_HitInteraction::~Player_HitInteraction()
{
}

void Player_HitInteraction::CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness)
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

				//RecordCollision(pActor.get());
				pActor->GetHit({ pParent, _iStiffness, eDir });
				
			}
		};

	pCollision->Collision(_Order, ColEvent);

	int a = 0;
}


void Player_HitInteraction::CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness /*= 0*/)
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
				

				RecordCollision(pActor.get());

				pActor->GetHitToShield({ pParent, _iStiffness });
			}
		};

	pCollision->Collision(_Order, ColEvent);
}