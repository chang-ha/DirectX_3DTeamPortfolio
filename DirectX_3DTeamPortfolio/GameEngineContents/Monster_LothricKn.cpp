#include "PreCompile.h"
#include "Monster_LothricKn.h"


Monster_LothricKn::Monster_LothricKn() 
{
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	BaseMonster::Start();

	GameEngineInput::AddInputObject(this);

	SetBoneIndex(Enum_BoneType::B_01_RightHand, 78);
	SetBoneIndex(Enum_BoneType::B_01_LeftHand, 47);

	EventLoad();
	ResourcesLoad();
	CreateFSM();
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);
}


void Monster_LothricKn::Release()
{
	BaseMonster::Release();
}

void Monster_LothricKn::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}