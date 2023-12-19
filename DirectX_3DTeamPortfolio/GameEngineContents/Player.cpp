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
		FBXRenderer->SetFBXMesh("Player.FBX", "FBXColor");

		FBXRenderer->CreateFBXAnimation("Run", "Ani001.FBX", { 0.1f, true });

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