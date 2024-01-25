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
	MainState.CreateState(Enum_LothricKn_State::Sleep, { .Start = std::bind(&Monster_LothricKn::StartSleep,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateSleep,this, std::placeholders::_1,std::placeholders::_2) });
	// MainState.CreateState(Enum_LothricKn_State::Scout, { .Start = std::bind(&Monster_LothricKn::StartUnWake,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateUnWake,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack11, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack11,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack11,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack12, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack12,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack12,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack13, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack13,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack13,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::LH_ShieldAttack, { .Start = std::bind(&Monster_LothricKn::StartLH_ShieldAttack,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateLH_ShieldAttack,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::RH_CAttack, { .Start = std::bind(&Monster_LothricKn::StartRH_CAttack,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_CAttack,this, std::placeholders::_1,std::placeholders::_2) });

	MainState.ChangeState(Enum_LothricKn_State::Idle_Standing1);
}

void Monster_LothricKn::StartSleep(GameEngineState* _State)
{
	MainRenderer->Off();
}

void Monster_LothricKn::StartIdle_Standing1(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Idle_Standing1");
}


void Monster_LothricKn::StartScout(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Scout");
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

void Monster_LothricKn::UpdateSleep(float _DeltaTime, GameEngineState* _State)
{
	// player 범위 
	if (IsFlag(Enum_ActorStatus::WakeValue))
	{
		_State->ChangeState(Enum_LothricKn_State::Scout);
		return;
	}
}

void Monster_LothricKn::UpdateScout(float _DeltaTime, GameEngineState* _State)
{
	if (false)
	{
		// 플레잉어 인식
		return;
	}
}

void Monster_LothricKn::UpdateRH_Attack11(float _DeltaTime, GameEngineState* _State)
{
	if (false == wpDummy.expired())
	{
		
	}

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
