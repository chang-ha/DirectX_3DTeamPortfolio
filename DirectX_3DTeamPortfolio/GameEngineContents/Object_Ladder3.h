#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Object_BaseLadder.h"

class Object_Ladder3 : public Object_BaseLadder
{
public:
	// constrcuter destructer
	Object_Ladder3();
	~Object_Ladder3();

	// delete Function
	Object_Ladder3(const Object_Ladder3& _Other) = delete;
	Object_Ladder3(Object_Ladder3&& _Other) noexcept = delete;
	Object_Ladder3& operator=(const Object_Ladder3& _Other) = delete;
	Object_Ladder3& operator=(Object_Ladder3&& _Other) noexcept = delete;

	//float4 GetRotation();
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> CollisionTop;
	std::shared_ptr<GameEngineCollision> CollisionBottom;
	std::shared_ptr<GameEngineCollision> CollisionBody;
	
};

