#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "math.h"

// ¼­¹ö¿ë
#include "GameEngineNetWindow.h"

#define Frame 0.033f
Player* Player::Main_Player;

Player::Player()
{
	//this_Player = this; 
}

Player::~Player()
{
}


void Player::Start()
{
	
	Main_Player = this;

	GameEngineInput::AddInputObject(this);

	
	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	


	MainRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	MainRenderer->Transform.SetLocalScale({ 100, 100, 100 });
	MainRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//MainRenderer->Transform.SetLocalPosition({ 0.0f, -300.0f, 0.0f });

	
	BoneName = "R_Hand";

	
	MainRenderer->SetFBXMesh("c0010.FBX", "FBXAnimationTexture"); // Bone 136
	

	
	MainRenderer->CreateFBXAnimation("Idle", "00000.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Shield_Idle", "00100.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Waek_jump", "004200.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_jump", "004210.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("String_Jump", "004220.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Roll_Forward", "004280.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hit_right", "005000.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hit_Left", "005001.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hit_Forward", "005002.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hit_Behind", "005003.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Left", "005100.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Right", "005101.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Forward", "005102.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Behind", "005203.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("String_Hit_Forward", "005300.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("String_Hit_Behind", "005303.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Run15", "017002.FBX", { Frame, true }); // ¿¡´Ï¸ÞÀÌ¼ÇÀÌ µ¹¾Æ°¨ 
	MainRenderer->CreateFBXAnimation("Weak_Shield_block", "019200.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_Shield_block", "019210.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Slow_Walk_Forward", "020000.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Slow_Walk_Behind", "0200001.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Slow_Walk_Right", "0200002.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Slow_Walk_Left", "0200003.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Walk_Forward", "020100.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Walk_Behind", "020101.FBX", { Frame, true });

	MainRenderer->CreateFBXAnimation("Walk_Right", "020102.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Walk_Left", "020103.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Slow_Shield_Move", "020140.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Run", "020200.FBX", { Frame, true });
	//FBXRenderer->CreateFBXAnimation("Shield_Move", "023050.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Back_Step", "027000.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Roll_Behind", "027101.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Roll_Right", "027102.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Roll_Left", "027103.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("portion_Down", "029029.FBX", { Frame, true }); // ?? 

	MainRenderer->CreateFBXAnimation("Weapon_Draw", "029090.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Shield_Draw", "029091.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Attack_02", "045120.FBX", { Frame, false }); //Attack_02
	MainRenderer->CreateFBXAnimation("Attack_01", "045130.FBX", { Frame, false }); //Attack_01
	MainRenderer->CreateFBXAnimation("Attack_03", "045140.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Attack_04", "045150.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Attack_05", "045110.FBX", { Frame, true });


	MainRenderer->CreateFBXAnimation("Open_Door", "060030.FBX", { Frame, true });

	MainRenderer->CreateFBXAnimation("String_Block", "19500.FBX", { Frame, true });

	MainRenderer->CreateFBXAnimation("Parrying_Attack", "030400.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("DownAttack", "030810.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Parrying", "032100.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Portion_Drink_01", "050110.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Portion_Drink_02", "050111.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Portion_Drink_03", "050112.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Sit_Down", "068010.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Stand_Up", "068012.FBX", { Frame, true });


	MainRenderer->CreateFBXAnimation("Solar_hurray", "080001.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hi", "080011.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("hand", "080012.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Fighting", "080013.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Fighting_02", "080014.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Surren", "080700.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Surren_Up", "080702.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Run20", "019500.FBX", { Frame, true });

	MainRenderer->CreateFBXAnimation("Left_Stop", "022102.FBX", { Frame, false }); // ¿ÞÂÊ ¸ØÃã 
	MainRenderer->CreateFBXAnimation("Behind_Stop", "022101.FBX", { Frame, false }); // µÚ ¸ØÃã 
	MainRenderer->CreateFBXAnimation("Right_Stop", "022103.FBX", { Frame, false }); // ¿À¸¥ÂÊ ¸ØÃã 
	MainRenderer->CreateFBXAnimation("Forward_Stop", "022200.FBX", { Frame, false }); // ¾Õ ¸ØÃã 
	MainRenderer->CreateFBXAnimation("Shield_Move", "023100.FBX", { Frame, true }); // ½¯µå ¿òÁ÷ÀÓ ¾ÈµÊ 
	MainRenderer->ChangeAnimation("Shield_Idle");
	

	MainRenderer->SetRootMotionComponent(Capsule.get());
	MainRenderer->SetRootMotion("Attack_01");
	MainRenderer->SetRootMotion("Walk_Forward","",Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Roll_Forward");

	//MainRenderer->Off();





	{
		SwordActor = GetLevel()->CreateActor<GameEngineActor>();
		//SwordActor->Transform.SetLocalPosition({ 0.0f - 300.0f });
		Weapon = SwordActor->CreateComponent<GameContentsFBXRenderer>();
		Weapon->SetFBXMesh("WP_A_0221.FBX", "FBXAnimationTexture");

		Weapon->Transform.SetLocalScale({ 50, 50, 50 });
		//Weapon->Transform.SetLocalPosition({ -4.0f, -152.0f, 165.0f });
		Weapon->Transform.SetLocalRotation({ 0.0f, 0.0f, 180.0f });
	}


	






	/*{
		Col = CreateComponent<GameEngineCollision>();
		Col->Transform.SetLocalScale({ 200.0f,200.0f });
	}*/

	Mini_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};

	Mini_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			float4 Monster = Col->GetActor()->Transform.GetLocalPosition();
			Monster.Normalize();

			float4 Other_Monster = col->GetActor()->Transform.GetLocalPosition();
			Other_Monster.Normalize();

			Col->GetActor()->Transform.AddLocalPosition(Other_Monster - Monster * DeltaTime);
		};



	Mini_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};
	
	MainRenderer->AddNotBlendBoneIndex(53);

	Transform.SetLocalPosition({ 0.0f,-300.0f });
	Player_State();

	Transform.AddLocalPosition({ 0.0f,-300.0f });
	
	GameEngineCore::MainWindow.SetMousePos(1280,720);

	{
		Actor_test = GetLevel()->CreateActor<GameEngineActor>();
	}

	{
		Actor_test_02 = GetLevel()->CreateActor<GameEngineActor>();
		Actor_test_02->SetParent(Actor_test);
		Actor_test_02->Transform.SetWorldPosition({ 0.0f,140.0f,-250.0f });
	}
}

void Player::Update(float _Delta)
{
	Time += _Delta;

	if (GameEngineInput::IsDown('Q', this))
	{
		MainRenderer->SwitchPause();
	}
	
	AnimationBoneData Data = MainRenderer->GetBoneData(Bone_index_01);

	SwordActor->Transform.SetLocalRotation(Data.RotQuaternion.QuaternionToEulerDeg());
	SwordActor->Transform.SetWorldPosition(Data.Pos+Transform.GetWorldPosition());
	

	CameraRotation(_Delta);
	



		float4 TargetPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
		float4 MyPos = Actor_test->Transform.GetWorldPosition();

		// YÃà °í·Á X
		TargetPos.Y = MyPos.Y = 0.f;

		float4 FrontVector = float4(0.f, 0.f, -1.f, 0.f);
		FrontVector.VectorRotationToDegY(Capsule->GetDir());

		float4 LocationVector = (TargetPos - MyPos).NormalizeReturn();

		float4 Angle_ = DirectX::XMVector3AngleBetweenNormals(FrontVector.DirectXVector, LocationVector.DirectXVector);

		float4 RotationDir = DirectX::XMVector3Cross(FrontVector.DirectXVector, LocationVector.DirectXVector);

		Angle = Angle_.X * GameEngineMath::R2D;

		if (0.0f <= RotationDir.Y)
		{

		}
		else
		{
			Angle *= -1.f;
		}





		/*if (GameEngineInput::IsDown('W', this))
		{
			Rotation_Check = true;
		}

		if (Rotation_Check == true)
		{
			if (Angle > 0)
			{
				Capsule->AddWorldRotation({ 0.0f,1.0f });
			}

			if (Angle < 0)
			{
				Capsule->AddWorldRotation({ 0.0f,-1.0f });
			}

		}*/





		float4 WorldMousePos = Angle;

		OutputDebugStringA(WorldMousePos.ToString("\n").c_str());


	/*Col->CollisionEvent(0, { .Stay = [&](class GameEngineCollision* _This,class GameEngineCollision* _collisions)
	{
			float4 Monster = _This->GetActor()->Transform.GetLocalPosition();

			float4 Other_Monster = _collisions->GetActor()->Transform.GetLocalPosition();

			float4 Dir = Monster - Other_Monster;

			_This->GetActor()->Transform.AddLocalPosition(Dir * _Delta);
	} });*/

	if (nullptr != GameEngineNetWindow::Net)
	{
		if (0 != GetPacketCount())
		{

		}

	}

	
	
	PlayerState.Update(_Delta);

}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(50.0f, 50.0f);
	Capsule->SetPositioningComponent();

}

//void Player::CameraRotation(float Delta)
//{
//	Actor_test->Transform.SetWorldPosition({ Transform.GetWorldPosition() });
//
//	CameraPos = { GameEngineCore::MainWindow.GetMousePos().X,GameEngineCore::MainWindow.GetMousePos().Y };
//	CameraPos.Normalize();
//
//	Mouse_Ro_X = GameEngineCore::MainWindow.GetMousePos().X;
//	Mouse_Ro_Y = GameEngineCore::MainWindow.GetMousePos().Y;
//
//
//
//
//	if (PrevPos.Y > Mouse_Ro_Y && abs(Actor_test_02->Transform.GetLocalPosition().Z) >= 999)
//	{
//		Camera_Pos_Y += CameraPos.Y * Delta * 700;
//
//		if (Camera_Pos_Y >= 60)
//		{
//			Camera_Pos_Y -= CameraPos.Y * Delta * 700;
//		}
//	}
//
//	else if (PrevPos.Y < Mouse_Ro_Y && abs(Actor_test_02->Transform.GetLocalPosition().Z) >= 999)
//	{
//		Camera_Pos_Y -= CameraPos.Y * Delta * 700;
//
//		if (Camera_Pos_Y <= 0)
//		{
//			Camera_Pos_Y = 0;
//		}
//	}
//
//
//	if (PrevPos.X > Mouse_Ro_X)
//	{
//		Camera_Pos_X += CameraPos.X * Delta * 700;
//	}
//
//	else if (PrevPos.X < Mouse_Ro_X)
//	{
//		Camera_Pos_X -= CameraPos.X * Delta * 700;
//	}
//
//
//	
//
//	
//
//
//	PrevPos.Y = Mouse_Ro_Y;
//	PrevPos.X = Mouse_Ro_X;
//
//	Actor_test->Transform.SetWorldRotation({ Camera_Pos_Y,Camera_Pos_X,0.0f });
//
//	// ¸¶¿ì½º °íÁ¤ÇÏ°í ½ÍÀ»‹š 
//
//	/*if (Time > 0.1)
//	{
//		Time = 0;
//
//		PrevPos.Y = 258;
//		PrevPos.X = 864;
//		GameEngineCore::MainWindow.SetMousePos(1280, 720);
//	}*/
//
//
//	GetLevel()->GetMainCamera()->Transform.SetWorldRotation(Actor_test_02->Transform.GetWorldRotationEuler());
//	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(Actor_test_02->Transform.GetWorldPosition());
//
//}

void Player::ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet)
{
	int a = 0;
}

