#include "PreCompile.h"
#include "CommonMonster.h"

CommonMonster::CommonMonster() 
{
}

CommonMonster::~CommonMonster() 
{
}

void CommonMonster::Start()
{
	MainRenderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
	//MainRenderer->SetMesh("Sphere");
	//MainRenderer->SetMaterial("FBXStaticColor");
	MainRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	MainRenderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void CommonMonster::Release()
{
	MainRenderer = nullptr;
}

