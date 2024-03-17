#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_BossDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_BossDoor();
	~Object_BossDoor();

	// delete Function
	Object_BossDoor(const Object_BossDoor& _Other) = delete;
	Object_BossDoor(Object_BossDoor&& _Other) noexcept = delete;
	Object_BossDoor& operator=(const Object_BossDoor& _Other) = delete;
	Object_BossDoor& operator=(Object_BossDoor&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXBox> Box;

	
};

