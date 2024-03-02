#include "PreCompile.h"
#include "DummyPolyCollision.h"

#include "DS3DummyData.h"
#include "BaseActor.h"

DummyPolyCollision::DummyPolyCollision()
{
}

DummyPolyCollision::~DummyPolyCollision()
{
}

void DummyPolyCollision::Start()
{
	GameEngineCollision::Start();
}

void DummyPolyCollision::Update(float _DeltaTime)
{
	GameEngineCollision::Update(_DeltaTime);

	if (nullptr != pSocket
		&& nullptr != pRendererTransform)
	{
		const float4 WS = Transform.GetWorldScale();
		const float4x4& RendererMat = pRendererTransform->GetWorldMatrix();
		const float4x4 Mat = DPMatrix * (*pSocket) * RendererMat;
		float4 WScale;
		float4 WRot;
		float4 WPos;
		Mat.Decompose(WScale, WRot, WPos);
		Transform.SetWorld(WS, WRot.QuaternionToEulerDeg(), WPos);
	}
}

void DummyPolyCollision::Release()
{
	GameEngineCollision::Release();
	pRendererTransform = nullptr;
	pSocket = nullptr;
}

void DummyPolyCollision::SetDummyPolyMatrix(const SetDPMatrixParameter& _Para)
{
	std::string IDName = _Para.pActor->GetIDName();
	const std::shared_ptr<DS3DummyData>& DPData = DS3DummyData::Find(IDName);
	if (nullptr == DPData)
	{
		MsgBoxAssert("더미폴리를 로드하지 않고 사용할수 없는 기능입니다.");
		return;
	}

	const DummyData* DummyData = DPData->GetDummyData(_Para.ReferenceID, _Para.AttachBoneIndex);
	if (nullptr == DummyData)
	{
		MsgBoxAssert("더미 데이터가 존재하지 않습니다.");
		return;
	}

	switch (_Para.Type)
	{
	case Enum_DP_Matrix_Type::None:
		break;
	case Enum_DP_Matrix_Type::NormalPos:
		DPMatrix = DummyData->Local;
		break;
	case Enum_DP_Matrix_Type::ReversePos:
		DPMatrix = DummyData->Local_ReversePos;
		break;
	case Enum_DP_Matrix_Type::NonePos:
		DPMatrix = DummyData->Local_NotPos;
		break;
	default:
		break;
	}
}