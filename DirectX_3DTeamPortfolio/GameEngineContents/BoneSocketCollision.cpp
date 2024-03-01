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

	if (nullptr != pSocket 
		&& nullptr != pTransform)
	{
		const float4x4& wMat = pTransform->GetWorldMatrix();
		const float4x4 Mat = (*pSocket)* wMat;
		float4 WScale;
		float4 WRot;
		float4 WPos;
		Mat.Decompose(WScale, WRot, WPos);
		Transform.SetWorldRotation(WRot);
		Transform.SetWorldPosition(WPos);
	}
}

void BoneSocketCollision::Release()
{
	GameEngineCollision::Release();

	pTransform = nullptr;
	pSocket = nullptr;
}
