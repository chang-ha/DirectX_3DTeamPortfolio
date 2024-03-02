#pragma once

// 더미 콜리전 타입
enum class Enum_DP_Matrix_Type
{
	None,
	NormalPos,
	ReversePos,
	NonePos,
};

class SetDPMatrixParameter
{
public:
	SetDPMatrixParameter() {}
	SetDPMatrixParameter(class BaseActor* _pActor, int _ReferenceID, int _AttachBoneIndex, Enum_DP_Matrix_Type _Type)
		: pActor(_pActor), ReferenceID(_ReferenceID), AttachBoneIndex(_AttachBoneIndex), Type(_Type)
	{
		if (nullptr == pActor)
		{
			MsgBoxAssert("부모가 존재하지 않습니다.");
			return;
		}
	}

	class BaseActor* pActor = nullptr;
	int ReferenceID = -1;
	int AttachBoneIndex = -1; 
	Enum_DP_Matrix_Type Type = Enum_DP_Matrix_Type::None;
};

// 설명 :
class DummyPolyCollision : public GameEngineCollision
{
public:
	// constrcuter destructer
	DummyPolyCollision();
	~DummyPolyCollision();

	// delete Function
	DummyPolyCollision(const DummyPolyCollision& _Other) = delete;
	DummyPolyCollision(DummyPolyCollision&& _Other) noexcept = delete;
	DummyPolyCollision& operator=(const DummyPolyCollision& _Other) = delete;
	DummyPolyCollision& operator=(DummyPolyCollision&& _Other) noexcept = delete;

	void SetDummyPolyMatrix(const SetDPMatrixParameter& _Para);
	void SetRendererTransformPointer(GameEngineTransform* _pTransform) { pRendererTransform = _pTransform; }
	void SetSocket(float4x4* _Socket) 
	{
		pSocket = _Socket; 
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Release() override;

private:
	int BoneIndex = -1;
	float4x4* pSocket = nullptr;
	float4x4 DPMatrix;
	GameEngineTransform* pRendererTransform = nullptr;
	Enum_DP_Matrix_Type Type = Enum_DP_Matrix_Type::None;

};

