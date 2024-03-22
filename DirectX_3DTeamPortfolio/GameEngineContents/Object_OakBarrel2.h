#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_OakBarrel2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_OakBarrel2();
	~Object_OakBarrel2();

	// delete Function
	Object_OakBarrel2(const Object_OakBarrel2& _Other) = delete;
	Object_OakBarrel2(Object_OakBarrel2&& _Other) noexcept = delete;
	Object_OakBarrel2& operator=(const Object_OakBarrel2& _Other) = delete;
	Object_OakBarrel2& operator=(Object_OakBarrel2&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXBox> Box;

	
};

