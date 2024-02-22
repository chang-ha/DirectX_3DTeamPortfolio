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
	Monster,
	MonsterAttack,
	Detect,
	Dummy,
	Map,
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
