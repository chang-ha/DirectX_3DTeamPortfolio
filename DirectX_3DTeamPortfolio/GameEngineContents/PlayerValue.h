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

	float GetHp()
	{
		return CurHp;
	}
	void SetHp(float _Value)
	{
		CurHp = _Value;
	}
	void SetMaxHp(float _Value)
	{
		MaxHp = _Value;
	}
	float GetMaxHp()
	{
		return MaxHp;
	}

	void AddHp(float _Hp)
	{
		CurHp += _Hp;

		if (CurHp >= MaxHp)
		{
			CurHp = MaxHp;
		}
	}
	void SubHp(float _Hp)
	{
		CurHp -= _Hp;

		if (CurHp <= MinHp)
		{
			CurHp = MinHp;
		}
	}

	float GetMp()
	{
		return CurMp;
	}
	void SetMaxMp(float _Value)
	{
		MaxMp = _Value;
	}
	float GetMaxMp()
	{
		return MaxMp;
	}

	void AddMp(float _Mp)
	{
		CurMp += _Mp;

		if (CurMp >= MaxMp)
		{
			CurMp = MaxMp;
		}
	}
	void SubMp(float _Mp)
	{
		CurMp -= _Mp;

		if (CurMp <= MinMp)
		{
			CurMp = MinMp;
		}
	}

	float GetStamina()
	{
		return CurStamina;
	}

	float GetMaxStamina()
	{
		return MaxStamina;
	}

	void AddStamina(float _Stamina)
	{
		CurStamina += _Stamina;

		if (CurStamina >= MaxStamina)
		{
			CurStamina = MaxStamina;
		}
	}
	void SubStamina(float _Stamina)
	{
		CurStamina -= _Stamina;

		if (CurStamina <= MinStamina)
		{
			CurStamina = MinStamina;
		}
	}


private:
	int Level = 1;

	float CurHp = 400;
	float MaxHp = 400;
	float MinHp = 0;

	float CurMp = 200;
	float MaxMp = 200;
	float MinMp = 0;

	float CurStamina = 300;
	float MaxStamina = 300;
	float MinStamina = 0;

	int Exp = 0;
	int MaxExp = 100;
};

