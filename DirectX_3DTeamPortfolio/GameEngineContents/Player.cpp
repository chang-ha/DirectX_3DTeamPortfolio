#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"


// 서버용
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

	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	FBXRenderer->Transform.SetLocalScale({ 400.0f, 400.0f, 400.0f });
	FBXRenderer->Transform.SetLocalPosition({ 0.0f, -300.0f, 0.0f });
	FBXRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });


	Weapon = CreateComponent<GameContentsFBXRenderer>();

	Col = CreateComponent<GameEngineCollision>();
	FBXRenderer->SetFBXMesh("c0010.FBX", "FBXAnimationTexture"); // Bone 136
	FBXRenderer->Transform.SetLocalScale({ 400.0f, 400.0f, 400.0f });
	FBXRenderer->Transform.SetLocalPosition({ 0.0f, -300.0f, 0.0f });
	FBXRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//	FBXRenderer->CreateFBXAnimation("Idle", "c0000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Idle", "00000.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Shield_Idle", "00100.FBX", { Frame, true });
	//FBXRenderer->CreateFBXAnimation("Run", "Ani001.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Waek_jump", "004200.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_jump", "004210.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("String_Jump", "004220.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Roll_Forward", "004280.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Hit_right", "005000.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Hit_Left", "005001.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Hit_Forward", "005002.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Hit_Behind", "005003.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Left", "005100.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Right", "005101.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Forward", "005102.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Behind", "005203.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("String_Hit_Forward", "005300.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("String_Hit_Behind", "005303.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Run15", "017002.FBX", { Frame, true }); // 에니메이션이 돌아감 
	FBXRenderer->CreateFBXAnimation("Weak_Shield_block", "019200.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Middle_Shield_block", "019210.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Forward", "020000.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Behind", "0200001.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Right", "0200002.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Left", "0200003.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Walk_Forward", "020100.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Walk_Behind", "020101.FBX", { Frame, true });

	FBXRenderer->CreateFBXAnimation("Walk_Right", "020102.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Walk_Left", "020103.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Slow_Shield_Move", "020140.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Run", "020200.FBX", { Frame, true });
	//FBXRenderer->CreateFBXAnimation("Shield_Move", "023050.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Back_Step", "027000.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Roll_Behind", "027101.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Roll_Right", "027102.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Roll_Left", "027103.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("portion_Down", "029029.FBX", { Frame, true }); // ?? 

	FBXRenderer->CreateFBXAnimation("Weapon_Draw", "029090.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Shield_Draw", "029091.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Attack_02", "045120.FBX", { Frame, false }); //Attack_02
	FBXRenderer->CreateFBXAnimation("Attack_01", "045130.FBX", { Frame, false }); //Attack_01
	FBXRenderer->CreateFBXAnimation("Attack_03", "045140.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Attack_04", "045150.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Attack_05", "045110.FBX", { Frame, true });


	FBXRenderer->CreateFBXAnimation("Open_Door", "060030.FBX", { Frame, true });

	FBXRenderer->CreateFBXAnimation("String_Block", "19500.FBX", { Frame, true });

	FBXRenderer->CreateFBXAnimation("Parrying_Attack", "030400.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("DownAttack", "030810.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Parrying", "032100.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_01", "050110.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_02", "050111.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_03", "050112.FBX", { Frame, false });
	FBXRenderer->CreateFBXAnimation("Sit_Down", "068010.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Stand_Up", "068012.FBX", { Frame, true });


	FBXRenderer->CreateFBXAnimation("Solar_hurray", "080001.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Hi", "080011.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("hand", "080012.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Fighting", "080013.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Fighting_02", "080014.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Surren", "080700.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Surren_Up", "080702.FBX", { Frame, true });
	FBXRenderer->CreateFBXAnimation("Run20", "019500.FBX", { Frame, true });

	FBXRenderer->CreateFBXAnimation("Left_Stop", "022102.FBX", { Frame, false }); // 왼쪽 멈춤 
	FBXRenderer->CreateFBXAnimation("Behind_Stop", "022101.FBX", { Frame, false }); // 뒤 멈춤 
	FBXRenderer->CreateFBXAnimation("Right_Stop", "022103.FBX", { Frame, false }); // 오른쪽 멈춤 
	FBXRenderer->CreateFBXAnimation("Forward_Stop", "022200.FBX", { Frame, false }); // 앞 멈춤 
	FBXRenderer->CreateFBXAnimation("Shield_Move", "023100.FBX", { Frame, true }); // 쉴드 움직임 안됨 
	FBXRenderer->ChangeAnimation("Shield_Idle");
	



	GameEngineInput::AddInputObject(this);


	{
	
		Weapon->SetFBXMesh("WP_A_0221.FBX", "FBXAnimationTexture");

		Weapon->Transform.SetLocalScale({ 400.0f, 400.0f, 400.0f });
		Weapon->Transform.SetLocalPosition({ -200.0f, 0.0f, 0.0f });
	}


	/*Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->Transform.SetLocalScale({ 200.0f,200.0f });*/

	
	Col->Transform.SetLocalScale({ 200.0f,200.0f });


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


	//Capsule = CreateComponent<GameEnginePhysXCapsule>();
	
	Player_State();
}

void Player::Update(float _Delta)
{



	DeltaTime = _Delta;



	Col->CollisionEvent(0, { .Stay = [&](class GameEngineCollision* _This,class GameEngineCollision* _collisions)
	{
			float4 Monster = _This->GetActor()->Transform.GetLocalPosition();

			float4 Other_Monster = _collisions->GetActor()->Transform.GetLocalPosition();

			float4 Dir = Monster - Other_Monster;

			_This->GetActor()->Transform.AddLocalPosition(Dir * _Delta);
	} });

	// 서버를 열었든
	if (nullptr != GameEngineNetWindow::Net)
	{
		if (0 != GetPacketCount())
		{
			// 이 오브젝트에 패킷이 왔다.
		}

		// 완전히 네트워크로만 돌아가는 녀석.
		if (ControllType::Net == GetControllType())
		{
			return;
		}
	}
	if (check == false)
	{
		PlayerState.Update(_Delta);
	}
	GetFBXRenderer()->Transform.GetWorldPosition(); 
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	//Capsule->PhysXComponentInit(100.0f, 50.0f);
	//Capsule->SetPositioningComponent();

}

void Player::ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet)
{
	int a = 0;
}

