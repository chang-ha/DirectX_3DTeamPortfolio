#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "DummyActor.h"
#include "ContentsMath.h"


static constexpr float CLOSE_RANGE = 1.0f;
static constexpr float MELEE_RANGE = 3.0f;
static constexpr float MEDIUM_RANGE = 5.0f;
static constexpr float LONG_RANGE = 7.0f;
static constexpr float FRONT_ANGLE = 75.0f;
static constexpr float SIDE_ANGLE = 115.0f;
static constexpr float BACK_ANGLE = 150.0f;

bool Monster_LothricKn::IsFrame(int _StartFrame, int _EndFrame /*= -1*/) const
{
	if (_StartFrame >= MainRenderer->GetCurAnimationFrame())
	{
		if (-1 == _EndFrame)
		{
			return true;
		}

		if (_EndFrame <= MainRenderer->GetCurAnimationFrame())
		{
			return true;
		}
	}

	return false;
}

bool Monster_LothricKn::IsFrameOnce(int _StartFrame)
{
	if (true == MainRenderer->IsFrameChange())
	{
		if (_StartFrame >= MainRenderer->GetCurAnimationFrame())
		{
			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////// State
////////////////////////////////////////////////////////////////////////////////////////

void Monster_LothricKn::CreateFSM()
{
	MainState.CreateState(Enum_LothricKn_State::Debug ,{.Start = std::bind(&Monster_LothricKn::Start_Debug,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Debug,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Idle_Standing1 ,{.Start = std::bind(&Monster_LothricKn::StartIdle_Standing1,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateIdle_Standing1,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Sleep, { .Start = std::bind(&Monster_LothricKn::StartSleep,this, std::placeholders::_1), .End = std::bind(&Monster_LothricKn::EndSleep,this, std::placeholders::_1) });
	MainState.CreateState(Enum_LothricKn_State::Patrol, { .Start = std::bind(&Monster_LothricKn::StartPatrol,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdatePatrol,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_11, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_11,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_11,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_12, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_12,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_12,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_13, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_13,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_13,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_21, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_21,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_21,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_22, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_22,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_22,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Combo_Att_23, { .Start = std::bind(&Monster_LothricKn::Start_Combo_Att_23,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Combo_Att_23,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::RH_Att_HitDown, { .Start = std::bind(&Monster_LothricKn::Start_RH_Att_HitDown,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_RH_Att_HitDown,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::LH_ShieldAttack, { .Start = std::bind(&Monster_LothricKn::StartLH_ShieldAttack,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateLH_ShieldAttack,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::RH_Rear_Att, { .Start = std::bind(&Monster_LothricKn::Start_RH_Rear_Att,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_RH_Rear_Att,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::L_Turn, { .Start = std::bind(&Monster_LothricKn::Start_L_Turn,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_L_Turn,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::R_Turn, { .Start = std::bind(&Monster_LothricKn::Start_R_Turn,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_R_Turn,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::L_TurnTwice, { .Start = std::bind(&Monster_LothricKn::Start_L_TurnTwice,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_L_TurnTwice,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::R_TurnTwice, { .Start = std::bind(&Monster_LothricKn::Start_R_TurnTwice,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_R_TurnTwice,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Run, { .Start = std::bind(&Monster_LothricKn::Start_Run,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_Run,this, std::placeholders::_1,std::placeholders::_2) });

	MainState.ChangeState(Enum_LothricKn_State::Debug);
}

void Monster_LothricKn::StartSleep(GameEngineState* _State)
{
	Off();
}

void Monster_LothricKn::Start_Debug(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Idle_Standing1");
}

void Monster_LothricKn::StartIdle_Standing1(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Idle_Standing1");
}

void Monster_LothricKn::StartPatrol(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Patrol");
}

void Monster_LothricKn::Start_Combo_Att_11(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_11");
}

void Monster_LothricKn::Start_Combo_Att_12(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_12");
}

void Monster_LothricKn::Start_Combo_Att_13(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_13");
}

void Monster_LothricKn::Start_Combo_Att_21(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_21");
}

void Monster_LothricKn::Start_Combo_Att_22(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_22");
}

void Monster_LothricKn::Start_Combo_Att_23(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Combo_Att_23");
}

void Monster_LothricKn::Start_RH_Att_HitDown(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_Att_HitDown");
}

void Monster_LothricKn::StartLH_ShieldAttack(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("LH_ShieldAttack");
}

void Monster_LothricKn::Start_RH_Rear_Att(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_Rear_Att");
}

void Monster_LothricKn::Start_L_Turn(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("L_Turn");
}

void Monster_LothricKn::Start_R_Turn(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("R_Turn");
}

void Monster_LothricKn::Start_L_TurnTwice(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("L_TurnTwice");
}

void Monster_LothricKn::Start_R_TurnTwice(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("R_TurnTwice");
}

void Monster_LothricKn::Start_Run(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Run");
}





////////////////////////////////////////////////////////////
////////////// Update-State

void Monster_LothricKn::Update_Debug(float _DeltaTime, GameEngineState* _State)
{
	if (GameEngineInput::IsDown('U', this))
	{
		_State->ChangeState(Enum_LothricKn_State::Combo_Att_11);
		return;
	}
}

void Monster_LothricKn::UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State)
{

}

void Monster_LothricKn::UpdatePatrol(float _DeltaTime, GameEngineState* _State)
{
	FindTarget();
	if (true == IsTargeting())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_11(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(19))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, FRONT_ANGLE))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_12);
			return;
		}
	}

	if (IsFrameOnce(55))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (Enum_LothricKn_State::None != FindState)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(60))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_12(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(21))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, FRONT_ANGLE))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_12);
			return;
		}
	}

	if (IsFrameOnce(44))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (Enum_LothricKn_State::None != FindState)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(51))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_13(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(55))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (Enum_LothricKn_State::None != FindState)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(61))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_21(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(23))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, FRONT_ANGLE))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_22);
			return;
		}
	}

	if (IsFrameOnce(42))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (FindState != Enum_LothricKn_State::None)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(50))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_22(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(32))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, FRONT_ANGLE))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_22);
			return;
		}
	}

	if (IsFrameOnce(57))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (FindState != Enum_LothricKn_State::None)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(66))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_23(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(58))
	{
		if (true == CanAttack(W_SCALE * MELEE_RANGE, SIDE_ANGLE))
		{
			Enum_LothricKn_State FindState = GetStateToAttackTable();
			if (FindState != Enum_LothricKn_State::None)
			{
				_State->ChangeState(FindState);
				return;
			}
		}
	}

	if (IsFrame(60))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}


void Monster_LothricKn::Update_RH_Att_HitDown(float _DeltaTime, GameEngineState* _State)
{

}

void Monster_LothricKn::UpdateLH_ShieldAttack(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(41))
	{
		// Back Hitted
	}

	if (IsFrame(45))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
	}
}

void Monster_LothricKn::Update_RH_Rear_Att(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(49))
	{
		// Back Hitted
	}

	if (IsFrame(53))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
	}
}

void Monster_LothricKn::Update_L_Turn(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_R_Turn(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_L_TurnTwice(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_R_TurnTwice(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Run(float _DeltaTime, GameEngineState* _State)
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("�������� ������Ʈ�� �������� �ʽ��ϴ�.");
		return;
	}

	const Enum_TargetDist eTargetDist = BaseMonster::GetTargetDistance_e(CLOSE_RANGE, MELEE_RANGE, MEDIUM_RANGE);
	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

	const float TurnSpeed = 510.0f;

	if (AbsTargetAngle > 3.0f)
	{
		const float fRotDir = BaseActor::GetRotDir_f();
		const float TurnValue = fRotDir * TurnSpeed * _DeltaTime;
		Capsule->AddWorldRotation(float4(0.0f, TurnValue, 0.0f));
	}

	if (Enum_TargetDist::Long != eTargetDist)
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == SelectState)
		{
			MsgBoxAssert("�ش� ���´� ��ϵ��� �ʾҽ��ϴ�.");
			return;
		}

		_State->ChangeState(SelectState);
		return;
	}
}



////////////////////////////////////////////////////////////
////////////// End

void Monster_LothricKn::EndSleep(GameEngineState* _State)
{
	On();
}





////////////////////////////////////////////////////////////
////////////// State Func

Enum_LothricKn_State Monster_LothricKn::GetStateToAggroTable()
{
	GameEngineActor* pTarget = GetTargetPointer();
	if (nullptr == pTarget)
	{
		MsgBoxAssert("Ÿ���� �������� �ʴµ� ���¸� ��ȯ�Ϸ� �߽��ϴ�.");
		return Enum_LothricKn_State::None;
	}

	Enum_TargetAngle eTargetRot = GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	Enum_TargetDist eTargetDist = GetTargetDistance_e(CLOSE_RANGE, MELEE_RANGE, MEDIUM_RANGE);

	if (Enum_TargetAngle::Back == eTargetRot)
	{
		if (Enum_RotDir::Left == BaseActor::GetRotDir_e())
		{
			return Enum_LothricKn_State::L_TurnTwice;
		}

		if (Enum_RotDir::Right == BaseActor::GetRotDir_e())
		{
			return Enum_LothricKn_State::R_TurnTwice;
		}
	}

	if (Enum_TargetDist::Long == eTargetDist)
	{
		if (Enum_TargetAngle::Side == eTargetRot)
		{
			if (Enum_RotDir::Left == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::L_Turn;
			}

			if (Enum_RotDir::Right == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::R_Turn;
			}
		}

		return Enum_LothricKn_State::Run;
	}

	if (Enum_TargetDist::Medium == eTargetDist)
	{
		if (Enum_TargetAngle::Side == eTargetRot)
		{
			if (Enum_RotDir::Left == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::L_Turn;
			}

			if (Enum_RotDir::Right == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::R_Turn;
			}
		}

		const int DirChance = ContentsRandom::RandomInt(0, 2);
		enum eDirChance
		{
			Left = 0,
			Right = 1,
			Front = 2,
		};

		if (DirChance == eDirChance::Left)
		{
			return Enum_LothricKn_State::Left_Walk;
		}

		if (DirChance == eDirChance::Right)
		{
			return Enum_LothricKn_State::Right_Walk;
		}

		if (DirChance == eDirChance::Front)
		{
			return Enum_LothricKn_State::Front_Walk;
		}
	}

	Enum_LothricKn_State FindAttackState = GetStateToAttackTable(eTargetDist, eTargetRot);
	if (Enum_LothricKn_State::None == FindAttackState)
	{
		return FindAttackState;
	}

	MsgBoxAssert("�⺻ ���°� ��ϵ��� �ʾҽ��ϴ�.");
	return Enum_LothricKn_State::None;
}


bool Monster_LothricKn::CanAttack(float _fDist, float _fDir) const
{
	const float Dist = BaseActor::GetTargetDistance();

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

	bool DistCheck = (Dist < _fDist);
	bool AngleCheck = (AbsTargetAngle < _fDir);

	if (AngleCheck && DistCheck)
	{
		return true;
	}

	return false;
}

Enum_LothricKn_State Monster_LothricKn::GetStateToAttackTable()
{
	Enum_TargetAngle eTargetRot = GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	Enum_TargetDist eTargetDist = GetTargetDistance_e(CLOSE_RANGE, MELEE_RANGE, MEDIUM_RANGE);

	Enum_LothricKn_State FindState = GetStateToAttackTable(eTargetDist, eTargetRot);
	return FindState;
}

Enum_LothricKn_State Monster_LothricKn::GetStateToAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle)
{
	if (Enum_TargetDist::Close == _eTDist)
	{
		const float HitDownAngle = 40.0f;

		if (Enum_TargetAngle::Front == _eTAngle)
		{
			return Enum_LothricKn_State::RH_Att_HitDown;
		}
	}

	if (Enum_TargetDist::Close == _eTDist || Enum_TargetDist::Melee == _eTDist)
	{
		if (Enum_TargetAngle::Side == _eTAngle)
		{
			if (Enum_RotDir::Left == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::LH_ShieldAttack;
			}

			if (Enum_RotDir::Right == BaseActor::GetRotDir_e())
			{
				return Enum_LothricKn_State::RH_Rear_Att;
			}
		}

		enum eAttackType
		{
			Combo1 = 0,
			Combo2,
			None,
		};

		Enum_LothricKn_State AttackState = Enum_LothricKn_State::None;

		switch (PrevAttackNum)
		{
		case eAttackType::Combo1:
			AttackState = Enum_LothricKn_State::Combo_Att_11;
			++PrevAttackNum;
			break;
		case eAttackType::Combo2:
			AttackState = Enum_LothricKn_State::Combo_Att_21;
			++PrevAttackNum;
			break;
		case eAttackType::None:
			PrevAttackNum = eAttackType::None;
			break;
		default:
			break;
		}

		return AttackState;
	}

	return Enum_LothricKn_State::None;
}