#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "DummyActor.h"
#include "ContentsMath.h"


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
	MainState.CreateState(Enum_LothricKn_State::Idle_Standing1 ,{.Start = std::bind(&Monster_LothricKn::StartIdle_Standing1,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateIdle_Standing1,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Sleep, { .Start = std::bind(&Monster_LothricKn::StartSleep,this, std::placeholders::_1), .End = std::bind(&Monster_LothricKn::EndSleep,this, std::placeholders::_1) });
	MainState.CreateState(Enum_LothricKn_State::Patrol, { .Start = std::bind(&Monster_LothricKn::StartPatrol,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdatePatrol,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack11, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack11,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack11,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack12, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack12,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack12,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack13, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack13,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack13,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::LH_ShieldAttack, { .Start = std::bind(&Monster_LothricKn::StartLH_ShieldAttack,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateLH_ShieldAttack,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::RH_CAttack, { .Start = std::bind(&Monster_LothricKn::StartRH_CAttack,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_CAttack,this, std::placeholders::_1,std::placeholders::_2) });

	MainState.ChangeState(Enum_LothricKn_State::Idle_Standing1);
}

void Monster_LothricKn::StartSleep(GameEngineState* _State)
{
	Off();
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

void Monster_LothricKn::StartRH_SwordDownAttack(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_SwordDownAttack");
}

void Monster_LothricKn::StartLH_ShieldAttack(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("LH_ShieldAttack");
}

void Monster_LothricKn::StartRH_CAttack(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("RH_CAttack");
}



void Monster_LothricKn::UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State)
{
	if (GameEngineInput::IsDown('U', this))
	{
		_State->ChangeState(Enum_LothricKn_State::Attack11);
		return;
	}
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


void Monster_LothricKn::UpdateRH_SwordDownAttack(float _DeltaTime, GameEngineState* _State)
{

}

void Monster_LothricKn::UpdateLH_ShieldAttack(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(45))
	{
		_State->ChangeState(Enum_LothricKn_State::Idle_Standing1);
		return;
	}
}

void Monster_LothricKn::UpdateRH_CAttack(float _DeltaTime, GameEngineState* _State)
{
	if (IsFrame(49))
	{
		_State->ChangeState(Enum_LothricKn_State::Idle_Standing1);
		return;
	}
}

////////////////////////////////////////////////////////////
////////////// End

void Monster_LothricKn::EndSleep(GameEngineState* _State)
{
	On();
}



Enum_LothricKn_State Monster_LothricKn::GetStateToAggroTable()
{
	GameEngineActor* pTarget = GetTargetPointer();
	if (nullptr == pTarget)
	{
		MsgBoxAssert("타겟이 존재하지 않는데 상태를 반환하려 했습니다.");
		return Enum_LothricKn_State::None;
	}

	const float4 MyPos = Transform.GetWorldPosition();
	const float4 OtherPos = pTarget->Transform.GetWorldPosition();
	const float Dist = ContentsMath::GetVector3Length(MyPos, OtherPos).X;

	const float AbsTargetAngle = std::fabs(GetTargetAngle());

	const float TwiceTurnAngle = 150.0f;
	const float TurnAngle = 115.0f;
	const float NotTurnAngle = 75.0f;

	const float AttRangeRatio = 3.0f;


	if (std::fabs(AbsTargetAngle) > TwiceTurnAngle)
	{
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			return Enum_LothricKn_State::Left_Turn_Twice;
		}

		if (Enum_RotDir::Right == GetRotDir_e())
		{
			return Enum_LothricKn_State::Right_Turn_Twice;
		}
	}

	if (std::fabs(AbsTargetAngle) > TurnAngle)
	{
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			return Enum_LothricKn_State::Left_Turn;
		}

		if (Enum_RotDir::Right == GetRotDir_e())
		{
			return Enum_LothricKn_State::Right_Turn;
		}
	}

	if (Dist > W_SCALE * 5.0f)
	{
		return Enum_LothricKn_State::Run;
	}

	if (Dist < W_SCALE * AttRangeRatio)
	{
		return Enum_LothricKn_State::Attack11;
	}

	const int DirChance = ContentsRandom::RandomInt(0,1);
	enum DirChance
	{
		LeftDir = 0,
		RightDir = 1,
	};

	if (DirChance == LeftDir)
	{
		return Enum_LothricKn_State::Left_Walk;
	}

	if (DirChance == RightDir)
	{
		return Enum_LothricKn_State::Right_Walk;
	}

	MsgBoxAssert("기본 상태가 등록되지 않았습니다.");
	return Enum_LothricKn_State::None;
}