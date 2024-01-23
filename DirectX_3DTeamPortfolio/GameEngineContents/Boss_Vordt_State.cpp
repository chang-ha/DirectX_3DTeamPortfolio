#include "PreCompile.h"
#include "Boss_Vordt.h"

////////////////////////// Move & Others

void Boss_Vordt::Howling_Start()
{
	BossFBXRenderer->ChangeAnimation("Howling");
}

void Boss_Vordt::Howling_Update(float _Delta)
{
	
}

void Boss_Vordt::Howling_End()
{

}

void Boss_Vordt::Idle_Start()
{
	BossFBXRenderer->ChangeAnimation("Idle");
}

void Boss_Vordt::Idle_Update(float _Delta)
{

}

void Boss_Vordt::Idle_End()
{

}

void Boss_Vordt::Walk_Start()
{
	// 플레이어 위치에 따라 조정
	BossFBXRenderer->ChangeAnimation("Walk_Front");
	// 좌우
	// BossFBXRenderer->ChangeAnimation("Walk_Left");
	// BossFBXRenderer->ChangeAnimation("Walk_Right");
}

void Boss_Vordt::Walk_Update(float _Delta)
{
	
}

void Boss_Vordt::Walk_End()
{

}

void Boss_Vordt::Jump_Start()
{
	// 플레이어 위치에 따라 조정
	BossFBXRenderer->ChangeAnimation("Jump_Back");
	// 좌우
	// BossFBXRenderer->ChangeAnimation("Jump_Left");
	// BossFBXRenderer->ChangeAnimation("Jump_Right");
}

void Boss_Vordt::Jump_Update(float _Delta)
{
	
}

void Boss_Vordt::Jump_End()
{

}

void Boss_Vordt::Turn_Start()
{
	// 플레이어와의 각도에 따라 다름
	BossFBXRenderer->ChangeAnimation("Turn_Left");
	// BossFBXRenderer->ChangeAnimation("Turn_Left_Twice");
	// BossFBXRenderer->ChangeAnimation("Turn_Right");
	// BossFBXRenderer->ChangeAnimation("Turn_Right_Twice");
}

void Boss_Vordt::Turn_Update(float _Delta)
{
	
}

void Boss_Vordt::Turn_End()
{

}

void Boss_Vordt::Hitten_Start()
{
	// 그로기 상태에 따라 다름
	BossFBXRenderer->ChangeAnimation("Hit_001");
	// BossFBXRenderer->ChangeAnimation("Hit_002");
	// BossFBXRenderer->ChangeAnimation("Hit_003_Left");
	// BossFBXRenderer->ChangeAnimation("Hit_003_Right");
	// BossFBXRenderer->ChangeAnimation("Hit_004_Groggy");
}

void Boss_Vordt::Hitten_Update(float _Delta)
{
	
}

void Boss_Vordt::Hitten_End()
{

}

void Boss_Vordt::Death_Start()
{
	// 그로기에서 죽으면 Death_Groggy
	BossFBXRenderer->ChangeAnimation("Death");
	// BossFBXRenderer->ChangeAnimation("Death_Groggy");
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
	BossFBXRenderer->ChangeAnimation("Breath");
}

void Boss_Vordt::Breath_Update(float _Delta)
{
	
}

void Boss_Vordt::Breath_End()
{

}

void Boss_Vordt::Combo1_Start()
{
	BossFBXRenderer->ChangeAnimation("Combo1_Step1");
}

void Boss_Vordt::Combo1_Update(float _Delta)
{
	
}

void Boss_Vordt::Combo1_End()
{

}

void Boss_Vordt::Combo2_Start()
{
	BossFBXRenderer->ChangeAnimation("Combo2_Step1");
}

void Boss_Vordt::Combo2_Update(float _Delta)
{
	
}

void Boss_Vordt::Combo2_End()
{

}

void Boss_Vordt::Sweap_Twice_Start()
{
	// 플레이어의 위치에 따라 다름
	// 좌우
	BossFBXRenderer->ChangeAnimation("Hit&Sweep");
	// BossFBXRenderer->ChangeAnimation("Sweep&Sweep");
}

void Boss_Vordt::Sweap_Twice_Update(float _Delta)
{
	
}

void Boss_Vordt::Sweap_Twice_End()
{

}

void Boss_Vordt::Hit_Down_001_Start()
{
	// 플레이어의 위치에 따라 다름
	BossFBXRenderer->ChangeAnimation("Hit_Down_001");
	// 좌우
	// BossFBXRenderer->ChangeAnimation("Hit_Down_002");
	// BossFBXRenderer->ChangeAnimation("Hit_Down_003");
}

void Boss_Vordt::Hit_Down_001_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_001_End()
{

}

void Boss_Vordt::Hit_Down_004_Start()
{
	BossFBXRenderer->ChangeAnimation("Hit_Down_004");
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
	BossFBXRenderer->ChangeAnimation("Hit_Down_005");
}

void Boss_Vordt::Hit_Down_005_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_005_End()
{

}

void Boss_Vordt::Hit_Down_006_Start()
{
	BossFBXRenderer->ChangeAnimation("Hit_Down_006");
}

void Boss_Vordt::Hit_Down_006_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_006_End()
{

}

void Boss_Vordt::Thrust_Start()
{
	BossFBXRenderer->ChangeAnimation("Thrust");
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
	BossFBXRenderer->ChangeAnimation("Sweep_001");
}

void Boss_Vordt::Sweep_001_Update(float _Delta)
{
	
}

void Boss_Vordt::Sweep_001_End()
{

}

void Boss_Vordt::Sweep_002_Start()
{
	BossFBXRenderer->ChangeAnimation("Sweep_002");
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
	BossFBXRenderer->ChangeAnimation("Rush_Attack");

}

void Boss_Vordt::Rush_Attack_001_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_001_End()
{

}

void Boss_Vordt::Rush_Attack_002_Start()
{
	BossFBXRenderer->ChangeAnimation("Rush_Attack_002");
}

void Boss_Vordt::Rush_Attack_002_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Attack_002_End()
{

}

void Boss_Vordt::Rush_Turn_Start()
{
	BossFBXRenderer->ChangeAnimation("Rush&Turn");
}

void Boss_Vordt::Rush_Turn_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Start()
{
	BossFBXRenderer->ChangeAnimation("Rush&Hit&Turn");
}

void Boss_Vordt::Rush_Hit_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_Start()
{
	BossFBXRenderer->ChangeAnimation("Rush&Hit&Turn&Rush");
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Hit_Turn_Rush_End()
{

}