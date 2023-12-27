#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
// #include "GameEngineCore/GameEngineFBXRenderer.h"

Player::Player() 
{	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		std::shared_ptr<GameEngineRenderer> NewRenderer = CreateComponent<GameEngineRenderer>();

		NewRenderer->SetMesh("Sphere");
		NewRenderer->SetMaterial("FBXColor");
		NewRenderer->Transform.SetLocalScale({ 500.0f, 500.0f, 500.0f });
		NewRenderer->RenderBaseInfoValue.BaseColor = float4::RED;

	}

	//{
	//	FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("c0000.FBX", "FBXColor"); // Bone 136
	//	FBXRenderer->Transform.SetLocalScale({50.0f, 50.0f, 50.0f});
	//	FBXRenderer->Transform.SetLocalRotation({0.0f, 0.0f, -90.0f });

	//	FBXRenderer->CreateFBXAnimation("Run", "Ani001.FBX", { 0.1f, true });
	//	FBXRenderer->ChangeAnimation("Run");

	//	FBXRenderer->RenderBaseInfoValue.BaseColor = float4::WHITE;
	//}

	//{
	//	FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("AnimMan.FBX", "FBXColor"); // Bone 68
	//	FBXRenderer->Transform.SetLocalPosition({ 200.0f,  });

	//	FBXRenderer->CreateFBXAnimation("Run", "ALS_N_Run_F.FBX", { 0.1f, true });
	//	FBXRenderer->ChangeAnimation("Run");

	//	FBXRenderer->RenderBaseInfoValue.BaseColor = float4::WHITE;
	//}

	//{
	//	Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player);
	//	Col->SetCollisionType(ColType::SPHERE2D);
	//	Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	//}

	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	PlayerState.Update(_Delta);
}