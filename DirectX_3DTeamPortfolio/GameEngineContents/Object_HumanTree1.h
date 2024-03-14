#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree1();
	~Object_HumanTree1();

	// delete Function
	Object_HumanTree1(const Object_HumanTree1& _Other) = delete;
	Object_HumanTree1(Object_HumanTree1&& _Other) noexcept = delete;
	Object_HumanTree1& operator=(const Object_HumanTree1& _Other) = delete;
	Object_HumanTree1& operator=(Object_HumanTree1&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	//е╦ют1
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

