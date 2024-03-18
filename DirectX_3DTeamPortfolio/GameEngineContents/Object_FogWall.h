#pragma once
#include <GameEngineCore/GameEngineActor.h>

 
class Object_FogWall : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_FogWall();
	~Object_FogWall();

	// delete Function
	Object_FogWall(const Object_FogWall& _Other) = delete;
	Object_FogWall(Object_FogWall&& _Other) noexcept = delete;
	Object_FogWall& operator=(const Object_FogWall& _Other) = delete;
	Object_FogWall& operator=(Object_FogWall&& _Other) noexcept = delete;

	void SetOutFunction(std::function<void()> _OutFunction)
	{
		OutFunction = _OutFunction;
	}

	void GetBossPtr(std::shared_ptr<class BaseActor> _BossPtr)
	{
		BossPtr = _BossPtr;
	}

	void Start_Boss()
	{
		if (nullptr == OutFunction)
		{
			MsgBoxAssert("시작함수가 존재하지 않습니다.");
			return;
		}

		OutFunction();
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<class ContentsFogWallRenderer> FogWallRenderer = nullptr;

	std::shared_ptr<GameEnginePhysXBox> WallCollision = nullptr;
	std::shared_ptr<GameEngineCollision> InDetectCollision = nullptr;
	std::shared_ptr<GameEngineCollision> OutDetectCollision = nullptr;

	std::function<void()> OutFunction;
	std::shared_ptr<class BaseActor> BossPtr = nullptr;

	void OutDetect();
};

