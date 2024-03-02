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
<<<<<<< HEAD
	Player = 1,
	Player_Shield = (1 << 1),
	Monster = (1 << 2),
	MonsterAttack = (1 << 3),
	Monster_Shield = (1 << 4),
	Detect = (1 << 5),
	Dummy = (1 << 6),
	Map = (1 << 7),
	Camera = (1 << 8),
	Sound = (1 << 9),
=======
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
>>>>>>> origin/Feature/MapObject
};

enum class Enum_RenderDepth
{
	Player,
	Monster,
};
