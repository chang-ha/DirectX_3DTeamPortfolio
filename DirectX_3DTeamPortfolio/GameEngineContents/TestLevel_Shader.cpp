#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "FXAAEffect.h"
#include <GameEngineCore/BlurPostEffect.h>
#include "ContentsLight.h"
#include "TestObject_Shader.h"
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "LUTEffect.h"
#include "BloomEffect.h"
#include "ContentsFireRenderer.h"

TestLevel_Shader::TestLevel_Shader()
{
}

TestLevel_Shader::~TestLevel_Shader()
{
}

void TestLevel_Shader::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void TestLevel_Shader::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void TestLevel_Shader::Start()
{
	GameEngineInput::AddInputObject(this);

	ContentLevel::Start();

	// GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, 3000.0f });
	// GetMainCamera()->Transform.AddWorldRotation({ 0.f, 180.f, 0.f });


	

		Test_Light1 = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "Direct");
		Test_Light1->CreateShadowMap();
		Test_Light1->Transform.SetWorldRotation({ 0.0f, 0.0f, 0.0f });

		Test_Light1->Transform.AddLocalPosition({ 0.0f, 0.0f, -1000.0f });

		Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();

		Data.LightPower = 2.0f;
		Data.AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
		Data.SpcPow = 50.0f;

		Test_Light1->SetLightData(Data);
		//Test_Light1->SetShadowRange(float4{ 16384,16384 });
	

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");


	//std::shared_ptr<GameEngineCoreWindow> CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	//if (nullptr != CoreWindow)
	//{
	//	CoreWindow->AddDebugRenderTarget(1, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
	//	CoreWindow->AddDebugRenderTarget(2, "ForwardTarget", GetMainCamera()->GetCameraForwardTarget());
	//	CoreWindow->AddDebugRenderTarget(3, "DeferredLightTarget", GetMainCamera()->GetCameraDeferredLightTarget());
	//	CoreWindow->AddDebugRenderTarget(4, "DeferredTarget", GetMainCamera()->GetCameraDeferredTarget());
	//	CoreWindow->AddDebugRenderTarget(5, "LightTarget", Test_Light1->GetShadowTarget());
	//	//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	//}


	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	//GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	GetMainCamera()->Transform.AddLocalPosition({ 0.0f, 0.0f, -500.0f });
	//GetLevelRenderTarget()->CreateEffect<BloomEffect>();
	//GetLevelRenderTarget()->CreateEffect<LUTEffect>();



	GetCamera(ECAMERAORDER::UI)->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f });
	GetCamera(ECAMERAORDER::UI)->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	GetCamera(ECAMERAORDER::UI)->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	/*HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 100.0f,0.0f,0.0f });


	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 0.0f,0.0f,100.0f });

	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 0.0f,0.0f,0.0f });

	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 0.0f,100.0f,0.0f });

	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 0.0f,-100.0f,0.0f });*/


	/*Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
	Boss_Object->Transform.SetLocalPosition({ 300.f, 0.f, 0.f });*/



	// 맵 오브젝트
	//{
	//	std::shared_ptr<GameEngineActor> actor = CreateActor<GameEngineActor>();


	//	std::shared_ptr<GameContentsFBXRenderer> renderer = actor->CreateComponent<GameContentsFBXRenderer>();

	//	renderer->SetFBXMesh("WorldSky.FBX", "FBX_Static_Alpha",RenderPath::Alpha);
	//	//renderer->RenderBaseInfoValue.TEXCOORDMult = 1.0f;
	//	//renderer->transform.setlocalscale({ 50.f, 50.f, 50.f, 1.0f });

	//	//renderer->renderbaseinfovalue.alphavalue = -10.0f;


	//}Q

		// 컬러 구체
	//{
	//	{
	//		std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
	//		std::shared_ptr<GameEngineRenderer> NewRenderer = Object->CreateComponent<GameEngineRenderer>();
	//		//NewRenderer->RenderBaseInfoValue.IsNormal = 1;
	//		NewRenderer->SetMesh("Sphere");
	//		NewRenderer->SetMaterial("FBX_Static_Color");
	//		//NewRenderer->GetShaderResHelper().SetTexture("DiffuseTexture", "m30_00_sky_04_a.png");
	//		NewRenderer->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	//		NewRenderer->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
	//		NewRenderer->RenderBaseInfoValue.BaseColor = float4::RED;
	//	}
	//}
	//불
	{
		std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
		

		std::shared_ptr<ContentsFireRenderer> Render = Object->CreateComponent<ContentsFireRenderer>();

		Render->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
		//Render = Object->CreateComponent<ContentsFireRenderer>();

		/*Render->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Render->Transform.SetLocalRotation({ 0.0f, 30.0f, 0.0f });
		Render = Object->CreateComponent<ContentsFireRenderer>();

		Render->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
		Render->Transform.SetLocalRotation({ 0.0f, 60.0f, 0.0f });*/
	}

	//SkyRenderer = CreateComponent<GameContentsFBXRenderer>();
	//SkyRenderer->SetFBXMesh("WorldSky.FBX", "FBX_Static");



	//{
	//	Test_Light1 = CreateActor<ContentsLight>(static_cast<int>(Enum_UpdateOrder::Light),"MainLight");
	//	Test_Light1->SetLightType(Enum_LightType::Point);
	//	Test_Light1->IsDebugValue = true;
	//	//Test_Light1->Transform.SetWorldScale(float4(100.f, 100.f, 100.f));
	//	LightData Data = Test_Light1->GetLightData();
	//	//Test_Light1->Transform.SetWorldRotation({ 90.0f, 0.0f, 0.0f });
	//	//Test_Light1->Transform.SetWorldPosition({ 0, 1000.0f, 0.0f });

	//	Data.DifLightPower = 2.0f;
	//	Data.SpcLightPower = 1.0f;
	//	Data.AmbientLight = float4::ONE * 0.1f;
	//	Data.SpcPow = 50.0f;
	//	Data.LightColor = { 1.0f,0.6f,0.0f };

	//	Test_Light1->SetLightData(Data);
	//}



	//{
	//	std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
	//	std::shared_ptr<GameEngineRenderer> NewRenderer = Object->CreateComponent<GameEngineRenderer>();
	//	NewRenderer->SetMesh("Box");
	//	NewRenderer->SetMaterial("FBX_Static_Color");
	//	// NewRenderer->GetShaderResHelper().SetTexture("NormalTexture", "BumpNormal.gif");
	//	NewRenderer->Transform.SetLocalPosition({ 0.0f, -200.0f, 0.0f });
	//	NewRenderer->Transform.SetLocalScale({ 3000.0f, 100.0f, 3000.0f });
	//	NewRenderer->RenderBaseInfoValue.BaseColor = float4(0.2f,0.2f,0.0f,1.0f);
	//}

	//{
	//	std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
	//	std::shared_ptr<class GameEngineSpriteRenderer> HpBar = Object->CreateComponent<GameEngineSpriteRenderer>();
	//	//HpBar->SetCameraOrder(ECAMERAORDER::UI);
	//	HpBar->Transform.SetLocalPosition({ 0.0f, -100 });
	//	//HpBar->Transform.SetWorldScale({ 1000.0f, 1300,1000.0f,1.0f });
	//	//HpBar->SetImageScale({ 100.0f, 100.0f,100.0f });
	//	HpBar->SetBillboardOn();

	//	//GetCamera(ECAMERAORDER::UI)->DebugOn();
	//}

	//{
	//	{
	//		std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
	//		std::shared_ptr<GameEngineRenderer> NewRenderer = Object->CreateComponent<GameEngineRenderer>();
	//		NewRenderer->RenderBaseInfoValue.IsDiffuse = 0;
	//		NewRenderer->SetMesh("Box");
	//		NewRenderer->SetMaterial("FBX_Static");
	//		// NewRenderer->GetShaderResHelper().SetTexture("NormalTexture", "BumpNormal.gif");
	//		NewRenderer->Transform.SetLocalPosition({ 0.0f, -200.0f, 2000.0f });
	//		NewRenderer->Transform.SetLocalScale({ 3000.0f, 100.0f, 3000.0f });
	//		NewRenderer->Transform.SetLocalRotation({ -30.0f, 0.0f, 0.0f });
	//		NewRenderer->RenderBaseInfoValue.BaseColor = float4::RED;
	//	}
	//}

}

void TestLevel_Shader::Update(float _Delta)
{

	float MoveSpeed = 300.0f;

	if (true == GameEngineInput::IsPress('A', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::FORWARD * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::FORWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('S', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::BACKWARD * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::BACKWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('Q', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('E', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
	}


	if (true == GameEngineInput::IsPress('Z', this))
	{
		Test_Light1->Transform.AddLocalRotation(float4::UP * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalRotation(float4::UP * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('C', this))
	{
		Test_Light1->Transform.AddLocalRotation(float4::DOWN * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalRotation(float4::DOWN * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsDown('1', this))
	{
		GameEngineCamera::FreeSpeed = 10000.0f;
	}
	if (true == GameEngineInput::IsDown('3', this))
	{
		GameEngineCamera::FreeSpeed = 200.0f;
	}

	
	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
	}


}

void TestLevel_Shader::Release()
{
}
