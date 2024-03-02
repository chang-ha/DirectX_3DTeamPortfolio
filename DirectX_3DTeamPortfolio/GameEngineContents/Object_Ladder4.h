#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Ladder4 : public GameEngineActor
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

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> CollisionTop;
	std::shared_ptr<GameEngineCollision> CollisionBottom;
	
};

