#include "PreCompile.h"
#include "Boss_Vordt.h"

void Boss_Vordt::SoundEventInit()
{
	//// Howling
	MainRenderer->SetFrameEvent("Howling", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006502.wav", BoneWorldPos(0));
		});

	//// Walk_Front
	MainRenderer->SetFrameEvent("Walk_Front", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	//// Walk_Right
	MainRenderer->SetFrameEvent("Walk_Right", 89, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Rush_Front
	MainRenderer->SetFrameEvent("Rush_Front", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Combo1_Step1
	MainRenderer->SetFrameEvent("Combo1_Step1", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	//// Combo1_Step3
	MainRenderer->SetFrameEvent("Combo1_Step3", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	//// Rush_Attack
	MainRenderer->SetFrameEvent("Rush_Attack", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	////// Hit_Down_004
	MainRenderer->SetFrameEvent("Hit_Down_004", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	////// Hit_Down_005
	MainRenderer->SetFrameEvent("Hit_Down_005", 73, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	////// Thrust
	MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	////// Sweep_001
	MainRenderer->SetFrameEvent("Sweep_001", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	////// Rush_Hit_Turn
	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	////// Rush_Hit_Turn_Rush
	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	////// Breath
	//MainRenderer->SetFrameEvent("Breath", 2, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 15, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 37, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 39, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 54, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 59, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 62, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 78, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224006510.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 82, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("s000613115.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 154, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("s000613115.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 158, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("s000613115.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 172, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 193, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 214, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 228, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 229, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 236, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 266, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 272, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Breath", 324, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Combo2_Step1
	//MainRenderer->SetFrameEvent("Combo2_Step2", 5, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 14, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224006000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 24, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 26, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 29, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 51, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 70, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 74, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Combo2_Step2", 85, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	////// Turn_Left
	//MainRenderer->SetFrameEvent("Turn_Left", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 16, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 17, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 20, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 24, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left", 30, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Turn_Right
	//MainRenderer->SetFrameEvent("Turn_Right", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 12, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 16, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 21, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 24, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 30, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right", 30, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201b.wav", BoneWorldPos(0));
	//	});

	////// Turn_Left_Twice
	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 12, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 17, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 17, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 20, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 24, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 30, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 37, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 44, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 44, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Left_Twice", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	////// Turn_Right_Twice
	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 12, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 17, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 20, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 28, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 37, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 42, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 46, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Turn_Right_Twice", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	////// Jump_Back
	//MainRenderer->SetFrameEvent("Jump_Back", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 5, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 16, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 16, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 28, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 29, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 30, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 33, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Back", 39, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	////// Jump_Left
	//MainRenderer->SetFrameEvent("Jump_Left", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 18, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 25, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 26, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 35, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 47, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Left", 52, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	////// Jump_Right
	//MainRenderer->SetFrameEvent("Jump_Right", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 9, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 18, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 25, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 27, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 28, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 33, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 35, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 42, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Jump_Right", 51, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Hit_001
	//MainRenderer->SetFrameEvent("Hit_001", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224009000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 6, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 28, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_001", 34, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Hit_002
	//MainRenderer->SetFrameEvent("Hit_002", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224009000b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 6, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 10, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_002", 26, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	////// Hit_003_Right
	//MainRenderer->SetFrameEvent("Hit_003_Right", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224009000c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 6, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 9, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 29, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Right", 39, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	////// Hit_003_Left
	//MainRenderer->SetFrameEvent("Hit_003_Left", 1, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224009000c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 6, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 9, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 23, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 29, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_003_Left", 39, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	////// Hit_004_Groggy
	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 0, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("Groggy.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 12, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 52, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 56, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 57, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 57, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224004001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 58, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 99, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 107, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_004_Groggy", 116, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Hit_Groggy
	//MainRenderer->SetFrameEvent("Hit_Groggy", 3, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 26, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 27, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 58, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 81, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224009000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 88, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008002.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 91, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 95, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 102, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 111, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 113, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 124, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 136, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 138, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 163, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Hit_Groggy", 179, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
	//	});

	////// Death
	//MainRenderer->SetFrameEvent("Death", 0, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 4, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 7, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 8, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008003.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 49, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224004001.wav", BoneWorldPos(0));
	//	});

	//// Death_Groggy
	//MainRenderer->SetFrameEvent("Death_Groggy", 2, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 5, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 11, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 16, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224008003.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 32, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 55, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 60, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224004001.wav", BoneWorldPos(0));
	//	});

	//MainRenderer->SetFrameEvent("Death_Groggy", 61, [&](GameContentsFBXRenderer* _Renderer)
	//	{
	//		GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
	//	});

}

// 타켓과 나의 각도 구함
// 내 현재 방향과 해당 각도를 외적해서 회전할 방향을 결정
// 각도가 어느정도 적어지면 회전 X
// 회전 속도는 Event를 사용해서 조절

////////////////////////// Move & Others

void Boss_Vordt::Howling_Start()
{
	MainRenderer->ChangeAnimation("Howling", true);
}

void Boss_Vordt::Howling_Update(float _Delta)
{
	if (134 <= MainRenderer->GetCurAnimationFrame())
	{
		MainState.ChangeState(Enum_BossState::Walk_Front);
	}
}

void Boss_Vordt::Howling_End()
{

}	

void Boss_Vordt::Idle_Start()
{
	MainRenderer->ChangeAnimation("Idle", true);
}

void Boss_Vordt::Idle_Update(float _Delta)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
	}
	
	if (0.3f > MainState.GetStateTime())
	{
		return;
	}
	// MainState.ChangeState(Enum_BossState::Walk_Front);
}

void Boss_Vordt::Idle_End()
{

}

void Boss_Vordt::Walk_Front_Start()
{
	// MainRenderer->ChangeAnimation("Walk_Left");
	MainRenderer->ChangeAnimation("Walk_Front", true);
}

void Boss_Vordt::Walk_Front_Update(float _Delta)
{
	//if (0 <= TargetAngle)
	//{
	//	MainRenderer->ChangeAnimation("Walk_Right");
	//}
	//else
	//{
	//	MainRenderer->ChangeAnimation("Walk_Left");
	//}
}

void Boss_Vordt::Walk_Front_End()
{

}

void Boss_Vordt::Walk_Right_Start()
{
	MainRenderer->ChangeAnimation("Walk_Right", true);
}

void Boss_Vordt::Walk_Right_Update(float _Delta)
{

}

void Boss_Vordt::Walk_Right_End()
{

}

void Boss_Vordt::Walk_Left_Start()
{
	MainRenderer->ChangeAnimation("Walk_Left", true);
}

void Boss_Vordt::Walk_Left_Update(float _Delta)
{
	
}

void Boss_Vordt::Walk_Left_End()
{

}

void Boss_Vordt::Rush_Front_Start()
{
	MainRenderer->ChangeAnimation("Rush_Front", true);
}

void Boss_Vordt::Rush_Front_Update(float _Delta)
{
	if (21 <= MainRenderer->GetCurAnimationFrame() /*&& true == MainRenderer->IsLoop*/)
	{
		MainRenderer->ChangeAnimation("Rush_Front", true);
	}
}

void Boss_Vordt::Rush_Front_End()
{

}

void Boss_Vordt::Jump_Back_Start()
{
	// 플레이어 위치에 따라 조정
	MainRenderer->ChangeAnimation("Jump_Back", true);
}

void Boss_Vordt::Jump_Back_Update(float _Delta)
{
	if (15 <= MainRenderer->GetCurAnimationFrame() &&
		33 >= MainRenderer->GetCurAnimationFrame())
	{
		SetRotSpeed(180.f);
	}
	else if (45 <= MainRenderer->GetCurAnimationFrame() &&
		52 >= MainRenderer->GetCurAnimationFrame())
	{
		MainRenderer->ChangeAnimation("Jump_Back", true);
	}
	else
	{
		SetRotSpeed(0.f);
	}
}

void Boss_Vordt::Jump_Back_End()
{

}

void Boss_Vordt::Jump_Right_Start()
{
	MainRenderer->ChangeAnimation("Jump_Right");
}

void Boss_Vordt::Jump_Right_Update(float _Delta)
{

}

void Boss_Vordt::Jump_Right_End()
{

}

void Boss_Vordt::Jump_Left_Start()
{
	MainRenderer->ChangeAnimation("Jump_Left");
}

void Boss_Vordt::Jump_Left_Update(float _Delta)
{
	
}

void Boss_Vordt::Jump_Left_End()
{

}

void Boss_Vordt::Turn_Right_Start()
{
	MainRenderer->ChangeAnimation("Turn_Right", true);
}

void Boss_Vordt::Turn_Right_Update(float _Delta)
{

}

void Boss_Vordt::Turn_Right_End()
{

}

void Boss_Vordt::Turn_Left_Start()
{
	MainRenderer->ChangeAnimation("Turn_Left", true);
}

void Boss_Vordt::Turn_Left_Update(float _Delta)
{

}

void Boss_Vordt::Turn_Left_End()
{

}

void Boss_Vordt::Turn_Right_Twice_Start()
{
	MainRenderer->ChangeAnimation("Turn_Right_Twice", true);

}

void Boss_Vordt::Turn_Right_Twice_Update(float _Delta)
{

}

void Boss_Vordt::Turn_Right_Twice_End()
{

}

void Boss_Vordt::Turn_Left_Twice_Start()
{
	MainRenderer->ChangeAnimation("Turn_Left_Twice", true);
}

void Boss_Vordt::Turn_Left_Twice_Update(float _Delta)
{
	
}

void Boss_Vordt::Turn_Left_Twice_End()
{

}

void Boss_Vordt::Hitten_Start()
{
	// 그로기 상태에 따라 다름
	// MainRenderer->ChangeAnimation("Hit_001", true);
	// MainRenderer->ChangeAnimation("Hit_002");
	// MainRenderer->ChangeAnimation("Hit_003_Left");
	// MainRenderer->ChangeAnimation("Hit_003_Right");
	MainRenderer->ChangeAnimation("Hit_004_Groggy", true);
}

void Boss_Vordt::Hitten_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_End()
{

}

void Boss_Vordt::Groggy_Start()
{
	MainRenderer->ChangeAnimation("Hit_Groggy");
}

void Boss_Vordt::Groggy_Update(float _Delta)
{
	
}

void Boss_Vordt::Groggy_End()
{

}

void Boss_Vordt::Death_Start()
{
	// MainRenderer->ChangeAnimation("Death", true);
	// 그로기에서 죽으면 Death_Groggy
	MainRenderer->ChangeAnimation("Death_Groggy", true);
}

void Boss_Vordt::Death_Update(float _Delta)
{

}

void Boss_Vordt::Death_End()
{

}

////////////////////////// Attack

void Boss_Vordt::Breath_Start()
{
	MainRenderer->ChangeAnimation("Breath", true);
}

void Boss_Vordt::Breath_Update(float _Delta)
{

}

void Boss_Vordt::Breath_End()
{

}

void Boss_Vordt::Combo1_Start()
{
	MainRenderer->ChangeAnimation("Combo1_Step3", true);
}

void Boss_Vordt::Combo1_Update(float _Delta)
{

}

void Boss_Vordt::Combo1_End()
{

}

void Boss_Vordt::Combo2_Start()
{
	MainRenderer->ChangeAnimation("Combo2_Step2", true);
}

void Boss_Vordt::Combo2_Update(float _Delta)
{

}

void Boss_Vordt::Combo2_End()
{

}

void Boss_Vordt::Sweap_Twice_Right_Start()
{
	MainRenderer->ChangeAnimation("Sweep&Sweep_Right", true);
}

void Boss_Vordt::Sweap_Twice_Right_Update(float _Delta)
{

}

void Boss_Vordt::Sweap_Twice_Right_End()
{

}

void Boss_Vordt::Sweap_Twice_Left_Start()
{
	MainRenderer->ChangeAnimation("Sweep&Sweep_Left", true);
}

void Boss_Vordt::Sweap_Twice_Left_Update(float _Delta)
{
	
}

void Boss_Vordt::Sweap_Twice_Left_End()
{

}

void Boss_Vordt::Hit_Down_001_Front_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_001_Front", true);
}

void Boss_Vordt::Hit_Down_001_Front_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_001_Front_End()
{

}

void Boss_Vordt::Hit_Down_001_Right_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_001_Right", true);
}

void Boss_Vordt::Hit_Down_001_Right_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_001_Right_End()
{

}

void Boss_Vordt::Hit_Down_001_Left_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_001_Left", true);
}

void Boss_Vordt::Hit_Down_001_Left_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_001_Left_End()
{

}

void Boss_Vordt::Hit_Down_004_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_004", true);
}

void Boss_Vordt::Hit_Down_004_Update(float _Delta)
{
	// Capsule->AddWorldRotation({0.f, 50.f * _Delta, 0.f, 0.f});
}

void Boss_Vordt::Hit_Down_004_End()
{

}

void Boss_Vordt::Hit_Down_005_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_005", true);
}

void Boss_Vordt::Hit_Down_005_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_005_End()
{

}

void Boss_Vordt::Hit_Down_006_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_006", true);
}

void Boss_Vordt::Hit_Down_006_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_006_End()
{

}

void Boss_Vordt::Thrust_Start()
{
	MainRenderer->ChangeAnimation("Thrust", true);
}

void Boss_Vordt::Thrust_Update(float _Delta)
{

}

void Boss_Vordt::Thrust_End()
{

}

// Sweep_002 is faster than Sweep_001
void Boss_Vordt::Sweep_001_Start()
{
	MainRenderer->ChangeAnimation("Sweep_001", true);
}

void Boss_Vordt::Sweep_001_Update(float _Delta)
{

}

void Boss_Vordt::Sweep_001_End()
{

}

void Boss_Vordt::Sweep_002_Start()
{
	MainRenderer->ChangeAnimation("Sweep_002", true);
}

void Boss_Vordt::Sweep_002_Update(float _Delta)
{

}

void Boss_Vordt::Sweep_002_End()
{

}

// Rush_Attack_002 is faster than Rush_Attack_001
void Boss_Vordt::Rush_Attack_001_Start()
{
	MainRenderer->ChangeAnimation("Rush_Attack", true);

}

void Boss_Vordt::Rush_Attack_001_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_001_End()	
{

}

void Boss_Vordt::Rush_Attack_002_Start()
{
	MainRenderer->ChangeAnimation("Rush_Attack_002", true);
}

void Boss_Vordt::Rush_Attack_002_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_002_End()
{

}

void Boss_Vordt::Rush_Turn_Start()
{
	MainRenderer->ChangeAnimation("Rush&Turn", true);
}

void Boss_Vordt::Rush_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Start()
{
	MainRenderer->ChangeAnimation("Rush&Hit&Turn", true);
}

void Boss_Vordt::Rush_Hit_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_Start()
{
	MainRenderer->ChangeAnimation("Rush&Hit&Turn&Rush", true);
	MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::RealTimeDir);
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_End()
{

}