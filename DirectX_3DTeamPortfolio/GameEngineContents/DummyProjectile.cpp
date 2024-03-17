#include "PreCompile.h"
#include "DummyProjectile.h"

#include "BaseActor.h"
#include "DummyActor.h"

DummyProjectile::DummyProjectile() 
{
}

DummyProjectile::~DummyProjectile() 
{
}

static constexpr float PROJECTILE_SPEED = 1500.0f;
static constexpr float DP_LIVETIME = 3.0f;

void DummyProjectile::Start()
{
	const float AttScale = 20.f;

	AttackRenderer = CreateComponent<GameEngineRenderer>(Enum_CollisionOrder::MonsterAttack);
	AttackRenderer->SetMesh("Sphere");
	AttackRenderer->SetMaterial("FBXStaticColor");
	AttackRenderer->RenderBaseInfoValue.BaseColor = float4(0.3f, 0.3f, 0.3f);

	AttackCol = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);

	bReady = true;

	CreateStateParameter RState;
	RState.Start = [=](GameEngineState* _State)
		{
			bReady = true;
			Off();
		};

	CreateStateParameter AState;
	AState.Start = [=](GameEngineState* _State)
		{
			if (nullptr == pParent)
			{
				MsgBoxAssert("부모를 지정하지 않으면 사용할 수 없는 기능입니다.");
				return;
			}

			const float4 WParentPos = pParent->Transform.GetWorldPosition();
			const float4 WCameraRot = GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler();
			float4 DirVec = float4::FORWARD;
			DirVec = float4::VectorRotationToDegX(DirVec, WCameraRot.X);
			DirVec = float4::VectorRotationToDegY(DirVec, WCameraRot.Y);

			DirVector = DirVec;

			Transform.SetWorldPosition(WParentPos);

			bReady = false;

			On();
		};
	AState.Stay = [=](float _Delta, GameEngineState* _State)
		{
			if (DP_LIVETIME < _State->GetStateTime())
			{
				_State->ChangeState(eState::Ready);
			}
			
			const float Scalar = PROJECTILE_SPEED * _Delta;
			const float4 MoveVec = DirVector * Scalar;

			Transform.AddWorldPosition(MoveVec);

			AttackCollision();
		};

	

	MainState.CreateState(eState::Ready, RState);
	MainState.CreateState(eState::Active, AState);

	Transform.SetWorldScale(float4(AttScale, AttScale, AttScale));

	Off();
}

void DummyProjectile::Update(float _Delta) 
{
	MainState.Update(_Delta);
}

void DummyProjectile::Release() 
{
	AttackRenderer = nullptr;
	AttackCol = nullptr;
	pParent = nullptr;
}

void DummyProjectile::Fire()
{
	if (true == bReady)
	{
		MainState.ChangeState(eState::Active);
	}
}

void DummyProjectile::AttackCollision()
{
	if (nullptr == AttackCol)
	{
		MsgBoxAssert("존재하지 않는 콜리전으로 충돌하려 했습니다.");
		return;
	}

	std::function AttackFunc = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (int i = 0; i < static_cast<int>(_Other.size()); i++)
			{
				GameEngineCollision* pCollsion = _Other[i];
				if (nullptr == pCollsion)
				{
					MsgBoxAssert("이상한 값이 담겨있습니다.");
					return;
				}

				std::weak_ptr<BaseActor> wpObject = pCollsion->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (wpObject.expired())
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				const std::shared_ptr<BaseActor>& pActor = wpObject.lock();

				const float4 Bullet_WPos = AttackCol->Transform.GetWorldPosition();
				const float4 Other_WPos = pActor->Transform.GetWorldPosition();
				const float4 DirVec = Other_WPos - Bullet_WPos;

				const float4 Other_WRot = pActor->Transform.GetWorldRotationEuler();
				const float4 Other_Forward = float4::VectorRotationToDegY(float4::FORWARD,Other_WRot.Y);

				const Enum_DirectionXZ_Quat eDir = ContentsMath::ReturnXZDirectionToVector(Other_Forward, DirVec);

				if (pActor->GetHitToShield({ pParent, 100 }))
				{
					MainState.ChangeState(eState::Ready); 
					return;
				}

				if (pActor->GetHit({ pParent ,100 ,eDir }))
				{
					MainState.ChangeState(eState::Ready);
					return;
				}
			}
		};

	AttackCol->Collision(Enum_CollisionOrder::Monster_Body, AttackFunc);
}