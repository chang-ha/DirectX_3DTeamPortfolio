#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Ladder5 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Ladder5();
	~Object_Ladder5();

	// delete Function
	Object_Ladder5(const Object_Ladder5& _Other) = delete;
	Object_Ladder5(Object_Ladder5&& _Other) noexcept = delete;
	Object_Ladder5& operator=(const Object_Ladder5& _Other) = delete;
	Object_Ladder5& operator=(Object_Ladder5&& _Other) noexcept = delete;

	float4 GetRotation();
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> CollisionTop;
	std::shared_ptr<GameEngineCollision> CollisionBottom;
	std::shared_ptr<GameEngineCollision> CollisionBody;
	
};

