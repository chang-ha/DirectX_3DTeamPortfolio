#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Object_BaseLadder.h"

class Object_Ladder4 : public Object_BaseLadder
{
public:
	// constrcuter destructer
	Object_Ladder4();
	~Object_Ladder4();

	// delete Function
	Object_Ladder4(const Object_Ladder4& _Other) = delete;
	Object_Ladder4(Object_Ladder4&& _Other) noexcept = delete;
	Object_Ladder4& operator=(const Object_Ladder4& _Other) = delete;
	Object_Ladder4& operator=(Object_Ladder4&& _Other) noexcept = delete;

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

