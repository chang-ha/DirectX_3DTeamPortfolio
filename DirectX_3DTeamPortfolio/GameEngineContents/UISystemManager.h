#pragma once

enum class Enum_SystemType
{
	Object_bonfire,
	Object_Ladder,
	Object_FogWall,
	Done,
};

// Ό³Έν :
class UISystemManager : public GameEngineActor
{
	enum class eState
	{
		None,
		FadeIn,
		FadeOut,
	};

public:
	// constructer destructer
	UISystemManager();
	~UISystemManager();

	// delete Function
	UISystemManager(const UISystemManager& _Other) = delete;
	UISystemManager(UISystemManager&& _Other) noexcept = delete;
	UISystemManager& operator = (const UISystemManager& _Other) = delete;
	UISystemManager& operator = (UISystemManager&& _Other) noexcept = delete;

	void OnSystem(Enum_SystemType _Type); // switch Name FontRenderer->ChangeText() On
	void OffSystem();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelEnd(GameEngineLevel* _NextLevel);

	// State
	void FadeIn_Start(GameEngineState* _Parent);
	void FadeIn_Update(float _Delta, GameEngineState* _Parent);

	void FdaeOut_Update(float _Delta, GameEngineState* _Parent);

	void SetGamma(float _Ratio);


private:
	std::shared_ptr<GameEngineUIRenderer> Window;
	std::shared_ptr<GameEngineUIRenderer> Font;
	std::shared_ptr<GameEngineUIRenderer> Debug;

	GameEngineState MainState;

	float GammaValue = 0.0f;

	static Enum_SystemType Type;
};