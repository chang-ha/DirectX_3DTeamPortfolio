#pragma once
#include "BaseActor.h"
class Weapon : public BaseActor
{
public:
	Weapon();
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;
	std::shared_ptr<GameContentsFBXRenderer> Getweapon()
	{
		return weapon;
	}
	
protected:

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;


private:
	std::shared_ptr<GameContentsFBXRenderer> weapon;
	std::shared_ptr<GameEngineCollision> Col;


};

