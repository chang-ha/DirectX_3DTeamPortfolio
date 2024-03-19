#include "PreCompile.h"
#include "Boss_Vordt.h"
#include "BoneSocketCollision.h"

#define JUMP_COOLDOWN 2.f
#define NORMAL_ATTACK_COOLDOWN 15.f
#define COMBO_COOLDOWN1 40.f
#define COMBO_COOLDOWN2 50.f
#define BOSS_ATT 7

void Boss_Vordt::FrameEventInit()
{
	//////// Sound
	{
		//// Howling
		MainRenderer->SetFrameEvent("Howling", 29, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224006502.wav", Transform.GetWorldPosition());
			});

		//// Walk_Front
		MainRenderer->SetFrameEvent("Walk_Front", 37, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
			});

		//// Walk_Right
		MainRenderer->SetFrameEvent("Walk_Right", 89, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
			});

		//// Rush_Front
		MainRenderer->SetFrameEvent("Rush_Front", 21, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
			});

		//// Combo1_Step1
		MainRenderer->SetFrameEvent("Combo1_Step1", 29, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224006001.wav", Transform.GetWorldPosition());
			});

		//// Combo1_Step3
		MainRenderer->SetFrameEvent("Combo1_Step3", 58, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224006500.wav", Transform.GetWorldPosition());
			});

		//// Rush_Attack
		MainRenderer->SetFrameEvent("Rush_Attack", 27, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001c.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Rush_Attack", 54, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001.wav", Transform.GetWorldPosition());
			});

		////// Hit_Down_004
		MainRenderer->SetFrameEvent("Hit_Down_004", 21, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224005001.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Hit_Down_004", 80, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
			});

		////// Hit_Down_005
		MainRenderer->SetFrameEvent("Hit_Down_005", 73, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224008004.wav", Transform.GetWorldPosition());
			});

		////// Thrust
		MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224006000.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Thrust", 26, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224003001.wav", Transform.GetWorldPosition());
			});

		////// Sweep_001
		MainRenderer->SetFrameEvent("Sweep_001", 46, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224008001.wav", Transform.GetWorldPosition());
			});

		////// Rush_Hit_Turn
		MainRenderer->SetFrameEvent("Rush&Hit&Turn", 30, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
			});

		////// Rush_Hit_Turn_Rush
		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 27, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224003001.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 81, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224003001.wav", Transform.GetWorldPosition());
			});

		////// Breath
		//MainRenderer->SetFrameEvent("Breath", 2, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005001.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 15, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005001b.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 37, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005001c.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 39, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224008001.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 54, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224003001.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 59, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224003001.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 62, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001001.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 78, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224006510.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 82, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("s000613115.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 154, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("s000613115.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 158, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("s000613115.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 172, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005000.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 193, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 214, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005000b.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 228, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001001c.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 229, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001201.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 236, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 266, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224008000.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 272, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224005001d.wav", Transform.GetWorldPosition());
		//	});

		//MainRenderer->SetFrameEvent("Breath", 324, [&](GameContentsFBXRenderer* _Renderer)
		//	{
		//		GameEngineSound::Sound3DPlay("c224001001.wav", Transform.GetWorldPosition());
		//	});

		////// Turn_Right
		MainRenderer->SetFrameEvent("Turn_Right", 30, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001.wav", Transform.GetWorldPosition());
			});

		////// Turn_Left_Twice
		MainRenderer->SetFrameEvent("Turn_Left_Twice", 17, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Turn_Left_Twice", 44, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001c.wav", Transform.GetWorldPosition());
			});

		////// Turn_Right_Twice
		MainRenderer->SetFrameEvent("Turn_Right_Twice", 10, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Turn_Right_Twice", 55, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001d.wav", Transform.GetWorldPosition());
			});

		////// Jump_Back
		MainRenderer->SetFrameEvent("Jump_Back", 16, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
			});

		////// Jump_Left
		MainRenderer->SetFrameEvent("Jump_Left", 32, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001.wav", Transform.GetWorldPosition());
			});

		////// Hit_004_Groggy
		MainRenderer->SetFrameEvent("Hit_004_Groggy", 4, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224008002.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Hit_004_Groggy", 57, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224004001.wav", Transform.GetWorldPosition());
			});

		////// Hit_Groggy
		MainRenderer->SetFrameEvent("Hit_Groggy", 81, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224009000.wav", Transform.GetWorldPosition());
			});

		////// Death
		MainRenderer->SetFrameEvent("Death", 0, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224001001b.wav", Transform.GetWorldPosition());
			});

		MainRenderer->SetFrameEvent("Death", 55, [&](GameContentsFBXRenderer* _Renderer)
			{
				GameEngineSound::Sound3DPlay("c224004001.wav", Transform.GetWorldPosition());
			});
	}

	//////// Collision
	{
		MainRenderer->SetFrameEvent("Hit_Down_001_Right", 36, [&](GameContentsFBXRenderer* _Renderer)
			{
				mAttackCollision.BodyCollision->On();
				mAttackCollision.HeadCollision->On();
				mAttackCollision.WeaponCollision->On();
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Right", 39, [&](GameContentsFBXRenderer* _Renderer)
			{
				mAttackCollision.BodyCollision->Off();
				mAttackCollision.HeadCollision->Off();
				mAttackCollision.WeaponCollision->Off();
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Left", 37, [&](GameContentsFBXRenderer* _Renderer)
			{
				mAttackCollision.BodyCollision->On();
				mAttackCollision.HeadCollision->On();
				mAttackCollision.WeaponCollision->On();
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Left", 40, [&](GameContentsFBXRenderer* _Renderer)
			{
				mAttackCollision.BodyCollision->Off();
				mAttackCollision.HeadCollision->Off();
				mAttackCollision.WeaponCollision->Off();
			});

		MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 26, [&](GameContentsFBXRenderer* _Renderer)
			{
				Stat.SetAtt(BOSS_ATT * 3);
				mAttackCollision.BodyCollision->On();
				mAttackCollision.WeaponCollision->On();
			});

		MainRenderer->SetFrameEvent("Sweep&Sweep_Right", 36, [&](GameContentsFBXRenderer* _Renderer)
			{
				Stat.SetAtt(BOSS_ATT * 5);
				mAttackCollision.BodyCollision->Off();
				mAttackCollision.WeaponCollision->Off();
				mAttackCollision.ResetRecord();
			});

		MainRenderer->SetFrameEvent("Sweep&Sweep_Left", 35, [&](GameContentsFBXRenderer* _Renderer)
			{
				mAttackCollision.ResetRecord();
			});
	}

	//////// Pattern
	{
		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 52, [&](GameContentsFBXRenderer* _Renderer)
			{
				std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = MainRenderer->GetCurAnimation();
				AniInfo->SetStartDir(Capsule->GetDir());
				MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::StartDir);
			});

		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 133, [&](GameContentsFBXRenderer* _Renderer)
			{
				std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = MainRenderer->GetCurAnimation();
				AniInfo->SetStartDir(Capsule->GetDir() + 180.f);
				MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::StartDir);
			});

		MainRenderer->SetFrameEvent("Hit_004_Groggy", 55, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME * 2.f);
			});

		MainRenderer->SetFrameEvent("Hit_004_Groggy", 105, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetAnimationChangeEvent("Hit_004_Groggy", [&]()
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetFrameEvent("Combo1_Step1", 36, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME * 1.5f);
			});

		MainRenderer->SetFrameEvent("Combo1_Step1", 75, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetAnimationChangeEvent("Combo1_Step1", [&]()
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Front", 46, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME / 1.5f);
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Front", 67, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Front", 74, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME * 1.5f);
			});

		MainRenderer->SetFrameEvent("Hit_Down_001_Front", 81, [&](GameContentsFBXRenderer* _Renderer)
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});

		MainRenderer->SetAnimationChangeEvent("Hit_Down_001_Front", [&]()
			{
				MainRenderer->ChangeCurAnimationSpeed(ONE_FRAME_DTIME);
			});
	}
}

void Boss_Vordt::StateInit()
{
	// State
	{
		// Move & Others
		CreateStateParameter Howling;
		Howling.Start = std::bind(&Boss_Vordt::Howling_Start, this);
		Howling.Stay = std::bind(&Boss_Vordt::Howling_Update, this, std::placeholders::_1);
		Howling.End = std::bind(&Boss_Vordt::Howling_End, this);

		mJumpTableManager.AddJumpTable("Howling", 143, 155, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Howling", 143, 155, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Howling", 143, 155, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Howling", 144, 155, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Idle;
		Idle.Start = std::bind(&Boss_Vordt::Idle_Start, this);
		Idle.Stay = std::bind(&Boss_Vordt::Idle_Update, this, std::placeholders::_1);
		Idle.End = std::bind(&Boss_Vordt::Idle_End, this);

		mJumpTableManager.AddJumpTable("Idle", 0, 120, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Idle", 0, 120, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Idle", 0, 120, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Walk_Front;
		Walk_Front.Start = std::bind(&Boss_Vordt::Walk_Front_Start, this);
		Walk_Front.Stay = std::bind(&Boss_Vordt::Walk_Front_Update, this, std::placeholders::_1);
		Walk_Front.End = std::bind(&Boss_Vordt::Walk_Front_End, this);

		mJumpTableManager.AddJumpTable("Walk_Front", 0, 108, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Walk_Front", 0, 108, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Walk_Front", 0, 108, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Walk_Right;
		Walk_Right.Start = std::bind(&Boss_Vordt::Walk_Right_Start, this);
		Walk_Right.Stay = std::bind(&Boss_Vordt::Walk_Right_Update, this, std::placeholders::_1);
		Walk_Right.End = std::bind(&Boss_Vordt::Walk_Right_End, this);

		mJumpTableManager.AddJumpTable("Walk_Right", 0, 108, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Walk_Right", 0, 108, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Walk_Right", 0, 108, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Walk_Left;
		Walk_Left.Start = std::bind(&Boss_Vordt::Walk_Left_Start, this);
		Walk_Left.Stay = std::bind(&Boss_Vordt::Walk_Left_Update, this, std::placeholders::_1);
		Walk_Left.End = std::bind(&Boss_Vordt::Walk_Left_End, this);

		mJumpTableManager.AddJumpTable("Walk_Left", 0, 108, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Walk_Left", 0, 108, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Walk_Left", 0, 108, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Front;
		Rush_Front.Start = std::bind(&Boss_Vordt::Rush_Front_Start, this);
		Rush_Front.Stay = std::bind(&Boss_Vordt::Rush_Front_Update, this, std::placeholders::_1);
		Rush_Front.End = std::bind(&Boss_Vordt::Rush_Front_End, this);

		mJumpTableManager.AddJumpTable("Rush_Front", 0, 22, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush_Front", 0, 22, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush_Front", 0, 22, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Jump_Back;
		Jump_Back.Start = std::bind(&Boss_Vordt::Jump_Back_Start, this);
		Jump_Back.Stay = std::bind(&Boss_Vordt::Jump_Back_Update, this, std::placeholders::_1);
		Jump_Back.End = std::bind(&Boss_Vordt::Jump_Back_End, this);

		mJumpTableManager.AddJumpTable("Jump_Back", 38, 56, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Jump_Back", 38, 56, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Jump_Back", 39, 56, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Jump_Back", 38, 56, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Jump_Right;
		Jump_Right.Start = std::bind(&Boss_Vordt::Jump_Right_Start, this);
		Jump_Right.Stay = std::bind(&Boss_Vordt::Jump_Right_Update, this, std::placeholders::_1);
		Jump_Right.End = std::bind(&Boss_Vordt::Jump_Right_End, this);

		mJumpTableManager.AddJumpTable("Jump_Right", 38, 56, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Jump_Right", 39, 56, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Jump_Right", 38, 56, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Jump_Left;
		Jump_Left.Start = std::bind(&Boss_Vordt::Jump_Left_Start, this);
		Jump_Left.Stay = std::bind(&Boss_Vordt::Jump_Left_Update, this, std::placeholders::_1);
		Jump_Left.End = std::bind(&Boss_Vordt::Jump_Left_End, this);

		mJumpTableManager.AddJumpTable("Jump_Left", 38, 56, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Jump_Left", 39, 56, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Jump_Left", 38, 56, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Turn_Right;
		Turn_Right.Start = std::bind(&Boss_Vordt::Turn_Right_Start, this);
		Turn_Right.Stay = std::bind(&Boss_Vordt::Turn_Right_Update, this, std::placeholders::_1);
		Turn_Right.End = std::bind(&Boss_Vordt::Turn_Right_End, this);

		mJumpTableManager.AddJumpTable("Turn_Right", 21, 40, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Turn_Right", 21, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Turn_Right", 22, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Turn_Right", 21, 40, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Turn_Left;
		Turn_Left.Start = std::bind(&Boss_Vordt::Turn_Left_Start, this);
		Turn_Left.Stay = std::bind(&Boss_Vordt::Turn_Left_Update, this, std::placeholders::_1);
		Turn_Left.End = std::bind(&Boss_Vordt::Turn_Left_End, this);

		mJumpTableManager.AddJumpTable("Turn_Left", 21, 40, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Turn_Left", 21, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Turn_Left", 22, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Turn_Left", 21, 40, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Turn_Right_Twice;
		Turn_Right_Twice.Start = std::bind(&Boss_Vordt::Turn_Right_Twice_Start, this);
		Turn_Right_Twice.Stay = std::bind(&Boss_Vordt::Turn_Right_Twice_Update, this, std::placeholders::_1);
		Turn_Right_Twice.End = std::bind(&Boss_Vordt::Turn_Right_Twice_End, this);

		mJumpTableManager.AddJumpTable("Turn_Right_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Turn_Right_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Turn_Right_Twice", 50, 65, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Turn_Right_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Turn_Left_Twice;
		Turn_Left_Twice.Start = std::bind(&Boss_Vordt::Turn_Left_Twice_Start, this);
		Turn_Left_Twice.Stay = std::bind(&Boss_Vordt::Turn_Left_Twice_Update, this, std::placeholders::_1);
		Turn_Left_Twice.End = std::bind(&Boss_Vordt::Turn_Left_Twice_End, this);

		mJumpTableManager.AddJumpTable("Turn_Left_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Turn_Left_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Turn_Left_Twice", 50, 65, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Turn_Left_Twice", 49, 65, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hitten_Front;
		Hitten_Front.Start = std::bind(&Boss_Vordt::Hitten_Front_Start, this);
		Hitten_Front.Stay = std::bind(&Boss_Vordt::Hitten_Front_Update, this, std::placeholders::_1);
		Hitten_Front.End = std::bind(&Boss_Vordt::Hitten_Front_End, this);

		mJumpTableManager.AddJumpTable("Hit_001", 38, 40, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_001", 38, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_001", 39, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_001", 38, 40, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hitten_Back;
		Hitten_Back.Start = std::bind(&Boss_Vordt::Hitten_Back_Start, this);
		Hitten_Back.Stay = std::bind(&Boss_Vordt::Hitten_Back_Update, this, std::placeholders::_1);
		Hitten_Back.End = std::bind(&Boss_Vordt::Hitten_Back_End, this);

		mJumpTableManager.AddJumpTable("Hit_002", 38, 40, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_002", 38, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_002", 39, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_002", 38, 40, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hitten_Right;
		Hitten_Right.Start = std::bind(&Boss_Vordt::Hitten_Right_Start, this);
		Hitten_Right.Stay = std::bind(&Boss_Vordt::Hitten_Right_Update, this, std::placeholders::_1);
		Hitten_Right.End = std::bind(&Boss_Vordt::Hitten_Right_End, this);

		mJumpTableManager.AddJumpTable("Hit_003_Right", 38, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_003_Right", 39, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_003_Right", 38, 40, std::bind(&Boss_Vordt::AI_Dodge, this));
		mJumpTableManager.AddJumpTable("Hit_003_Right", 38, 40, std::bind(&Boss_Vordt::AI_Combo, this));

		CreateStateParameter Hitten_Left;
		Hitten_Left.Start = std::bind(&Boss_Vordt::Hitten_Left_Start, this);
		Hitten_Left.Stay = std::bind(&Boss_Vordt::Hitten_Left_Update, this, std::placeholders::_1);
		Hitten_Left.End = std::bind(&Boss_Vordt::Hitten_Left_End, this);

		mJumpTableManager.AddJumpTable("Hit_003_Left", 38, 40, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_003_Left", 38, 40, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_003_Left", 39, 40, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_003_Left", 38, 40, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hitten_Groggy;
		Hitten_Groggy.Start = std::bind(&Boss_Vordt::Hitten_Groggy_Start, this);
		Hitten_Groggy.Stay = std::bind(&Boss_Vordt::Hitten_Groggy_Update, this, std::placeholders::_1);
		Hitten_Groggy.End = std::bind(&Boss_Vordt::Hitten_Groggy_End, this);

		mJumpTableManager.AddJumpTable("Hit_004_Groggy", 114, 120, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_004_Groggy", 114, 120, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_004_Groggy", 115, 120, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_004_Groggy", 114, 120, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Groggy;
		Groggy.Start = std::bind(&Boss_Vordt::Groggy_Start, this);
		Groggy.Stay = std::bind(&Boss_Vordt::Groggy_Update, this, std::placeholders::_1);
		Groggy.End = std::bind(&Boss_Vordt::Groggy_End, this);

		mJumpTableManager.AddJumpTable("Hit_Groggy", 180, 190, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Groggy", 180, 190, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Groggy", 180, 190, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Death;
		Death.Start = std::bind(&Boss_Vordt::Death_Start, this);
		Death.Stay = std::bind(&Boss_Vordt::Death_Update, this, std::placeholders::_1);
		Death.End = std::bind(&Boss_Vordt::Death_End, this);

		CreateStateParameter Death_Groggy;
		Death_Groggy.Start = std::bind(&Boss_Vordt::Death_Groggy_Start, this);
		Death_Groggy.Stay = std::bind(&Boss_Vordt::Death_Groggy_Update, this, std::placeholders::_1);
		Death_Groggy.End = std::bind(&Boss_Vordt::Death_Groggy_End, this);

		// mJumpTableManager.AddJumpTable("Death", 114, 120, std::bind(&Boss_Vordt::Distance, this));
		// mJumpTableManager.AddJumpTable("Death_Groggy", 89, 105, std::bind(&Boss_Vordt::Distance, this));

		// Attack
		CreateStateParameter Breath;
		Breath.Start = std::bind(&Boss_Vordt::Breath_Start, this);
		Breath.Stay = std::bind(&Boss_Vordt::Breath_Update, this, std::placeholders::_1);
		Breath.End = std::bind(&Boss_Vordt::Breath_End, this);

		CreateStateParameter Combo1_Step1;
		Combo1_Step1.Start = std::bind(&Boss_Vordt::Combo1_Step1_Start, this);
		Combo1_Step1.Stay = std::bind(&Boss_Vordt::Combo1_Step1_Update, this, std::placeholders::_1);
		Combo1_Step1.End = std::bind(&Boss_Vordt::Combo1_Step1_End, this);

		mJumpTableManager.AddJumpTable("Combo1_Step1", 55, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Combo1_Step1", 79, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Combo1_Step1", 79, 90, std::bind(&Boss_Vordt::AI_Dodge, this));
		mJumpTableManager.AddJumpTable("Combo1_Step1", 80, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));

		CreateStateParameter Combo1_Step2;
		Combo1_Step2.Start = std::bind(&Boss_Vordt::Combo1_Step2_Start, this);
		Combo1_Step2.Stay = std::bind(&Boss_Vordt::Combo1_Step2_Update, this, std::placeholders::_1);
		Combo1_Step2.End = std::bind(&Boss_Vordt::Combo1_Step2_End, this);

		mJumpTableManager.AddJumpTable("Combo1_Step2", 39, 100, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Combo1_Step2", 75, 100, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Combo1_Step2", 75, 100, std::bind(&Boss_Vordt::AI_Dodge, this));
		mJumpTableManager.AddJumpTable("Combo1_Step2", 76, 100, std::bind(&Boss_Vordt::AI_MoveMent, this));

		CreateStateParameter Combo1_Step3;
		Combo1_Step3.Start = std::bind(&Boss_Vordt::Combo1_Step3_Start, this);
		Combo1_Step3.Stay = std::bind(&Boss_Vordt::Combo1_Step3_Update, this, std::placeholders::_1);
		Combo1_Step3.End = std::bind(&Boss_Vordt::Combo1_Step3_End, this);

		mJumpTableManager.AddJumpTable("Combo1_Step3", 126, 130, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Combo1_Step3", 126, 130, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Combo1_Step3", 126, 130, std::bind(&Boss_Vordt::AI_Dodge, this));
		mJumpTableManager.AddJumpTable("Combo1_Step3", 127, 130, std::bind(&Boss_Vordt::AI_MoveMent, this));

		CreateStateParameter Combo2_Step1;
		Combo2_Step1.Start = std::bind(&Boss_Vordt::Combo2_Step1_Start, this);
		Combo2_Step1.Stay = std::bind(&Boss_Vordt::Combo2_Step1_Update, this, std::placeholders::_1);
		Combo2_Step1.End = std::bind(&Boss_Vordt::Combo2_Step1_End, this);

		mJumpTableManager.AddJumpTable("Combo2_Step1", 47, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Combo2_Step1", 86, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Combo2_Step1", 87, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Combo2_Step1", 86, 90, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Combo2_Step2;
		Combo2_Step2.Start = std::bind(&Boss_Vordt::Combo2_Step2_Start, this);
		Combo2_Step2.Stay = std::bind(&Boss_Vordt::Combo2_Step2_Update, this, std::placeholders::_1);
		Combo2_Step2.End = std::bind(&Boss_Vordt::Combo2_Step2_End, this);

		mJumpTableManager.AddJumpTable("Combo2_Step2", 42, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Combo2_Step2", 81, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Combo2_Step2", 82, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Combo2_Step2", 81, 90, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Sweap_Twice_Right;
		Sweap_Twice_Right.Start = std::bind(&Boss_Vordt::Sweap_Twice_Right_Start, this);
		Sweap_Twice_Right.Stay = std::bind(&Boss_Vordt::Sweap_Twice_Right_Update, this, std::placeholders::_1);
		Sweap_Twice_Right.End = std::bind(&Boss_Vordt::Sweap_Twice_Right_End, this);

		mJumpTableManager.AddJumpTable("Sweep&Sweep_Right", 135, 165, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Right", 135, 165, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Right", 136, 165, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Right", 135, 165, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Sweap_Twice_Left;
		Sweap_Twice_Left.Start = std::bind(&Boss_Vordt::Sweap_Twice_Left_Start, this);
		Sweap_Twice_Left.Stay = std::bind(&Boss_Vordt::Sweap_Twice_Left_Update, this, std::placeholders::_1);
		Sweap_Twice_Left.End = std::bind(&Boss_Vordt::Sweap_Twice_Left_End, this);

		mJumpTableManager.AddJumpTable("Sweep&Sweep_Left", 136, 165, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Left", 136, 165, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Left", 137, 165, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Sweep&Sweep_Left", 136, 165, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hit_Down_001_Front;
		Hit_Down_001_Front.Start = std::bind(&Boss_Vordt::Hit_Down_001_Front_Start, this);
		Hit_Down_001_Front.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Front_Update, this, std::placeholders::_1);
		Hit_Down_001_Front.End = std::bind(&Boss_Vordt::Hit_Down_001_Front_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_001_Front", 179, 200, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Front", 179, 200, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Front", 179, 200, std::bind(&Boss_Vordt::AI_Dodge, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Front", 180, 200, std::bind(&Boss_Vordt::AI_MoveMent, this));

		CreateStateParameter Hit_Down_001_Right;
		Hit_Down_001_Right.Start = std::bind(&Boss_Vordt::Hit_Down_001_Right_Start, this);
		Hit_Down_001_Right.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Right_Update, this, std::placeholders::_1);
		Hit_Down_001_Right.End = std::bind(&Boss_Vordt::Hit_Down_001_Right_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_001_Right", 66, 110, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Right", 66, 110, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Right", 67, 110, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Right", 66, 110, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hit_Down_001_Left;
		Hit_Down_001_Left.Start = std::bind(&Boss_Vordt::Hit_Down_001_Left_Start, this);
		Hit_Down_001_Left.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Left_Update, this, std::placeholders::_1);
		Hit_Down_001_Left.End = std::bind(&Boss_Vordt::Hit_Down_001_Left_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_001_Left", 66, 110, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Left", 66, 110, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Left", 67, 110, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Down_001_Left", 66, 110, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hit_Down_004;
		Hit_Down_004.Start = std::bind(&Boss_Vordt::Hit_Down_004_Start, this);
		Hit_Down_004.Stay = std::bind(&Boss_Vordt::Hit_Down_004_Update, this, std::placeholders::_1);
		Hit_Down_004.End = std::bind(&Boss_Vordt::Hit_Down_004_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_004", 30, 110, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_004", 71, 110, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_004", 72, 110, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Down_004", 71, 110, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hit_Down_005;
		Hit_Down_005.Start = std::bind(&Boss_Vordt::Hit_Down_005_Start, this);
		Hit_Down_005.Stay = std::bind(&Boss_Vordt::Hit_Down_005_Update, this, std::placeholders::_1);
		Hit_Down_005.End = std::bind(&Boss_Vordt::Hit_Down_005_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_005", 44, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_005", 58, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_005", 59, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Down_005", 58, 90, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Hit_Down_006;
		Hit_Down_006.Start = std::bind(&Boss_Vordt::Hit_Down_006_Start, this);
		Hit_Down_006.Stay = std::bind(&Boss_Vordt::Hit_Down_006_Update, this, std::placeholders::_1);
		Hit_Down_006.End = std::bind(&Boss_Vordt::Hit_Down_006_End, this);

		mJumpTableManager.AddJumpTable("Hit_Down_006", 76, 100, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Hit_Down_006", 76, 100, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Hit_Down_006", 77, 100, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Hit_Down_006", 76, 100, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Thrust;
		Thrust.Start = std::bind(&Boss_Vordt::Thrust_Start, this);
		Thrust.Stay = std::bind(&Boss_Vordt::Thrust_Update, this, std::placeholders::_1);
		Thrust.End = std::bind(&Boss_Vordt::Thrust_End, this);

		mJumpTableManager.AddJumpTable("Thrust", 45, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Thrust", 70, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Thrust", 71, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Thrust", 70, 90, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Sweep_001;
		Sweep_001.Start = std::bind(&Boss_Vordt::Sweep_001_Start, this);
		Sweep_001.Stay = std::bind(&Boss_Vordt::Sweep_001_Update, this, std::placeholders::_1);
		Sweep_001.End = std::bind(&Boss_Vordt::Sweep_001_End, this);

		mJumpTableManager.AddJumpTable("Sweep_001", 107, 130, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Sweep_001", 107, 130, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Sweep_001", 108, 130, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Sweep_001", 107, 130, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Sweep_002;
		Sweep_002.Start = std::bind(&Boss_Vordt::Sweep_002_Start, this);
		Sweep_002.Stay = std::bind(&Boss_Vordt::Sweep_002_Update, this, std::placeholders::_1);
		Sweep_002.End = std::bind(&Boss_Vordt::Sweep_002_End, this);

		mJumpTableManager.AddJumpTable("Sweep_002", 47, 90, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Sweep_002", 83, 90, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Sweep_002", 84, 90, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Sweep_002", 83, 90, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Attack_001;
		Rush_Attack_001.Start = std::bind(&Boss_Vordt::Rush_Attack_001_Start, this);
		Rush_Attack_001.Stay = std::bind(&Boss_Vordt::Rush_Attack_001_Update, this, std::placeholders::_1);
		Rush_Attack_001.End = std::bind(&Boss_Vordt::Rush_Attack_001_End, this);

		mJumpTableManager.AddJumpTable("Rush_Attack", 126, 130, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush_Attack", 126, 130, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush_Attack", 126, 130, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Rush_Attack", 127, 130, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Attack_002;
		Rush_Attack_002.Start = std::bind(&Boss_Vordt::Rush_Attack_002_Start, this);
		Rush_Attack_002.Stay = std::bind(&Boss_Vordt::Rush_Attack_002_Update, this, std::placeholders::_1);
		Rush_Attack_002.End = std::bind(&Boss_Vordt::Rush_Attack_002_End, this);

		mJumpTableManager.AddJumpTable("Rush_Attack_002", 93, 100, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush_Attack_002", 93, 100, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush_Attack_002", 94, 100, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Rush_Attack_002", 93, 100, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Turn;
		Rush_Turn.Start = std::bind(&Boss_Vordt::Rush_Turn_Start, this);
		Rush_Turn.Stay = std::bind(&Boss_Vordt::Rush_Turn_Update, this, std::placeholders::_1);
		Rush_Turn.End = std::bind(&Boss_Vordt::Rush_Turn_End, this);

		mJumpTableManager.AddJumpTable("Rush&Turn", 40, 48, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush&Turn", 40, 48, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush&Turn", 40, 48, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Rush&Turn", 41, 48, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Hit_Turn;
		Rush_Hit_Turn.Start = std::bind(&Boss_Vordt::Rush_Hit_Turn_Start, this);
		Rush_Hit_Turn.Stay = std::bind(&Boss_Vordt::Rush_Hit_Turn_Update, this, std::placeholders::_1);
		Rush_Hit_Turn.End = std::bind(&Boss_Vordt::Rush_Hit_Turn_End, this);

		mJumpTableManager.AddJumpTable("Rush&Hit&Turn", 57, 65, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn", 60, 65, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn", 61, 65, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn", 60, 65, std::bind(&Boss_Vordt::AI_Dodge, this));

		CreateStateParameter Rush_Hit_Turn_Rush;
		Rush_Hit_Turn_Rush.Start = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_Start, this);
		Rush_Hit_Turn_Rush.Stay = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_Update, this, std::placeholders::_1);
		Rush_Hit_Turn_Rush.End = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_End, this);

		mJumpTableManager.AddJumpTable("Rush&Hit&Turn&Rush", 192, 197, std::bind(&Boss_Vordt::AI_Combo, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn&Rush", 192, 197, std::bind(&Boss_Vordt::AI_Attack, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn&Rush", 193, 197, std::bind(&Boss_Vordt::AI_MoveMent, this));
		mJumpTableManager.AddJumpTable("Rush&Hit&Turn&Rush", 192, 197, std::bind(&Boss_Vordt::AI_Dodge, this));

		// Move & Others
		MainState.CreateState(Enum_BossState::Howling, Howling, "Howling");
		MainState.CreateState(Enum_BossState::Idle, Idle, "Idle");
		MainState.CreateState(Enum_BossState::Walk_Front, Walk_Front, "Walk_Front");
		MainState.CreateState(Enum_BossState::Walk_Right, Walk_Right, "Walk_Right");
		MainState.CreateState(Enum_BossState::Walk_Left, Walk_Left, "Walk_Left");
		MainState.CreateState(Enum_BossState::Rush_Front, Rush_Front, "Rush_Front");
		MainState.CreateState(Enum_BossState::Jump_Back, Jump_Back, "Jump_Back");
		MainState.CreateState(Enum_BossState::Jump_Right, Jump_Right, "Jump_Right");
		MainState.CreateState(Enum_BossState::Jump_Left, Jump_Left, "Jump_Left");
		MainState.CreateState(Enum_BossState::Turn_Right, Turn_Right, "Turn_Right");
		MainState.CreateState(Enum_BossState::Turn_Left, Turn_Left, "Turn_Left");
		MainState.CreateState(Enum_BossState::Turn_Right_Twice, Turn_Right_Twice, "Turn_Right_Twice");
		MainState.CreateState(Enum_BossState::Turn_Left_Twice, Turn_Left_Twice, "Turn_Left_Twice");
		MainState.CreateState(Enum_BossState::Hitten_Front, Hitten_Front, "Hitten_Front");
		MainState.CreateState(Enum_BossState::Hitten_Back, Hitten_Back, "Hitten_Back");
		MainState.CreateState(Enum_BossState::Hitten_Right, Hitten_Right, "Hitten_Right");
		MainState.CreateState(Enum_BossState::Hitten_Left, Hitten_Left, "Hitten_Left");
		MainState.CreateState(Enum_BossState::Hitten_Groggy, Hitten_Groggy, "Hitten_Groggy");
		MainState.CreateState(Enum_BossState::Groggy, Groggy, "Groggy");
		MainState.CreateState(Enum_BossState::Death, Death, "Death");
		MainState.CreateState(Enum_BossState::Death_Groggy, Death_Groggy, "Death_Groggy");

		// Attack
		MainState.CreateState(Enum_BossState::Breath, Breath, "Breath");
		MainState.CreateState(Enum_BossState::Combo1_Step1, Combo1_Step1, "Combo1_Step1");
		MainState.CreateState(Enum_BossState::Combo1_Step2, Combo1_Step2, "Combo1_Step2");
		MainState.CreateState(Enum_BossState::Combo1_Step3, Combo1_Step3, "Combo1_Step3");
		MainState.CreateState(Enum_BossState::Combo2_Step1, Combo2_Step1, "Combo2_Step1");
		MainState.CreateState(Enum_BossState::Combo2_Step2, Combo2_Step2, "Combo2_Step2");
		MainState.CreateState(Enum_BossState::Sweap_Twice_Right, Sweap_Twice_Right, "Sweap_Twice_Right");
		MainState.CreateState(Enum_BossState::Sweap_Twice_Left, Sweap_Twice_Left, "Sweap_Twice_Left");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Front, Hit_Down_001_Front, "Hit_Down_001_Front");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Right, Hit_Down_001_Right, "Hit_Down_001_Right");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Left, Hit_Down_001_Left, "Hit_Down_001_Left");
		MainState.CreateState(Enum_BossState::Hit_Down_004, Hit_Down_004, "Hit_Down_004");
		MainState.CreateState(Enum_BossState::Hit_Down_005, Hit_Down_005, "Hit_Down_005");
		MainState.CreateState(Enum_BossState::Hit_Down_006, Hit_Down_006, "Hit_Down_006");
		MainState.CreateState(Enum_BossState::Thrust, Thrust, "Thrust");
		MainState.CreateState(Enum_BossState::Sweep_001, Sweep_001, "Sweep_001");
		MainState.CreateState(Enum_BossState::Sweep_002, Sweep_002, "Sweep_002");
		MainState.CreateState(Enum_BossState::Rush_Attack_001, Rush_Attack_001, "Rush_Attack_001");
		MainState.CreateState(Enum_BossState::Rush_Attack_002, Rush_Attack_002, "Rush_Attack_002");
		MainState.CreateState(Enum_BossState::Rush_Turn, Rush_Turn, "Rush_Turn");
		MainState.CreateState(Enum_BossState::Rush_Hit_Turn, Rush_Hit_Turn, "Rush_Hit_Turn");
		MainState.CreateState(Enum_BossState::Rush_Hit_Turn_Rush, Rush_Hit_Turn_Rush, "Rush_Hit_Turn_Rush");

		//// Start State
		MainState.ChangeState(Enum_BossState::Idle);

		//// AI State
		// Move & Others
		AI_States[Enum_BossState::Howling] = AI_State(0.f);
		AI_States[Enum_BossState::Idle] = AI_State(0.f);
		AI_States[Enum_BossState::Walk_Front] = AI_State(0.f);
		AI_States[Enum_BossState::Walk_Right] = AI_State(0.f);
		AI_States[Enum_BossState::Walk_Left] = AI_State(0.f);
		AI_States[Enum_BossState::Rush_Front] = AI_State(0.f);
		AI_States[Enum_BossState::Jump_Back] = AI_State(JUMP_COOLDOWN);
		AI_States[Enum_BossState::Jump_Right] = AI_State(JUMP_COOLDOWN);
		AI_States[Enum_BossState::Jump_Left] = AI_State(JUMP_COOLDOWN);
		AI_States[Enum_BossState::Turn_Right] = AI_State(0.f);
		AI_States[Enum_BossState::Turn_Left] = AI_State(0.f);
		AI_States[Enum_BossState::Turn_Right_Twice] = AI_State(0.f);
		AI_States[Enum_BossState::Turn_Left_Twice] = AI_State(0.f);
		AI_States[Enum_BossState::Hitten_Front] = AI_State(0.f);
		AI_States[Enum_BossState::Hitten_Back] = AI_State(0.f);
		AI_States[Enum_BossState::Hitten_Right] = AI_State(0.f);
		AI_States[Enum_BossState::Hitten_Left] = AI_State(0.f);
		AI_States[Enum_BossState::Hitten_Groggy] = AI_State(0.f);
		AI_States[Enum_BossState::Groggy] = AI_State(0.f);
		AI_States[Enum_BossState::Death] = AI_State(0.f);
		AI_States[Enum_BossState::Breath] = AI_State(0.f);
		AI_States[Enum_BossState::Combo1_Step1] = AI_State(COMBO_COOLDOWN1);
		AI_States[Enum_BossState::Combo1_Step2] = AI_State(COMBO_COOLDOWN1);
		AI_States[Enum_BossState::Combo1_Step3] = AI_State(COMBO_COOLDOWN1);
		AI_States[Enum_BossState::Combo2_Step1] = AI_State(COMBO_COOLDOWN1);
		AI_States[Enum_BossState::Combo2_Step2] = AI_State(COMBO_COOLDOWN1);
		AI_States[Enum_BossState::Sweap_Twice_Right] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Sweap_Twice_Left] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_001_Front] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_001_Right] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_001_Left] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_004] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_005] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Hit_Down_006] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Thrust] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Sweep_001] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Sweep_002] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Rush_Attack_001] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Rush_Attack_002] = AI_State(NORMAL_ATTACK_COOLDOWN);
		AI_States[Enum_BossState::Rush_Turn] = AI_State(0.f);
		AI_States[Enum_BossState::Rush_Hit_Turn] = AI_State(COMBO_COOLDOWN2);
		AI_States[Enum_BossState::Rush_Hit_Turn_Rush] = AI_State(COMBO_COOLDOWN2);
	}
}

Enum_JumpTableFlag Boss_Vordt::AI_Combo()
{
	// Combo Attack
	//// List of Combo State
	//	1. Combo1_Step1
	//	2. Combo1_Step2
	//	3. Combo1_Step3
	//	4. Combo2_Step1
	//	5. Combo2_Step2
	//  6. Rush&Hit&Turn (Rush_Combo)

	if (true == AI_Off)
	{
		if (true == ChangeAI_State(Enum_BossState::Idle))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		return Enum_JumpTableFlag::Default;
	}

	int CurState = MainState.GetCurState();
	int tDis = mTargetState.mTargetDis;
	int tDeg = mTargetState.mTargetDeg;

	switch (CurState)
	{
	default:
	{
		if (Enum_TargetDeg::Deg_Side < tDeg)
		{
			break;
		}

		if (Enum_Boss_Phase::Phase_2 == mBoss_Phase && Enum_TargetDeg::Deg_Front == tDeg)
		{
			if (true == ChangeAI_State(Enum_BossState::Rush_Hit_Turn))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
		}

		if (Enum_TargetDis::Dis_Middle < tDis)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Combo1_Step1))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}

		if (Enum_TargetDis::Dis_Close < tDis)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Combo2_Step1))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_BossState::Rush_Hit_Turn:
	{
		if (true == ChangeAI_State(Enum_BossState::Rush_Hit_Turn))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_BossState::Combo1_Step1:
	{
		if (Enum_TargetDis::Dis_Close < tDis)
		{
			break;
		}

		if (Enum_TargetDeg::Deg_Side < tDeg)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Combo1_Step2))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_BossState::Combo1_Step2:
	{
		if (Enum_TargetDis::Dis_Middle < tDis)
		{
			break;
		}

		if (Enum_TargetDeg::Deg_Side < tDeg)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Combo1_Step3))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_BossState::Combo2_Step1:
	{
		if (Enum_TargetDis::Dis_Close < tDis)
		{
			break;
		}

		if (Enum_TargetDeg::Deg_Front < tDeg)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Combo2_Step2))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_BossState::Combo1_Step3:
	case Enum_BossState::Combo2_Step2:
		break;
	}

	return Enum_JumpTableFlag::Default;
}

Enum_JumpTableFlag Boss_Vordt::AI_Attack()
{
	// Attack
	//// List of Attack State
	//	1. Rush_Attack
	//	2. Hit_Down_001_Front
	//	3. Hit_Down_001_Right
	//	4. Hit_Down_001_Left
	//  5. Hit_Down_004
	//	6. Hit_Down_005
	//	7. Thrust
	//	8. Sweep_001
	//	9. Sweep&Sweep_Right
	//	10. Sweep&Sweep_Left
	//  11. Rush_Attack_002
	//	13. Rush&Hit&Turn&Rush
	//	14. Rush&Turn
	//  15. Sweep_002
	//  16. Hit_Down_006

	if (true == AI_Off)
	{
		if (true == ChangeAI_State(Enum_BossState::Idle))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		return Enum_JumpTableFlag::Default;
	}

	int CurState = MainState.GetCurState();
	int tDis = mTargetState.mTargetDis;

	if (Enum_TargetDis::Dis_OutOfRange == tDis)
	{
		return Enum_JumpTableFlag::Default;
	}

	int tDeg = mTargetState.mTargetDeg;
	Enum_RotDir Dir = GetRotDir_e();

	switch (tDis)
	{
	case Enum_TargetDis::Dis_Long:
	case Enum_TargetDis::Dis_Far:
	{
		if (Enum_Boss_Phase::Phase_2 != mBoss_Phase)
		{
			break;
		}

		if (Enum_TargetDeg::Deg_Front < tDeg)
		{
			break;
		}

		if (true == ChangeAI_State(Enum_BossState::Rush_Hit_Turn_Rush))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Enum_TargetDis::Dis_Attach:
	{
		if (Enum_TargetDeg::Deg_Side < tDeg)
		{
			break;
		}

		switch (Dir)
		{
		case Enum_RotDir::Left:
		{
			if (true == ChangeAI_State(Enum_BossState::Hit_Down_005))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}

			if (true == ChangeAI_State(Enum_BossState::Sweap_Twice_Left))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
			break;
		}
		case Enum_RotDir::Right:
		{
			if (true == ChangeAI_State(Enum_BossState::Sweap_Twice_Right))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
			break;
		}
		case Not_Rot:
		default:
			break;
		}

		if (Enum_TargetDeg::Deg_Front == tDeg)
		{
			if (true == ChangeAI_State(Enum_BossState::Hit_Down_006))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}

			if (true == ChangeAI_State(Enum_BossState::Hit_Down_001_Front))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
		}
		else
		{
			switch (Dir)
			{
			case Left:
			{
				if (true == ChangeAI_State(Enum_BossState::Hit_Down_001_Left))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}

				break;
			}
			case Right:
			{
				if (true == ChangeAI_State(Enum_BossState::Hit_Down_001_Right))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}

				if (true == ChangeAI_State(Enum_BossState::Hit_Down_004))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}
				break;
			}
			case Not_Rot:
			default:
				break;
			}
			break;
		}
	}
	default:
		break;
	}

	if (Enum_TargetDeg::Deg_Side < tDeg && true == ChangeAI_State(Enum_BossState::Rush_Turn))
	{
		return Enum_JumpTableFlag::StopJumpTable;
	}

	if (Enum_TargetDeg::Deg_Front < tDeg)
	{
		return Enum_JumpTableFlag::Default;
	}

	if (Enum_TargetDis::Dis_Close >= tDis && Enum_RotDir::Left == Dir)
	{
		if (true == ChangeAI_State(Enum_BossState::Thrust))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
	}
	else if (Enum_TargetDis::Dis_Middle >= tDis)
	{
		if (true == ChangeAI_State(Enum_BossState::Rush_Attack_002))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
	}
	else if (Enum_TargetDis::Dis_Far >= tDis)
	{
		if (true == ChangeAI_State(Enum_BossState::Rush_Attack_001))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
	}

	if (Enum_TargetDis::Dis_Close < tDis)
	{
		return Enum_JumpTableFlag::Default;
	}

	switch (Dir)
	{
	case Left:
	{
		if (true == ChangeAI_State(Enum_BossState::Sweep_002))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Right:
	{
		if (true == ChangeAI_State(Enum_BossState::Sweep_001))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Not_Rot:
	default:
		break;
	}

	return Enum_JumpTableFlag::Default;
}

Enum_JumpTableFlag Boss_Vordt::AI_MoveMent()
{
	// Move to Target
	//// List of MoveMent
	//	1. Walk_Front // tDis > Enum_TargetDis::Dis_Close && tDeg == Enum_TargetDeg::Deg_Front
	//	2. Walk_Left // tDis > Enum_TargetDis::Dis_Close && tDeg == Enum_TargetDeg::Deg_Side && Dir == Enum_RotDir::Left
	//	3. Walk_Right // tDis > Enum_TargetDis::Dis_Close && tDeg == Enum_TargetDeg::Deg_Side && Dir == Enum_RotDir::Right
	//	4. Rush_Front // tDis == Enum_TargetDis::Dis_Far && tDeg == Enum_TargetDeg::Deg_Front
	//	5. Turn_Left // tDis < Enum_TargetDis::Dis_Middle && tDeg == Enum_TargetDeg::Deg_Side && Dir == Enum_RotDir::Left
	//	6. Turn_Right // tDis < Enum_TargetDis::Dis_Middle && tDeg == Enum_TargetDeg::Deg_Side && Dir == Enum_RotDir::Right
	//	7. Turn_Left_Twice // tDis < Enum_TargetDis::Dis_Middle && tDeg == Enum_TargetDeg::Deg_Back && Dir == Enum_RotDir::Left
	//	8. Turn_Right_Twice // tDis < Enum_TargetDis::Dis_Middle && tDeg == Enum_TargetDeg::Deg_Back && Dir == Enum_RotDir::Right

	if (true == AI_Off)
	{
		if (true == ChangeAI_State(Enum_BossState::Idle))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		return Enum_JumpTableFlag::Default;
	}

	int CurState = MainState.GetCurState();
	int tDis = mTargetState.mTargetDis;
	int tDeg = mTargetState.mTargetDeg;
	Enum_RotDir Dir = GetRotDir_e();

	switch (tDeg)
	{
	case Enum_TargetDeg::Deg_Front:
	{
		if (tDis == Enum_TargetDis::Dis_Close)
		{
			break;
		}

		if (tDis >= Enum_TargetDis::Dis_Far && Enum_Boss_Phase::Phase_2 == mBoss_Phase)
		{
			if (true == ChangeAI_State(Enum_BossState::Rush_Front))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
		}

		if (true == ChangeAI_State(Enum_BossState::Walk_Front))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}

		break;
	}
	case Enum_TargetDeg::Deg_Side:
	{
		switch (Dir)
		{
		case Left:
		{
			if (tDis < Enum_TargetDis::Dis_Middle)
			{
				if (true == ChangeAI_State(Enum_BossState::Turn_Left))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}
			}
			else
			{
				if (true == ChangeAI_State(Enum_BossState::Walk_Left))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}
			}
			break;
		}
		case Right:
		{
			if (tDis < Enum_TargetDis::Dis_Middle)
			{
				if (true == ChangeAI_State(Enum_BossState::Turn_Right))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}
			}
			else
			{
				if (true == ChangeAI_State(Enum_BossState::Walk_Right))
				{
					return Enum_JumpTableFlag::StopJumpTable;
				}
			}
			break;
		}
		case Not_Rot:
		default:
			break;
		}
		break;
	}
	case Enum_TargetDeg::Deg_Back:
	{
		switch (Dir)
		{
		case Left:
		{
			if (true == ChangeAI_State(Enum_BossState::Turn_Left_Twice))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
			break;
		}
		case Right:
		{
			if (true == ChangeAI_State(Enum_BossState::Turn_Right_Twice))
			{
				return Enum_JumpTableFlag::StopJumpTable;
			}
			break;
		}
		case Not_Rot:
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

	return Enum_JumpTableFlag::Default;
}

Enum_JumpTableFlag Boss_Vordt::AI_Dodge()
{
	// Jump(Dodge)
	//// List of Dodge State
	//	1. Jump_Back
	//	2. Jump_Left
	//	3. Jump_Right

	if (true == AI_Off)
	{
		if (true == ChangeAI_State(Enum_BossState::Idle))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		return Enum_JumpTableFlag::Default;
	}

	int CurState = MainState.GetCurState();
	int tDis = mTargetState.mTargetDis;
	int tDeg = mTargetState.mTargetDeg;

	if (Enum_TargetDis::Dis_Middle < tDis)
	{
		return Enum_JumpTableFlag::Default;
	}

	if (Enum_TargetDeg::Deg_Side < tDeg)
	{
		return Enum_JumpTableFlag::Default;
	}

	if (Enum_TargetDeg::Deg_Front == tDeg && true == ChangeAI_State(Enum_BossState::Jump_Back))
	{
		return Enum_JumpTableFlag::StopJumpTable;
	}

	Enum_RotDir Dir = GetRotDir_e();

	switch (Dir)
	{
	case Left:
	{
		if (true == ChangeAI_State(Enum_BossState::Jump_Left))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Right:
	{
		if (true == ChangeAI_State(Enum_BossState::Jump_Right))
		{
			return Enum_JumpTableFlag::StopJumpTable;
		}
		break;
	}
	case Not_Rot:
	default:
		break;
	}

	return Enum_JumpTableFlag::Default;
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
	Stat.SetPoise(100);
}

void Boss_Vordt::Howling_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Idle_Start()
{
	MainRenderer->ChangeAnimation("Idle", true);
}

void Boss_Vordt::Idle_Update(float _Delta)
{

}

void Boss_Vordt::Idle_End()
{

}

void Boss_Vordt::Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("Walk_Front", true);
}

void Boss_Vordt::Walk_Front_Update(float _Delta)
{

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
	if (21 <= MainRenderer->GetCurAnimationFrame())
	{
		MainRenderer->ChangeAnimation("Rush_Front", true);
	}
}

void Boss_Vordt::Rush_Front_End()
{

}

void Boss_Vordt::Jump_Back_Start()
{
	MainRenderer->ChangeAnimation("Jump_Back", true);
}

void Boss_Vordt::Jump_Back_Update(float _Delta)
{

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

void Boss_Vordt::Hitten_Front_Start()
{
	MainRenderer->ChangeAnimation("Hit_001", true);
}

void Boss_Vordt::Hitten_Front_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_Front_End()
{

}

void Boss_Vordt::Hitten_Back_Start()
{
	MainRenderer->ChangeAnimation("Hit_002", true);
}

void Boss_Vordt::Hitten_Back_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_Back_End()
{

}

void Boss_Vordt::Hitten_Right_Start()
{
	MainRenderer->ChangeAnimation("Hit_003_Right", true);
}

void Boss_Vordt::Hitten_Right_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_Right_End()
{

}

void Boss_Vordt::Hitten_Left_Start()
{
	MainRenderer->ChangeAnimation("Hit_003_Left", true);
}

void Boss_Vordt::Hitten_Left_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_Left_End()
{

}

void Boss_Vordt::Hitten_Groggy_Start()
{
	MainRenderer->ChangeAnimation("Hit_004_Groggy", true);
}

void Boss_Vordt::Hitten_Groggy_Update(float _Delta)
{

}

void Boss_Vordt::Hitten_Groggy_End()
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
	MainRenderer->ChangeAnimation("Death", true);
	SetFlag(Enum_ActorFlag::Death, true);
}

void Boss_Vordt::Death_Update(float _Delta)
{

}

void Boss_Vordt::Death_End()
{

}

void Boss_Vordt::Death_Groggy_Start()
{
	MainRenderer->ChangeAnimation("Death_Groggy", true);
	SetFlag(Enum_ActorFlag::Death, true);
	mHitCollision.Off();
}

void Boss_Vordt::Death_Groggy_Update(float _Delta)
{

}

void Boss_Vordt::Death_Groggy_End()
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

void Boss_Vordt::Combo1_Step1_Start()
{
	MainRenderer->ChangeAnimation("Combo1_Step1", true);
	Stat.SetAtt(BOSS_ATT * 6);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Combo1_Step1_Update(float _Delta)
{

}

void Boss_Vordt::Combo1_Step1_End()
{
	mAttackCollision.ResetRecord();
}


void Boss_Vordt::Combo1_Step2_Start()
{
	MainRenderer->ChangeAnimation("Combo1_Step2", true);
	Stat.SetAtt(BOSS_ATT * 6);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Combo1_Step2_Update(float _Delta)
{

}

void Boss_Vordt::Combo1_Step2_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Combo1_Step3_Start()
{
	MainRenderer->ChangeAnimation("Combo1_Step3", true);
	Stat.SetAtt(BOSS_ATT * 4);
	Hit_Type = Enum_Player_Hit::Strong;
}

void Boss_Vordt::Combo1_Step3_Update(float _Delta)
{

}

void Boss_Vordt::Combo1_Step3_End()
{
	mAttackCollision.ResetRecord();
}


void Boss_Vordt::Combo2_Step1_Start()
{
	MainRenderer->ChangeAnimation("Combo2_Step1", true);
	Stat.SetAtt(BOSS_ATT * 5);
	Hit_Type = Enum_Player_Hit::weak;
}

void Boss_Vordt::Combo2_Step1_Update(float _Delta)
{

}

void Boss_Vordt::Combo2_Step1_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Combo2_Step2_Start()
{
	MainRenderer->ChangeAnimation("Combo2_Step2", true);
	Stat.SetAtt(BOSS_ATT * 3);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Combo2_Step2_Update(float _Delta)
{

}

void Boss_Vordt::Combo2_Step2_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Sweap_Twice_Right_Start()
{
	MainRenderer->ChangeAnimation("Sweep&Sweep_Right", true);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Sweap_Twice_Right_Update(float _Delta)
{

}

void Boss_Vordt::Sweap_Twice_Right_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Sweap_Twice_Left_Start()
{
	Stat.SetAtt(BOSS_ATT * 4);
	MainRenderer->ChangeAnimation("Sweep&Sweep_Left", true);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Sweap_Twice_Left_Update(float _Delta)
{

}

void Boss_Vordt::Sweap_Twice_Left_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_001_Front_Start()
{
	Stat.SetAtt(BOSS_ATT * 6);
	MainRenderer->ChangeAnimation("Hit_Down_001_Front", true);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Hit_Down_001_Front_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_001_Front_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_001_Right_Start()
{
	Stat.SetAtt(BOSS_ATT * 6);
	MainRenderer->ChangeAnimation("Hit_Down_001_Right", true);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Hit_Down_001_Right_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_001_Right_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_001_Left_Start()
{
	Stat.SetAtt(BOSS_ATT * 6);
	MainRenderer->ChangeAnimation("Hit_Down_001_Left", true);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Hit_Down_001_Left_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_001_Left_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_004_Start()
{
	Stat.SetAtt(BOSS_ATT * 3);
	MainRenderer->ChangeAnimation("Hit_Down_004", true);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Hit_Down_004_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_004_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_005_Start()
{
	Stat.SetAtt(BOSS_ATT * 4);
	MainRenderer->ChangeAnimation("Hit_Down_005", true);
	Hit_Type = Enum_Player_Hit::Down;
}

void Boss_Vordt::Hit_Down_005_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_005_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Hit_Down_006_Start()
{
	Stat.SetAtt(BOSS_ATT * 5);
	MainRenderer->ChangeAnimation("Hit_Down_006", true);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Hit_Down_006_Update(float _Delta)
{

}

void Boss_Vordt::Hit_Down_006_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Thrust_Start()
{
	Stat.SetAtt(BOSS_ATT * 2);
	MainRenderer->ChangeAnimation("Thrust", true);
	Hit_Type = Enum_Player_Hit::weak;
}

void Boss_Vordt::Thrust_Update(float _Delta)
{

}

void Boss_Vordt::Thrust_End()
{
	mAttackCollision.ResetRecord();
}

// Sweep_002 is faster than Sweep_001
void Boss_Vordt::Sweep_001_Start()
{
	Stat.SetAtt(BOSS_ATT * 7);
	MainRenderer->ChangeAnimation("Sweep_001", true);
	Hit_Type = Enum_Player_Hit::Strong;
}

void Boss_Vordt::Sweep_001_Update(float _Delta)
{

}

void Boss_Vordt::Sweep_001_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Sweep_002_Start()
{
	Stat.SetAtt(BOSS_ATT * 5);
	MainRenderer->ChangeAnimation("Sweep_002", true);
	Hit_Type = Enum_Player_Hit::weak;
}

void Boss_Vordt::Sweep_002_Update(float _Delta)
{

}

void Boss_Vordt::Sweep_002_End()
{
	mAttackCollision.ResetRecord();
}

// Rush_Attack_002 is faster than Rush_Attack_001
void Boss_Vordt::Rush_Attack_001_Start()
{
	Stat.SetAtt(BOSS_ATT * 7);
	MainRenderer->ChangeAnimation("Rush_Attack", true);
	Hit_Type = Enum_Player_Hit::Strong;  
}

void Boss_Vordt::Rush_Attack_001_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_001_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Rush_Attack_002_Start()
{
	Stat.SetAtt(BOSS_ATT * 5);
	MainRenderer->ChangeAnimation("Rush_Attack_002", true);
	Hit_Type = Enum_Player_Hit::Middle;
}

void Boss_Vordt::Rush_Attack_002_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_002_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Rush_Turn_Start()
{
	Stat.SetAtt(BOSS_ATT * 3);
	MainRenderer->ChangeAnimation("Rush&Turn", true);
	Hit_Type = Enum_Player_Hit::weak;
}

void Boss_Vordt::Rush_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Turn_End()
{
	mAttackCollision.ResetRecord();
}

void Boss_Vordt::Rush_Hit_Turn_Start()
{
	Stat.SetAtt(BOSS_ATT * 7);
	++Rush_Combo_Count;
	MainRenderer->ChangeAnimation("Rush&Hit&Turn", true);
	Hit_Type = Enum_Player_Hit::Strong;
	if (3 > Rush_Combo_Count)
	{
		AI_States[Enum_BossState::Rush_Hit_Turn].CurCoolDown = 0.f;
	}
}

void Boss_Vordt::Rush_Hit_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_End()
{
	mAttackCollision.ResetRecord();

	if (3 == Rush_Combo_Count)
	{
		Rush_Combo_Count = 0;
		AI_States[Enum_BossState::Rush_Hit_Turn].CurCoolDown = AI_States[Enum_BossState::Rush_Hit_Turn].StateCoolDown;
	}
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Start()
{
	Stat.SetAtt(BOSS_ATT * 8);
	MainRenderer->ChangeAnimation("Rush&Hit&Turn&Rush", true);
	MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::RealTimeDir);
	Hit_Type = Enum_Player_Hit::Strong;
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_End()
{
	mAttackCollision.ResetRecord();
}