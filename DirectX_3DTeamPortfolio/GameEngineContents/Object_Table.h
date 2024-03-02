#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Table : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Table();
	~Object_Table();

	// delete Function
	Object_Table(const Object_Table& _Other) = delete;
	Object_Table(Object_Table&& _Other) noexcept = delete;
	Object_Table& operator=(const Object_Table& _Other) = delete;
	Object_Table& operator=(Object_Table&& _Other) noexcept = delete;

	
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
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer10;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer11;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer12;
	
	
};

