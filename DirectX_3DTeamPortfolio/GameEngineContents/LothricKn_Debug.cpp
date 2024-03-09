#include "PreCompile.h"
#include "LothricKn_Debug.h"

#include "Monster_LothricKn.h"

LothricKn_Debug::LothricKn_Debug() 
{
}

LothricKn_Debug::~LothricKn_Debug() 
{
}

void LothricKn_Debug::OutPutChangeState(int _State)
{
	if (_State != CurState)
	{
		CurState = _State;
		ContentsDebug::OutputString("c1280 State Change", GetDebugString(_State));
	}
	
}

std::string LothricKn_Debug::GetDebugString(int _State)
{
	const std::map<int, std::string> StateNames
	{
		std::pair(static_cast<int>(Enum_LothricKn_State::Debug),"Debug"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Sleep),"Sleep"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Idle_Standing1),"Idle_Standing1"),
		std::pair(static_cast<int>(Enum_LothricKn_State::L_Side_Step),"L_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::R_Side_Step),"R_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Step),"F_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Step),"B_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Run),"Run"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Patrol),"Patrol"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_11),"Combo_Att_11"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_12),"Combo_Att_12"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_13),"Combo_Att_13"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_21),"Combo_Att_21"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_22),"Combo_Att_22"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Combo_Att_23),"Combo_Att_23"),
		std::pair(static_cast<int>(Enum_LothricKn_State::RH_Att_HitDown),"RH_Att_HitDown"),
		std::pair(static_cast<int>(Enum_LothricKn_State::LH_ShieldAttack),"LH_ShieldAttack"),
		std::pair(static_cast<int>(Enum_LothricKn_State::RH_Rear_Att),"RH_Rear_Att"),
		std::pair(static_cast<int>(Enum_LothricKn_State::L_Turn),"L_Turn"),
		std::pair(static_cast<int>(Enum_LothricKn_State::R_Turn),"R_Turn"),
		std::pair(static_cast<int>(Enum_LothricKn_State::L_TurnTwice),"L_TurnTwice"),
		std::pair(static_cast<int>(Enum_LothricKn_State::R_TurnTwice),"R_TurnTwice"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Idle_Sit),"Idle_Sit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::SitUp),"SitUp"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_Hold),"DH_Hold"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_UnHold),"DH_UnHold"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_Stab_Att),"DH_Stab_Att"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_Swing_Att),"DH_Swing_Att"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_L_Side_Step),"DH_L_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_R_Side_Step),"DH_R_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_F_Step),"DH_F_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::DH_B_Step),"DH_B_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_Up),"G_Up"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_Down),"G_Down"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_L_Side_Step),"G_L_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_R_Side_Step),"G_R_Side_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Step),"G_F_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_B_Step),"G_B_Step"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_L_Turn),"G_L_Turn"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_R_Turn),"G_R_Turn"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_L_TurnTwice),"G_L_TurnTwice"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_R_TurnTwice),"G_R_TurnTwice"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_Run),"G_Run"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_Att_Bash),"G_Att_Bash"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Hit_W),"F_Hit_W"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Hit_W),"B_Hit_W"),
		std::pair(static_cast<int>(Enum_LothricKn_State::R_Hit_W),"R_Hit_W"),
		std::pair(static_cast<int>(Enum_LothricKn_State::L_Hit_W),"L_Hit_W"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Hit),"F_Hit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Hit),"B_Hit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::R_Hit),"R_Hit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::L_Hit),"L_Hit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Hit_W),"G_F_Hit_W"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Hit_W_PushBack),"G_F_Hit_W_PushBack"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Hit),"G_F_Hit"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Hit_PushBack),"G_F_Hit_PushBack"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_F_Hit_S_PushBack),"G_F_Hit_S_PushBack"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Block_Shield),"Block_Shield"),
		std::pair(static_cast<int>(Enum_LothricKn_State::G_Break),"G_Break"),
		std::pair(static_cast<int>(Enum_LothricKn_State::Break_Down),"Break_Down"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Death),"F_Death"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Death_End),"F_Death_End"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Death_B),"F_Death_B"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Death_B_End),"F_Death_B_End"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Stab),"B_Stab"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Stab_Death),"B_Stab_Death"),
		std::pair(static_cast<int>(Enum_LothricKn_State::B_Stab_Death_End),"B_Stab_Death_End"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Stab),"F_Stab"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Stab_Death),"F_Stab_Death"),
		std::pair(static_cast<int>(Enum_LothricKn_State::F_Stab_Death_End),"F_Stab_Death_End"),
	};

	auto FindIter = StateNames.find(_State);
	return FindIter->second;
}
