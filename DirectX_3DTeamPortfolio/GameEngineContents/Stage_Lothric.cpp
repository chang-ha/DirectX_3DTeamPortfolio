#include "PreCompile.h"
#include "Stage_Lothric.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "Player.h"
#include "WorldMap.h"
#include <GameEngineCore\FogEffect.h>
#include <GameEngineCore\DepthOfField.h>
#include "FXAAEffect.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "LUTEffect.h"
#include "Object_FogWall.h"


//오브젝트 헤더
#include "Object_Ladder1.h"
#include "Object_Ladder2.h"
#include "Object_Ladder3.h"
#include "Object_Ladder4.h"
#include "Object_Ladder5.h"
#include "Object_Ladder6.h"
#include "TestMapObjcet.h"
#include "ContentsLight.h"
#include "Object_BossDoor.h"
#include "Object_CastleDoor .h"
#include "Object_Desk.h"
#include "Object_Skeleton.h"
#include "Object_Skeleton1.h"
#include "Object_StartDoor.h"
#include "Object_bonfire.h"
#include "Object_Table.h"
#include "Object_HumanTree1.h"
#include "Object_HumanTree2.h"
#include "Object_HumanTree3.h"
#include "Object_HumanTree4.h"
#include "Object_HumanTree5.h"
#include "Object_CandleHuman.h"
#include "Object_Torchlight.h"
#include "Object_CandleHuman2.h"
#include "Monster_LothricKn.h"
#include "Monster_Hollow_RaggedRobes.h"
#include "Monster_HollowSoldier_Lantern.h"
#include "Monster_Hollow_Unarmed.h"
#include "Monster_HollowSoldier_RoundShield.h"
#include "Monster_HollowSoldier_Spear.h"
#include "Monster_HollowSoldier_Sword.h"
#include "EventCol.h"

//UI
#include "MainUIActor.h"

Stage_Lothric::Stage_Lothric()
{

}

Stage_Lothric::~Stage_Lothric()
{

}

void Stage_Lothric::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		Map_Lothric = CreateActor<WorldMap>(0, "WorldMap");
	}

	{
		std::shared_ptr<GameEngineActor> Ground = CreateActor<GameEngineActor>(0);
		std::shared_ptr<GameEngineRenderer> NewRenderer = Ground->CreateComponent<GameEngineRenderer>();
		NewRenderer->SetMesh("Box");
		NewRenderer->SetMaterial("FBX_Static_Color");
		// NewRenderer->GetShaderResHelper().SetTexture("NormalTexture", "BumpNormal.gif");
		NewRenderer->Transform.SetLocalPosition({ 0.0f, -40000.0f, 0.0f });
		NewRenderer->Transform.SetLocalScale({ 1000000.0f, 100.0f, 1000000.0f });
		NewRenderer->RenderBaseInfoValue.BaseColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->SetWorldPosition({ -1100.f, -2500.f, 3000.f });
		Boss_Object->SetWorldRotation({ 0.f, -30.f, 0.f });
	}


	// Light
	if (nullptr == Light)
	{
		Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "mainDirect");
		LightData Data = Light->GetLightData();
		Light->CreateShadowMap();

		//Data.DifLightPower = 0.1f;
		Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
		Data.LightColor = float4(1.0f, 1.0f, 0.7f);
		Data.LightPower = 2.0f;
		Data.ForceLightPower = 0.25f;

		Light->Transform.SetLocalPosition({ -12000.0f, 16200.0f, -4260.0f });
		Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


		Light->SetLightData(Data);
		//Light->IsDebugValue = true;
	}


	// DepthOfField
	{
		std::shared_ptr<DepthOfField> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<DepthOfField>();
		Effect->Init(GetMainCamera());
	}
	//
	// Fog
	{
		std::shared_ptr<FogEffect> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
		Effect->Init(GetMainCamera());
	}


	////FXAA

	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<LUTEffect>();

	// Building

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	{
		Player_Object = CreateActor<Player>(0, "Player");
		// 볼드 위치
		// Player_Object->SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		// 
		// 계단 위치
		//Player_Object->SetWorldPosition({ -9910.0f, 2328.0f, -2894.0f });
		// 
		// 시작 위치
		Player_Object->SetWorldPosition({ -1400.0f, 5101.0f, -5331.0f });

		Player_Object->SetWorldRotation({ 0.f, 0.f, 0.f });
		Player_Object->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(Player_Object.get());
	}
	{
		std::shared_ptr<Monster_HollowSoldier> GameMap = CreateActor<Monster_HollowSoldier>(0 );
		GameMap->Transform.SetWorldPosition({ -2900.f,-2500.f,6800.f });
	}

	BossBGM = GameEngineSound::SoundPlay("1-06 Vordt Of The Boreal Valley.mp3", 100);
	BossBGMVolume = BEGIN_BOSS_BGM_VOLUME;
	BossBGM.SetVolume(BossBGMVolume);
	BossBGM.Pause();

	{
		FogWall = CreateActor<Object_FogWall>();
		FogWall->Transform.SetWorldPosition({ -3125, -2100.f, 7070.f });
		FogWall->Transform.SetWorldRotation({ 0.f,152.f });

		FogWall->SetOutFunction([&]()
			{
				Boss_Object->AI_Start();
				Boss_Object->DummyPolySoundOn();
				MainUI->BossUIOn();
				BossBGMVolume = BEGIN_BOSS_BGM_VOLUME;
				BossBGM.SetVolume(BossBGMVolume);
				BossBGM.Resume();
			});
	}

	CreateObject();

	{
		std::shared_ptr<Monster_LothricKn> Monster;
		// Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Lothric1");
		// Monster->SetIdleType(Enum_Lothric_IdleType::Sit);
		// Monster->WakeUp();
		// Monster->SetWPosition(float4( -3874.0f, 4118.0f, -951.0f ));
		// Monster->SetWPosition(float4(-5443.0f, -876.f, 10681.f));
		Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Lothric2");
		Monster->SetWPosition(float4(-6276, -683, 13803));
	}

	// 몬스터 위치 셋팅
	SetAllMonster();

	SetAllEvCol();

	std::shared_ptr<GameEngineCoreWindow> CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(1, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		CoreWindow->AddDebugRenderTarget(2, "ForwardTarget", GetMainCamera()->GetCameraForwardTarget());
		CoreWindow->AddDebugRenderTarget(3, "DeferredLightTarget", GetMainCamera()->GetCameraDeferredLightTarget());
		CoreWindow->AddDebugRenderTarget(4, "DeferredTarget", GetMainCamera()->GetCameraDeferredTarget());
		//CoreWindow->AddDebugRenderTarget(5, "LightTarget", Light->GetShadowTarget());
		//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	}

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

		if (nullptr == GameEngineSprite::Find("DarkSoulsIII_Main_Menu_Theme.wav"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources\\Sound\\UI");

			std::vector<GameEngineFile> Files = Dir.GetAllFile();
			for (GameEngineFile& pFiles : Files)
			{
				GameEngineSound::SoundLoad(pFiles.GetStringPath());
			}
		}

		MainUI = CreateActor<MainUIActor>(Enum_UpdateOrder::UI);
		MainUI->CreateBossUI(Boss_Object.get());
		MainUI->CreateAndCheckEsteUI(Player_Object.get());
		MainUI->CreateAndCheckPlayerGaugeBar(Player_Object.get());
	}
}

void Stage_Lothric::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Stage_Lothric::Start()
{
	IsDebug = false;
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	
}

void Stage_Lothric::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	EvColUpdate();
	BossBGMUpdate(_Delta);

	float4 PPos = Player_Object->Transform.GetWorldPosition();

	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
	}
	if (true == GameEngineInput::IsDown('J', this))
	{
		Player_Object->Off();
	}

}

void Stage_Lothric::Release()
{
	if (nullptr != Boss_Object)
	{
		Boss_Object->Death();
		Boss_Object = nullptr;
	}

	if (nullptr != Player_Object)
	{
		Player_Object->Death();
		Player_Object = nullptr;
	}

	if (nullptr != Map_Lothric)
	{
		Map_Lothric->Death();
		Map_Lothric = nullptr;
	}

	if (nullptr != Light)
	{
		Light->Death();
		Light = nullptr;
	}


	//오브젝트 릴리즈
	if (nullptr != BossDoor)
	{
		BossDoor->Death();
		BossDoor = nullptr;
	}
	if (nullptr != CastleDoor)
	{
		CastleDoor->Death();
		CastleDoor = nullptr;
	}
	if (nullptr != Ladder1)
	{
		Ladder1->Death();
		Ladder1 = nullptr;
	}
	if (nullptr != Ladder2)
	{
		Ladder2->Death();
		Ladder2 = nullptr;
	}
	if (nullptr != Ladder3)
	{
		Ladder3->Death();
		Ladder3 = nullptr;
	}
	if (nullptr != Ladder4)
	{
		Ladder4->Death();
		Ladder4 = nullptr;
	}
	if (nullptr != Ladder5)
	{
		Ladder5->Death();
		Ladder5 = nullptr;
	}
	if (nullptr != Ladder6)
	{
		Ladder6->Death();
		Ladder6 = nullptr;
	}
	if (nullptr != Desk)
	{
		Desk->Death();
		Desk = nullptr;
	}

	if (true != VBonfire.empty())
	{
		for (size_t i = 0; i < VBonfire.size(); i++)
		{
			VBonfire[i]->Release();
			VBonfire[i] = nullptr;
		}
	}

	if (true != VTable.empty())
	{
		for (size_t i = 0; i < VTable.size(); i++)
		{
			VTable[i]->Release();
			VTable[i] = nullptr;
		}
	}
	if (true != VTorchlight.empty())
	{
		for (size_t i = 0; i < VTorchlight.size(); i++)
		{
			VTorchlight[i]->Release();
			VTorchlight[i] = nullptr;
		}
	}
	if (true != VSkeleton.empty())
	{
		for (size_t i = 0; i < VSkeleton.size(); i++)
		{
			VSkeleton[i]->Release();
			VSkeleton[i] = nullptr;
		}
	}
	if (true != VSkeleton1.empty())
	{
		for (size_t i = 0; i < VSkeleton1.size(); i++)
		{
			VSkeleton1[i]->Release();
			VSkeleton1[i] = nullptr;
		}
	}
	if (true != VHumanTree1.empty())
	{
		for (size_t i = 0; i < VHumanTree1.size(); i++)
		{
			VHumanTree1[i]->Release();
			VHumanTree1[i] = nullptr;
		}
	}
	if (true != VHumanTree2.empty())
	{
		for (size_t i = 0; i < VHumanTree2.size(); i++)
		{
			VHumanTree2[i]->Release();
			VHumanTree2[i] = nullptr;
		}
	}
	if (true != VHumanTree3.empty())
	{
		for (size_t i = 0; i < VHumanTree3.size(); i++)
		{
			VHumanTree3[i]->Release();
			VHumanTree3[i] = nullptr;
		}
	}
	if (true != VHumanTree4.empty())
	{
		for (size_t i = 0; i < VHumanTree4.size(); i++)
		{
			VHumanTree4[i]->Release();
			VHumanTree4[i] = nullptr;
		}
	}
	if (true != VHumanTree5.empty())
	{
		for (size_t i = 0; i < VHumanTree5.size(); i++)
		{
			VHumanTree5[i]->Release();
			VHumanTree5[i] = nullptr;
		}
	}
	if (true != VCandleHuman.empty())
	{
		for (size_t i = 0; i < VCandleHuman.size(); i++)
		{
			VCandleHuman[i]->Release();
			VCandleHuman[i] = nullptr;
		}
	}
	if (true != VCandleHuman2.empty())
	{
		for (size_t i = 0; i < VCandleHuman2.size(); i++)
		{
			VCandleHuman2[i]->Release();
			VCandleHuman2[i] = nullptr;
		}
	}

	
	
}

void Stage_Lothric::SetAllMonster()
{

	////// Area0
	// 0
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_RaggedRobes>(Enum_UpdateOrder::Monster, "Monster_Hollow_RaggedRobes");
		Monster->SetResponPos({ -3874.0f, 4118.0f, -1151.0f });
		AllMonster.push_back(Monster);
	}

	// 1
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_RaggedRobes>(Enum_UpdateOrder::Monster, "Monster_Hollow_RaggedRobes");
		Monster->SetResponPos({ -5730.0f, 3409.0f, -2575.0f });
		AllMonster.push_back(Monster);
	}

	// 2
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_Unarmed>(Enum_UpdateOrder::Monster, "Monster_Hollow_Unarmed");
		Monster->SetResponPos({ -6684.0f, 3405.0f, -3450.0f });
		//Monster->SetResponRotation({ 0.0f, 90.0f, 0.0f });
		AllMonster.push_back(Monster);
	}

	// 3
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Lantern>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Lantern");
		Monster->SetResponPos({ -6330.0f, 3400.0f, -3088.0f });
		AllMonster.push_back(Monster);
	}

	////// Area1
	// 4
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -8496.0f, 2878.0f, -4483.0f });
		AllMonster.push_back(Monster);
	}

	// 지하실 내부
	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
	//	Monster->SetResponPos({ -9050.0f, 2033.0f, -4071.0f });
	//	//Monster->SetIdleType(Enum_Lothric_IdleType::Sit);
	//	AllMonster.push_back(Monster);
	//}

	////// Area2
	// 5
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Spear>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Spear");
		Monster->SetResponPos({ -10210.0f, 2030.0f, -3207.0f });
		AllMonster.push_back(Monster);
	}

	// 6
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_RaggedRobes>(Enum_UpdateOrder::Monster, "Monster_Hollow_RaggedRobes");
		Monster->SetResponPos({ -11925.0f, 2892.0f, -4067.0f });
		AllMonster.push_back(Monster);
	}

	// 7
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_Unarmed>(Enum_UpdateOrder::Monster, "Monster_Hollow_Unarmed");
		Monster->SetResponPos({ -12531.0f, 2892.0f, -4134.0f });
		AllMonster.push_back(Monster);
	}

	// 8
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Lantern>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Lantern");
		Monster->SetResponPos({ -13050.0f, 2886.0f, -3783.0f });
		AllMonster.push_back(Monster);
	}

	// 9
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -14467.0f, 2893.0f, -4080.0f });
		AllMonster.push_back(Monster);
	}

	// 10
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -15491.0f, 2943.0f, -4392.0f });
		AllMonster.push_back(Monster);
	}

	// 11
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -14397.0f, 2277.0f, -2812.0f });
		AllMonster.push_back(Monster);
	}

	// 12
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Spear>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Spear");
		Monster->SetResponPos({ -16297.0f, 2689.0f, -1427.0f });
		AllMonster.push_back(Monster);
	}

	// 13
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_Hollow_RaggedRobes>(Enum_UpdateOrder::Monster, "Monster_Hollow_RaggedRobes");
		Monster->SetResponPos({ -15816.0f, 2683.0f, -472.0f });
		AllMonster.push_back(Monster);
	}

	// 14
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -17594.0f, 2834.0f, 1350.0f });
		AllMonster.push_back(Monster);
	}

	// 15
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -15476.0f, 2327.0f, 2870.0f });
		AllMonster.push_back(Monster);
	}

	// 16
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -11968.0f, 1924.0f, 3882.0f });
		AllMonster.push_back(Monster);
	}

	// 17
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -10196.0f, 984.0f, 4174.0f });
		AllMonster.push_back(Monster);
	}

	// 18
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -8623.0f, 907.0f, 3707.0f });
		AllMonster.push_back(Monster);
	}

	// 19
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Spear>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Spear");
		Monster->SetResponPos({ -8546.0f, -683.0f, 3904.0f });
		AllMonster.push_back(Monster);
	}

	// 20
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -9154.0f, 542.0f, 5211.0f });
		AllMonster.push_back(Monster);
	}

	// 21
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -7885.0f, -538.0f, 5512.0f });
		AllMonster.push_back(Monster);
	}

	// 22
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -8476.0f, -548.0f, 7715.0f });
		AllMonster.push_back(Monster);
	}

	// 23
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6396.0f, -624.0f, 8055.0f });
		AllMonster.push_back(Monster);
	}

	// 24
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6433.0f, -750.0f, 10232.0f });
		AllMonster.push_back(Monster);
	}

	// 25
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -4026.0f, -1788.0f, 9562.0f });
		AllMonster.push_back(Monster);
	}

	// 테스트
	//AllMonsterOn();
	// 실적용
	AllMonsterOff();
}

void Stage_Lothric::AllMonsterOn()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->SetWorldRotation(AllMonster[i]->GetResponRot());
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->On();
	}
}

void Stage_Lothric::AllMonsterOff()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->SetWorldRotation(AllMonster[i]->GetResponRot());
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->Off();
	}
}

void Stage_Lothric::SetAllEvCol()
{
	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -1300.0f, 5101.0f, -5000.0f });
		EventCollision->SetWorldScale({ 200.0f, 200.0f, 200.0f });

		EventCollision->Event = [=]()
			{
				// AllMonsterOff();
				Area0_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -8167.0f, 2934.0f, -3950.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area1_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -9172.0f, 2039.0f, -3144.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area2_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}
	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -16535.0f, 2836.0f, 691.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area3_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}
}

void Stage_Lothric::EvColUpdate()
{
	for (size_t i = 0; i < AllEvCol.size(); i++)
	{
		if (true == AllEvCol[i]->Collision(Enum_CollisionOrder::Player_Body))
		{
			AllEvCol[i]->Event();
			AllEvCol[i]->Off();
		}
	}
}

void Stage_Lothric::Area0_On()
{
	for (size_t i = 0; i < 4; i++)
	{
		AllMonster[i]->On();
	}

	AllMonster[3]->WakeUp();
}

void Stage_Lothric::Area1_On()
{
	for (size_t i = 4; i < 5; i++)
	{
		AllMonster[i]->On();
		//AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::Area2_On()
{
	for (size_t i = 5; i < 14; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::Area3_On()
{
	for (size_t i = 14; i < 18; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}


void Stage_Lothric::CreateObject()
{
	//화톳불

	//화톳불

	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		VBonfire.push_back(Object);
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -1125, -2489 , 3232 });
		VBonfire.push_back(Object);
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -16547, 3372 , 2144 });
		VBonfire.push_back(Object);
	}



	//사다리
	{
		Ladder1 = CreateActor<Object_Ladder1>(1);
	}
	{
		Ladder2 = CreateActor<Object_Ladder2>(1);
	}
	{
		Ladder3 = CreateActor<Object_Ladder3>(1);
	}
	{
		Ladder4 = CreateActor<Object_Ladder4>(1);
	}
	{
		Ladder5 = CreateActor<Object_Ladder5>(1);
	}
	{
		Ladder6 = CreateActor<Object_Ladder6>(1);
	}


	{
		BossDoor = CreateActor<Object_BossDoor>(1);
	}
	{
		CastleDoor = CreateActor<Object_CastleDoor>(1);
	}
	{
		Desk = CreateActor<Object_Desk>(1);
	}
	/*{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
	}
	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
	}*/

	/*{
		std::shared_ptr<Object_StartDoor> Object = CreateActor<Object_StartDoor>(1);
	}*/

	/*{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
	}*/

	/*{
		std::shared_ptr<Object_HumanTree> Object = CreateActor<Object_HumanTree>(1);
	}*/

	/*{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
	}*/

	//횃불
	//1
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -7286, -550 , 14098 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//2
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6465, -550 , 14515 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//3
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6035, -437 , 9824 });
		Object->Transform.SetWorldRotation({ 0, -90, 0 });
		VTorchlight.push_back(Object);
	}
	//4
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6889, -350 , 9890 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//5
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15436, 2548 , 2582 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
		VTorchlight.push_back(Object);
	}
	//6
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15265, 2548 , 2249 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
		VTorchlight.push_back(Object);
	}
	//7
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -12890, -1940 , 2970 });
		Object->Transform.SetWorldRotation({ 0, -25, 0 });
		VTorchlight.push_back(Object);
	}
	//8
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6050, 193 , 6861 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//9
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -5760, 193 , 7011 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//10
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15440, 2683 , -4280 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//11
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15790, 2683 , -4225 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//12
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15960, 2683 , -4239 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//13
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16320, 2683 , -4208 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//14
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16720, 3110 , 230 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
		VTorchlight.push_back(Object);
	}
	//15
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16280, 3110 , 285 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
		VTorchlight.push_back(Object);
	}
	//16
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -230, -2205 , 4460 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//17
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -654 ,-2205 , 5294 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//18
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1076, -2205 , 6123 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//19
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1509, -2205 , 6969 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//20
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -2758, -2205 , 3187 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//21
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3196, -2205 , 4048 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//22
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3618, -2205 , 4876 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//23
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -4045, -2205 , 5715 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//24
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6979, -252 , 8556 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//25
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6705, -252 , 8015 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//26
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3497, -2236 , 7094 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//27
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -2934, -2236 , 7381 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//28
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -17716, -3039 , 2180 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//29
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15512, 3079 , 1700 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//30
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -17056, 2754 , 2799 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//촛불동상
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6611, 3400 , -3566 });
		VCandleHuman.push_back(Object);
	}

	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7511, 3400 , -3966 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7111, 3470 , -4116 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6961, 3482 , -4016 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6355, 3480 , -4178 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -5805, 3485 , -3878 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -11664, 2887 , -4428 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -11764, 2887 , -4428 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12648, 2890 , -4339 });
		VCandleHuman.push_back(Object);
	}
	//2
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -7092, 3400 , -3759 });
		VCandleHuman2.push_back(Object);
	}

	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5651, 3490 , -3813 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5399, 3480 , -3308 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12379, 2970 , -4687 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12166, 2888 , -4414 });
		VCandleHuman2.push_back(Object);
	}

	//테이블

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 100 , 0 });
		Object->Transform.SetWorldPosition({ -9420, 2873 , -5022 });
		VTable.push_back(Object);
	}

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -8970, 2873 , -5022 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 10 , 0 });
		Object->Transform.SetWorldPosition({ -8320, 2873 , -4772 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -8270, 2873 , -4372 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12981, 1630 , 3222 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -16644, 2324 , 703 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 110 , 0 });
		Object->Transform.SetWorldPosition({ -17144, 2324 , 853 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 40 , 0 });
		Object->Transform.SetWorldPosition({ -16380, 2440 , -3867 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -15830, 2440 , -3817 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -11242, 996 , 5644 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -10892, 996 , 5794 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 50 , 0 });
		Object->Transform.SetWorldPosition({ -11462, 996 , 6044 });
		VTable.push_back(Object);
	}

	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -4208, 4121 , -2223 });
		VHumanTree1.push_back(Object);
	}

	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.SetWorldPosition({ -5862, 3373 , -2474 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -7124, 3400 , -2627 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10304, 3630 , -4057 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -9779, 3625 , -3386 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -75 , 0 });
		Object->Transform.SetWorldPosition({ -11954, 2880 , -3783 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -15964, 3383 , 2464 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -16253, 3392 , 786 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15684, 2685 , -228 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -16702, 2760 , -2225 });
		VHumanTree1.push_back(Object);
	}

	//타입2
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -110 , 0 });
		Object->Transform.SetWorldPosition({ -3863, 4132 , -829 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12805, 2028 , -2796 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 180 , 0 });
		Object->Transform.SetWorldPosition({ -15877, 3390 , 693 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -16953, 3387 , 1146 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -100 , 0 });
		Object->Transform.SetWorldPosition({ -16724, 2761 , -1474 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12679, 2652 , 2944 });
		VHumanTree2.push_back(Object);
	}

	//3
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -5616, 3400 , -2408 });
		VHumanTree3.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10276, 3635 , -4497 });
		VHumanTree3.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -16323, 3383 , 1735 });
		VHumanTree3.push_back(Object);
	}

	//4
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -7280, 3410 , -3220 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -10125, 3628 , -3695 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12936, 2879 , -3303 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -120 , 0 });
		Object->Transform.SetWorldPosition({ -11593, 2229 , 5327 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15570, 3392 , 1287 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12659, 2020 , -2837 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -4312, 4131 , -1138 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6452, 3410 , -2587 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -16699, 2763 , -1721 });
		VHumanTree4.push_back(Object);
	}

	//5

	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -4181, 4123 , -2059 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -3515, 4130 , -744 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -12085, 2893 , -3772 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -11879, 2143 , 5269 });
		VHumanTree5.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1337, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1187, 4950 , -4534 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5299 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5149 });
		Object->Transform.SetWorldRotation({ 0, 120 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -1037, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton1.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -937, 4950 , -4734 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
		VSkeleton1.push_back(Object);
	}
}

void Stage_Lothric::BossBGMUpdate(float _Delta)
{
	if (nullptr == Boss_Object)
	{
		return;
	}

	if (false == BossBGM.IsPlaying())
	{
		return;
	}

	if (false == Boss_Object->IsFlag(Enum_ActorFlag::Death))
	{
		return;
	}

	BossBGMVolume -= _Delta * 0.01f;
	BossBGM.SetVolume(BossBGMVolume);

	if (0.f >= BossBGMVolume)
	{
		BossBGMVolume = 0.f;
		BossBGM.Stop();
	}
}
