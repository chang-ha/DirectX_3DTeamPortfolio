#include "PreCompile.h"
#include "Boss_Vordt.h"

void Boss_Vordt::SoundEventInit()
{
	// Idle
	MainRenderer->SetFrameEvent("Idle", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Idle", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Idle", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	// Howling
	MainRenderer->SetFrameEvent("Howling", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006502.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 52, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008005.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 116, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 120, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 127, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Howling", 133, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	// Walk_Front

	MainRenderer->SetFrameEvent("Walk_Front", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Front", 88, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	// Walk_Left
	MainRenderer->SetFrameEvent("Walk_Left", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 86, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 89, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	// Walk_Right
	MainRenderer->SetFrameEvent("Walk_Right", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 86, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 89, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 89, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	// Rush_Front
	MainRenderer->SetFrameEvent("Rush_Front", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Front", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Front", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Front", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Front", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Front", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	// Combo1_Step1
	MainRenderer->SetFrameEvent("Combo1_Step1", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 44, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 67, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step1", 74, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	// Combo1_Step2
	MainRenderer->SetFrameEvent("Combo1_Step2", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 68, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 69, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step2", 94, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	// Combo1_Step3
	MainRenderer->SetFrameEvent("Combo1_Step3", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 48, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 84, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 104, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Combo1_Step3", 118, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	// Rush_Attack
	MainRenderer->SetFrameEvent("Rush_Attack", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 42, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 64, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 65, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 86, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 87, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 91, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224004001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 105, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 115, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 117, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack", 115, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Hit_Down_001_Front
	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 64, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 71, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 87, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 117, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 119, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 154, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 161, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 174, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Front", 192, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Hit_Down_001_Right
	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 42, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 49, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 74, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 79, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Right", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	//// Hit_Down_001_Left
	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 34, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 38, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 42, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 75, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_001_Left", 102, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Hit_Down_004
	MainRenderer->SetFrameEvent("Hit_Down_004", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 69, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_004", 104, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	//// Hit_Down_005
	MainRenderer->SetFrameEvent("Hit_Down_005", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 33, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 44, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 64, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 73, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 73, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Hit_Down_005", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Thrust
	MainRenderer->SetFrameEvent("Thrust", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 51, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 55, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 70, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 74, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Thrust", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Sweep_001
	MainRenderer->SetFrameEvent("Sweep_001", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006501.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 49, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 63, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 96, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 102, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 110, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 120, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep_001", 127, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	//// Sweep&Sweep_Right
	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 43, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 59, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 67, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 74, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 79, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 82, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 91, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 104, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 124, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 131, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 134, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 143, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	//// Sweep&Sweep_Left
	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 43, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 51, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 72, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006010b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 79, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 82, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 88, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 91, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008004.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 103, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 131, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 134, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 157, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	//// Rush_Attack_002
	MainRenderer->SetFrameEvent("Rush_Attack_002", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 45, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 50, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 55, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 60, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224004001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 65, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 86, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush_Attack_002", 96, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	//// Rush_Hit_Turn
	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 33, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 52, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	//// Rush_Hit_Turn_Rush
	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001201.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 41, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 63, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 75, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 81, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 83, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224006500.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 94, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 103, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 111, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 121, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 126, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005000.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 131, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224008001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 139, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 152, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001c.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 154, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224005001b.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 156, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224003001.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 170, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001d.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 182, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c224001001.wav", BoneWorldPos(0));
		});

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
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		// MainState.ChangeState(Enum_BossState::Walk_Front);
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
	MainRenderer->ChangeAnimation("Hit_001", true);
	// MainRenderer->ChangeAnimation("Hit_002");
	// MainRenderer->ChangeAnimation("Hit_003_Left");
	// MainRenderer->ChangeAnimation("Hit_003_Right");
	// MainRenderer->ChangeAnimation("Hit_004_Groggy");
}

void Boss_Vordt::Hitten_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_End()
{

}

void Boss_Vordt::Death_Start()
{
	MainRenderer->ChangeAnimation("Death", true);
	// 그로기에서 죽으면 Death_Groggy
	// MainRenderer->ChangeAnimation("Death_Groggy");
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
	MainRenderer->ChangeAnimation("Combo2_Step1", true);
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