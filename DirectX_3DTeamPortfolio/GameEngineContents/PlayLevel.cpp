#include "PreCompile.h"

#include "PlayLevel.h"
#include "Player.h"

#include "GameEngineNetWindow.h"
#include "ContentsControlWindow.h"

#include "MainUIActor.h"
#include "MonsterHpBar.h"

#include "WorldMap.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "Monster_HollowSoldier.h"
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

	GetMainCamera()->Transform.SetWorldRotation({ 0.0f,0.0f,0.0f });
	GetMainCamera()->Transform.SetWorldPosition({ 0.0f, 0.0f, -1000.0f });

	{
		std::shared_ptr<GameEngineLight> Object = CreateActor<GameEngineLight>(0);
		//Object->CreateShadowMap();
	}

}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	

	/*{
		std::shared_ptr<WorldMap> GameMap = CreateActor<WorldMap>(0, "WorldMap");
	}*/

	


	{

	}

	//GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("Test");


	//GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1.0f,1.0f,1.0f,1.0f });

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	

	
	{
		std::shared_ptr<Boss_Vordt> GameMap = CreateActor<Boss_Vordt>(0, "WorldMap");

		GameMap->Transform.SetWorldPosition({ 0.0f,0.0f,300.3f });

		std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
		Object->SetTargeting(GameMap.get());
		//GameMap->SetTargeting(Object.get()); 
		PlayerObject = Object;
		GameMap->SetTargeting(GameMap.get());

		// 시작위치
		//PlayerObject->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });

		
	}

	//{
	//	std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");

	//	//Object->Transform.AddLocalPosition({ 500.0f,0.0f });
	//	PlayerObject = Object;

	//	Ptr->MainPlayer = PlayerObject.get();
	//	Object->check = true;
	//}

	

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


		MainUI = CreateActor<MainUIActor>();

		//std::shared_ptr<MonsterHpBar> Test = CreateActor<MonsterHpBar>();
	}

	

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);
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