#pragma once
#include "HitInteraction.h"


class Player_HitInteraction : public HitInteraction
{
public:

	Player_HitInteraction();
	~Player_HitInteraction();

	// delete Function
	Player_HitInteraction(const Player_HitInteraction& _Other) = delete;
	Player_HitInteraction(Player_HitInteraction&& _Other) noexcept = delete;
	Player_HitInteraction& operator=(const Player_HitInteraction& _Other) = delete;
	Player_HitInteraction& operator=(Player_HitInteraction&& _Other) noexcept = delete;

	void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) override;
	void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) override;

protected:

private:
};

