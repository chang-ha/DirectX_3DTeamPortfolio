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
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		FBXRenderer->SetFBXMesh("c0000.FBX", "FBXColor");
		FBXRenderer->Transform.SetLocalScale({50.0f, 50.0f, 50.0f});
		FBXRenderer->Transform.SetLocalRotation({0.0f, 0.0f, -90.0f });

		FBXRenderer->CreateFBXAnimation("Run", "Ani001.FBX", { 0.1f, true });
		FBXRenderer->ChangeAnimation("Run");

		FBXRenderer->RenderBaseInfoValue.BaseColor = float4::WHITE;
	}

	{
		Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	PlayerState.Update(_Delta);
}