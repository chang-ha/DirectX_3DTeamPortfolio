#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
// #include "GameEngineCore/GameEngineFBXRenderer.h"

// 서버용
#include "GameEngineNetWindow.h"

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
	FBXRenderer->SetFBXMesh("c0010.FBX", "FBXAnimationTexture"); // Bone 136
	FBXRenderer->Transform.SetLocalScale({ 200.0f, 200.0f, 200.0f });
	FBXRenderer->Transform.SetLocalPosition({ 0.0f, -100.0f, 0.0f });
	FBXRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	//	FBXRenderer->CreateFBXAnimation("Idle", "c0000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Idle", "00000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Shield_Idle", "00100.FBX", { 0.1f, true });
	//FBXRenderer->CreateFBXAnimation("Run", "Ani001.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Waek_jump", "004200.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_jump", "004210.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("String_Jump", "004220.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Forward_roll", "004280.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Hit_right", "005000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Hit_Left", "005001.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Hit_Forward", "005002.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Hit_Behind", "005003.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Left", "005100.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Right", "005101.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Forward", "005102.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_Hit_Behind", "005203.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("String_Hit_Forward", "005300.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("String_Hit_Behind", "005303.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Run15", "017002.FBX", { 0.1f, true }); // 에니메이션이 돌아감 
	FBXRenderer->CreateFBXAnimation("Weak_Shield_block", "019200.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Middle_Shield_block", "019210.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Forward", "020000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Behind", "0200001.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Right", "0200002.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Slow_Walk_Left", "0200003.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Walk_Forward", "020100.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Walk_Behind", "020101.FBX", { 0.1f, true });

	FBXRenderer->CreateFBXAnimation("Walk_Right", "020102.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Walk_Left", "020103.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Slow_Shield_Move", "020140.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Run", "020200.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Shield_Move", "023050.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Back_Step", "027000.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Roll_Behind", "027101.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Roll_Right", "027102.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Roll_Left", "027103.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("portion_Down", "029029.FBX", { 0.1f, true }); // ?? 

	FBXRenderer->CreateFBXAnimation("Weapon_Draw", "029090.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Shield_Draw", "029091.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Attack_01", "045120.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Attack_02", "045130.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Attack_03", "045140.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Attack_04", "045150.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Open_Door", "060030.FBX", { 0.1f, true });

	FBXRenderer->CreateFBXAnimation("String_Block", "19500.FBX", { 0.1f, true });

	FBXRenderer->CreateFBXAnimation("Parrying_Attack", "030400.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("DownAttack", "030810.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Parrying", "032100.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_01", "050110.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_02", "050111.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Portion_Drink_03", "050112.FBX", { 0.1f, true });
	//FBXRenderer->CreateFBXAnimation("Run10", "060250.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Sit_Down", "068010.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Stand_Up", "068012.FBX", { 0.1f, true });


	FBXRenderer->CreateFBXAnimation("Solar_hurray", "080001.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Hi", "080011.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("hand", "080012.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Fighting", "080013.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Fighting_02", "080014.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Surren", "080700.FBX", { 0.1f, true });
	FBXRenderer->CreateFBXAnimation("Surren_Up", "080702.FBX", { 0.1f, true });
	//FBXRenderer->CreateFBXAnimation("Run20", "019500.FBX", { 0.1f, true });

	FBXRenderer->CreateFBXAnimation("Left_Stop", "022102.FBX", { 0.1f, false }); // 왼쪽 멈춤 
	FBXRenderer->CreateFBXAnimation("Behind_Stop", "022101.FBX", { 0.1f, false }); // 뒤 멈춤 
	FBXRenderer->CreateFBXAnimation("Right_Stop", "022103.FBX", { 0.1f, false }); // 오른쪽 멈춤 
	FBXRenderer->CreateFBXAnimation("Forward_Stop", "022200.FBX", { 0.1f, false }); // 앞 멈춤 

	FBXRenderer->ChangeAnimation("Idle");

	GameEngineInput::AddInputObject(this);


	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->Transform.SetLocalScale({ 200.0f,200.0f });


	Player_State();
}

void Player::Update(float _Delta)
{


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

}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();
}

void Player::ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet)
{
	int a = 0;
}

