#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "math.h"

// 서버용
#include "GameEngineNetWindow.h"
#include "Player_HitInteraction.h"
#include "BoneSocketCollision.h"
#define Frame 0.033f
#define cdcdc 0.05f
Player* Player::Main_Player;

Player::Player()
{
	SetID(Enum_ActorType::Player);

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
	
	Cameracapsule = GetLevel()->CreateActor<CameraCapsule>(0,"Camera");




	MainRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	MainRenderer->Transform.SetLocalScale({ 100, 100, 100 });
	//MainRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//MainRenderer->Transform.SetLocalPosition({ 0.0f, -300.0f, 0.0f });

	
	BoneName = "R_Hand";

	
	MainRenderer->SetFBXMesh("c0010.FBX", "FBX_Animation"); // Bone 136
	

	
	MainRenderer->CreateFBXAnimation("Idle", "00000.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Shield_Idle", "00100.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Waek_jump", "004200.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Middle_jump", "004210.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("String_Jump", "004220.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Roll_Forward", "004280.FBX", { Frame, true });
	MainRenderer->CreateFBXAnimation("Hit_right", "005000.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Hit_Left", "005001.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Hit_Forward", "005002.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Hit_Behind", "005003.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Left", "005100.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Right", "005101.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Forward", "005102.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Middle_Hit_Behind", "005203.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("String_Hit_Forward", "005300.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("String_Hit_Behind", "005303.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Run15", "017002.FBX", { Frame, true }); // 에니메이션이 돌아감 
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
	MainRenderer->CreateFBXAnimation("Big_Shield_block", "019500.FBX", { Frame, true });

	MainRenderer->CreateFBXAnimation("Left_Stop", "022102.FBX", { Frame, false }); // 왼쪽 멈춤 
	MainRenderer->CreateFBXAnimation("Behind_Stop", "022101.FBX", { Frame, false }); // 뒤 멈춤 
	MainRenderer->CreateFBXAnimation("Right_Stop", "022103.FBX", { Frame, false }); // 오른쪽 멈춤 
	MainRenderer->CreateFBXAnimation("Forward_Stop", "022200.FBX", { Frame, false }); // 앞 멈춤 
	MainRenderer->CreateFBXAnimation("Shield_Move", "023100.FBX", { Frame, true }); // 쉴드 움직임 안됨 



	MainRenderer->CreateFBXAnimation("Death", "017140.FBX", { Frame, false }); // 죽음

	MainRenderer->CreateFBXAnimation("ladder_Up_Start", "028100.FBX", { Frame, false }); // 사다리 올라가기 시작

	MainRenderer->CreateFBXAnimation("ladder_Up_Left", "028011.FBX", { Frame, false }); // 사다리 오름 왼발?
	MainRenderer->CreateFBXAnimation("ladder_Up_Right", "028012.FBX", { Frame, false }); // 사다리 오름 오른발?

	MainRenderer->CreateFBXAnimation("ladder_Up_Stop_Left", "028013.FBX", { Frame, false }); // 사다리 올라가기 외발?
	MainRenderer->CreateFBXAnimation("ladder_Up_Stop_Right", "028014.FBX", { Frame, false }); //  사다리 올라가기 외발?

	MainRenderer->CreateFBXAnimation("ladder_Down_Start", "028020.FBX", { Frame, false }); // 사다리 내려가기 시작 

	MainRenderer->CreateFBXAnimation("ladder_Down_Left", "028021.FBX", { Frame, false }); //사다리 내려가기 왼발?
	MainRenderer->CreateFBXAnimation("ladder_Down_Right", "028022.FBX", { Frame, false }); // 사다리 내려가기 오른발?

	MainRenderer->CreateFBXAnimation("ladder_Down_Stop_Left", "028023.FBX", { Frame, false }); // 사다리 내려가기 왼발?
	MainRenderer->CreateFBXAnimation("ladder_Down_Stop_Right", "028024.FBX", { Frame, false }); // 사다리 내려가기 오른발?




	MainRenderer->CreateFBXAnimation("Parry_Attack", "030400.FBX", { Frame, false }); // 패링후 공격 



	MainRenderer->ChangeAnimation("Shield_Idle");
	

	MainRenderer->SetRootMotionComponent(Capsule.get());

	
	

	//MainRenderer->SetRootMotion("Walk_Forward","",Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Roll_Forward");

	//MainRenderer->SetRootMotion("Weak_Shield_block", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Middle_Shield_block", "", Enum_RootMotionMode::RealTimeDir);

	MainRenderer->SetRootMotion("Slow_Walk_Forward", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Slow_Walk_Behind", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Slow_Walk_Right", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Slow_Walk_Left", "", Enum_RootMotionMode::RealTimeDir);

	//MainRenderer->SetRootMotion("Walk_Right", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Walk_Left", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Slow_Shield_Move", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Run", "", Enum_RootMotionMode::RealTimeDir);

	//MainRenderer->SetRootMotion("Back_Step", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Roll_Behind", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Roll_Right", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Roll_Left", "", Enum_RootMotionMode::RealTimeDir);

//	MainRenderer->SetRootMotion("Weapon_Draw", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Shield_Draw", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Attack_01" ,"", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Attack_02", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Attack_03", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Attack_04", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Attack_05", "", Enum_RootMotionMode::RealTimeDir);

	MainRenderer->SetRootMotion("Open_Door", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("String_Block", "", Enum_RootMotionMode::RealTimeDir);  // 2게?
//	MainRenderer->SetRootMotion("Parrying_Attack", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("DownAttack", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Parrying", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Portion_Drink_01", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Portion_Drink_02", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Portion_Drink_03", "", Enum_RootMotionMode::RealTimeDir);

//	MainRenderer->SetRootMotion("Left_Stop", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Behind_Stop", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Right_Stop", "", Enum_RootMotionMode::RealTimeDir);
//	MainRenderer->SetRootMotion("Forward_Stop", "", Enum_RootMotionMode::RealTimeDir);



	//MainRenderer->Off();



	//MainRenderer->SetRootMotion("Hit_right", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Hit_Left", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Hit_Forward", "", Enum_RootMotionMode::RealTimeDir);
	//MainRenderer->SetRootMotion("Hit_Behind", "", Enum_RootMotionMode::RealTimeDir);

	MainRenderer->SetRootMotion("Middle_Hit_Left", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Middle_Hit_Right", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Middle_Hit_Forward", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("Middle_Hit_Behind", "", Enum_RootMotionMode::RealTimeDir);

	/*MainRenderer->SetRootMotion("String_Hit_Forward","", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("String_Hit_Behind", "", Enum_RootMotionMode::RealTimeDir);*/
	//MainRenderer->SetRootMotionMoveRatio("String_Hit_Forward");

	//MainRenderer->SetRootMotion("ladder_Up_Start");

	/*MainRenderer->SetRootMotion("ladder_Up_Left","", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("ladder_Up_Right", "", Enum_RootMotionMode::RealTimeDir);*/

	/*MainRenderer->SetRootMotion("ladder_Up_Stop_Left", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("ladder_Up_Stop_Right", "", Enum_RootMotionMode::RealTimeDir);*/

	/*MainRenderer->SetRootMotionMoveRatio("ladder_Up_Stop_Left",-1.0, cdcdc, -1.0);
	MainRenderer->SetRootMotionMoveRatio("ladder_Up_Stop_Right", -1.0, cdcdc, -1.0);*/

	MainRenderer->SetRootMotion("ladder_Down_Start", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Start", 0.2f, -0.01f, 0.2f);
	/*MainRenderer->SetRootMotion("ladder_Down_Left", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("ladder_Down_Right", "", Enum_RootMotionMode::RealTimeDir);*/

	MainRenderer->SetRootMotion("ladder_Down_Stop_Left", "", Enum_RootMotionMode::RealTimeDir);
	MainRenderer->SetRootMotion("ladder_Down_Stop_Right", "", Enum_RootMotionMode::RealTimeDir);
	

	/*MainRenderer->SetRootMotionMoveRatio("ladder_Up_Left", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Up_Right", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Up_Stop_Left", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Up_Stop_Right", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Start", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Left", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Right", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Stop_Left", cdcdc, cdcdc, cdcdc);
	MainRenderer->SetRootMotionMoveRatio("ladder_Down_Stop_Right", cdcdc, cdcdc, cdcdc);*/
	{
		//SwordActor = GetLevel()->CreateActor<GameEngineActor>();
		//SwordActor->Transform.SetLocalPosition({ 0.0f - 300.0f });
		Weapon_Actor = GetLevel()->CreateActor<Weapon>();

		Weapon_Actor->Transform.SetWorldRotation({ 0.0f, 0.0f, -90.0f });


		Shield_Actor = GetLevel()->CreateActor<shield>();
		Shield_Actor->Transform.SetWorldRotation({ 0.0f, 0.0f, -90.0f });

		//Weapon->SetFBXMesh("WP_A_0221.FBX", "FBXAnimationTexture");

		//Weapon->Transform.SetLocalScale({ 100, 100, 100 });
		////Weapon->Transform.SetLocalPosition({ -4.0f, -152.0f, 165.0f });
		//Weapon->Transform.SetLocalRotation({ 0.0f, 0.0f, 180.0f });
	}

	
	


	{
		Shield_Col = CreateSocketCollision(Enum_CollisionOrder::Player_Shield, 18);
		Shield_Col->SetCollisionType(ColType::SPHERE3D);
		Shield_Col->Transform.SetLocalScale({ 70.f,70.f, 50.f });
		Shield_Col->On();
	}
	



	BSCol_TransitionParameter ColParameter;

	
	{

		ColParameter.R = 0.0f;
		ColParameter.S = { 20.f, 60.f, 20.f };
		ColParameter.T = { 0.f, 0.5f, 0.f };

		Attack_Col = CreateSocketCollision(Enum_CollisionOrder::Player_Attack, Bone_index_01, ColParameter,"Player_Weapon");
		Attack_Col->SetCollisionType(ColType::AABBBOX3D);
		//Attack_Col->Transform.SetLocalScale({ 20.f,60.f, 20.f });

		Attack_Col->On();
	}


	{

		ColParameter.R = 0.0f;
		ColParameter.S = { 20.f, 60.f, 20.f };
		ColParameter.T = { 0.f, 0.8f, 0.f };

		Body_Col = CreateSocketCollision(Enum_CollisionOrder::Player, 0, ColParameter, "Player_Body");
		Body_Col->SetCollisionType(ColType::SPHERE3D);
		Body_Col->Transform.SetLocalScale({ 100.f,120.f, 30.f });
		Body_Col->On();
	}



	{
		Col = CreateComponent<GameEngineCollision>();
		Col->Transform.SetLocalScale({ 200.0f,200.0f });
	}

	/*Mini_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};
	Mini_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			std::shared_ptr<BaseActor> pActor = col->GetActor()->GetDynamic_Cast_This<BaseActor>();


			pActor->



		};

	Mini_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};*/
	
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
		//Actor_test_02->Transform.SetWorldPosition({ 0.0f,140.0f,-250.0f });

		Actor_test_02->Transform.SetLocalPosition({ 0.0f,0.0f,-250.0f });

	}


	// col

	
	
	GameEnginePhysX::PushSkipCollisionPair(2, Enum_CollisionOrder::Player, Enum_CollisionOrder::Camera);
	GameEnginePhysX::PushSkipCollisionPair(2, Enum_CollisionOrder::Player, Enum_CollisionOrder::Big_Camera);

	Body_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

			float4 TargetPos = col->GetActor()->Transform.GetWorldPosition(); 
			float4 MyPos = Actor_test->Transform.GetWorldPosition();

			// Y축 고려 X
			TargetPos.Y = MyPos.Y = 0.f;

			float4 FrontVector = float4(0.f, 0.f, -1.f, 0.f);
			FrontVector.VectorRotationToDegY(Capsule->GetDir());

			float4 LocationVector = (TargetPos - MyPos).NormalizeReturn();

			float4 Angle_ = DirectX::XMVector3AngleBetweenNormals(FrontVector.DirectXVector, LocationVector.DirectXVector);

			float4 RotationDir = DirectX::XMVector3Cross(FrontVector.DirectXVector, LocationVector.DirectXVector);

			Monster_Degree = Angle_.X * GameEngineMath::R2D;

			if (0.0f <= RotationDir.Y)
			{

			}
			else
			{
				Monster_Degree *= -1.f;
			}




			if (Monster_Degree >= 135)
			{
				if (Monster_Degree <= 180)
				{
					//Collision_Left_drop();
					PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);
				}
			}
			if (Monster_Degree >= -180)
			{
				if (Monster_Degree < -135)
				{
					//Collision_Left_drop();
					PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);
				}
			}

			if (Monster_Degree <= 135)
			{
				if (Monster_Degree > 45)
				{
					//Collision_Up_drop();

					PlayerStates.ChangeState(PlayerState::Right_Hit);

				}
			}

			if (Monster_Degree <= 45)
			{
				if (Monster_Degree > -45)
				{
					//Collision_Down_drop();
					PlayerStates.ChangeState(PlayerState::Backward_Big_Hit);

				}
			}
			if (Monster_Degree >= -135)
			{
				if (Monster_Degree < -45)
				{
					//Collision_Right_drop();
					PlayerStates.ChangeState(PlayerState::Left_Hit);

				}
			}



		};

	Body_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{






		};

	Body_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};


	Labber_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
		};

	Labber_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			if (Rabber_Collision_Check == false)
			{
				Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
				Rabber_Collision_Check = true;
			}
			
			Rabber_Collision_Check = false;

		};

	Labber_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			Rabber_Collision_Check = false;
		};


	SoundFrameEvent();

}

void Player::Update(float _Delta)
{

	if (GameEngineInput::IsDown('G', this))
	{
		PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);
	}

	


	BaseActor::Update(_Delta);


	//Body.CollisionToBody(Enum_CollisionOrder::Player);



	

	

	Body_Col->CollisionEvent(Enum_CollisionOrder::MonsterAttack, Body_Event);

	
	
	/*if (Body_Col->Collision(Enum_CollisionOrder::MonsterAttack))
	{
		Body.CollisionToBody(Enum_CollisionOrder::MonsterAttack);
	}*/


	if (Body_Col->Collision(Enum_CollisionOrder::LadderBot))
	{
		if (GameEngineInput::IsDown('E', this))
		{
			Body_Col->CollisionEvent(Enum_CollisionOrder::LadderBot, Labber_Event);
			Capsule->MoveForce({ 0.0f,500.0f,0.0f }, Capsule->GetDir());
			PlayerStates.ChangeState(PlayerState::ladder_Up_Left);

		}
	}
	
		
	
	
	if (Body_Col->Collision(Enum_CollisionOrder::LadderTop))
	{
		if (GameEngineInput::IsDown('E', this))
		{
			Body_Col->CollisionEvent(Enum_CollisionOrder::LadderTop, Labber_Event);
			//	Capsule->MoveForce({ 0.0f,-500.0f,0.0f }, Capsule->GetDir());
			PlayerStates.ChangeState(PlayerState::ladder_Down_Start);
		}
	}

	if (GameEngineInput::IsDown('H', this))
	{
		PlayerStates.ChangeState(PlayerState::Idle);
	}
	
	
	

	{
		AnimationBoneData Data = MainRenderer->GetBoneData(Bone_index_01);
		Weapon_Actor->Transform.SetLocalRotation(Data.RotQuaternion.QuaternionToEulerDeg());
		Weapon_Actor->Transform.SetWorldPosition(Data.Pos + float4{ Capsule->GetWorldPosition().x, Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	}
	//MainRenderer->G
	{
		AnimationBoneData Data = MainRenderer->GetBoneData(Bone_index_02);
		Shield_Actor->Transform.SetLocalRotation(Data.RotQuaternion.QuaternionToEulerDeg());
		Shield_Actor->Transform.SetWorldPosition(Data.Pos + float4{ Capsule->GetWorldPosition().x, Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	}
	Col->Off();
	








	Time += _Delta;



	{
		float4 TargetPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
		float4 MyPos = Actor_test->Transform.GetWorldPosition();

		// Y축 고려 X
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
	}

	if(GetTargetPointer() != nullptr)
	{
		float4 Dir = GetTargetPos() - Actor_test_02->Transform.GetWorldPosition();
		float4 Monster = { 0,0,0,-1.0f };
		float Dot = float4::DotProduct3D(Dir.NormalizeReturn(), Monster);
		float radian = atan2(Dir.X, Dir.Z) - atan2(Monster.X, Monster.Z);
		degree_X = float(radian * (180.0 / 3.141592));
	}


	if (GetTargetPointer() != nullptr)
	{
		float4 Dir = GetTargetPos() - Actor_test_02->Transform.GetWorldPosition();
		float4 Monster = { 0,0,0,-1.0f };
		float Dot = float4::DotProduct3D(Dir.NormalizeReturn(), Monster);
		float radian = atan2(Dir.Y, Dir.Z) - atan2(Monster.Y, Monster.Z);
		degree_Y = float(radian * (180.0 / 3.141592));
	}


	float4 WorldMousePos = { Capsule->GetWorldPosition().x,Capsule->GetWorldPosition().y,Capsule->GetWorldPosition().z };

	OutputDebugStringA(WorldMousePos.ToString("\n").c_str());

	
	
	
	PlayerStates.Update(_Delta);

	

	if (GameEngineInput::IsDown(VK_F1, this))
	{
		Cameratest = !Cameratest;
	}

	if (true == Cameratest)
	{
		int a = 0;
	}
	else if (false == Cameratest)
	{
		CameraRotation(_Delta);
	}
	
	


	

	if (GameEngineInput::IsDown('Q', this) && Rock_On_Check==false)
	{
		
		PlayerStates.ChangeState(PlayerState::RockOn);

	}
	else if (GameEngineInput::IsDown('Q', this) && Rock_On_Check == true)
	{
		Rock_On_Check = false;
		Camera_Pos_Y = 0;
		Player_Pos.X = degree_X;
	}



	

	



}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{

	{
		GameEngineDirectory Dir;
		Dir.SetCurrentPath();
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound\\c0010");
		std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

		for (int i = 0; i < AllFile.size(); i++)
		{
			GameEngineSound::Sound3DLoad(AllFile[i].GetStringPath());
		}
	}



	Capsule->PhysXComponentInit(50.0f, 50.0f);
	Capsule->SetPositioningComponent();

	Capsule->SetFiltering(Enum_CollisionOrder::Player, Enum_CollisionOrder::Camera);
	Capsule->SetFiltering(Enum_CollisionOrder::Player, Enum_CollisionOrder::Big_Camera);

	//Capsule->SetFiltering(Enum_CollisionOrder::Monster);
	//GameEnginePhysX::PushSkipCollisionPair(2, Enum_CollisionOrder::Monster, Enum_CollisionOrder::Map);

}

void Player::CameraRotation(float Delta)
{
	

	Actor_test->Transform.SetWorldPosition({ Capsule->GetWorldPosition().x,Capsule->GetWorldPosition().y+140.0f, Capsule->GetWorldPosition().z });




	CameraPos = { GameEngineCore::MainWindow.GetMousePos().X,GameEngineCore::MainWindow.GetMousePos().Y };
	CameraPos.Normalize();

	Mouse_Ro_X = GameEngineCore::MainWindow.GetMousePos().X;
	Mouse_Ro_Y = GameEngineCore::MainWindow.GetMousePos().Y;


	


	


	if (PrevPos.Y > Mouse_Ro_Y+5 )
	{
		float4 Cur_Camera_Pos = { 0.0f, PrevPos.Y - Mouse_Ro_Y,0.0f };

		Cur_Camera_Pos.Normalize();

		Camera_Pos_Y += Cur_Camera_Pos.Y * Delta * 200;

		if (Camera_Pos_Y >= 60)
		{
			Camera_Pos_Y -= Cur_Camera_Pos.Y * Delta * 200;
		}
	}

	else if (PrevPos.Y < Mouse_Ro_Y-5 )
	{
		float4 Cur_Camera_Pos = { 0.0f, Mouse_Ro_Y- PrevPos.Y,0.0f };

		Cur_Camera_Pos.Normalize();

		Camera_Pos_Y -= Cur_Camera_Pos.Y * Delta * 200;

		if (Camera_Pos_Y <= -50)
		{
			Camera_Pos_Y += Cur_Camera_Pos.Y * Delta * 200;
		}

	}

	if (PrevPos.X > Mouse_Ro_X)
	{

		float4 Cur_Camera_Pos = { PrevPos.X - Mouse_Ro_X,0.0f,0.0f };

		Cur_Camera_Pos.Normalize();

		Camera_Pos_X += Cur_Camera_Pos.X * Delta * 200;
		Player_Pos.X -= Cur_Camera_Pos.X * Delta * 200;

		if ((StateValue == PlayerState::Run || StateValue == PlayerState::Move) && Rotation_Check_X == true && Rock_On_Check == false)
		{
			Capsule->AddWorldRotation({ 0.0f,-Cur_Camera_Pos.X * Delta * 200,0.0f });

		}
	}
	else if (PrevPos.X < Mouse_Ro_X)
	{

		float4 Cur_Camera_Pos = { Mouse_Ro_X - PrevPos.X,0.0f,0.0f };

		Cur_Camera_Pos.Normalize();

		Camera_Pos_X -= Cur_Camera_Pos.X * Delta * 200;
		Player_Pos.X += Cur_Camera_Pos.X * Delta * 200;

		if ((StateValue == PlayerState::Run || StateValue == PlayerState::Move) && Rotation_Check_X == true && Rock_On_Check == false)
		{
			Capsule->AddWorldRotation({ 0.0f, Cur_Camera_Pos.X * Delta * 200, 0.0f });

		}
	}







	float4 ASDF = { Actor_test->Transform.GetWorldPosition().X,Actor_test->Transform.GetWorldPosition().Y,Actor_test->Transform.GetWorldPosition().Z };

	float4 ASsd	 = float4{ Actor_test_02->Transform.GetWorldPosition().X, Actor_test_02->Transform.GetWorldPosition().Y, Actor_test_02->Transform.GetWorldPosition().Z };

	float4 AS = ASDF - ASsd;


	int a = 0; 
	AS.Normalize();


	


	//140.0f, -300.0f


	

	if (testa == true)
	{


		if (abs(Actor_test->Transform.GetWorldPosition().Z - Actor_test_02->Transform.GetWorldPosition().Z) >= 20)
		{
			Actor_test_02->Transform.AddWorldPosition(AS * 1200 * Delta);
		}
	}

	/*if (testa == true && testaa == false)
	{
		Actor_test_02->Transform.AddWorldPosition(-AS * 800 * Delta);
	}*/

	if (testaa == false && testa == false)
	{
		
		if (abs(Actor_test_02->Transform.GetLocalPosition().Z) < abs(250))
		{
			Actor_test_02->Transform.AddWorldPosition(-AS * Delta * 1200);
		}
		
	}








	testaa = false;
	testa = false;


	




	//if (Camera_Pos_Y <= 0 && testa == false)
	//{

	//	if (PrevPos.Y < Mouse_Ro_Y)
	//	{
	//		Actor_test_02->Transform.AddWorldPosition(A * Delta * 300);

	//	}

	//	/*else if (PrevPos.Y > Mouse_Ro_Y)
	//	{
	//		Actor_test_02->Transform.AddWorldPosition(-A * Delta * 300);
	//	}*/
	//}


	PrevPos.Y = Mouse_Ro_Y;
	PrevPos.X = Mouse_Ro_X;




	if (Rock_On_Check == false)
	{
		Actor_test->Transform.SetWorldRotation({ Camera_Pos_Y,Player_Pos.X,0.0f });
	}


	// 마우스 고정하고 싶을떄 
	if (GameEngineInput::IsDown('Z', this))
	{
		IsFreeCameraValue = !IsFreeCameraValue;
	}

	if (true == IsFreeCameraValue)
	{
		if (Time > 0.01)
		{
			Time = 0;

			PrevPos.Y = 258;
			PrevPos.X = 864;
			GameEngineCore::MainWindow.SetMousePos(1280, 720);
		}

	}
	else
	{

	}


	//Actor_test->Transform.SetLocalPosition({ Capsule->GetWorldPosition().x,Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	GetLevel()->GetMainCamera()->Transform.SetWorldRotation(Actor_test_02->Transform.GetWorldRotationEuler());
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(Actor_test_02->Transform.GetWorldPosition());

	


}

