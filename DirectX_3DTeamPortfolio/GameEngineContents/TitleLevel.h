#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class TitleLevel : public ContentLevel
{
public:
	// constructer destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator = (const TitleLevel& _Other) = delete;
	TitleLevel& operator = (TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NetxLevel) override;

	void TestClear();

private:
	std::shared_ptr<class GameEngineCoreWindow> CoreWindow;
	std::shared_ptr<class GameEngineSpriteRenderer> DarkBack;

	std::shared_ptr<class TitleLogo> Title_Logo = nullptr;

	GameEngineSoundPlayer BGMPlayer;
};

