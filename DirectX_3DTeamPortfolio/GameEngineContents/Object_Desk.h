#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Desk : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Desk();
	~Object_Desk();

	// delete Function
	Object_Desk(const Object_Desk& _Other) = delete;
	Object_Desk(Object_Desk&& _Other) noexcept = delete;
	Object_Desk& operator=(const Object_Desk& _Other) = delete;
	Object_Desk& operator=(Object_Desk&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	
};

