#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Skeleton1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Skeleton1();
	~Object_Skeleton1();

	// delete Function
	Object_Skeleton1(const Object_Skeleton1& _Other) = delete;
	Object_Skeleton1(Object_Skeleton1&& _Other) noexcept = delete;
	Object_Skeleton1& operator=(const Object_Skeleton1& _Other) = delete;
	Object_Skeleton1& operator=(Object_Skeleton1&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer3;

	
};

