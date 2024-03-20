#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Shelf : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Shelf();
	~Object_Shelf();

	// delete Function
	Object_Shelf(const Object_Shelf& _Other) = delete;
	Object_Shelf(Object_Shelf&& _Other) noexcept = delete;
	Object_Shelf& operator=(const Object_Shelf& _Other) = delete;
	Object_Shelf& operator=(Object_Shelf&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXBox> Box;

	
};

