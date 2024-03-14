#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree5 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree5();
	~Object_HumanTree5();

	// delete Function
	Object_HumanTree5(const Object_HumanTree5& _Other) = delete;
	Object_HumanTree5(Object_HumanTree5&& _Other) noexcept = delete;
	Object_HumanTree5& operator=(const Object_HumanTree5& _Other) = delete;
	Object_HumanTree5& operator=(Object_HumanTree5&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	//е╦ют1
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

