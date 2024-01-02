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
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
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