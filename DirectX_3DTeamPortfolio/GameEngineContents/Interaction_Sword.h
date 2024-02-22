#pragma once

// Ό³Έν :
class Interaction_Sword : public GameEngineObjectBase
{
public:
	// constrcuter destructer
	Interaction_Sword();
	~Interaction_Sword();

	// delete Function
	Interaction_Sword(const Interaction_Sword& _Other) = delete;
	Interaction_Sword(Interaction_Sword&& _Other) noexcept = delete;
	Interaction_Sword& operator=(const Interaction_Sword& _Other) = delete;
	Interaction_Sword& operator=(Interaction_Sword&& _Other) noexcept = delete;

	void On() override;
	void Off() override;

	void Init(const std::vector<GameEngineCollision*>& _pCols);
	void Collision(Enum_CollisionOrder _Order, std::function<void (std::vector<class GameEngineCollision*>& _Other)> _CallBack);
	void RecordCollision(class BaseActor* _pActor);
	bool IsContain(class BaseActor* _pActor) const;

	void ResetRecord();
	void Release();

private:
	std::vector<class GameEngineCollision*> Collisions;
	std::set<class BaseActor*> HitRecord;

};

