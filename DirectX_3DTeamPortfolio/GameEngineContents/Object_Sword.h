#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Sword : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Sword();
	~Object_Sword();

	// delete Function
	Object_Sword(const Object_Sword& _Other) = delete;
	Object_Sword(Object_Sword&& _Other) noexcept = delete;
	Object_Sword& operator=(const Object_Sword& _Other) = delete;
	Object_Sword& operator=(Object_Sword&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;
	

	
};

