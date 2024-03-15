#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "math.h"

// 서버용
#include "GameEngineNetWindow.h"
#include "Player_HitInteraction.h"
#include "BoneSocketCollision.h"
#define Frame 0.033f

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
	BaseActor::Start(); 
	
	Main_Player = this;

	GameEngineInput::AddInputObject(this);
	

	
	Capsule = CreateComponent<GameEnginePhysXCapsule>(Enum_CollisionOrder::Player);
	Capsule->PhysXComponentInit(50.0f, 50.0f);
	Capsule->SetPositioningComponent();

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
	MainRenderer->CreateFBXAnimation("String_Jump", "004220.FBX", { Frame, true });

	

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
	MainRenderer->CreateFBXAnimation("Roll_Forward", "004280.FBX", { Frame, true });
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
	MainRenderer->CreateFBXAnimation("Sit_Down", "068010.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("Stand_Up", "068012.FBX", { Frame, false });

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
	MainRenderer->CreateFBXAnimation("Attack_Block", "034200.FBX", { Frame, false }); 


	MainRenderer->CreateFBXAnimation("ladder_Fast_Down_Stop", "028002.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("fail", "004000.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("landing", "004210.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("ladder_Fast_Down_Start", "028000.FBX", { Frame, false });
	MainRenderer->CreateFBXAnimation("ladder_Fast_Down", "028001.FBX", { Frame, false });



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

	MainRenderer->SetRootMotion("ladder_Up_Start");

	MainRenderer->SetRootMotion("ladder_Up_Left");
	MainRenderer->SetRootMotion("ladder_Up_Right");

	MainRenderer->SetRootMotion("ladder_Up_Stop_Left");
	MainRenderer->SetRootMotion("ladder_Up_Stop_Right");
	//MainRenderer->SetRootMotion("Parri");

	




	MainRenderer->SetRootMotion("ladder_Down_Start");

	MainRenderer->SetRootMotion("ladder_Down_Left");
	MainRenderer->SetRootMotion("ladder_Down_Right");

	MainRenderer->SetRootMotion("ladder_Down_Stop_Left");
	MainRenderer->SetRootMotion("ladder_Down_Stop_Right");
	



	//MainRenderer->SetRootMotion("ladder_Fast_Down_Start");
	MainRenderer->SetRootMotion("ladder_Fast_Down");
	MainRenderer->SetRootMotion("ladder_Fast_Down_Stop");
	MainRenderer->SetRootMotion("fail");
	//MainRenderer->SetRootMotion("landing");

	// 중력 x 

	//MainRenderer->SetRootMotionGravityFlag("ladder_Fast_Down_Start", true);

	MainRenderer->SetRootMotionGravityFlag("ladder_Fast_Down", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Fast_Down_Stop", true);

	MainRenderer->SetRootMotionGravityFlag("ladder_Up_Stop_Left", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Up_Stop_Right", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Up_Left", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Up_Right", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Up_Start", true);


	MainRenderer->SetRootMotionGravityFlag("ladder_Down_Stop_Left", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Down_Stop_Right", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Down_Left", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Down_Right", true);
	MainRenderer->SetRootMotionGravityFlag("ladder_Down_Start", true);


	
	{
		
		Weapon_Actor = GetLevel()->CreateActor<Weapon>();

		Weapon_Actor->Transform.SetWorldRotation({ 0.0f, 0.0f, -90.0f });


		Shield_Actor = GetLevel()->CreateActor<shield>();
		Shield_Actor->Transform.SetWorldRotation({ 0.0f, 0.0f, -90.0f });

		
	}



	



	BSCol_TransitionParameter ColParameter;

	
	{

		ColParameter.R = 0.0f;
		ColParameter.S = { 20.f, 110.f, 20.f };
		ColParameter.T = { 0.f, 0.5f, 0.f };

		Attack_Col = CreateSocketCollision(Enum_CollisionOrder::Player_Attack, Bone_index_01, ColParameter,"Player_Weapon");
		Attack_Col->SetCollisionType(ColType::AABBBOX3D);
		//Attack_Col->Transform.SetLocalScale({ 20.f,60.f, 20.f });

		Attack_Col->On();
	}


	{

		ColParameter.R = 0.0f;
		ColParameter.S = { 50.f, 120.f, 40.f };
		//ColParameter.S = { 300.f, 300.f, 300.f };
		ColParameter.T = { 0.f, 0.8f, 0.f };

		Body_Col = CreateSocketCollision(Enum_CollisionOrder::Player_Body, 0, ColParameter, "Player_Body");
		Body_Col->SetCollisionType(ColType::AABBBOX3D);
		//Body_Col->Transform.SetLocalScale({ 100.f,120.f, 30.f });
		Body_Col->On();

	}
	{
		Player_Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player);
		Player_Col->SetCollisionType(ColType::SPHERE3D);
		Player_Col->Transform.SetLocalScale({ 10.f,10.f, 10.f });

	}

	{
		Arround_Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Player_Arround);
		Arround_Col->SetCollisionType(ColType::SPHERE3D);
		Arround_Col->Transform.SetLocalScale({ 2000.f,2000.f, 2000.f});
		//Arround_Col->Off();
	}

	{
		ColParameter.R = 0.0f;
		ColParameter.S = { 80.f, 80.f, 80.f };
		//ColParameter.S = { 300.f, 300.f, 300.f };
		ColParameter.T = { 0.0f, 0.0f, 0.0f };

		Shield_Col = CreateSocketCollision(Enum_CollisionOrder::Player_Shield, 18, ColParameter);
		Shield_Col->SetCollisionType(ColType::SPHERE3D);
		//Shield_Col->Transform.SetLocalScale({ 80.f,80.f, 80.f });
		Shield_Col->Off();
	}


	{
		Parring_Attack_Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Parring_Arround);
		Parring_Attack_Col->SetCollisionType(ColType::SPHERE3D);
		Parring_Attack_Col->Transform.SetLocalScale({ 300.f,300.f, 300.f });
		Parring_Attack_Col->Off();
	}

	Stat.SetHp(100);
	Stat.SetAtt(20);

	Sword.Init(this, Attack_Col.get());
	
	MainRenderer->AddNotBlendBoneIndex(53);

	Transform.SetLocalPosition({ 0.0f,-300.0f });
	Player_State();

	Transform.AddLocalPosition({ 0.0f,-300.0f });
	
	GameEngineCore::MainWindow.SetMousePos(960,540);

	{
		Actor_test = GetLevel()->CreateActor<GameEngineActor>();		
	}

	{
		Actor_test_02 = GetLevel()->CreateActor<GameEngineActor>();
		Actor_test_02->SetParent(Actor_test);
	

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


			if (Stat.GetPoise() <= 0)
			{
				if (Monster_Degree >= 135)
				{
					if (Monster_Degree <= 180)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);
					}
				}
				if (Monster_Degree >= -180)
				{
					if (Monster_Degree < -135)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);
					}
				}

				if (Monster_Degree <= 135)
				{
					if (Monster_Degree > 45)
					{
						//Collision_Up_drop();

						PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);

					}
				}

				if (Monster_Degree <= 45)
				{
					if (Monster_Degree > -45)
					{
						//Collision_Down_drop();
						PlayerStates.ChangeState(PlayerState::Forward_Big_Hit);

					}
				}
				if (Monster_Degree >= -135)
				{
					if (Monster_Degree < -45)
					{
						//Collision_Right_drop();
						PlayerStates.ChangeState(PlayerState::Backward_Big_Hit);
					}
				}
			}

			else if (Stat.GetPoise() > 50)
			{
				if (Monster_Degree >= 135)
				{
					if (Monster_Degree <= 180)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Hit);
					}
				}
				if (Monster_Degree >= -180)
				{
					if (Monster_Degree < -135)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Hit);
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
						PlayerStates.ChangeState(PlayerState::Backward_Hit);

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
			}

			else if (Stat.GetPoise() < 50)
			{
				if (Monster_Degree >= 135)
				{
					if (Monster_Degree <= 180)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Middle_Hit);
					}
				}
				if (Monster_Degree >= -180)
				{
					if (Monster_Degree < -135)
					{
						PlayerStates.ChangeState(PlayerState::Forward_Middle_Hit);
					}
				}

				if (Monster_Degree <= 135)
				{
					if (Monster_Degree > 45)
					{
						//Collision_Up_drop();

						PlayerStates.ChangeState(PlayerState::Right_Middle_Hit);

					}
				}

				if (Monster_Degree <= 45)
				{
					if (Monster_Degree > -45)
					{
						//Collision_Down_drop();
						PlayerStates.ChangeState(PlayerState::Backward_Middle_Hit);

					}
				}
				if (Monster_Degree >= -135)
				{
					if (Monster_Degree < -45)
					{
						//Collision_Right_drop();
						PlayerStates.ChangeState(PlayerState::Left_Middle_Hit);
					}
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
			
		};

	Labber_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

			if (Rabber_Collision_Check == false)
			{
				if (GameEngineInput::IsDown('E', this))
				{


					float4 TargetPos = col->Transform.GetWorldPosition();
					float4 MyPos = Actor_test->Transform.GetWorldPosition();

					// Y축 고려 X
					TargetPos.Y = MyPos.Y = 0.f;

					float4 FrontVector = float4(0.f, 0.f, -1.f, 0.f);
					FrontVector.VectorRotationToDegY(Capsule->GetDir());

					float4 LocationVector = (TargetPos - MyPos).NormalizeReturn();

					float4 Angle_ = DirectX::XMVector3AngleBetweenNormals(FrontVector.DirectXVector, LocationVector.DirectXVector);

					float4 RotationDir = DirectX::XMVector3Cross(FrontVector.DirectXVector, LocationVector.DirectXVector);

					Labber_Angle = Angle_.X * GameEngineMath::R2D;

					if (0.0f <= RotationDir.Y)
					{

					}
					else
					{
						Labber_Angle *= -1.f;
					}

					

					//Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
					Capsule->SetWorldRotation({ 0.0f, -Labber_Angle,0.0f });
					Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
					Capsule->GravityOff(); 
					//Capsule->MoveForce(float4{ 0.0f,500.0f,0.0f,Labber_Angle });
					PlayerStates.ChangeState(PlayerState::ladder_Up_Start);				
					Rabber_Collision_Check = true;
				}
			}
			
			

		};


	

	Labber_Middle_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};

	Labber_Middle_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};

	Labber_Middle_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

			if (StateValue == PlayerState::ladder_Up_Left)
			{
				PlayerStates.ChangeState(PlayerState::ladder_Up_Stop_Right);
			}
			else if(StateValue == PlayerState::ladder_Up_Right)
			{
				PlayerStates.ChangeState(PlayerState::ladder_Up_Stop_Left);
			}




		};




	Labber_Top_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{

		};

	Labber_Top_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			if (Rabber_Collision_Check == false)
			{
				if (GameEngineInput::IsDown('E', this))
				{
					float4 TargetPos = col->Transform.GetWorldPosition();
					float4 MyPos = Actor_test->Transform.GetWorldPosition();

					float4 Dir = MyPos-TargetPos;
					float4 Monster = { 0,0,-1 };
					float Dot = float4::DotProduct3D(Dir.NormalizeReturn(), Monster);
					float radian = atan2(Dir.X, Dir.Z) - atan2(Monster.X, Monster.Z);
					Labber_Angle = float(radian * (180.0 / 3.141592));

					//Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
					Capsule->SetWorldRotation({ 0.0f,Labber_Angle,0.0f });
					Capsule->SetWorldPosition(col->Transform.GetWorldPosition());
					Capsule->GravityOff();
					//MainRenderer->SetRootMotionMode(")
					//Capsule->MoveForce(float4{ 0.0f,500.0f,0.0f,Labber_Angle });
					PlayerStates.ChangeState(PlayerState::ladder_Down_Start);
					Rabber_Collision_Check = true;
				}
			}
		};

	Labber_Top_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{


		};


	Arround_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			
			Monster_Actor.push_back(col->GetActor());
			
		};

	Arround_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			
		
			Rock_on_Time_Check = true;

		};

	Arround_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			for (size_t i = 0; i < Monster_Actor.size(); i++) 
			{
				if (Monster_Actor[i] == col->GetActor())// ?? 이게 왜 되지?? 아니 개 위험한거 아닌가? 클래스 크기값 다르면 조지는데 망하면 다른걸로하지뭐 
				{
					Monster_Actor.erase(Monster_Actor.begin()+i);
				}
			}		
		};

	//SoundFrameEvent();
	Shield_Col->Off();
	Attack_Col->Off(); 
}

void Player::Update(float _Delta)
{



	Parring_Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			Parring_Monster_Actor.push_back(col->GetActor());
		};

	Parring_Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{


			const std::shared_ptr<BaseActor>& pActor = col->GetActor()->GetDynamic_Cast_This<BaseActor>();
			const float4 WRot = Transform.GetWorldRotationEuler();
			const float4 WPos = Transform.GetWorldPosition();
			bool CheckFrontStab = pActor->FrontStabCheck(WPos, WRot.Y);

				if (GameEngineInput::IsDown('E', this))
				{
					//pActor->DebugFlag();

					if (pActor->IsFlag(Enum_ActorFlag::Groggy) == true)
					{
						PlayerStates.ChangeState(PlayerState::Parring_Attack);
						const float4 StabPos = pActor->GetFrontStabPosition();
						Transform.SetWorldPosition(StabPos + float4::UP * 150.0f);
						Transform.SetWorldRotation(WRot);
						pActor->Damage(3000);
						pActor->SetHit(true);
						pActor->SetFlag(Enum_ActorFlag::FrontStab, true);
					}
				}
			
		};

	Parring_Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
		{
			
		};
	BaseActor::Update(_Delta);

	// 시간 
	Poise_Time += _Delta;
	Delta_Time = _Delta;
	Time += _Delta;

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


	// 충돌 
	Sword.CollisionToBody(Enum_CollisionOrder::Monster_Body,0);
	Sword.CollisionToShield(Enum_CollisionOrder::Monster_Shield, 0);

	Arround_Col->CollisionEvent(Enum_CollisionOrder::Monster, Arround_Event);
	Body_Col->CollisionEvent(Enum_CollisionOrder::MonsterAttack, Body_Event);
	Body_Col->CollisionEvent(Enum_CollisionOrder::LadderBot, Labber_Event);
	Body_Col->CollisionEvent(Enum_CollisionOrder::LadderTop, Labber_Event);
	Parring_Attack_Col->CollisionEvent(Enum_CollisionOrder::Monster_Body, Parring_Event);

	if (Body_Col->Collision(Enum_CollisionOrder::LadderTop))
	{
		if (GameEngineInput::IsDown('E', this))
		{
			Body_Col->CollisionEvent(Enum_CollisionOrder::LadderTop, Labber_Event);
			PlayerStates.ChangeState(PlayerState::ladder_Down_Start);
		}
	}
	

	if (true == IsFlag(Enum_ActorFlag::Block_Shield))
	{
		PlayerStates.ChangeState(PlayerState::Attack_Block);
	}
	
	// 일단 두자 
	if (Rock_on_Time_Check == true)
	{
		Rock_on_Time += Delta_Time;
	}
	
	// 경직도 
	if (Poise_Time > 1.0)
	{
		Stat.SetPoise(100);
	}

	if (StateValue != PlayerState::StaminaCheck || StateValue != PlayerState::Parrying || StateValue != PlayerState::Shield_Idle)
	{
		if (Stamina < 100)
		{
			Stamina += _Delta * 10;
		}
	}

	
	// 디버그용 
	if (GameEngineInput::IsPress('N', this))
	{
		Capsule->MoveForce({ 0.0f,200.0f,0.0f },Capsule->GetDir());
	}

	if (GameEngineInput::IsDown('H', this))
	{
		PlayerStates.ChangeState(PlayerState::Idle);
	}

	float4 WorldMousePos = { Actor_test_02->Transform.GetWorldRotationEuler() };
	float4 WorldMousePos2 = { degree_X };

	OutputDebugStringA(WorldMousePos2.ToString("\n").c_str());
	OutputDebugStringA(WorldMousePos.ToString("\n").c_str());

	


	// 무기 방패 트랜스폼 

	{
		AnimationBoneData Data = MainRenderer->GetBoneData(Bone_index_01);
		Weapon_Actor->Transform.SetLocalRotation(Data.RotQuaternion.QuaternionToEulerDeg());
		Weapon_Actor->Transform.SetWorldPosition(Data.Pos + float4{ Capsule->GetWorldPosition().x, Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	}

	{
		AnimationBoneData Data = MainRenderer->GetBoneData(Bone_index_02);
		Shield_Actor->Transform.SetLocalRotation(Data.RotQuaternion.QuaternionToEulerDeg());
		Shield_Actor->Transform.SetWorldPosition(Data.Pos + float4{ Capsule->GetWorldPosition().x, Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	}


	/*if (Capsule->GetLinearVelocity_f().Y <= -1200)
	{
		PlayerStates.ChangeState(PlayerState::fail);
	}*/


	


	// 각도 계산 
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

	// 락온계산 

	if (GameEngineInput::IsDown('Q', this) && Rock_On_Check == false && Rock_on_Time_Check ==true)
	{
		for (size_t i = 0; i < Monster_Actor.size(); i++)
		{

			float MonsterAngle;
			float4 TargetPos = Monster_Actor[i]->Transform.GetWorldPosition();
			float4 MyPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition(); 

			// Y축 고려 X
			TargetPos.Y = MyPos.Y = 0.f;

			float4 FrontVector = float4(0.f, 0.f, -1.f, 0.f);
			FrontVector.VectorRotationToDegY(Cameracapsule->Capsule_02->GetDir());

			float4 LocationVector = (TargetPos - MyPos).NormalizeReturn();

			float4 Angle_ = DirectX::XMVector3AngleBetweenNormals(FrontVector.DirectXVector, LocationVector.DirectXVector);

			float4 RotationDir = DirectX::XMVector3Cross(FrontVector.DirectXVector, LocationVector.DirectXVector);

			MonsterAngle = Angle_.X * GameEngineMath::R2D;

			if (0.0f <= RotationDir.Y)
			{

			}
			else
			{
				MonsterAngle *= -1.f;
			}




			if (MonsterAngle >= 135)
			{
				if (MonsterAngle <= 180)
				{
					MonsterAngles.push_back(static_cast<int>(i));

				}
			}
			if (MonsterAngle >= -180)
			{
				if (MonsterAngle < -135)
				{
					MonsterAngles.push_back(static_cast<int>(i));
				}
			}

		}

		for (int i = 0; i < static_cast<int>(MonsterAngles.size()); i++)
		{
			float Check = abs(Transform.GetWorldPosition().Z -Monster_Actor[MonsterAngles[i]]->Transform.GetWorldPosition().Z);


			if (i > 0)
			{
				if (Check < Monser_Dir)
				{
					Monser_Dir = Check;

					Number = i;
				}
			}
			else
			{
				Monser_Dir = Check;
				Number = 0;
			}
		}
		if (MonsterAngles.size() != 0)
		{
			SetTargeting(Monster_Actor[MonsterAngles[Number]]);
			PlayerStates.ChangeState(PlayerState::RockOn);
		}


	}
	else if (GameEngineInput::IsDown('Q', this) && Rock_On_Check == true && Rock_on_Time_Check == true)
	{
		MonsterAngles.clear(); 
		Rock_on_Time = 0;
		Rock_on_Time_Check = false;

		Rock_On_Check = false;
		Camera_Pos_Y = 0;
		Player_Pos.X = degree_X;
	}


	if (GetTargetPointer() != nullptr)
	{
		float4 Dir = GetTargetPos() - GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
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
	

	// 애니메이션 업데이트 

	PlayerStates.Update(_Delta);



	std::function StabCollisionEvent = [=](std::vector<GameEngineCollision*>& _Other)
		{



			for (GameEngineCollision* pCol : _Other)
			{
				
			}
		};

	if (GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		int a = 0;
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


	


	


	if (PrevPos.Y > Mouse_Ro_Y)
	{
		float4 Cur_Camera_Pos = { 0.0f, PrevPos.Y - Mouse_Ro_Y,0.0f };

		float4 Lerp = float4::LerpClamp(0, Cur_Camera_Pos, Delta);


		Camera_Pos_Y -= Lerp.Y *10;

		if (Camera_Pos_Y <= -50)
		{
			Camera_Pos_Y += Lerp.Y * 10;
		}
	}

	else if (PrevPos.Y < Mouse_Ro_Y)
	{
		float4 Cur_Camera_Pos = { 0.0f, Mouse_Ro_Y- PrevPos.Y,0.0f };


		float4 Lerp = float4::LerpClamp(0, Cur_Camera_Pos, Delta);

		//Cur_Camera_Pos.Normalize();

		Camera_Pos_Y += Lerp.Y * 10;

		
		if (Camera_Pos_Y >= 60)
		{
			Camera_Pos_Y -= Lerp.Y  * 10;
		}

	}

	if (PrevPos.X > Mouse_Ro_X)
	{

		float4 Cur_Camera_Pos = { PrevPos.X - Mouse_Ro_X,0.0f,0.0f };

		float4 Lerp = float4::LerpClamp(0, Cur_Camera_Pos, Delta);
		//Cur_Camera_Pos.Normalize();



		Camera_Pos_X += Lerp.X * 20;
		Player_Pos.X -= Lerp.X * 20;

		if ((StateValue == PlayerState::Run || StateValue == PlayerState::Move) && Rotation_Check_X == true && Rock_On_Check == false)
		{
			Capsule->AddWorldRotation({ 0.0f,-Lerp.X * 20,0.0f });

		}
	}
	else if (PrevPos.X < Mouse_Ro_X)
	{

		float4 Cur_Camera_Pos = { Mouse_Ro_X - PrevPos.X,0.0f,0.0f };

		float4 Lerp = float4::LerpClamp(0, Cur_Camera_Pos, Delta);
		//Cur_Camera_Pos.Normalize();

		Camera_Pos_X -= Lerp.X * 20;
		Player_Pos.X += Lerp.X * 20;



		if ((StateValue == PlayerState::Run || StateValue == PlayerState::Move) && Rotation_Check_X == true && Rock_On_Check == false)
		{
			Capsule->AddWorldRotation({ 0.0f, Lerp.X * 20, 0.0f });
		}
	}


	float4 sadasd = float4::LerpClamp(Actor_test_02->Transform.GetWorldPosition(),Actor_test->Transform.GetWorldPosition(), Delta*5);
	float4 sadassd = float4::LerpClamp(Actor_test_02->Transform.GetWorldPosition(), Actor_test->Transform.GetWorldPosition(), -Delta*5);

	
	//140.0f, -300.0f



	

	if (testa == true)
	{


		//if (abs(Actor_test->Transform.GetWorldPosition().Z - Actor_test_02->Transform.GetWorldPosition().Z) >= 50)
		{
			//float4 sadasd = float4::LerpClamp(Actor_test_02->Transform.GetWorldPosition(),Actor_test->Transform.GetWorldPosition(), Delta);
			Actor_test_02->Transform.SetWorldPosition(sadasd);
		}
	}


	if (testaa == false)
	{
		
		if (abs(Actor_test_02->Transform.GetLocalPosition().Z) < abs(250))
		{
			//float4 sadasd = float4::LerpClamp(Actor_test->Transform.GetWorldPosition(), Actor_test_02->Transform.GetWorldPosition(), Delta);
			//sadasd.Normalize();
			Actor_test_02->Transform.SetWorldPosition(sadassd);
		}
		
	}

	// 다음 프레임에 콜리전이 충돌한 포지션이면 멈춰 






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

			PrevPos.Y = 540;
			PrevPos.X = 960;
			GameEngineCore::MainWindow.SetMousePos(960, 540);
		}

	}
	

	else
	{

	}



	//Actor_test->Transform.SetLocalPosition({ Capsule->GetWorldPosition().x,Capsule->GetWorldPosition().y, Capsule->GetWorldPosition().z });
	GetLevel()->GetMainCamera()->Transform.SetWorldRotation(Actor_test_02->Transform.GetWorldRotationEuler());
	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(Actor_test_02->Transform.GetWorldPosition());

	


}

bool Player::GetHit(const HitParameter& _Para /*= HitParameter()*/)
{
	Poise_Time = 0; 

	if (nullptr == _Para.pAttacker)
	{
		MsgBoxAssert("공격자를 모르고 사용할 수 없는 기능입니다.");
		return false;
	}

	/*if (true == Hit.IsHit())
	{
		return false;
	}*/
	BaseActor* pAttacker = _Para.pAttacker;


	const int AttackerAtt = pAttacker->GetAtt();
	const int Stiffness = _Para.iStiffness;

	Stat.AddPoise(-Stiffness);
	Stat.AddHp(-AttackerAtt);

	//Hit.SetHit(true);
	


	return true;
}

bool Player::GetHitToShield(const HitParameter& _Para /*= HitParameter()*/)
{
	

	if (nullptr == _Para.pAttacker)
	{
		MsgBoxAssert("공격자의 포인터를 모르고 사용할 수 없는 기능입니다.");
		return false;
	}

	/*if (true == Hit.IsHit())
	{
		return false;
	}*/

	BaseActor* pAttacker = _Para.pAttacker;

	// 패링상태
	if (StateValue == PlayerState::Parrying)
	{		
	
		pAttacker->SetHit(true);
		pAttacker->SetFlag(Enum_ActorFlag::Break_Posture, true);
		return true;
	}
	

	if (StateValue == PlayerState::Shield_Idle)
	{
		const int AttackerAtt = pAttacker->GetAtt();
		const int Stiffness = _Para.iStiffness;
		Stat.AddPoise(-Stiffness);

		Stamina -= pAttacker->GetAtt();


		if (0 >= Stamina)
		{
			PlayerStates.ChangeState(PlayerState::Big_Shield_block);
		}


		else
		{
			const int PassPoise = 50;
			if (Stiffness < PassPoise)
			{
				pAttacker->SetHit(true);
				pAttacker->SetFlag(Enum_ActorFlag::Block_Shield, true);
			}

			Hit.SetGuardSuccesss(true);
		}

		//const int FinalDamage = -10;
		//Stat.AddHp(FinalDamage);
		//Hit.SetHit(true);

		return true;
	}
	
	return false;
}