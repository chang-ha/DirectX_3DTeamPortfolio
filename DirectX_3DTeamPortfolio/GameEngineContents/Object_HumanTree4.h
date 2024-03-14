#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree4 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree4();
	~Object_HumanTree4();

	// delete Function
	Object_HumanTree4(const Object_HumanTree4& _Other) = delete;
	Object_HumanTree4(Object_HumanTree4&& _Other) noexcept = delete;
	Object_HumanTree4& operator=(const Object_HumanTree4& _Other) = delete;
	Object_HumanTree4& operator=(Object_HumanTree4&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	//е╦ют1
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

