#pragma once


#include <GameEngineCore/GameEngineActor.h>
class AppearTextures : public GameEngineActor
{
	enum struct TextureActor
	{
		None,
		Off,
		Appear,
		Disappear,
	};

public:
	// constructer destructer
	AppearTextures();
	~AppearTextures();

	// delete Function
	AppearTextures(const AppearTextures& _Other) = delete;
	AppearTextures(AppearTextures&& _Other) noexcept = delete;
	AppearTextures& operator = (const AppearTextures& _Other) = delete;
	AppearTextures& operator = (AppearTextures&& _Other) noexcept = delete;

	void ReceivePointer(class Player* _pPlayer, class Boss_Vordt* _pBoss);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void OffStart();
	void OffUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void DisappearStart();
	void DisappearUpdate(float _Delta);

	void ChangeState(TextureActor _State);
	void StateUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> Lit;
	std::shared_ptr<GameEngineUIRenderer> LitBack;
	std::shared_ptr<GameEngineUIRenderer> SoulImage;
	float4 ImageScale = float4::ZERO;

	float TextureTime = 0.0f;
	float TextureLimitTime = 2.0f;

	TextureActor TextActor = TextureActor::Off;


	// 받을 포인터들
	Player* PlayerObject = nullptr;
	Boss_Vordt* BossObject = nullptr;
};

