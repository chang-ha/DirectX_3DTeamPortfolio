#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Table : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Table();
	~Object_Table();

	// delete Function
	Object_Table(const Object_Table& _Other) = delete;
	Object_Table(Object_Table&& _Other) noexcept = delete;
	Object_Table& operator=(const Object_Table& _Other) = delete;
	Object_Table& operator=(Object_Table&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	//std::shared_ptr<GameEnginePhysXCapsule> Capsule;
	
};

