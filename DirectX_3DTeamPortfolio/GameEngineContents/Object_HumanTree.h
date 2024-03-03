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
	//타입1
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
	//타입2
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer10;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer11;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer12;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer13;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer14;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer15;
	//타입3
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer16;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer17;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer18;
	//타입4
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer19;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer20;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer21;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer22;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer23;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer24;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer25;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer26;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer27;
	//타입5
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer28;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer29;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer30;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer31;
	
};

