#include "PreCompile.h"
#include "BaseMonster.h"


BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	BaseActor::Start();
}

void BaseMonster::Update(float _Delta)
{
	BaseActor::Update(_Delta);
}

void BaseMonster::Release()
{
	BaseActor::Release();
}