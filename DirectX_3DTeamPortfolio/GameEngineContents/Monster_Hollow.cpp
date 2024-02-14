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

	//MainRenderer->SetFBXMesh("c1100.fbx", "FBXAnimationTexture");
	MainRenderer->SetFBXMesh("c1100.fbx", "FBX_Animation");

	/*Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();*/
	

	CreateAnimation();
	//SettingRootMotion();

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

void Monster_Hollow::CreateAnimation()
{
	MainRenderer->CreateFBXAnimation("c1100_Idle1", "c1100_Idle1.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle2", "c1100_Idle2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle3", "c1100_Idle3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray1", "c1100_Pray1.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray2", "c1100_Pray2.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray3", "c1100_Pray3.FBX", { 0.1f, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle1", "c1100_Idle2ToIdle1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle1ToIdle2", "c1100_Idle1ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle3", "c1100_Idle2ToIdle3.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle3ToIdle2", "c1100_Idle3ToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle1", "c1100_PrayToIdle1.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle2", "c1100_PrayToIdle2.FBX", { 0.1f, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle3", "c1100_PrayToIdle3.FBX", { 0.1f, false });
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

//void Monster_Hollow::SettingRootMotion()
//{
//	MainRenderer->SetRootMotionComponent(Capsule.get());
//	MainRenderer->SetRootMotion("c1100_Idle1");
//	MainRenderer->SetRootMotion("c1100_Idle2");
//	MainRenderer->SetRootMotion("c1100_Idle3");
//	MainRenderer->SetRootMotion("c1100_Pray1");
//	MainRenderer->SetRootMotion("c1100_Pray2");
//	MainRenderer->SetRootMotion("c1100_Pray3");
//	MainRenderer->SetRootMotion("c1100_PrayToIdle1");
//	MainRenderer->SetRootMotion("c1100_PrayToIdle2");
//	MainRenderer->SetRootMotion("c1100_PrayToIdle3");
//	MainRenderer->SetRootMotion("c1100_Idle2ToIdle1");
//	MainRenderer->SetRootMotion("c1100_Idle1ToIdle2");
//	MainRenderer->SetRootMotion("c1100_Idle2ToIdle3");
//	MainRenderer->SetRootMotion("c1100_Idle3ToIdle2");
//	MainRenderer->SetRootMotion("c1100_Walk_Front");
//	MainRenderer->SetRootMotion("c1100_Walk_Back");
//	MainRenderer->SetRootMotion("c1100_Walk_Left");
//	MainRenderer->SetRootMotion("c1100_Walk_Right");
//	MainRenderer->SetRootMotion("c1100_Walk_Front3");
//	MainRenderer->SetRootMotion("c1100_Walk_Back3");
//	MainRenderer->SetRootMotion("c1100_Walk_Left3");
//	MainRenderer->SetRootMotion("c1100_Walk_Right3");
//	MainRenderer->SetRootMotion("c1100_Run");
//	MainRenderer->SetRootMotion("c1100_Run3");
//	MainRenderer->SetRootMotion("c1100_Scout");
//	MainRenderer->SetRootMotion("c1100_RH_VerticalSlash");
//	MainRenderer->SetRootMotion("c1100_RH_HorizontalSlash");
//	MainRenderer->SetRootMotion("c1100_RH_ChargingSting");
//	MainRenderer->SetRootMotion("c1100_RH_RunToSting");
//	MainRenderer->SetRootMotion("c1100_LH_Fist");
//	MainRenderer->SetRootMotion("c1100_TH_VerticalSlash");
//	MainRenderer->SetRootMotion("c1100_RH_ComboAttack");
//	MainRenderer->SetRootMotion("c1100_RH_ChargingSlash");
//	MainRenderer->SetRootMotion("c1100_RH_Sting");
//	MainRenderer->SetRootMotion("c1100_RH_TwinSlash");
//	MainRenderer->SetRootMotion("c1100_Turn_Left2");
//	MainRenderer->SetRootMotion("c1100_Turn_Right2");
//	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice2");
//	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice2");
//	MainRenderer->SetRootMotion("c1100_Turn_Left");
//	MainRenderer->SetRootMotion("c1100_Turn_Right");
//	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice");
//	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice");
//	MainRenderer->SetRootMotion("c1100_Turn_Left3");
//	MainRenderer->SetRootMotion("c1100_Turn_Right3");
//	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice3");
//	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice3");
//	MainRenderer->SetRootMotion("c1100_Hit_Front");
//	MainRenderer->SetRootMotion("c1100_Hit_Back");
//	MainRenderer->SetRootMotion("c1100_Hit_Left");
//	MainRenderer->SetRootMotion("c1100_Hit_Right");
//	MainRenderer->SetRootMotion("c1100_Guard");
//	MainRenderer->SetRootMotion("c1100_AttackFail");
//	MainRenderer->SetRootMotion("c1100_GuardBreak");
//	MainRenderer->SetRootMotion("c1100_Parrying");
//	MainRenderer->SetRootMotion("c1100_HitToDeath");
//	MainRenderer->SetRootMotion("c1100_Death");
//	MainRenderer->SetRootMotion("c1100_BurnToDeath");
//	MainRenderer->SetRootMotion("c1100_BackAttackHit");
//	MainRenderer->SetRootMotion("c1100_AfterGuardBreakHit");
//	MainRenderer->SetRootMotion("c1100_PrayToBeScared1");
//	MainRenderer->SetRootMotion("c1100_PrayToBeScared2");
//	MainRenderer->SetRootMotion("c1100_PrayToBeScared3");
//	MainRenderer->SetRootMotion("c1100_BeScaredToIdle");
//	MainRenderer->SetRootMotion("c1100_BeScared");
//
//	MainRenderer->SetRootMotion("c1100_Spear_Idle1");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle2");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle3");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle2ToIdle1");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle1ToIdle2");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle2ToIdle3");
//	MainRenderer->SetRootMotion("c1100_Spear_Idle3ToIdle2");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Front2");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Back2");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Left2");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Right2");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Front3");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Back3");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Left3");
//	MainRenderer->SetRootMotion("c1100_Spear_Walk_Right3");
//	MainRenderer->SetRootMotion("c1100_Spear_Run2");
//	MainRenderer->SetRootMotion("c1100_Spear_Run3");
//	MainRenderer->SetRootMotion("c1100_Spear_Scout");
//	MainRenderer->SetRootMotion("c1100_Spear_Pike1");
//	MainRenderer->SetRootMotion("c1100_Spear_Pike2");
//	MainRenderer->SetRootMotion("c1100_Spear_StepAndPike");
//	MainRenderer->SetRootMotion("c1100_Spear_Swing");
//	MainRenderer->SetRootMotion("c1100_Spear_RunToPike");
//	MainRenderer->SetRootMotion("c1100_Spear_ShieldCharge");
//	MainRenderer->SetRootMotion("c1100_Spear_TriplePike");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left2");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right2");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice2");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice2");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left1");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right1");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice1");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice1");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left3");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right3");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice3");
//	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice3");
//	MainRenderer->SetRootMotion("c1100_Spear_Hit_Front");
//	MainRenderer->SetRootMotion("c1100_Spear_Hit_Back");
//	MainRenderer->SetRootMotion("c1100_Spear_Hit_Left");
//	MainRenderer->SetRootMotion("c1100_Spear_Hit_Right");
//	MainRenderer->SetRootMotion("c1100_Spear_Guard");
//	MainRenderer->SetRootMotion("c1100_Spear_AttackFail");
//	MainRenderer->SetRootMotion("c1100_Spear_GuardBreak");
//	MainRenderer->SetRootMotion("c1100_Spear_Parrying");
//
//	MainRenderer->SetRootMotion("c1100_Lantern_Idle");
//	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Front");
//	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Back");
//	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Left");
//	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Right");
//	MainRenderer->SetRootMotion("c1100_Lantern_Run");
//	MainRenderer->SetRootMotion("c1100_Lantern_Scout");
//	MainRenderer->SetRootMotion("c1100_Lantern_AwakeHollows");
//	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Left");
//	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Right");
//	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Left_Twice");
//	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Right_Twice");
//}



//void Monster_Hollow::MeshOnOffSwitch(Enum_Hollow_MeshIndex _Index)
//{
//	MainRenderer->GetRenderUnits()[static_cast<int>(_Index)][0]->OnOffSwitch();
//}