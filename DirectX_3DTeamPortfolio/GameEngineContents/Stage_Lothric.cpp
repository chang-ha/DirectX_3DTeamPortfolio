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
#include "Object_Box.h"
#include "Object_OakBarrel.h"
#include "Object_Shelf.h"

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
#include "UILocationAlert.h"

// Effect
#include "AllFadeEffect.h"


bool Stage_Lothric::ResLoadingDone = false;
bool Stage_Lothric::ResetLoadingDone = false;
Stage_Lothric::Stage_Lothric()
{
	ResLoadingDone = false;
}

Stage_Lothric::~Stage_Lothric()
{

}

void Stage_Lothric::LevelStart(GameEngineLevel* _PrevLevel)
{
	ResLoading();
	LevelState.ChangeState(Enum_LevelState::Play);
}

void Stage_Lothric::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != BlackScreen)
	{
		BlackScreen->Death();
		BlackScreen = nullptr;
	}

	BossStageState.ChangeState(Enum_BossStageState::Ready);
}

void Stage_Lothric::Start()
{
	IsDebug = false;
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });


	{
		Map_Lothric = CreateActor<WorldMap>(0, "WorldMap");
	}

	StateInit();
}

void Stage_Lothric::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	LevelState.Update(_Delta);
	BossStageState.Update(_Delta);

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

void Stage_Lothric::PlayUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('L', this))
	{
		Player_Object->SetFlag(Enum_ActorFlag::Death, true);
	}
}


//////////////////////////////////////// 몬스터 배치
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
		//Monster->SetResponRotation({ 0.0f,180.0f,0.0f });
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

	///////// Area3
	// 14
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -17034.0f, 2836.0f, 900.0f });
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

	///////// Area4
	// 17
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -10100.0f, 984.0f, 4174.0f });
		AllMonster.push_back(Monster);
	}
	// 18
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -8011.0f, 907.0f, 3547.0f });
		AllMonster.push_back(Monster);
	}

	////////// Area5
	// 19
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Spear>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Spear");
		Monster->SetResponPos({ -8546.0f, -683.0f, 3904.0f });
		AllMonster.push_back(Monster);
	}

	// 20
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_RoundShield");
		Monster->SetResponPos({ -9154.0f, -540.0f, 5211.0f });
		AllMonster.push_back(Monster);
	}

	// 21
	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -7885.0f, -540.0f, 5512.0f });
		AllMonster.push_back(Monster);
	}

	// 22
	{
		std::shared_ptr<Monster_HollowSoldier_Sword> Monster = CreateActor<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster, "Monster_HollowSoldier_Sword");
		Monster->SetResponPos({ -8473.0f, -541.0f, 7471.0f });
		AllMonster.push_back(Monster);
	}

	///////// Area6
	// 23
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6396.0f, -624.0f, 8055.0f });
		Monster->SetIdleType(Enum_Lothric_IdleType::Sit);
		AllMonster.push_back(Monster);
	}
	// 24
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6641.0f, -624.0f, 9742.0f });
		Monster->SetIdleType(Enum_Lothric_IdleType::Sit);
		AllMonster.push_back(Monster);
	}

	// 25
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -4986.0f, -1122.0f, 11500.0f });

		std::vector<float4> Path1
		{
			{ -4528.0f, -1730.0f, 9810.0f },
			{ -6372.0f, -957.0f, 12818.0f },
		};
		Monster->SetPatrolPath(Path1, 0);
		Monster->SetIdleType(Enum_Lothric_IdleType::Patrol);

		AllMonster.push_back(Monster);
	}

	// 26
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -4353.0f, -1792.0f, 9500.0f });

		std::vector<float4> Path1
		{
			{ -3672.0f, -1789.0f, 9842.0f },
			{ -5071.0f, -1792.0f, 9120.0f },
		};
		Monster->SetPatrolPath(Path1, 0);
		Monster->SetIdleType(Enum_Lothric_IdleType::Patrol);

		AllMonster.push_back(Monster);
	}
	// 27
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6556.0f, -960.0f, 13240.0f });
		std::vector<float4> Path1
		{
			{ -8332.0f, -450.0f, 12420.0f },
			{ -4800.0f, -625.0f, 14000.0f },
		};
		Monster->SetPatrolPath(Path1, 0);
		Monster->SetIdleType(Enum_Lothric_IdleType::Patrol);
		AllMonster.push_back(Monster);
	}

	// 28
	{
		std::shared_ptr<Monster_LothricKn> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -4496.0f, -625.0f, 14229.0f });
		std::vector<float4> Path1
		{
			{ -4496.0f, -625.0f, 14229.0f },
			{ -2883.0f, -626.0f, 11003.0f },
		};
		Monster->SetPatrolPath(Path1, 0);
		Monster->SetIdleType(Enum_Lothric_IdleType::Patrol);
		AllMonster.push_back(Monster);
	}

	// 테스트
	//AllMonsterOn();
	// 실제 적용
	AllMonsterOff();
}

void Stage_Lothric::AllMonsterOn()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		//AllMonster[i]->Transform.SetWorldRotation(AllMonster[i]->GetResponRot());
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->On();
	}
}

void Stage_Lothric::AllMonsterOff()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		//AllMonster[i]->Transform.SetWorldRotation(AllMonster[i]->GetResponRot());
		AllMonster[i]->Reset();
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->Off();
	}
}

void Stage_Lothric::SetAllEvCol()
{
	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -1885.0f, 5015.0f, -3987.0f });
		EventCollision->SetWorldScale({ 500.0f, 500.0f, 500.0f });
		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area0_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{// 0-1
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -3868.0f, 4130.0f, -2010.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });
		EventCollision->Event = [=]()
			{
				if (true == AllEvCol[0]->IsUpdate())
				{
					AllMonsterOff();
					Area0_On();
				}

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
	{// 3-1
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -16547.0f, 3370.0f, 2050.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });

		EventCollision->Event = [=]()
			{
				if (true == AllEvCol[4]->IsUpdate())
				{
					AllMonsterOff();
					Area3_On();
				}

				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -10708.0f, 1890.0f, 4230.0f });
		EventCollision->SetWorldScale({ 600.0f, 600.0f, 600.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area4_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -8574.0f, -553.0f, 3194.0f });
		EventCollision->SetWorldScale({ 700.0f, 700.0f, 700.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area5_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}

	{
		std::shared_ptr<EventCol> EventCollision = CreateActor<EventCol>(Enum_UpdateOrder::Player, "EventCollision");
		EventCollision->SetWorldPosition({ -7291.0f, -739.0f, 8076.0f });
		EventCollision->SetWorldScale({ 400.0f, 400.0f, 400.0f });

		EventCollision->Event = [=]()
			{
				AllMonsterOff();
				Area6_On();
				return;
			};

		AllEvCol.push_back(EventCollision);
	}
}

void Stage_Lothric::AllEvColOn()
{
	for (size_t i = 0; i < AllEvCol.size(); i++)
	{
		AllEvCol[i]->On();
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
		AllMonster[i]->WakeUp();
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
	for (size_t i = 14; i < 17; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::Area4_On()
{
	for (size_t i = 17; i < 19; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::Area5_On()
{
	for (size_t i = 19; i < 23; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::Area6_On()
{
	for (size_t i = 23; i < 29; i++)
	{
		AllMonster[i]->On();
		AllMonster[i]->WakeUp();
	}
}

void Stage_Lothric::CreateObject()
{

	//화톳불

	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		Object->SetPlayerRespawnPos({ -3925, 4130 , -2050 });
		VBonfire.push_back(Object);
	}
	//보스방 화톳불
	{
		BossRoom_bonfire = CreateActor<Object_bonfire>(1);
		BossRoom_bonfire->Transform.SetWorldPosition({ -1125, -2489 , 3232 });
		BossRoom_bonfire->SetPlayerRespawnPos({ -1125, -2495 , 3150 });
		BossRoom_bonfire->Off();
		VBonfire.push_back(BossRoom_bonfire);
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -16547, 3372 , 2144 });
		Object->SetPlayerRespawnPos({ -16547, 3380 , 2050 });
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

	//여기부터 보스방 23번까지
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

	//31
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -9502, 2217 , -2678 });
		Object->Transform.SetWorldRotation({ 0, -90, 0 });
		VTorchlight.push_back(Object);
	}
	//32
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -10008, 2217 , -3262 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//33
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -10950, 2419 , -3742 });
		Object->Transform.SetWorldRotation({ 0, 10, 0 });
		VTorchlight.push_back(Object);
	}
	//34
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -11538, 2217 , -3351 });
		Object->Transform.SetWorldRotation({ 0, 0, 0 });
		VTorchlight.push_back(Object);
	}
	//35
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -12234, 2217 , -3290 });
		Object->Transform.SetWorldRotation({ 0, -90, 0 });
		VTorchlight.push_back(Object);
	}

	//37
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -2139, 4979 , -2306 });
		Object->Transform.SetWorldRotation({ 0, -110, 0 });
		VTorchlight.push_back(Object);
	}
	//38
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1651, 5255 , -4073 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//39
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1970, 5255 , -4183 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//40
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -4196, 4229 , -932 });
		Object->Transform.SetWorldRotation({ 0, 140, 0 });
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

	//박스
	//1
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -8419, 2900 , -5200 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VBox.push_back(Object);
	}
	//2
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -8519, 2900 , -5200 });
		Object->Transform.SetWorldRotation({ 0, 60 , 0 });
		VBox.push_back(Object);
	}
	//3
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -8469, 2992 , -5200 });
		Object->Transform.SetWorldRotation({ 0, 60 , 0 });
		VBox.push_back(Object);
	}
	//4
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9524, 2827 , -4081 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VBox.push_back(Object);
	}
	//5
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9524, 2827 , -3970 });
		Object->Transform.SetWorldRotation({ 0, 70 , 0 });
		VBox.push_back(Object);
	}
	//6
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9574, 2827 , -4170 });
		Object->Transform.SetWorldRotation({ 0, 10 , 0 });
		VBox.push_back(Object);
	}
	//7
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9574, 2919 , -4120 });
		Object->Transform.SetWorldRotation({ 0, -40 , 0 });
		VBox.push_back(Object);
	}
	//8
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9524, 2919 , -4015 });
		Object->Transform.SetWorldRotation({ 0, 10 , 0 });
		VBox.push_back(Object);
	}
	//9
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9524, 3010 , -4065 });
		Object->Transform.SetWorldRotation({ 0, 10 , 0 });
		VBox.push_back(Object);
	}
	//10
	{
		std::shared_ptr<Object_Box> Object = CreateActor<Object_Box>(1);
		Object->Transform.SetWorldPosition({ -9374, 2827 , -3690 });
		Object->Transform.SetWorldRotation({ 0, 30 , 0 });
		VBox.push_back(Object);
	}
	//오크통
	//1
	{
		std::shared_ptr<Object_OakBarrel> Object = CreateActor<Object_OakBarrel>(1);
		Object->Transform.SetWorldPosition({ -9578, 2827 , -4278 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VOakBarrel.push_back(Object);
	}
	{
		std::shared_ptr<Object_OakBarrel> Object = CreateActor<Object_OakBarrel>(1);
		Object->Transform.SetWorldPosition({ -9428, 2826 , -3800 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VOakBarrel.push_back(Object);
	}

	//선반
	//1
	{
		std::shared_ptr<Object_Shelf> Object = CreateActor<Object_Shelf>(1);
		Object->Transform.SetWorldPosition({ -9132, 2878 , -5503 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
		VShelf.push_back(Object);
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

	BossBGMVolume -= _Delta * (BEGIN_BOSS_BGM_VOLUME / 15.f);
	BossBGM.SetVolume(BossBGMVolume);

	if (0.f >= BossBGMVolume)
	{
		BossBGMVolume = 0.f;
		BossBGM.Stop();
	}
}

// LevelStart Resources Loading
void Stage_Lothric::ResLoading()
{
	if (true == Stage_Lothric::ResLoadingDone)
	{
		return;
	}

	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		float4 ResponPos = float4(-1100.f, -2500.f, 3000.f);
		float4 ResponRot = float4(0.f, -30.f, 0.f);
		Boss_Object->SetWorldPosition(ResponPos);
		Boss_Object->SetWorldRotation(ResponRot);
		Boss_Object->SetResponPos(ResponPos);
		Boss_Object->SetResponRotation(ResponRot);
	}


	// Light
	if (nullptr == Light)
	{
		Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "mainDirect");
		LightData Data = Light->GetLightData();
		Light->CreateShadowMap();

		Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
		Data.LightColor = float4(1.0f, 1.0f, 0.7f);
		Data.LightPower = 2.0f;
		Data.ForceLightPower = 0.25f;

		Light->Transform.SetLocalPosition({ -12000.0f, 16200.0f, -4260.0f });
		Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


		Light->SetLightData(Data);
		//Light->IsDebugValue = true;
	}

	if (nullptr == BossDoorLight)
	{
		BossDoorLight = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "BossDoorLight");
		BossDoorLight->SetLightType(Enum_LightType::Point);

		LightData Data = BossDoorLight->GetLightData();
		Data.quadraticAttenuation = 0.00006f;
		Data.LightPower = 30.f;
		Data.LightColor = { 2.0f,0.2f,0.2f };
		Data.linearAttenuation = 0.006f;
		Data.quadraticAttenuation = 0.0002f;

		BossDoorLight->SetLightData(Data);
		BossDoorLight->Transform.SetLocalPosition({ -808.f, -1970.0f, 2330.0f });
		//Light->IsDebugValue = true;
	}


	// DepthOfField
	{
		std::shared_ptr<DepthOfField> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<DepthOfField>();
		Effect->Init(GetMainCamera());
	}
	//
	// Fog
	/*{
		std::shared_ptr<FogEffect> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
		Effect->Init(GetMainCamera());
	}*/


	////FXAA

	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<LUTEffect>();

	// Building

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	// Player
	{
		Player_Object = CreateActor<Player>(200, "Player");
		// 볼드 위치
		Player_Object->SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		// 안개 테스트 위치 
		// Player_Object->SetWorldPosition({ -3417.f, -2552.f, 7606.f });
		
		// 테스트 위치
		//Player_Object->SetWorldPosition({ -8011.0f, 907.0f, 3547.0f });
		// 
		//시작 위치
		//Player_Object->SetWorldPosition({ -1400.0f, 4945.0f, -5330.0f });
		Player_Object->SetWorldRotation({ 0.f, 0.f, 0.f });
		//Player_Object->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(Player_Object.get());
	}

	{
		FogWall = CreateActor<Object_FogWall>();
		FogWall->Transform.SetWorldPosition({ -3125, -2100.f, 7070.f });
		FogWall->Transform.SetWorldRotation({ 0.f,152.f });

		FogWall->SetOutFunction([&]()
			{
				Boss_Object->AI_Start();
				Boss_Object->On();
				MainUI->BossUIOn();
				BossBGMStart();
				AllMonsterOff();
				BossStageState.ChangeState(Enum_BossStageState::Fight);
			});
	}

	// 몬스터 셋팅
	SetAllMonster();

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
		if (nullptr == GameEngineSprite::Find("Lothric_Wall.png"))
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
		MainUI->CreateAlertManger();
		MainUI->CreateBossUI(Boss_Object.get());
		MainUI->CreateAndCheckEsteUI(Player_Object.get());
		MainUI->CreateAndCheckPlayerGaugeBar(Player_Object.get());

		UILot = CreateActor<UILocationAlert>(Enum_UpdateOrder::UI);
		UILot->SetCollision(float4(400.0f, 400.0f, 400.0f), float4(-1885.0f, 5015.0f, -3987.0f));
	}

	CreateObject();
	// 이벤트 충돌체 셋팅
	SetAllEvCol();

	Stage_Lothric::ResLoadingDone = true;
}

// Reset Loading
// 리셋 함수들 넣어주세요
void Stage_Lothric::ResetLoading()
{
	// 몬스터 끄고 이벤트 충돌체 켜고
	AllMonsterOff();
	AllEvColOn();
	Player_Object->Reset();

	Boss_Object->Reset();
	BossBGMEnd();

	FogWall->Reset();

	ContentsDebug::NUllCheck(MainUI.get());
	MainUI->AllUIActorReset();
	Stage_Lothric::ResetLoadingDone = true;
}

void Stage_Lothric::BossBGMStart()
{
	BossBGM = GameEngineSound::SoundPlay("1-06 Vordt Of The Boreal Valley.mp3", 100);
	BossBGMVolume = BEGIN_BOSS_BGM_VOLUME;
	BossBGM.SetVolume(BossBGMVolume);
}

void Stage_Lothric::BossBGMEnd()
{
	if (false == BossBGM.IsPlaying())
	{
		return;
	}

	BossBGM.Stop();
}