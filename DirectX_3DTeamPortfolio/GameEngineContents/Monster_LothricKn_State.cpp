#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "DummyActor.h"
#include "ContentsMath.h"

static constexpr float MIN_TIME_STEPSTATE = 0.5f;
static constexpr float MAX_TIME_STEPSTATE = 2.0f;
static constexpr float MAX_AGGRO_TIME = 8.0f;

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

void Monster_LothricKn::StateTimeSet(float _fMin, float _fMax)
{
	fMaxStateTime = ContentsRandom::Randomfloat(_fMin, _fMax);
}

void Monster_LothricKn::ResetStateTime()
{
	fMaxStateTime = 0.0f;
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
	MainState.CreateState(Enum_LothricKn_State::L_Side_Step, { .Start = std::bind(&Monster_LothricKn::Start_L_Side_Step,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_L_Side_Step,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::R_Side_Step, { .Start = std::bind(&Monster_LothricKn::Start_R_Side_Step,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_R_Side_Step,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::F_Step, { .Start = std::bind(&Monster_LothricKn::Start_F_Step,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_F_Step,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::B_Step, { .Start = std::bind(&Monster_LothricKn::Start_B_Step,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::Update_B_Step,this, std::placeholders::_1,std::placeholders::_2) });
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

void Monster_LothricKn::Start_L_Side_Step(GameEngineState* _State)
{
	StateTimeSet(MIN_TIME_STEPSTATE, MAX_TIME_STEPSTATE);
	MainRenderer->ChangeAnimation("L_Side_Step");
}

void Monster_LothricKn::Start_R_Side_Step(GameEngineState* _State)
{
	StateTimeSet(MIN_TIME_STEPSTATE, MAX_TIME_STEPSTATE);
	MainRenderer->ChangeAnimation("R_Side_Step");
}

void Monster_LothricKn::Start_F_Step(GameEngineState* _State)
{
	StateTimeSet(MIN_TIME_STEPSTATE, MAX_TIME_STEPSTATE);
	MainRenderer->ChangeAnimation("F_Step");
}

void Monster_LothricKn::Start_B_Step(GameEngineState* _State)
{
	StateTimeSet(MIN_TIME_STEPSTATE, MAX_TIME_STEPSTATE);
	MainRenderer->ChangeAnimation("B_Step");
}

void Monster_LothricKn::Start_Run(GameEngineState* _State)
{
	ResetStateTime();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
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
		Enum_LothricKn_State FindState = GetStateToMovementTable();
		_State->ChangeState(FindState);
		return;
	}
}


void Monster_LothricKn::Update_RH_Att_HitDown(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(45))
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

	if (IsFrame(51))
	{
		Enum_LothricKn_State FindState = GetStateToMovementTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::UpdateLH_ShieldAttack(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(41))
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

	if (IsFrame(45))
	{
		Enum_LothricKn_State FindState = GetStateToMovementTable();
		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_RH_Rear_Att(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrameOnce(48))
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

	if (IsFrame(53))
	{
		Enum_LothricKn_State FindState = GetStateToMovementTable();
		_State->ChangeState(FindState);
		return;
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

void Monster_LothricKn::Update_L_Side_Step(float _DeltaTime, GameEngineState* _State)
{
	// Time
	const float fStateTime = _State->GetStateTime();
	if (fMaxStateTime < fStateTime)
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}

	// Angle
	if (false == IsTargetInAngle(MIN_ROT_ANGLE))
	{
		RotToTarget(_DeltaTime, ROTSPEED_TO_TARGET);
	}

	// Dist 
	if (Enum_TargetDist::Medium != Monster_LothricKn::GetTargetDistance_e())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_R_Side_Step(float _DeltaTime, GameEngineState* _State)
{
	// Time
	const float fStateTime = _State->GetStateTime();
	if (fMaxStateTime < fStateTime)
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}

	// Angle
	if (false == IsTargetInAngle(MIN_ROT_ANGLE))
	{
		RotToTarget(_DeltaTime, ROTSPEED_TO_TARGET);
	}

	if (Enum_TargetDist::Medium != Monster_LothricKn::GetTargetDistance_e())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_F_Step(float _DeltaTime, GameEngineState* _State)
{
	// Time
	const float fStateTime = _State->GetStateTime();
	if (fMaxStateTime < fStateTime)
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}

	// Angle
	if (false == IsTargetInAngle(MIN_ROT_ANGLE))
	{
		RotToTarget(_DeltaTime, ROTSPEED_TO_TARGET);
	}

	if (Enum_TargetDist::Medium != Monster_LothricKn::GetTargetDistance_e())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_B_Step(float _DeltaTime, GameEngineState* _State)
{
	// Time
	const float fStateTime = _State->GetStateTime();
	if (fMaxStateTime < fStateTime)
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}

	// Angle
	if (false == IsTargetInAngle(MIN_ROT_ANGLE))
	{
		RotToTarget(_DeltaTime, ROTSPEED_TO_TARGET);
	}

	if (Enum_TargetDist::Medium != Monster_LothricKn::GetTargetDistance_e())
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
		return;
	}
}

void Monster_LothricKn::Update_Run(float _DeltaTime, GameEngineState* _State)
{
	if (fMaxStateTime > _State->GetStateTime())
	{
		// ReturnPatrolRoute

		// _State->ChangeState(Enum_LothricKn_State::);
		return;
	}

	// Check
	if (false == IsTargetInAngle(MIN_ROT_ANGLE))
	{
		RotToTarget(_DeltaTime, ROTSPEED_TO_TARGET);
	}

	if (true == IsTargetInRange(Enum_TargetDist::Long))
	{
		Enum_LothricKn_State FindState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == FindState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
			return;
		}

		_State->ChangeState(FindState);
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
		MsgBoxAssert("타겟이 존재하지 않는데 상태를 반환하려 했습니다.");
		return Enum_LothricKn_State::None;
	}

	Enum_TargetAngle eTargetRot = GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	Enum_TargetDist eTargetDist = Monster_LothricKn::GetTargetDistance_e();

	Enum_LothricKn_State FindMovementState = GetStateToMovementTable(eTargetDist, eTargetRot);
	if (Enum_LothricKn_State::None != FindMovementState)
	{
		return FindMovementState;
	}

	Enum_LothricKn_State FindAttackState = GetStateToAttackTable(eTargetDist, eTargetRot);
	if (Enum_LothricKn_State::None != FindAttackState)
	{
		return FindAttackState;
	}

	MsgBoxAssert("기본 상태가 등록되지 않았습니다.");
	return Enum_LothricKn_State::None;
}

Enum_LothricKn_State Monster_LothricKn::GetStateToMovementTable() const
{
	Enum_TargetAngle eTargetRot = GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	Enum_TargetDist eTargetDist = Monster_LothricKn::GetTargetDistance_e();

	Enum_LothricKn_State FindState = GetStateToMovementTable(eTargetDist, eTargetRot);
	return FindState;
}

Enum_LothricKn_State Monster_LothricKn::GetStateToMovementTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const
{
	if (Enum_TargetAngle::Back == _eTAngle)
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

	if (Enum_TargetDist::Long == _eTDist)
	{
		if (Enum_TargetAngle::Side == _eTAngle)
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

	if (Enum_TargetDist::Medium == _eTDist)
	{
		if (Enum_TargetAngle::Side == _eTAngle)
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
			return Enum_LothricKn_State::L_Side_Step;
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

bool Monster_LothricKn::IsTargetInAngle(float _fAngle) const
{
	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle < _fAngle)
	{
		return true;
	}

	return false;
}

void Monster_LothricKn::RotToTarget(float _DeltaTime, float _fSpeed)
{
	const float fRotDir = BaseActor::GetRotDir_f();
	const float RotAngle = fRotDir * _fSpeed * _DeltaTime;

	if (nullptr == Capsule)
	{
		MsgBoxAssert("피직스 컨포넌트가 존재하지 않습니다.");
		return;
	}

	Capsule->AddWorldRotation(float4(0.0f, RotAngle, 0.0f));
}

Enum_LothricKn_State Monster_LothricKn::GetStateToAttackTable()
{
	Enum_TargetAngle eTargetRot = GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	Enum_TargetDist eTargetDist = Monster_LothricKn::GetTargetDistance_e();

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

	if (Enum_TargetDist::Melee == _eTDist)
	{
		if (Enum_TargetAngle::Front == _eTAngle)
		{
			const int iChance = ContentsRandom::RandomInt(0,3);
			enum eAttackType
			{
				Combo = 0,
				Att_Shot = 3,
			};

			switch (iChance)
			{
			case 0:
			case 1:
			case 2:
				break;
			case Att_Shot:
				return Enum_LothricKn_State::Combo_Att_23;
			default:
			{
				MsgBoxAssert("상태 값이 잘못들어왔습니다. 값을 확인해주세요")
			}
				break;
			}
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

		switch (AttackRecord)
		{
		case eAttackType::Combo1:
			AttackState = Enum_LothricKn_State::Combo_Att_11;
			++AttackRecord;
			break;
		case eAttackType::Combo2:
			AttackState = Enum_LothricKn_State::Combo_Att_21;
			++AttackRecord;
			break;
		case eAttackType::None:
			AttackRecord = eAttackType::None;
			break;
		default:
			break;
		}

		return AttackState;
	}

	return Enum_LothricKn_State::None;
}