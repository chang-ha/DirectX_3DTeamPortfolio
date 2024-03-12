#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree3 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree3();
	~Object_HumanTree3();

	// delete Function
	Object_HumanTree3(const Object_HumanTree3& _Other) = delete;
	Object_HumanTree3(Object_HumanTree3&& _Other) noexcept = delete;
	Object_HumanTree3& operator=(const Object_HumanTree3& _Other) = delete;
	Object_HumanTree3& operator=(Object_HumanTree3&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	//е╦ют1
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

