#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Box : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Box();
	~Object_Box();

	// delete Function
	Object_Box(const Object_Box& _Other) = delete;
	Object_Box(Object_Box&& _Other) noexcept = delete;
	Object_Box& operator=(const Object_Box& _Other) = delete;
	Object_Box& operator=(Object_Box&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXBox> Box;

	
};

