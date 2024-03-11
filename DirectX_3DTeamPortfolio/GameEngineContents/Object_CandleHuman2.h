#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_CandleHuman2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_CandleHuman2();
	~Object_CandleHuman2();

	// delete Function
	Object_CandleHuman2(const Object_CandleHuman2& _Other) = delete;
	Object_CandleHuman2(Object_CandleHuman2&& _Other) noexcept = delete;
	Object_CandleHuman2& operator=(const Object_CandleHuman2& _Other) = delete;
	Object_CandleHuman2& operator=(Object_CandleHuman2&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};