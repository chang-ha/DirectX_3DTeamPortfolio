#include "PreCompile.h"

#include "PlayLevel.h"
#include "Player.h"

#include "GameEngineNetWindow.h"
#include "ContentsControlWindow.h"

#include "MainUIActor.h"
#include "UIPlayerGaugeBar.h"

#include "WorldMap.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{


	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);

	/*{
		std::shared_ptr<WorldMap> GameMap = CreateActor<WorldMap>(0, "WorldMap");
	}*/

	GetMainCamera()->Transform.SetWorldRotation({ 0.0f,0.0f,0.0f });
	GetMainCamera()->Transform.SetWorldPosition({ 0.0f, 0.0f, -1000.0f });


	GetCamera(3)->Transform.SetWorldRotation({ 0.0f,0.0f,0.0f });
	GetCamera(3)->Transform.SetWorldPosition({ 0.0f, 0.0f, -1000.0f });
	GetCamera(3)->SetProjectionType(EPROJECTIONTYPE::Perspective);


	//GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("Test");


	//GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1.0f,1.0f,1.0f,1.0f });

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	// ���ٲ���
	std::shared_ptr<GameEngineNetWindow> Ptr = GameEngineGUI::CreateGUIWindow<GameEngineNetWindow>("GameEngineNetWIndow");

	/*if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(0, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	}*/

	{
		std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
		PlayerObject = Object;

		// ������ġ
		PlayerObject->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });

		Ptr->MainPlayer = PlayerObject.get();
	}

	//{
	//	std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");

	//	//Object->Transform.AddLocalPosition({ 500.0f,0.0f });
	//	PlayerObject = Object;

	//	Ptr->MainPlayer = PlayerObject.get();
	//	Object->check = true;
	//}

	{
		std::shared_ptr<GameEngineLight> Object = CreateActor<GameEngineLight>(0);
	}


	{
		std::shared_ptr<MainUIActor> MainUI = CreateActor<MainUIActor>();
	}

	{
		//std::shared_ptr<UIPlayerGaugeBar> Test = CreateActor<UIPlayerGaugeBar>();
	}

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("Dark.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != GameEngineSprite::Find("Dark.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineSprite::Release(pFiles.GetFileName());
			GameEngineTexture::Release(pFiles.GetFileName());
		}
	}
}