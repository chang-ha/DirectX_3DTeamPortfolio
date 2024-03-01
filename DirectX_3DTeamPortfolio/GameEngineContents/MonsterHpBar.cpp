#include "PreCompile.h"
#include "MonsterHpBar.h"

MonsterHpBar::MonsterHpBar()
{
}

MonsterHpBar::~MonsterHpBar()
{
}

#define ImageXScale 300.0f
#define BackBarYScale 11.0f

void MonsterHpBar::Start()
{
	Monster_HpBackBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_HpBackBar->SetSprite("BossBar.Png");
	Monster_HpBackBar->SetImageScale({ ImageXScale, BackBarYScale });


}

void MonsterHpBar::Update(float _Delta)
{

}

void MonsterHpBar::OffStart()
{

}
void MonsterHpBar::OffUpdate(float _Delta)
{

}
void MonsterHpBar::AppearStart()
{

}
void MonsterHpBar::AppearUpdate(float _Delta)
{

}
void MonsterHpBar::AddStart()
{

}
void MonsterHpBar::AddUpdate(float _Delta)
{

}

void MonsterHpBar::Release()
{
	Death();
}