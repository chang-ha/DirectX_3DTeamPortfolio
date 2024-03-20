#pragma once

enum class Enum_UpdateOrder
{
	Player,
	Monster,
	Component,
	Light,
	UI,
};

enum class Enum_RenderOrder
{
	Play,
	Monster,
	Effect,

	UI = 600, //UI Start
	UI_BackBar,
	UI_BackGauge,
	UI_StatGauge,
	UI_BackTexture,
	UI_FontTexture,
	UI_Font = 690, 
	UI_Loading = 699, //UI End
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
	Camera = (1 << 15),
	Big_Camera = (1 << 9),
	Sound = (1 << 10),
	LadderTop = (1 << 11),
	LadderBot = (1 << 12),
	Player = (1 << 13),
	Player_Body = (1 << 14),
	Monster_Body = (1 << 8),
	Monster_Lantern = (1 << 16),
	LabberMiddle = (1 << 17),
	Player_Arround = (1 << 18),
	Parring_Arround = (1 << 19),
	Fog_Wall = (1 << 20),
	EventCol = (1 << 21),
	Monster_FindLantern = (1 << 22),
	Bonfire = (1 < 23),
	Fog_Wall_Out = (1 << 24)
	Trigger = (1 < 24),
};