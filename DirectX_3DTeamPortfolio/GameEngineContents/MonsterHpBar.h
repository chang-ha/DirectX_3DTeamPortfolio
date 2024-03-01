#pragma once

// Ό³Έν :
class MonsterHpBar
{
public:
	// constructer destructer
	MonsterHpBar();
	~MonsterHpBar();

	// delete Function
	MonsterHpBar(const MonsterHpBar& _Other) = delete;
	MonsterHpBar(MonsterHpBar&& _Other) noexcept = delete;
	MonsterHpBar& operator = (const MonsterHpBar& _Other) = delete;
	MonsterHpBar& operator = (MonsterHpBar&& _Other) noexcept = delete;

protected:

private:

};

