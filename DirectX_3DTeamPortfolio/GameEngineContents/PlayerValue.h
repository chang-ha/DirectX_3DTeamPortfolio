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

		if (CurHp <= 0.0f)
		{
			CurHp = 0.0f;
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

		if (CurMp <= 0.0f)
		{
			CurMp = 0.0f;
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

		if (CurStamina <= 0.0f)
		{
			CurStamina = 0.0f;
		}
	}


private:
	int Level = 1;

	float CurHp = 400.f;
	float CurMp = 200.f;
	float CurStamina = 300.f;


	float MaxHp = 400.f;
	float MaxMp = 200.f;
	float MaxStamina = 300.f;

	int Exp = 0;
	int MaxExp = 100;
};

