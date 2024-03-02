#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_CandleHuman : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_CandleHuman();
	~Object_CandleHuman();

	// delete Function
	Object_CandleHuman(const Object_CandleHuman& _Other) = delete;
	Object_CandleHuman(Object_CandleHuman&& _Other) noexcept = delete;
	Object_CandleHuman& operator=(const Object_CandleHuman& _Other) = delete;
	Object_CandleHuman& operator=(Object_CandleHuman&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	//std::shared_ptr<GameContentsFBXRenderer> FBXRenderer1;
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
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer13;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer14;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer15;
};

