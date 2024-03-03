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
};

enum class Enum_CollisionOrder
{
	Player = 1,
	Player_Shield = (1 << 1),
	Monster = (1 << 2),
	MonsterAttack = (1 << 3),
	Monster_Shield = (1 << 4),
	Detect = (1 << 5),
	Dummy = (1 << 6),
	Camera = (1 << 8),
	Big_Camera = (1 << 9),
	Sound = (1 << 10),
	LadderTop = (1 << 11),
	LadderBot = (1 << 12),
	//Map = (1 << 15),
	Map = 2,
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
