#include "PreCompile.h"
#include "Monster_LothricKn.h"


void Monster_LothricKn::CreateFSM()
{
	MainState.CreateState(Enum_LothricKn_State::Idle_Standing1 ,{.Start = std::bind(&Monster_LothricKn::StartIdle_Standing1,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateIdle_Standing1,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Unwake, { .Start = std::bind(&Monster_LothricKn::StartUnWake,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateUnWake,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Scout, { .Start = std::bind(&Monster_LothricKn::StartUnWake,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateUnWake,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack11, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack11,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack11,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack12, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack12,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack12,this, std::placeholders::_1,std::placeholders::_2) });
	MainState.CreateState(Enum_LothricKn_State::Attack13, { .Start = std::bind(&Monster_LothricKn::StartRH_Attack13,this, std::placeholders::_1), .Stay = std::bind(&Monster_LothricKn::UpdateRH_Attack13,this, std::placeholders::_1,std::placeholders::_2) });

	MainState.ChangeState(Enum_LothricKn_State::Idle_Standing1);
}


void Monster_LothricKn::StartIdle_Standing1(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Idle_Standing1");
}

void Monster_LothricKn::StartUnWake(GameEngineState* _State)
{
	MainRenderer->ChangeAnimation("Standup");
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


void Monster_LothricKn::UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State)
{
	if (GameEngineInput::IsDown('U', this))
	{
		_State->ChangeState(Enum_LothricKn_State::Attack11);
		return;
	}
}

void Monster_LothricKn::UpdateUnWake(float _DeltaTime, GameEngineState* _State)
{
	// player 범위 
	if (false)
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
	if (21 == MainRenderer->GetCurAnimationFrame())
	{
		_State->ChangeState(Enum_LothricKn_State::Attack12);
		return;
	}
}

void Monster_LothricKn::UpdateRH_Attack12(float _DeltaTime, GameEngineState* _State)
{
	if (21 == MainRenderer->GetCurAnimationFrame())
	{
		_State->ChangeState(Enum_LothricKn_State::Attack13);
		return;
	}
}

void Monster_LothricKn::UpdateRH_Attack13(float _DeltaTime, GameEngineState* _State)
{
	if (54 == MainRenderer->GetCurAnimationFrame())
	{
		_State->ChangeState(Enum_LothricKn_State::Idle_Standing1);
		return;
	}
}