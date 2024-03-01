#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Ladder3 : public GameEngineActor
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

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> CollisionTop;
	std::shared_ptr<GameEngineCollision> CollisionBottom;
	
};

