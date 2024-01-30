#include "PreCompile.h"
#include "TestLevel_Monster.h"

#include "GameEngineCore/GameEngineGUI.h"

#include "ContentsLight.h"

#include "Monster_LothricKn.h"
#include "Monster_Hollow_Unarmed.h"
#include "DummyActor.h"

void MonsterGUITab::Init(MonsterGUI* _GUI)
{
	pParentGUI = _GUI;
	Start();
}


void DummyTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == pActor)
	{
		pActor = pParentGUI->GetLevel()->GetDummyActorPointer();
	}

	if (ImGui::Checkbox("Update Box", &IsUpdate))
	{
		pActor->OnOffSwitch();
	}

	float* pActorSpeed = pActor->GetSpeedPointer();
	ImGui::InputFloat("Dummy Move Speed", pActorSpeed, 1.0f, 100.0f, "%.f");
}

void MonsterGUI::Start()
{
	CreateTab<DummyTab>("Dummy");
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
	GameEngineInput::AddInputObject(this);
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

	// DummySetting
	pDummyActor = CreateActor<DummyActor>(static_cast<int>(Enum_UpdateOrder::Monster));
	pDummyActor->Off();

	// CameraSetting
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);
	GetMainCamera()->Transform.SetLocalPosition({0.0f, 0.0f, -200.0f});
}

void TestLevel_Monster::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);

	if (nullptr != pMonsterGUI)
	{
		if (true == GameEngineInput::IsDown(VK_F4, this))
		{
			pMonsterGUI->OnOffSwitch();
		}
	}
}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Monster_LothricKn> LothricKn = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	LothricKn->Transform.SetWorldPosition(float4(100.0f, 0.0f, 0.0f));

	std::shared_ptr<Monster_Hollow_Unarmed> Hollow = CreateActor<Monster_Hollow_Unarmed>(static_cast<int>(Enum_UpdateOrder::Monster), "Hollow");
	Hollow->Transform.SetWorldPosition(float4(100.0f, 0.0f, 0.0f));
	//Hollow->SetStateIdle1();

	if (nullptr != pMonsterGUI)
	{
		pMonsterGUI->On();
	}
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_Hollow_Unarmed>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<DummyActor>(Enum_UpdateOrder::Monster);

	if (nullptr != pMonsterGUI)
	{
		pMonsterGUI->Off();
	}
}


DummyActor* TestLevel_Monster::GetDummyActorPointer() const
{
	if (nullptr == pDummyActor)
	{
		MsgBoxAssert("존재하지 않는 액터를 반환하려 했습니다.");
	}

	return pDummyActor.get();
}