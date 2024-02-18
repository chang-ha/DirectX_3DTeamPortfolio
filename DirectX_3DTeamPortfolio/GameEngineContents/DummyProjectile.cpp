#include "PreCompile.h"
#include "DummyProjectile.h"

#include "BaseActor.h"

DummyProjectile::DummyProjectile() 
{
}

DummyProjectile::~DummyProjectile() 
{
}

void DummyProjectile::Start()
{
	AttackRenderer = CreateComponent<GameEngineRenderer>(Enum_CollisionOrder::MonsterAttack);
	AttackRenderer->SetMesh("Sphere");
	AttackRenderer->SetMaterial("FBXStaticColor");
	AttackRenderer->RenderBaseInfoValue.BaseColor = float4(0.3f, 0.3f, 0.3f);

	AttackCol = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);

	const float AttScale = 20.f;

	Transform.SetWorldScale(float4(AttScale, AttScale, AttScale));
}

void DummyProjectile::Update(float _Delta) 
{

}

void DummyProjectile::Release() 
{
	AttackRenderer = nullptr;
	AttackCol = nullptr;
}

void DummyProjectile::AttackCollision()
{
	if (nullptr == AttackCol)
	{
		MsgBoxAssert("�������� �ʴ� �ݸ������� �浹�Ϸ� �߽��ϴ�.");
		return;
	}

	AttackCol->Collision(Enum_CollisionOrder::Monster, [](std::vector<GameEngineCollision*> _Other)
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
				
			}
		});
}