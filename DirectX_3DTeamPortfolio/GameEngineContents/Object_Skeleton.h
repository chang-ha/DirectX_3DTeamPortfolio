#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Skeleton : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Skeleton();
	~Object_Skeleton();

	// delete Function
	Object_Skeleton(const Object_Skeleton& _Other) = delete;
	Object_Skeleton(Object_Skeleton&& _Other) noexcept = delete;
	Object_Skeleton& operator=(const Object_Skeleton& _Other) = delete;
	Object_Skeleton& operator=(Object_Skeleton&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer3;

	
};

