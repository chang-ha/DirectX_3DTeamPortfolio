#include "PreCompile.h"
#include "SwordCollision.h"

SwordCollision::SwordCollision() 
{
}

SwordCollision::~SwordCollision() 
{
}


void SwordCollision::Start()
{
	BoneSocketCollision::Start();
}

void SwordCollision::Update(float _Delta)
{
	BoneSocketCollision::Update(_Delta);
}

void SwordCollision::Release()
{
	BoneSocketCollision::Release();
}

void SwordCollision::HitDone()
{
	HitRecord.clear();
}