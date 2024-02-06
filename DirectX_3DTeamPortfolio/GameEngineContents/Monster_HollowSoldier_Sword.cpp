#include "PreCompile.h"
#include "Monster_HollowSoldier_Sword.h"

Monster_HollowSoldier_Sword::Monster_HollowSoldier_Sword()
{
}

Monster_HollowSoldier_Sword::~Monster_HollowSoldier_Sword()
{
}

void Monster_HollowSoldier_Sword::Start() 
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Sword);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ChainMail);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
}
void Monster_HollowSoldier_Sword::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_Sword::ChangeState(Enum_HollowSoldier_Sword_State _State)
{
	if (_State != SoldierState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Sword_State::Idle1:
			State_Idle1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_TwinSlash:
			State_RH_TwinSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack1:
			State_Attack1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack2:
			State_Attack2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack3:
			State_Attack3_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack4:
			State_Attack4_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack5:
			State_Attack5_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack6:
			State_Attack6_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack7:
			State_Attack7_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack8:
			State_Attack8_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack9:
			State_Attack9_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack10:
			State_Attack10_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack11:
			State_Attack11_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack12:
			State_Attack12_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack13:
			State_Attack13_Start();
			break;
		case Enum_HollowSoldier_Sword_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Hit:
			State_Hit_Start();
			break;
		case Enum_HollowSoldier_Sword_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Sword_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	SoldierState = _State;
}
void Monster_HollowSoldier_Sword::StateUpdate(float _Delta)
{
	switch (SoldierState)
	{
	case Enum_HollowSoldier_Sword_State::Idle1:
		return State_Idle1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack1:
		return State_Attack1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack2:
		return State_Attack2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack3:
		return State_Attack3_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack4:
		return State_Attack4_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack5:
		return State_Attack5_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack6:
		return State_Attack6_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack7:
		return State_Attack7_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack8:
		return State_Attack8_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack9:
		return State_Attack9_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack10:
		return State_Attack10_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack11:
		return State_Attack11_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack12:
		return State_Attack12_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack13:
		return State_Attack13_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Sword::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_Sword::State_Idle1_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}*/

	// 트리거 발동시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}
}

void Monster_HollowSoldier_Sword::State_Idle2_Start()
{
	//Debug
	{
		AttackPattern++;
	}
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_Sword::State_Idle2_Update(float _Delta)
{
	// 여기서 공격 등등 이루어짐.
	StateTime += _Delta;

	//if (StateTime >= 3.0f)
	//{
	//	StateTime = 0.0f;
	//	ChangeState(Enum_HollowSoldier_Sword_State::Attack1);
	//}

	if (StateTime >= 1.0f)
	{
		StateTime = 0.0f;
		if (AttackPattern > 0 || AttackPattern < 14)
		{
			switch (AttackPattern)
			{
			case 1:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack1);
				break;
			case 2:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack2);
				break;
			case 3:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack3);
				break;
			case 4:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack4);
				break;
			case 5:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack5);
				break;
			case 6:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack6);
				break;
			case 7:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack7);
				break;
			case 8:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack8);
				break;
			case 9:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack9);
				break;
			case 10:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack10);
				break;
			case 11:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack11);
				break;
			case 12:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack12);
				break;
			case 13:
				ChangeState(Enum_HollowSoldier_Sword_State::Attack13);
				break;
			default:
				break;
			}
		}
		else
		{
			AttackPattern = 1;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Scout");
	StateTime = 0.0f;
}
void Monster_HollowSoldier_Sword::State_Scout_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}*/




	// 플레이어 인식시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_RH_VerticalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
}
void Monster_HollowSoldier_Sword::State_RH_HorizontalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_ComboAttack");
}
void Monster_HollowSoldier_Sword::State_RH_ComboAttack_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_TwinSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_RH_TwinSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Attack1_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
	
}
void Monster_HollowSoldier_Sword::State_Attack1_Update(float _Delta)
{
	std::string_view name = MainRenderer->GetCurAnimation()->Aniamtion->GetName();
	std::string name2 = MainRenderer->GetCurAnimation()->FBXAnimationData->AniName;
	int a = 0;
	
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 100)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack2_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack2_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack3_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack3_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack4_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack4_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			MainRenderer->ChangeAnimation("c1100_RH_Sting");
		}
	}

	if (CheckAnimationName("c1100_RH_Sting"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 119)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack5_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack5_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			MainRenderer->ChangeAnimation("c1100_RH_ChargingSting");
		}
	}

	if (CheckAnimationName("c1100_RH_ChargingSting"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 144)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack6_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack6_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack7_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack7_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 45)
		{
			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack8_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack8_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_Th_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack9_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack9_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack10_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack10_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 45)
		{
			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack11_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_Sting");
}
void Monster_HollowSoldier_Sword::State_Attack11_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_Sting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 119)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack12_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_Sting");
}
void Monster_HollowSoldier_Sword::State_Attack12_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_Sting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 31)
		{
			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack13_Start()
{
	MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack13_Update(float _Delta)
{
	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_AttackFail_Start() 
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");

}
void Monster_HollowSoldier_Sword::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_Sword::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Sword::State_Hit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_Sword::State_HitToDeath_Update(float _Delta)
{
	// 죽는 애니메이션 재생중 무기 Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::Sword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Death);
	}
}

void Monster_HollowSoldier_Sword::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Sword::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");

}
void Monster_HollowSoldier_Sword::State_Death_Update(float _Delta) 
{

}