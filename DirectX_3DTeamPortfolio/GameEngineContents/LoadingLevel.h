#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class LoadingLevel : public ContentLevel
{
public:
	// constrcuter destructer
	LoadingLevel();
	~LoadingLevel();

	// delete Function
	LoadingLevel(const LoadingLevel& _Other) = delete;
	LoadingLevel(LoadingLevel&& _Other) noexcept = delete;
	LoadingLevel& operator=(const LoadingLevel& _Other) = delete;
	LoadingLevel& operator=(LoadingLevel&& _Other) noexcept = delete;

public:
	static Enum_LevelFlag LoadingFlag;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	enum class eLoadingState
	{
		Loading,
		FadeOut,
	};

	GameEngineState LevelState;

	void Start_Loading(GameEngineState* _Parent);
	void Update_Loading(float _Delta, GameEngineState* _Parent);

	void Start_FadeOut(GameEngineState* _Parent);
	void Update_FadeOut(float _Delta, GameEngineState* _Parent);

	//// Thread Function
	GameEngineThreadJobQueue LoadingThread;


};

