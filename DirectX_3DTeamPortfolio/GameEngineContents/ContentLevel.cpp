#include "PreCompile.h"
#include "ContentLevel.h"
#include "FXAAEffect.h"
#include "Player.h"

#include "AllFadeEffect.h"

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
	Scene->lockWrite();
	Scene->setSimulationEventCallback(&CollisionCallBack);
	Scene->unlockWrite();

	FadeObject = GetLevelRenderTarget()->CreateEffect<AllFadeEffect>();
	FadeObject->Off();
}

void ContentLevel::Update(float _Delta)
{
	DebugInput();
	RunSimulation(_Delta);
	ChaseListener();

	UpdateScreenShake(_Delta);

	if (GameEngineInput::IsDown('N',this))
	{
		FadeObject->FadeIn();
	}
	if (GameEngineInput::IsDown('M',this))
	{
		FadeObject->FadeOut();
	}
}

void ContentLevel::UpdateScreenShake(float _deltaTime)
{
	if (screenShakeValue.elapsed < screenShakeValue.duration)
	{
		// 보다 자연스러운 감쇠를 위해 부드러운 단계 함수를 사용하여 시간이 지남에 따라 흔들림 계수가 1에서 0으로 감소합니다.
		float swayFactor = 1.0f - static_cast<float>(pow(screenShakeValue.elapsed / screenShakeValue.duration, 2));

		// 부드러운 진동을 위해 사인파를 사용하여 스웨이 오프셋을 계산합니다.
		// 주파수는 초당 발생하는 전체 진동 횟수를 결정합니다.
		float phase = screenShakeValue.elapsed * screenShakeValue.frequency * DirectX::XM_2PI;


		// 각 축에 대해 사인파의 위상과 진폭을 무작위화합니다.
		float randomPhaseX = rand() % 1000 * 0.001f * DirectX::XM_2PI; // 0과 2*PI 사이의 랜덤 위상
		float randomPhaseY = rand() % 1000 * 0.001f * DirectX::XM_2PI;
		float randomAmplitudeX = (rand() % 1000 * 0.001f) * screenShakeValue.magnitude;
		float randomAmplitudeY = (rand() % 1000 * 0.001f) * screenShakeValue.magnitude;


		// 부드러운 진동을 위해 무작위성을 가진 사인파를 사용하여 흔들림 오프셋을 계산합니다.
		//float time = screenShakeValue.elapsed * screenShakeValue.frequency;
		float offsetX = sin(phase + randomPhaseX) * randomAmplitudeX * swayFactor;
		float offsetY = cos(phase + randomPhaseY) * randomAmplitudeY * swayFactor;

		//float offsetZ = ContentsCore::MainRandom->RandomFloat(-2.0f, 2.0f);


		Player::Main_Player->Actor_test_02->Transform.AddLocalPosition(-PrevShackeMovePos + float4(offsetX, offsetY, 0.0f, 0.0f));
		PrevShackeMovePos = float4(offsetX, offsetY, 0.0f, 0.0f);

		//GetMainCamera()->Transform.AddLocalRotation(-PrevShackeRotationPos + float4(0.0f, 0.0f, offsetZ,0.0f));
		//PrevShackeRotationPos = float4(0.0f, 0.0f, offsetZ, 0.0f);


		screenShakeValue.elapsed += _deltaTime;
	}
	else if (PrevShackeMovePos != float4::ZERO)
	{
		Player::Main_Player->Actor_test_02->Transform.AddLocalPosition(-PrevShackeMovePos);
		//GetMainCamera()->Transform.AddLocalRotation(-PrevShackeRotationPos);
		PrevShackeMovePos = float4::ZERO;
		//PrevShackeRotationPos = float4::ZERO;
	}
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
				Player::Main_Player->testa = true;
			}		
		}
		
		if (thisFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Big_Camera))
		{
			if ((CollisionFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Map)))
			{
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

		if (thisFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Player))
		{
			if ((CollisionFilterdata.word0 & static_cast<int>(Enum_CollisionOrder::Fog_Wall)))
			{
				Player::Main_Player->Fog_Check = true;
			}
		}
	}
	
}
