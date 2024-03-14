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
	std::shared_ptr<class ContentsAlphaSpriteRenderer> FireRender;
	std::shared_ptr<class ContentsLight> Light;
};

