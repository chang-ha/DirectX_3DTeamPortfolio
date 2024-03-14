#pragma once
#include "HitInteraction.h"

// 설명 :
class Boss_HitInteraction : public HitInteraction
{
	friend class Boss_Vordt;
public:
	// constructer destructer
	Boss_HitInteraction();
	~Boss_HitInteraction();

	// delete function
	Boss_HitInteraction(const Boss_HitInteraction& _Ohter) = delete;
	Boss_HitInteraction(Boss_HitInteraction&& _Ohter) noexcept = delete;
	Boss_HitInteraction& operator=(const Boss_HitInteraction& _Other) = delete;
	Boss_HitInteraction& operator=(Boss_HitInteraction&& _Other) noexcept = delete;

protected:

private:
	void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) override; // 충돌 To Body << 쓰지 않으셔도 상관없습니다.
	void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) override; // 충돌 To Shield << 쓰지 않으셔도 상관없습니다. Body와 작동하는 방식이 달라서 분리했습니다.

};

