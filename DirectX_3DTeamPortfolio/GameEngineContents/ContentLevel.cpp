#include "PreCompile.h"
#include "ContentLevel.h"
#include "FXAAEffect.h"
#include "Player.h"
ContentsCollisionCallBack  ContentLevel::CollisionCallBack;

ContentLevel::ContentLevel()
{
	GameEngineInput::AddInputObject(this);
}

ContentLevel::~ContentLevel()
{

}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	
	PhysXLevelInit();
	Scene->setSimulationEventCallback(&CollisionCallBack);
}

void ContentLevel::Update(float _Delta)
{
	DebugInput();
	RunSimulation(_Delta);
	ChaseListener();
}

void ContentLevel::Release()
{

}

void ContentLevel::ChaseListener()
{
	float4 Pos = GetMainCamera()->Transform.GetWorldPosition();
	float4 Rot = GetMainCamera()->Transform.GetWorldRotationEuler();

	// Y축만 고려 X,Z축은 필요시
	float4 ForWard = { 0.f, 0.f, 1.f, 1.f };
	ForWard.VectorRotationToDegY(Rot.Y);

	float4 Up = { 0.f, 1.f, 0.f, 1.f };

	GameEngineSound::SetListenerPos(Pos, ForWard, Up);
}

void ContentLevel::DebugInput()
{
	if (GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}
}

void ContentsCollisionCallBack::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
	for (physx::PxU32 i = 0; i < nbPairs; i++)
	{
		physx::PxContactPair current = *pairs++;

		physx::PxShape* thisActor = current.shapes[0];
		physx::PxShape* CollisionActor = current.shapes[1];

		physx::PxFilterData thisFilterdata = thisActor->getSimulationFilterData(); // 주체
		physx::PxFilterData CollisionFilterdata = CollisionActor->getSimulationFilterData();     // 대상

		if (thisFilterdata.word0 == 0 || CollisionFilterdata.word0 == 0)
		{
			continue;
		}

		if (thisFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Camera))		
		{
			if ((CollisionFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Map)))
			{
				//Player::Main_Player->Actor_test_02->Transform.AddWorldPosition(-Player::Main_Player->CameraDir * 10);
				Player::Main_Player->testa = true;
			}		
		}
		
		if (thisFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Big_Camera))
		{
			if ((CollisionFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Map)))
			{
				//testaa = true;
				//Player::Main_Player->Actor_test_02->Transform.AddWorldPosition(Player::Main_Player->CameraDir * 10);
				Player::Main_Player->testaa = true;
			}
		}
		
		if (thisFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Player))
		{
			if ((CollisionFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Map)))
			{
				Player::Main_Player->testaaa = true;
			}
		}
	}
}
