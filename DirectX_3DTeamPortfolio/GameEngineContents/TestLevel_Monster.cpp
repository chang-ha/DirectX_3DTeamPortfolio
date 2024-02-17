#include "PreCompile.h"
#include "TestLevel_Monster.h"

#include <GameEngineCore/GameEngineGUI.h>

#include "ContentsLight.h"

#include "Monster_LothricKn.h"
#include "Monster_HollowSoldier_RoundShield.h"

void MonsterGUITab::Init()
{
	Start();
}

void InputTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("Wake Object"))
	{
		std::vector<std::shared_ptr<Monster_LothricKn>> Monsters = pParentGUI->GetLevel()->GetObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
		for (std::shared_ptr<Monster_LothricKn>& Mosnter : Monsters)
		{
			Mosnter->WakeUp();
		}
	}
}

void MonsterControlTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == pActor)
	{
		if (ObjNames.empty())
		{
			int Cnt = 0;
			const std::list<std::shared_ptr<GameEngineObject>>& ObjList = _Level->GetObjectGroup(Enum_UpdateOrder::Monster);

			ObjNames.reserve(ObjList.size());
			CObjNames.reserve(ObjList.size());

			for (const std::shared_ptr<GameEngineObject>& Object : ObjList)
			{
				std::string Name = Object->GetName();
				if (false == Name.empty())
				{
					ObjNames.push_back(Name);
					CObjNames.push_back(ObjNames[Cnt].c_str());
					++Cnt;
				}
			}
		}
	}

	if (ImGui::Combo("Monster List", &MonsterNum, &CObjNames[0], static_cast<int>(CObjNames.size())))
	{
		std::vector<std::shared_ptr<BaseMonster>> Monsters = _Level->GetObjectGroupConvert<BaseMonster>(Enum_UpdateOrder::Monster);

		for (const std::shared_ptr<BaseMonster>& Monster : Monsters)
		{
			if (CObjNames[MonsterNum] == Monster->GetName())
			{
				pActor = Monster.get();
				break;
			}
		}
	}

	if (nullptr != pActor)
	{
		if (ImGui::Button("WakeUp"))
		{
			pActor->WakeUp();
		}

		ImGui::Checkbox("Zero Pos", &bFixPos);

		if (bFixPos)
		{
			pActor->GetPhysxCapsulePointer()->SetWorldPosition(float4(0.0f));
		}
	}
}

void MonsterGUI::Start()
{
	CreateTab<InputTab>("Input");
	CreateTab<MonsterControlTab>("Monster Control");
}

void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == CurLevel)
	{
		CurLevel = static_cast<TestLevel_Monster*>(_Level);
	}

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("GUI bar", tab_bar_flags))
	{
		for (std::shared_ptr<MonsterGUITab>& Tab : Tabs)
		{
			if (ImGui::BeginTabItem(Tab->Name.c_str()))
			{
				Tab->OnGUI(_Level, _DeltaTime);
				ImGui::EndTabItem();
			}
		}

		ImGui::EndTabBar();
	}
}




TestLevel_Monster::TestLevel_Monster() 
{
}

TestLevel_Monster::~TestLevel_Monster() 
{
}

void TestLevel_Monster::Start()
{
	ContentLevel::Start();

	// Light
	{
		std::shared_ptr<ContentsLight> Test_Light1 = CreateActor<ContentsLight>(0);
		Test_Light1->SetLightType(Enum_LightType::Directional);
		Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();

		Data.DifLightPower = 3.0f;
		Data.SpcPow = 50.0f;
		Data.AmbientLight = float4(0.4f);
		Data.LightPower = 5.0f;

		Test_Light1->SetLightData(Data);
	}

	// Physx Plane
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	// GUI
	pMonsterGUI = GameEngineGUI::CreateGUIWindow<MonsterGUI>("MonsterGUI");
	pMonsterGUI->Off();

	// CameraSetting
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);
	GetMainCamera()->Transform.SetLocalPosition({0.0f, 0.0f, -200.0f});
}

void TestLevel_Monster::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Monster_LothricKn> LothricKn = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	LothricKn->SetWPosition(float4(100.0f, 0.0f, 0.0f));

	std::shared_ptr<Monster_HollowSoldier_Sword> Hollow = CreateActor<Monster_HollowSoldier_Sword>(static_cast<int>(Enum_UpdateOrder::Monster), "Hollow");
	Hollow->SetWPosition(float4(-200.0f, 0.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 180.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 90.0f, 0.0f));
	Hollow->SetStateIdle1();

	std::shared_ptr<DummyActor> Dummy = CreateActor<DummyActor>(static_cast<int>(Enum_UpdateOrder::Player), "Dummy");
	Dummy->Transform.SetWorldPosition(float4(0.0f, 0.0f, 400.0f));
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_HollowSoldier_RoundShield>(Enum_UpdateOrder::Monster);

	if (nullptr != pMonsterGUI)
	{
		pMonsterGUI->Off();
	}
}