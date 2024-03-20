#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_OakBarrel : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_OakBarrel();
	~Object_OakBarrel();

	// delete Function
	Object_OakBarrel(const Object_OakBarrel& _Other) = delete;
	Object_OakBarrel(Object_OakBarrel&& _Other) noexcept = delete;
	Object_OakBarrel& operator=(const Object_OakBarrel& _Other) = delete;
	Object_OakBarrel& operator=(Object_OakBarrel&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXBox> Box;

	
};

