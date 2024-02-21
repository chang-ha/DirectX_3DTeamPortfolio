#pragma once
#include "BoneSocketCollision.h"

// Ό³Έν :
class SwordCollision : public BoneSocketCollision
{
public:
	// constrcuter destructer
	SwordCollision();
	~SwordCollision();

	// delete Function
	SwordCollision(const SwordCollision& _Other) = delete;
	SwordCollision(SwordCollision&& _Other) noexcept = delete;
	SwordCollision& operator=(const SwordCollision& _Other) = delete;
	SwordCollision& operator=(SwordCollision&& _Other) noexcept = delete;

	void HitDone();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::set<class BaseActor*> HitRecord;
	std::function<void()> Collision;

};

