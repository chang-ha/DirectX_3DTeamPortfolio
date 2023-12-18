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
	int a = 0;

	int b = 0;

	{
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		FBXRenderer->SetFBXMesh("AnimMan.FBX", "FBXColor");
		FBXRenderer->RenderBaseInfoValue.BaseColor = float4::WHITE;
	}

	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::Player);
		Col->SetCollisionType(ColType::SPHERE2D);
		Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	GameEngineInput::AddInputObject(this);
}

void Player::Update(float _Delta)
{
	PlayerState.Update(_Delta);
}