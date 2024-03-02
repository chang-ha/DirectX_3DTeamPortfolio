#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_StartDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_StartDoor();
	~Object_StartDoor();

	// delete Function
	Object_StartDoor(const Object_StartDoor& _Other) = delete;
	Object_StartDoor(Object_StartDoor&& _Other) noexcept = delete;
	Object_StartDoor& operator=(const Object_StartDoor& _Other) = delete;
	Object_StartDoor& operator=(Object_StartDoor&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	
};

