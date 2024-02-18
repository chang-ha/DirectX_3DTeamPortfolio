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
static constexpr float DP_LIVETIME = 5.0f;

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
				MsgBoxAssert("�θ� �������� ������ ����� �� ���� ����Դϴ�.");
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
		MsgBoxAssert("�������� �ʴ� �ݸ������� �浹�Ϸ� �߽��ϴ�.");
		return;
	}

	std::function AttackFunc = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (int i = 0; i < static_cast<int>(_Other.size()); i++)
			{
				GameEngineCollision* pCollsion = _Other[i];
				if (nullptr == pCollsion)
				{
					MsgBoxAssert("�̻��� ���� ����ֽ��ϴ�.");
					return;
				}

				std::weak_ptr<BaseActor> wpObject = pCollsion->GetDynamic_Cast_This<BaseActor>();
				if (wpObject.expired())
				{
					MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
					return;
				}

				const std::shared_ptr<BaseActor>& pActor = wpObject.lock();
				pActor->GetHit(Att);

				Off();
				break;
			}
		};

	AttackCol->Collision(Enum_CollisionOrder::Monster, AttackFunc);

	// ���� ��������
	//AttackCol->Collision(Enum_CollisionOrder::Monster, [](std::vector<GameEngineCollision*> _Other)
	//	{
	//		for (int i = 0; i < static_cast<int>(_Other.size()); i++)
	//		{
	//			GameEngineCollision* pCollsion = _Other[i];
	//			if (nullptr == pCollsion)
	//			{
	//				MsgBoxAssert("�̻��� ���� ����ֽ��ϴ�.");
	//				return;
	//			}

	//			std::weak_ptr<BaseActor> wpObject = pCollsion->GetDynamic_Cast_This<BaseActor>();
	//			if (wpObject.expired())
	//			{
	//				MsgBoxAssert("����ȯ�� �����߽��ϴ�.");
	//				return;
	//			}

	//			const std::shared_ptr<BaseActor>& pActor = wpObject.lock();
	//			
	//		}
	//	});
}