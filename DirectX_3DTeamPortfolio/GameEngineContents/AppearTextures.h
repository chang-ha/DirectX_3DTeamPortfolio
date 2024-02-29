#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class AppearTextures : public GameEngineActor
{
public:
	// constructer destructer
	AppearTextures();
	~AppearTextures();

	// delete Function
	AppearTextures(const AppearTextures& _Other) = delete;
	AppearTextures(AppearTextures&& _Other) noexcept = delete;
	AppearTextures& operator = (const AppearTextures& _Other) = delete;
	AppearTextures& operator = (AppearTextures&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> Lit;
	std::shared_ptr<GameEngineUIRenderer> LitBack;
	float4 ImageScale = float4::ZERO;

	float TextureTime = 0.0f;
	float TextureLimitTime = 4.0f;
};

