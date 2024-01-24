#pragma once
#include <GameEngineCore/GameEngineActor.h>
//#include "Player.h"
class BasePlayer : public GameEngineActor
{
public:
	BasePlayer();
	~BasePlayer();

	// delete Function
	BasePlayer(const BasePlayer& _Other) = delete;
	BasePlayer(BasePlayer&& _Other) noexcept = delete;
	BasePlayer& operator=(const BasePlayer& _Other) = delete;
	BasePlayer& operator=(BasePlayer&& _Other) noexcept = delete;


	std::shared_ptr<GameContentsFBXRenderer> GetFBXRenderer()
	{
		return FBXRenderer;
	}
	
	std::shared_ptr<GameContentsFBXRenderer> GetWeapon()
	{
		return Weapon;
	}

	std::shared_ptr<GameEnginePhysXCapsule> GetCapsule()
	{
		return Capsule;
	}
	std::shared_ptr<GameEngineCollision> GetCol()
	{
		return Col;
	}
	
protected:

	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameContentsFBXRenderer> Weapon;
	std::shared_ptr<GameEnginePhysXCapsule> Capsule;
	std::shared_ptr<GameEngineCollision> Col;
	GameEngineState PlayerState;
	EventParameter Mini_Event;
	class Player* this_Player = nullptr;

private:

	

};

