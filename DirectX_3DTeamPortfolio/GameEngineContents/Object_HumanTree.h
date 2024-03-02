#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_HumanTree : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_HumanTree();
	~Object_HumanTree();

	// delete Function
	Object_HumanTree(const Object_HumanTree& _Other) = delete;
	Object_HumanTree(Object_HumanTree&& _Other) noexcept = delete;
	Object_HumanTree& operator=(const Object_HumanTree& _Other) = delete;
	Object_HumanTree& operator=(Object_HumanTree&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer3;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer4;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer5;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer6;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer7;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer8;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer9;

	
	
};

