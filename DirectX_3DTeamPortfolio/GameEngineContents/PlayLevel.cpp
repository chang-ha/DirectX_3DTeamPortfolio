#include "PreCompile.h"

#include "PlayLevel.h"
#include "Player.h"

#include "GameEngineNetWindow.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	GameEngineInput::AddInputObject(this);

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f });




	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	// ¾ø¾Ù²¨ÀÓ
	std::shared_ptr<GameEngineNetWindow> Ptr = GameEngineGUI::CreateGUIWindow<GameEngineNetWindow>("GameEngineNetWIndow");

	if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
		PlayerObject = Object;

		Ptr->MainPlayer = PlayerObject.get();
	}

	{
		std::shared_ptr<GameEngineLight> Object = CreateActor<GameEngineLight>(0);
	}
}

void PlayLevel::Update(float _Delta)
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}
