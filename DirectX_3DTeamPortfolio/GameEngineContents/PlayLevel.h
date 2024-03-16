#pragma once
#include "ContentLevel.h"



// Ό³Έν :
class PlayLevel : public ContentLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


private:



	std::shared_ptr<class GameEngineCoreWindow> CoreWindow;
	std::shared_ptr<class FadePostEffect> FadeEffect;
	std::shared_ptr<class Player> PlayerObject;
	std::shared_ptr<class PlayMap> Map;

	std::shared_ptr<class Boss_Vordt> Boss_Object = nullptr;
	std::shared_ptr<class MainUIActor> MainUI;
	std::shared_ptr<class UIActor> ActorUI;
};

