#include "PreCompile.h"
#include "ContentLevel.h"

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurScene = Scene;
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	CurScene = nullptr;
}

void ContentLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	PhysXLevelInit();
}

void ContentLevel::Update(float _Delta)
{
	RunSimulation(_Delta);
}

void ContentLevel::Release()
{

}