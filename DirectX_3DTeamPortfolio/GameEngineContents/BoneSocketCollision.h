#pragma once

enum class Enum_B_S_Collision_Type
{
	None,
	Body,
	Weapon,
	Shield,
};

// ���� :
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Release() override;

private:
	int BoneIndex = -1;
	float4x4* pSocket = nullptr;
	GameEngineTransform* pTransform = nullptr;

};

