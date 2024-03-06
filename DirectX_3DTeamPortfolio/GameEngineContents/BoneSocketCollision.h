#pragma once

// Ό³Έν :
class BoneSocketCollision : public GameEngineCollision
{
public:
	// constrcuter destructer
	BoneSocketCollision();
	~BoneSocketCollision();

	// delete Function
	BoneSocketCollision(const BoneSocketCollision& _Other) = delete;
	BoneSocketCollision(BoneSocketCollision&& _Other) noexcept = delete;
	BoneSocketCollision& operator=(const BoneSocketCollision& _Other) = delete;
	BoneSocketCollision& operator=(BoneSocketCollision&& _Other) noexcept = delete;

	inline void SetBoneIndex(int _Index) { BoneIndex = _Index; }
	inline int GetBoneIndex() const { return BoneIndex; }
	inline void SetSocket(float4x4* _Socket) { pSocket = _Socket; }
	inline void SetRendererTransformPointer(GameEngineTransform* _pTransform) { pTransform = _pTransform; }
	void SetAttachedMatrix(const float4& _S, const float4& _R, const float4& _T);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Release() override;

private:
	int BoneIndex = -1;
	float4x4* pSocket = nullptr;
	float4x4 LocalMatrix = float4x4::Iden;
	GameEngineTransform* pTransform = nullptr;

};

