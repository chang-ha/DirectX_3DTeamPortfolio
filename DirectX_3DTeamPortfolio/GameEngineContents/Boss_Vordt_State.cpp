#include "PreCompile.h"
#include "Boss_Vordt.h"

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
	if (0.3f > MainState.GetStateTime())
	{
		return;
	}
	MainState.ChangeState(Enum_BossState::Walk_Front);
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
	float Angle = abs(GetTargetAngle());
	if (5.f < Angle)
	{
		Capsule->AddWorldRotation(float4(0.f, GetRotSpeed() * GetRotDir_f() * _Delta, 0.f));
	}

	if (true == DetectCollision->Collision(Enum_CollisionOrder::Player) && Angle)
	{

	}
	// Capsule->AddWorldRotation(float4(0.f, -10.f * _Delta, 0.f));
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
	MainRenderer->ChangeAnimation("Combo1_Step1", true);
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
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_End()
{

}