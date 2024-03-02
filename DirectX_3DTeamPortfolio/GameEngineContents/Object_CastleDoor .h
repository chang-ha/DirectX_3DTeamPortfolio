#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_CastleDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_CastleDoor();
	~Object_CastleDoor();

	// delete Function
	Object_CastleDoor(const Object_CastleDoor& _Other) = delete;
	Object_CastleDoor(Object_CastleDoor&& _Other) noexcept = delete;
	Object_CastleDoor& operator=(const Object_CastleDoor& _Other) = delete;
	Object_CastleDoor& operator=(Object_CastleDoor&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	
};

