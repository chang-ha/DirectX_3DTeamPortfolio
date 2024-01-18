#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "BoneSocketCollision.h"


Monster_LothricKn::Monster_LothricKn() 
{
	SetID(Type);
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

	ResourcesLoad();

	FindAndCreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_RightHand);

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