#include "PreCompile.h"
#include "Boss_Vordt.h"

// Ÿ�ϰ� ���� ���� ����
// �� ���� ����� �ش� ������ �����ؼ� ȸ���� ������ ����
// ������ ������� �������� ȸ�� X
// ȸ�� �ӵ��� Event�� ����ؼ� ����

////////////////////////// Move & Others

void Boss_Vordt::Howling_Start()
{
	MainRenderer->ChangeAnimation("Howling");
}

void Boss_Vordt::Howling_Update(float _Delta)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		MainState.ChangeState(Enum_BossState::Walk);
	}
}

void Boss_Vordt::Howling_End()
{

}

void Boss_Vordt::Idle_Start()
{
	MainRenderer->ChangeAnimation("Idle");
}

void Boss_Vordt::Idle_Update(float _Delta)
{
	if (0.3f > MainState.GetStateTime())
	{
		return;
	}
	MainState.ChangeState(Enum_BossState::Walk);
}

void Boss_Vordt::Idle_End()
{

}

void Boss_Vordt::Walk_Start()
{
	// �÷��̾� ��ġ�� ���� ����
	// MainRenderer->ChangeAnimation("Walk_Front");
	// �¿�
	// MainRenderer->ChangeAnimation("Walk_Left");
	// MainRenderer->ChangeAnimation("Walk_Right");
	MainRenderer->ChangeAnimation("Walk_Front");
}

void Boss_Vordt::Walk_Update(float _Delta)
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
		Capsule->AddWorldRotation(float4(0.f, 10.f * GetRotDir_f() * _Delta, 0.f));
	}

	if (true == DetectCollision->Collision(Enum_CollisionOrder::Player) && Angle)
	{

	}
	// Capsule->AddWorldRotation(float4(0.f, -10.f * _Delta, 0.f));
}

void Boss_Vordt::Walk_End()
{

}

void Boss_Vordt::Jump_Start()
{
	// �÷��̾� ��ġ�� ���� ����
	MainRenderer->ChangeAnimation("Jump_Back");
	// �¿�
	// MainRenderer->ChangeAnimation("Jump_Left");
	// MainRenderer->ChangeAnimation("Jump_Right");
}

void Boss_Vordt::Jump_Update(float _Delta)
{
	
}

void Boss_Vordt::Jump_End()
{

}

void Boss_Vordt::Turn_Start()
{
	// �÷��̾���� ������ ���� �ٸ�
	MainRenderer->ChangeAnimation("Turn_Left");
	// MainRenderer->ChangeAnimation("Turn_Left_Twice");
	// MainRenderer->ChangeAnimation("Turn_Right");
	// MainRenderer->ChangeAnimation("Turn_Right_Twice");
}

void Boss_Vordt::Turn_Update(float _Delta)
{
	
}

void Boss_Vordt::Turn_End()
{

}

void Boss_Vordt::Hitten_Start()
{
	// �׷α� ���¿� ���� �ٸ�
	MainRenderer->ChangeAnimation("Hit_001");
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
	MainRenderer->ChangeAnimation("Death");
	// �׷α⿡�� ������ Death_Groggy
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
	MainRenderer->ChangeAnimation("Breath");
}

void Boss_Vordt::Breath_Update(float _Delta)
{
	
}

void Boss_Vordt::Breath_End()
{

}

void Boss_Vordt::Combo1_Start()
{
	MainRenderer->ChangeAnimation("Combo1_Step1");
}

void Boss_Vordt::Combo1_Update(float _Delta)
{
	
}

void Boss_Vordt::Combo1_End()
{

}

void Boss_Vordt::Combo2_Start()
{
	MainRenderer->ChangeAnimation("Combo2_Step1");
}

void Boss_Vordt::Combo2_Update(float _Delta)
{
	
}

void Boss_Vordt::Combo2_End()
{

}

void Boss_Vordt::Sweap_Twice_Start()
{
	// �÷��̾��� ��ġ�� ���� �ٸ�
	// �¿�
	MainRenderer->ChangeAnimation("Sweep&Sweep_Left");
	// MainRenderer->ChangeAnimation("Sweep&Sweep_Right");
}

void Boss_Vordt::Sweap_Twice_Update(float _Delta)
{
	
}

void Boss_Vordt::Sweap_Twice_End()
{

}

void Boss_Vordt::Hit_Down_001_Start()
{
	// �÷��̾��� ��ġ�� ���� �ٸ�
	MainRenderer->ChangeAnimation("Hit_Down_001");
	// �¿�
	// MainRenderer->ChangeAnimation("Hit_Down_001_Right");
	// MainRenderer->ChangeAnimation("Hit_Down_001_Left");
}

void Boss_Vordt::Hit_Down_001_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_001_End()
{

}

void Boss_Vordt::Hit_Down_004_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_004");
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
	MainRenderer->ChangeAnimation("Hit_Down_005");
}

void Boss_Vordt::Hit_Down_005_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_005_End()
{

}

void Boss_Vordt::Hit_Down_006_Start()
{
	MainRenderer->ChangeAnimation("Hit_Down_006");
}

void Boss_Vordt::Hit_Down_006_Update(float _Delta)
{
	
}

void Boss_Vordt::Hit_Down_006_End()
{

}

void Boss_Vordt::Thrust_Start()
{
	MainRenderer->ChangeAnimation("Thrust");
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
	MainRenderer->ChangeAnimation("Sweep_001");
}

void Boss_Vordt::Sweep_001_Update(float _Delta)
{
	
}

void Boss_Vordt::Sweep_001_End()
{

}

void Boss_Vordt::Sweep_002_Start()
{
	MainRenderer->ChangeAnimation("Sweep_002");
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
	MainRenderer->ChangeAnimation("Rush_Attack");

}

void Boss_Vordt::Rush_Attack_001_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Attack_001_End()
{

}

void Boss_Vordt::Rush_Attack_002_Start()
{
	MainRenderer->ChangeAnimation("Rush_Attack_002");
}

void Boss_Vordt::Rush_Attack_002_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Attack_002_End()
{

}

void Boss_Vordt::Rush_Turn_Start()
{
	MainRenderer->ChangeAnimation("Rush&Turn");
}

void Boss_Vordt::Rush_Turn_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Start()
{
	MainRenderer->ChangeAnimation("Rush&Hit&Turn");
}

void Boss_Vordt::Rush_Hit_Turn_Update(float _Delta)
{

}

void Boss_Vordt::Rush_Hit_Turn_End()
{

}

void Boss_Vordt::Rush_Hit_Turn_Rush_Start()
{
	MainRenderer->ChangeAnimation("Rush&Hit&Turn&Rush");
}

void Boss_Vordt::Rush_Hit_Turn_Rush_Update(float _Delta)
{
	
}

void Boss_Vordt::Rush_Hit_Turn_Rush_End()
{

}