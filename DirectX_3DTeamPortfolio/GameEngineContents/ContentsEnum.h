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
	Player = 0,
	Player_Shield = (1 << 0),
	Monster,
	MonsterAttack,
	Monster_Shield,
	Detect,
	Dummy, 
	Map,
	Camera = (1 << 8),
	Camera_02 = (1 << 9),
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
