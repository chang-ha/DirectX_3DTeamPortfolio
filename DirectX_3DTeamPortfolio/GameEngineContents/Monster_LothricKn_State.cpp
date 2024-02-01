#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "DummyActor.h"
#include "ContentsMath.h"

static constexpr float Stop_RANGE_RATIO_TO_RUN = 5.0f;

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

float Monster_LothricKn::GetDirByDot(const float4& _OtherPos) const
{
	float4 VectorToOther = ContentsMath::GetVectorToOther(Transform.GetWorldPosition(), _OtherPos);
	VectorToOther.Normalize();
	float4 Rot = Transform.GetLocalRotationEuler();
	return 0.0f;
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
	MainState.CreateState(Enum_LothricKn_State::Attack11, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack11,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack11,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack12, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack12,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack12,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack13, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack13,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack13,this, std::placeholders::_1,std::placeholders::_2) });
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

void Monster_LothricKn::StartRH_Attack11(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_Attack11");
}

void Monster_LothricKn::StartRH_Attack12(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_Attack12");
}

void Monster_LothricKn::StartRH_Attack13(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_Attack13");
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
		_State->ChangeState(Enum_LothricKn_State::Attack11);
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
	}
}

void Monster_LothricKn::UpdateRH_Attack11(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(21))
	{
		// Idle

		// Shield Attack
		
		// LongSword Attack

		GameEngineRandom Random;
		if (3 == Random.RandomInt(0, 3))
		{
			_State->ChangeState(Enum_LothricKn_State::Idle_Standing1);
			return;
		}

		_State->ChangeState(Enum_LothricKn_State::Attack12);
		return;
	}
}

void Monster_LothricKn::UpdateRH_Attack12(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(21))
	{
		_State->ChangeState(Enum_LothricKn_State::Attack13);
		return;
	}
}

void Monster_LothricKn::UpdateRH_Attack13(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(33))
	{
		_State->ChangeState(Enum_LothricKn_State::Idle_Standing1);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_21(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(23))
	{
		if (true == CanAttack(50.0f, 50.0f))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_22);
			return;
		}

		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}

	if (IsFrame(33))
	{
		// Back Hitted
	}
}

void Monster_LothricKn::Update_Combo_Att_22(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(32))
	{
		if (true == CanAttack(50.0f, 50.0f))
		{
			_State->ChangeState(Enum_LothricKn_State::Combo_Att_22);
			return;
		}
	}

	if (IsFrame(52))
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}
}

void Monster_LothricKn::Update_Combo_Att_23(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(23))
	{
		// Back Hitted
	}

	if (IsFrame(33))
	{

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
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
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
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
	}
}

void Monster_LothricKn::Update_L_Turn(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}
}

void Monster_LothricKn::Update_R_Turn(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}
}

void Monster_LothricKn::Update_L_TurnTwice(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}
}

void Monster_LothricKn::Update_R_TurnTwice(float _DeltaTime, GameEngineState* _State)
{
	if (true == MainRenderer->IsCurAnimationEnd())
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		_State->ChangeState(SelectState);
		return;
	}
}

void Monster_LothricKn::Update_Run(float _DeltaTime, GameEngineState* _State)
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("물리엔진 컴포넌트가 존재하지 않습니다.");
		return;
	}

	const float TargetDist = BaseActor::GetDistanceToTarget();
	const float StopDist = W_SCALE* Stop_RANGE_RATIO_TO_RUN;
	const float TargetAngle = BaseActor::GetTargetAngle();

	const float TurnSpeed = 510.0f;

	if (std::fabs(TargetAngle) > 3.0f)
	{
		const float fRotDir = BaseActor::GetRotDir_f();
		const float TurnValue = fRotDir * TurnSpeed * _DeltaTime;
		Capsule->AddWorldRotation(float4(0.0f, TurnValue, 0.0f));
	}

	if (TargetDist < StopDist)
	{
		Enum_LothricKn_State SelectState = GetStateToAggroTable();
		if (Enum_LothricKn_State::None == SelectState)
		{
			MsgBoxAssert("해당 상태는 등록되지 않았습니다.");
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
		MsgBoxAssert("타겟이 존재하지 않는데 상태를 반환하려 했습니다.");
		return Enum_LothricKn_State::None;
	}

	
	const float Dist = BaseActor::GetDistanceToTarget();

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

	const float TwiceTurnAngle = 150.0f;
	const float TurnAngle = 115.0f;
	const float NotTurnAngle = 75.0f;

	const float AttRangeRatio = 3.0f;
	const float HitDownAttRangeRatio = 1.0f;


	if (std::fabs(AbsTargetAngle) > TwiceTurnAngle)
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

	if (std::fabs(AbsTargetAngle) > TurnAngle)
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

	if (Dist > W_SCALE * Stop_RANGE_RATIO_TO_RUN)
	{
		return Enum_LothricKn_State::Run;
	}

	if (Dist < W_SCALE * HitDownAttRangeRatio)
	{
		const float HitDownAngle = 40.0f;

		if (AbsTargetAngle < HitDownAngle)
		{
			return Enum_LothricKn_State::RH_Att_HitDown;
		}
	}

	if (Dist < W_SCALE * AttRangeRatio)
	{
		if (AbsTargetAngle > NotTurnAngle)
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

		enum AttackType
		{
			Combo1 = 0,
			Combo2,
			None,
		};

		Enum_LothricKn_State AttackState = Enum_LothricKn_State::None;

		if (AttackTypeCount = AttackType::Combo1)
		{
			AttackTypeCount++;
			AttackState = Enum_LothricKn_State::Attack11;
		}

		if (AttackTypeCount = AttackType::Combo2)
		{
			AttackTypeCount++;
			AttackState = Enum_LothricKn_State::Combo_Att_21;
		}

		if (AttackTypeCount == None)
		{
			AttackTypeCount = AttackType::Combo1;
		}

		return AttackState;
	}

	const int DirChance = ContentsRandom::RandomInt(0, 2);
	enum DirChance
	{
		Left = 0,
		Right = 1,
		Front = 2,
	};

	if (DirChance == DirChance::Left)
	{
		return Enum_LothricKn_State::Left_Walk;
	}

	if (DirChance == DirChance::Right)
	{
		return Enum_LothricKn_State::Right_Walk;
	}

	if (DirChance == DirChance::Right)
	{
		return Enum_LothricKn_State::Right_Walk;
	}

	MsgBoxAssert("기본 상태가 등록되지 않았습니다.");
	return Enum_LothricKn_State::None;
}


bool Monster_LothricKn::CanAttack(float _fDist, float _fDir)
{
	if (true)
	{
		return true;
	}

	return false;
}