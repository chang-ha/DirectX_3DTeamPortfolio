#include "PreCompile.h"
#include "shield.h"

shield::shield()
{
}

shield::~shield()
{
}

void shield::Start()
{
	Shield = CreateComponent<GameContentsFBXRenderer>();
	Shield->SetFBXMesh("WP_A_2116.FBX", "FBX_Static");
	Shield->Transform.SetLocalScale({ 100, 100, 100 });
	Shield->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });


	{
		Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player_Shield);
		Col->Transform.SetLocalScale({ 100.0f,100.0f });
		Col->Off();
	}

}

void shield::Update(float _Delta)
{
}

void shield::LevelStart(GameEngineLevel* _PrevLevel)
{
}
