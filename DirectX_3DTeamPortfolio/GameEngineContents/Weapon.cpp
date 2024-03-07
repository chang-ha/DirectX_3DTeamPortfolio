#include "PreCompile.h"
#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

void Weapon::Start()
{
	
		
	weapon = CreateComponent<GameContentsFBXRenderer>();
	weapon->SetFBXMesh("WP_A_0221.FBX", "FBX_Static");
	weapon->Transform.SetLocalScale({ 100, 100, 100 });
	weapon->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	

	//{
	//	Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player_Attack);
	//	Col->Transform.SetLocalScale({ 50.0f,50.0f });
	//	Col->Transform.SetLocalPosition({ 50.0f,-100.0f });
	//	//Col->Off(); 
	//}

}

void Weapon::Update(float _Delta)
{

}

void Weapon::LevelStart(GameEngineLevel* _PrevLevel)
{
}
