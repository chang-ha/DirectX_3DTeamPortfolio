#pragma once
#include "Player.h"
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayerValue : public GameEngineActor
{
	friend Player;
private:
	static PlayerValue MainPlayerValue;
public:
	static PlayerValue* GetValue()
	{
		return &MainPlayerValue;
	}

	// constructer destructer
	PlayerValue();
	~PlayerValue();

	// delete Function
	PlayerValue(const PlayerValue& _Other) = delete;
	PlayerValue(PlayerValue&& _Other) noexcept = delete;
	PlayerValue& operator = (const PlayerValue& _Other) = delete;
	PlayerValue& operator = (PlayerValue&& _Other) noexcept = delete;

	int GetHp()
	{
		return MainHp;
	}

	int GetMaxHp()
	{
		return MaxHp;
	}

	void AddHp(int _Hp)
	{
		MainHp += _Hp;

		if (MainHp >= MaxHp)
		{
			MainHp = MaxHp;
		}
	}

	void SubHp(int _Hp)
	{
		MainHp -= _Hp;

		if (MainHp <= MinHp)
		{
			MainHp = MinHp;
		}
	}

private:
	int Level = 1;

	int MainHp = 100;
	int MaxHp = 100;
	int MinHp = 0;

	int MainMp = 100;
	int MaxMp = 100;
	int MinMp = 0;

	int MainStamina = 100;
	int MaxStamina = 100;
	int MinStamina = 0;

	int Exp = 0;
	int MaxExp = 100;
};

