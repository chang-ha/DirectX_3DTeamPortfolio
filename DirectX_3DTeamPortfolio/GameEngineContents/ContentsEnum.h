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
	Player,
	Player_Shield,
	Monster,
	MonsterAttack,
	Monster_Shield,
	Detect,
	Dummy,
	Map,
	LadderTop,
	LadderBot,
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
