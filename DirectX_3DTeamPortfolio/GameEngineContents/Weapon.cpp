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
	weapon->SetFBXMesh("WP_A_0221.FBX", "FBXAnimationTexture");
	weapon->Transform.SetLocalScale({ 100, 100, 100 });
	weapon->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
	



}

void Weapon::Update(float _Delta)
{

}

void Weapon::LevelStart(GameEngineLevel* _PrevLevel)
{
}
