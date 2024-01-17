#include "PreCompile.h"
#include "BoneSocketCollision.h"

BoneSocketCollision::BoneSocketCollision() 
{
}

BoneSocketCollision::~BoneSocketCollision() 
{
}

void BoneSocketCollision::Start()
{
	GameEngineCollision::Start();
}

void BoneSocketCollision::Update(float _DeltaTime)
{
	GameEngineCollision::Update(_DeltaTime);

	if (nullptr != pSocket)
	{
		Transform.SetLocalMatrix(*pSocket);
	}
}

void BoneSocketCollision::Release()
{
	GameEngineCollision::Release();
}
