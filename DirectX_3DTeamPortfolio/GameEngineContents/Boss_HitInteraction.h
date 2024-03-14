#pragma once
#include "HitInteraction.h"

// ���� :
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
	void CollisionToBody(Enum_CollisionOrder _Order, int _iStiffness = 0) override; // �浹 To Body << ���� �����ŵ� ��������ϴ�.
	void CollisionToShield(Enum_CollisionOrder _Order, int _iStiffness = 0) override; // �浹 To Shield << ���� �����ŵ� ��������ϴ�. Body�� �۵��ϴ� ����� �޶� �и��߽��ϴ�.

};

