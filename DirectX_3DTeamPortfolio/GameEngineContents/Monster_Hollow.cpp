#include "PreCompile.h"
#include "Monster_Hollow.h"
#include "BasePlayer.h"


Monster_Hollow::Monster_Hollow()
{
}

Monster_Hollow::~Monster_Hollow()
{
}

void Monster_Hollow::Start()
{
	BaseMonster::Start();

	MainRenderer->SetFBXMesh("c1100.fbx", "FBXAnimationTexture");

	LoadAnimation();

	{
		MainRenderer->ChangeAnimation("c1100_Idle1");
	}

	for (int i = 0; i < static_cast<int>(Enum_Hollow_MeshIndex::None); i++)
	{
		MainRenderer->GetRenderUnits()[i][0]->Off();
	}

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Bone);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::UpperBody);
}

void Monster_Hollow::Update(float _Delta)
{
	
}

void Monster_Hollow::Release()
{
	BaseMonster::Release();
}

void Monster_Hollow::LevelEnd(class GameEngineLevel* _NextLevel)
{

}

void Monster_Hollow::LoadAnimation()
{
	MainRenderer->CreateFBXAnimation("c1100_Idle1", "c1100_Idle1.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle2", "c1100_Idle2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle3", "c1100_Idle3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray1", "c1100_Pray1.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray2", "c1100_Pray2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray3", "c1100_Pray3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle1", "c1100_PrayToIdle1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle2", "c1100_PrayToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle3", "c1100_PrayToIdle3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle1", "c1100_Idle2ToIdle1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle1ToIdle2", "c1100_Idle1ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle3", "c1100_Idle2ToIdle3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle3ToIdle2", "c1100_Idle3ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Front", "c1100_Walk_Front.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Back", "c1100_Walk_Back.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Left", "c1100_Walk_Left.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Right", "c1100_Walk_Right.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Front3", "c1100_Walk_Front3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Back3", "c1100_Walk_Back3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Left3", "c1100_Walk_Left3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Right3", "c1100_Walk_Right3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Run", "c1100_Run.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Run3", "c1100_Run3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Scout", "c1100_Scout.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_RH_VerticalSlash", "c1100_RH_VerticalSlash.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_HorizontalSlash", "c1100_RH_HorizontalSlash.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ChargingSting", "c1100_RH_ChargingSting.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_RunToSting", "c1100_RH_RunToSting.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_LH_Fist", "c1100_LH_Fist.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_TH_VerticalSlash", "c1100_TH_VerticalSlash.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ComboAttack", "c1100_RH_ComboAttack.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ChargingSlash", "c1100_RH_ChargingSlash.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_Sting", "c1100_RH_Sting.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_TwinSlash", "c1100_RH_TwinSlash.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left2", "c1100_Turn_Left2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right2", "c1100_Turn_Right2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice2", "c1100_Turn_Left_Twice2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice2", "c1100_Turn_Right_Twice2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left", "c1100_Turn_Left.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right", "c1100_Turn_Right.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice", "c1100_Turn_Left_Twice.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice", "c1100_Turn_Right_Twice.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left3", "c1100_Turn_Left3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right3", "c1100_Turn_Right3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice3", "c1100_Turn_Left_Twice3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice3", "c1100_Turn_Right_Twice3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Front", "c1100_Hit_Front.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Back", "c1100_Hit_Back.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Left", "c1100_Hit_Left.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Right", "c1100_Hit_Right.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Guard", "c1100_Guard.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_AttackFail", "c1100_AttackFail.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_GuardBreak", "c1100_GuardBreak.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Parrying", "c1100_Parrying.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_HitToDeath", "c1100_HitToDeath.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Death", "c1100_Death.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_BurnToDeath", "c1100_BurnToDeath.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_BackAttackHit", "c1100_BackAttackHit.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_AfterGuardBreakHit", "c1100_AfterGuardBreakHit.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared1", "c1100_PrayToBeScared1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared2", "c1100_PrayToBeScared2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared3", "c1100_PrayToBeScared3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_BeScaredToIdle", "c1100_BeScaredToIdle.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_BeScared", "c1100_BeScared.FBX", { 0.1f, true });

	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle1", "c1100_Spear_Idle1.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2", "c1100_Spear_Idle2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle3", "c1100_Spear_Idle3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2ToIdle1", "c1100_Spear_Idle2ToIdle1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle1ToIdle2", "c1100_Spear_Idle1ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2ToIdle3", "c1100_Spear_Idle2ToIdle3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle3ToIdle2", "c1100_Spear_Idle3ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Front2", "c1100_Spear_Walk_Front2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Back2", "c1100_Spear_Walk_Back2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Left2", "c1100_Spear_Walk_Left2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Right2", "c1100_Spear_Walk_Right2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Front3", "c1100_Spear_Walk_Front3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Back3", "c1100_Spear_Walk_Back3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Left3", "c1100_Spear_Walk_Left3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Right3", "c1100_Spear_Walk_Right3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Run2", "c1100_Spear_Run2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Run3", "c1100_Spear_Run3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Scout", "c1100_Spear_Scout.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Pike1", "c1100_Spear_Pike1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Pike2", "c1100_Spear_Pike2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_StepAndPike", "c1100_Spear_StepAndPike.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Swing", "c1100_Spear_Swing.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_RunToPike", "c1100_Spear_RunToPike.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_ShieldCharge", "c1100_Spear_ShieldCharge.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_TriplePike", "c1100_Spear_TriplePike.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left2", "c1100_Spear_Turn_Left2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right2", "c1100_Spear_Turn_RIght2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice2", "c1100_Spear_Turn_Left_Twice2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice2", "c1100_Spear_Turn_RIght_Twice2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left1", "c1100_Spear_Turn_Left1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right1", "c1100_Spear_Turn_RIght1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice1", "c1100_Spear_Turn_Left_Twice1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice1", "c1100_Spear_Turn_RIght_Twice1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left3", "c1100_Spear_Turn_Left3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right3", "c1100_Spear_Turn_RIght3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice3", "c1100_Spear_Turn_Left_Twice3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice3", "c1100_Spear_Turn_RIght_Twice3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Front", "c1100_Spear_Hit_Front.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Back", "c1100_Spear_Hit_Back.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Left", "c1100_Spear_Hit_Left.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Right", "c1100_Spear_Hit_Right.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Guard", "c1100_Spear_Guard.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_AttackFail", "c1100_Spear_AttackFail.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_GuardBreak", "c1100_Spear_GuardBreak.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Parrying", "c1100_Spear_Parrying.FBX", { 0.1f, false });

	MainRenderer->CreateFBXAnimation("c1100_Lantern_Idle", "c1100_Lantern_Idle.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Front", "c1100_Lantern_Walk_Front.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Back", "c1100_Lantern_Walk_Back.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Left", "c1100_Lantern_Walk_Left.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Right", "c1100_Lantern_Walk_Right.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Run", "c1100_Lantern_Run.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Scout", "c1100_Lantern_Scout.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_AwakeHollows", "c1100_Lantern_AwakeHollows.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Left", "c1100_Lantern_Turn_Left.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Right", "c1100_Lantern_Turn_Right.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Left_Twice", "c1100_Lantern_Turn_Left_Twice.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Right_Twice", "c1100_Lantern_Turn_Right_Twice.FBX", { 0.1f, false });
}



//void Monster_Hollow::MeshOnOffSwitch(Enum_Hollow_MeshIndex _Index)
//{
//	MainRenderer->GetRenderUnits()[static_cast<int>(_Index)][0]->OnOffSwitch();
//}