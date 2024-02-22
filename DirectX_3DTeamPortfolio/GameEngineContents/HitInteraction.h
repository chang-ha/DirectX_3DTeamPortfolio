#pragma once

// Ό³Έν :
class HitInteraction : public GameEngineObjectBase
{
public:
	// constrcuter destructer
	HitInteraction();
	~HitInteraction();

	// delete Function
	HitInteraction(const HitInteraction& _Other) = delete;
	HitInteraction(HitInteraction&& _Other) noexcept = delete;
	HitInteraction& operator=(const HitInteraction& _Other) = delete;
	HitInteraction& operator=(HitInteraction&& _Other) noexcept = delete;

	void On() override;
	void Off() override;

	void Init(class BaseActor* _pParent, GameEngineCollision* _pCol);
	virtual void CollisionToBody(Enum_CollisionOrder _Order) = 0;
	virtual void CollisionToShield(Enum_CollisionOrder _Order) = 0;

	void RecordCollision(class BaseActor* _pActor);
	bool IsContain(class BaseActor* _pActor) const;

	void ResetRecord();
	void Release();

protected:
	void ValidityCheck(std::string_view _MSG = "");

protected:
	class GameEngineCollision* pCollision = nullptr;
	class BaseActor* pParent = nullptr;

private:
	std::set<class BaseActor*> HitRecord;

};

