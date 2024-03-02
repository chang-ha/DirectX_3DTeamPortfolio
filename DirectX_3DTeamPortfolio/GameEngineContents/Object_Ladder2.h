#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Ladder2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Ladder2();
	~Object_Ladder2();

	// delete Function
	Object_Ladder2(const Object_Ladder2& _Other) = delete;
	Object_Ladder2(Object_Ladder2&& _Other) noexcept = delete;
	Object_Ladder2& operator=(const Object_Ladder2& _Other) = delete;
	Object_Ladder2& operator=(Object_Ladder2&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> CollisionTop;
	std::shared_ptr<GameEngineCollision> CollisionBottom;
	
};

