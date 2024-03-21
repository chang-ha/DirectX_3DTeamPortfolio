#pragma once
#include "GameEngineCore\GameEnginePhysXLevel.h"

class ContentsCollisionCallBack : public physx::PxSimulationEventCallback
{
	void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {}
	void onWake(physx::PxActor** actors, physx::PxU32 count) override {}
	void onSleep(physx::PxActor** actors, physx::PxU32 count) override {}
	void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
	void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override {}
	void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {}
};

struct ScreenShake {
	float duration; // 흔들림이 지속되는 시간
	float magnitude; // 흔들림의 세기
	float elapsed; // 흔들림이 지속되는 시간 타이머
	float frequency = 2.0f; // 흔들림의 빈도
};

class ContentLevel : public GameEngineLevel, public GameEnginePhysXLevel
{
public:
	// constructer destructer
	ContentLevel();
	~ContentLevel();

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	void StartScreenShake(float duration = 0.5f, float magnitude = 8.0f, float frequency = 10.0f) {
		screenShakeValue.duration = duration;
		screenShakeValue.magnitude = magnitude;
		screenShakeValue.frequency = frequency;
		screenShakeValue.elapsed = 0.0f;
	}

	

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void UpdateScreenShake(float _deltaTime);
	void Release() override;

	template<typename ObjectType, typename OrderType>
	void AllDeathObjectGroupConvert(OrderType _Order)
	{
		std::vector<std::shared_ptr<ObjectType>> Objects = GetObjectGroupConvert<ObjectType>(_Order);
		for (const std::shared_ptr<ObjectType>& ObjectPointer : Objects)
		{
			ObjectPointer->Death();
		}

		if (bool OutputMsg = true)
		{
			OutputDebugStringA((std::to_string(Objects.size()) + "\t" + std::string(typeid(ObjectType).name()) + " have been released. \n").c_str());
		}
	}

	std::shared_ptr<class AllFadeEffect> FadeObject;

private:
	void ChaseListener();
	void DebugInput();
	static ContentsCollisionCallBack  CollisionCallBack;

	ScreenShake screenShakeValue;
	float4 PrevShackeMovePos = float4::ZERO;
	float4 PrevShackeRotationPos = float4::ZERO;


	
};