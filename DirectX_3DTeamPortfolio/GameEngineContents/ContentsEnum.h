#pragma once

enum class Enum_UpdateOrder
{
	Player,
	Monster,
	Component,
	Light,
};

enum class Enum_RenderOrder
{
	Play,
	Monster,
	Effect,
};

enum class Enum_CollisionOrder
{
	Null = 0,
	Map = (1 << 0),
	Player_Shield = (1 << 1),
	Player_Attack = (1 << 2),
	Monster = (1 << 3),
	MonsterAttack = (1 << 4),
	Monster_Shield = (1 << 5),
	Detect = (1 << 6),
	Dummy = (1 << 7),
	Camera = (1 << 8),
	Big_Camera = (1 << 9),
	Sound = (1 << 10),
	LadderTop = (1 << 11),
	LadderBot = (1 << 12),
	Player = (1 << 13),
	Monster_Body = (1 << 14),
	Monster_Lantern = (1 << 15),
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
