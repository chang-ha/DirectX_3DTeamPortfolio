#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree2();
	~Object_HumanTree2();

	// delete Function
	Object_HumanTree2(const Object_HumanTree2& _Other) = delete;
	Object_HumanTree2(Object_HumanTree2&& _Other) noexcept = delete;
	Object_HumanTree2& operator=(const Object_HumanTree2& _Other) = delete;
	Object_HumanTree2& operator=(Object_HumanTree2&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

