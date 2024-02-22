#pragma once
#include "HitInteraction.h"

// Ό³Έν :
class Monster_HitInteraction : public HitInteraction
{
public:
	// constrcuter destructer
	Monster_HitInteraction();
	~Monster_HitInteraction();

	// delete Function
	Monster_HitInteraction(const Monster_HitInteraction& _Other) = delete;
	Monster_HitInteraction(Monster_HitInteraction&& _Other) noexcept = delete;
	Monster_HitInteraction& operator=(const Monster_HitInteraction& _Other) = delete;
	Monster_HitInteraction& operator=(Monster_HitInteraction&& _Other) noexcept = delete;

	void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) override;
	void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) override;

protected:

private:

};

