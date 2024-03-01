#pragma once

enum struct TextureActor
{
	None,
	Off,
	Appear,
	Disappear,
};

#include <GameEngineCore/GameEngineActor.h>
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

	void ChangeState(TextureActor _State);
	void StateUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void OffStart();
	void OffUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void DisappearStart();
	void DisappearUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> Lit;
	std::shared_ptr<GameEngineUIRenderer> LitBack;
	float4 ImageScale = float4::ZERO;

	float TextureTime = 0.0f;
	float TextureLimitTime = 1.5f;
	//float TextureLimitTime = 4.0f;

	TextureActor TextActor = TextureActor::Off;
};

