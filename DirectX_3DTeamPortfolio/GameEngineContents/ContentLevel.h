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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
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

private:
	void ChaseListener();
	void DebugInput();
	static ContentsCollisionCallBack  CollisionCallBack;
	
};