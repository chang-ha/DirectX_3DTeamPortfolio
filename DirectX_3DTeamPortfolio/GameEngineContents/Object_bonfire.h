#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_bonfire : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_bonfire();
	~Object_bonfire();

	// delete Function
	Object_bonfire(const Object_bonfire& _Other) = delete;
	Object_bonfire(Object_bonfire&& _Other) noexcept = delete;
	Object_bonfire& operator=(const Object_bonfire& _Other) = delete;
	Object_bonfire& operator=(Object_bonfire&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;
	
};

