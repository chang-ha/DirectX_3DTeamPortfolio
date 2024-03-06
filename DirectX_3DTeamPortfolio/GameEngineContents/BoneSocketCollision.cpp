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
		const float4x4& RendererMat = pTransform->GetWorldMatrix();
		const float4x4 Mat = LocalMatrix * (*pSocket)* RendererMat;
		float4 S;
		float4 Q;
		float4 T;
		Mat.Decompose(S, Q, T);

		const float4 WS = Transform.GetWorldScale();
		float4 WRot = Q.QuaternionToEulerDeg();
		Transform.SetWorld(WS, WRot, T);
	}
}

void BoneSocketCollision::Release()
{
	GameEngineCollision::Release();

	pTransform = nullptr;
	pSocket = nullptr;
}

void BoneSocketCollision::SetAttachedMatrix(const float4& _S, const float4& _R /*= float4::ZERONULL*/, const float4& _T /*= float4::ZERO*/)
{
	Transform.SetWorldScale(_S);
	float4 S = float4::ONE;
	float4 R = _R;
	R.W = 0.0f;
	float4 Q = R.EulerDegToQuaternion();
	float4 T = _T;
	LocalMatrix.Compose(S, Q, T);
}