#include "PreCompile.h"
#include "Monster_Hollow.h"
#include "BasePlayer.h"
#include "BoneSocketCollision.h"

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

	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();
	

	CreateAnimation();
	SettingRootMotion();
	SoundLoad();
	SettingSoundFrameEvent();

	{
		MainRenderer->ChangeAnimation("c1100_Idle1");
	}

	for (int i = 0; i < static_cast<int>(Enum_Hollow_MeshIndex::None); i++)
	{
		MainRenderer->GetRenderUnits()[i][0]->Off();
	}

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Bone);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::UpperBody);

	RecognizeCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	RecognizeCollision->SetCollisionType(ColType::SPHERE3D);
	RecognizeCollision->SetCollisionColor(float4::BLACK);
	RecognizeCollision->Transform.SetLocalPosition(float4(0.0f, 100.0f, 0.0f));
	RecognizeCollision->Transform.SetWorldScale(float4(500.0f, 500.0f, 500.0f));

	/*AttackRangeCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	AttackRangeCollision->SetCollisionType(ColType::SPHERE3D);
	AttackRangeCollision->SetCollisionColor(float4::RED);
	AttackRangeCollision->Transform.SetLocalPosition(float4(0, 100, 0));
	AttackRangeCollision->Transform.SetWorldScale(float4(300, 300, 300));*/

	BodyCollision = CreateSocketCollision(Enum_CollisionOrder::Monster_Body, Enum_Hollow_BoneType::Spine, { float4(100.0f, 100.0f, 100.0f), float4::ZERONULL, float4::ZERO }, "Spine");
	
	BodyCollision->On();

	MonsterCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster);
	MonsterCollision->SetCollisionType(ColType::SPHERE3D);
	MonsterCollision->Transform.SetWorldScale(float4(1.0f, 1.0f, 1.0f));


	// UISetting
	//CreateMonsterUI(0);
}

void Monster_Hollow::Update(float _Delta)
{
	BaseMonster::Update(_Delta);
}

void Monster_Hollow::Release()
{
	BaseMonster::Release();
}

void Monster_Hollow::LevelStart(class GameEngineLevel* _NextLevel)
{
	BaseMonster::LevelStart(_NextLevel);
}

void Monster_Hollow::LevelEnd(class GameEngineLevel* _NextLevel)
{

}

void Monster_Hollow::CreateAnimation()
{
	const float Inter = 0.0f;
	MainRenderer->CreateFBXAnimation("c1100_Idle1", "c1100_Idle1.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle2", "c1100_Idle2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle3", "c1100_Idle3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray1", "c1100_Pray1.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray2", "c1100_Pray2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Pray3", "c1100_Pray3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle1", "c1100_Idle2ToIdle1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle1ToIdle2", "c1100_Idle1ToIdle2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle2ToIdle3", "c1100_Idle2ToIdle3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Idle3ToIdle2", "c1100_Idle3ToIdle2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle1", "c1100_PrayToIdle1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle2", "c1100_PrayToIdle2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToIdle3", "c1100_PrayToIdle3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Front", "c1100_Walk_Front.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Back", "c1100_Walk_Back.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Left", "c1100_Walk_Left.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Right", "c1100_Walk_Right.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Front3", "c1100_Walk_Front3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Back3", "c1100_Walk_Back3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Left3", "c1100_Walk_Left3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Walk_Right3", "c1100_Walk_Right3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Run", "c1100_Run.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Run3", "c1100_Run3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Scout", "c1100_Scout.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_RH_VerticalSlash", "c1100_RH_VerticalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_HorizontalSlash", "c1100_RH_HorizontalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ChargingSting", "c1100_RH_ChargingSting.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_RunToSting", "c1100_RH_RunToSting.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_LH_Fist", "c1100_LH_Fist.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_TH_VerticalSlash", "c1100_TH_VerticalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ComboAttack", "c1100_RH_ComboAttack.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_ChargingSlash", "c1100_RH_ChargingSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_Sting", "c1100_RH_Sting.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_RH_TwinSlash", "c1100_RH_TwinSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left2", "c1100_Turn_Left2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right2", "c1100_Turn_Right2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice2", "c1100_Turn_Left_Twice2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice2", "c1100_Turn_Right_Twice2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left", "c1100_Turn_Left.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right", "c1100_Turn_Right.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice", "c1100_Turn_Left_Twice.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice", "c1100_Turn_Right_Twice.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left3", "c1100_Turn_Left3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right3", "c1100_Turn_Right3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Left_Twice3", "c1100_Turn_Left_Twice3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Turn_Right_Twice3", "c1100_Turn_Right_Twice3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Front", "c1100_Hit_Front.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Back", "c1100_Hit_Back.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Left", "c1100_Hit_Left.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Hit_Right", "c1100_Hit_Right.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Guard", "c1100_Guard.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_AttackFail", "c1100_AttackFail.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_GuardBreak", "c1100_GuardBreak.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Parrying", "c1100_Parrying.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_HitToDeath", "c1100_HitToDeath.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Death", "c1100_Death.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BurnToDeath", "c1100_BurnToDeath.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BackAttackHit", "c1100_BackAttackHit.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BackAttackDeath", "c1100_BackAttackDeath.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_AfterGuardBreakHit", "c1100_AfterGuardBreakHit.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_AfterGuardBreakDeath", "c1100_AfterGuardBreakDeath.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared1", "c1100_PrayToBeScared1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared2", "c1100_PrayToBeScared2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_PrayToBeScared3", "c1100_PrayToBeScared3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BeScaredToIdle", "c1100_BeScaredToIdle.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BeScared", "c1100_BeScared.FBX", { Inter, true });

	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle1", "c1100_Spear_Idle1.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2", "c1100_Spear_Idle2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle3", "c1100_Spear_Idle3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2ToIdle1", "c1100_Spear_Idle2ToIdle1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle1ToIdle2", "c1100_Spear_Idle1ToIdle2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle2ToIdle3", "c1100_Spear_Idle2ToIdle3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Idle3ToIdle2", "c1100_Spear_Idle3ToIdle2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Front2", "c1100_Spear_Walk_Front2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Back2", "c1100_Spear_Walk_Back2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Left2", "c1100_Spear_Walk_Left2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Right2", "c1100_Spear_Walk_Right2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Front3", "c1100_Spear_Walk_Front3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Back3", "c1100_Spear_Walk_Back3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Left3", "c1100_Spear_Walk_Left3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Walk_Right3", "c1100_Spear_Walk_Right3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Run2", "c1100_Spear_Run2.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Run3", "c1100_Spear_Run3.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Scout", "c1100_Spear_Scout.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Pike1", "c1100_Spear_Pike1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Pike2", "c1100_Spear_Pike2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_StepAndPike", "c1100_Spear_StepAndPike.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Swing", "c1100_Spear_Swing.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_RunToPike", "c1100_Spear_RunToPike.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_ShieldCharge", "c1100_Spear_ShieldCharge.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_TriplePike", "c1100_Spear_TriplePike.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left2", "c1100_Spear_Turn_Left2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right2", "c1100_Spear_Turn_RIght2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice2", "c1100_Spear_Turn_Left_Twice2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice2", "c1100_Spear_Turn_RIght_Twice2.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left1", "c1100_Spear_Turn_Left1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right1", "c1100_Spear_Turn_RIght1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice1", "c1100_Spear_Turn_Left_Twice1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice1", "c1100_Spear_Turn_RIght_Twice1.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left3", "c1100_Spear_Turn_Left3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right3", "c1100_Spear_Turn_RIght3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Left_Twice3", "c1100_Spear_Turn_Left_Twice3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Turn_Right_Twice3", "c1100_Spear_Turn_RIght_Twice3.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Front", "c1100_Spear_Hit_Front.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Back", "c1100_Spear_Hit_Back.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Left", "c1100_Spear_Hit_Left.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Hit_Right", "c1100_Spear_Hit_Right.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Guard", "c1100_Spear_Guard.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_AttackFail", "c1100_Spear_AttackFail.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_GuardBreak", "c1100_Spear_GuardBreak.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Spear_Parrying", "c1100_Spear_Parrying.FBX", { Inter, false });

	MainRenderer->CreateFBXAnimation("c1100_BrokenSword_RH_VerticalSlash", "c1100_BrokenSword_RH_VerticalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BrokenSword_RH_HorizontalSlash", "c1100_BrokenSword_RH_HorizontalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BrokenSword_TH_VerticalSlash", "c1100_BrokenSword_TH_VerticalSlash.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BrokenSword_RH_ComboAttack", "c1100_BrokenSword_RH_ComboAttack.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_BrokenSword_RH_RunToSlash", "c1100_BrokenSword_RH_RunToSlash.FBX", { Inter, false });

	MainRenderer->CreateFBXAnimation("c1100_Lantern_Idle", "c1100_Lantern_Idle.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_IdleToStay", "c1100_Lantern_IdleToStay.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_StayToIdle", "c1100_Lantern_StayToIdle.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Front", "c1100_Lantern_Walk_Front.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Back", "c1100_Lantern_Walk_Back.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Left", "c1100_Lantern_Walk_Left.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Walk_Right", "c1100_Lantern_Walk_Right.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Run", "c1100_Lantern_Run.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Scout", "c1100_Lantern_Scout.FBX", { Inter, true });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_AwakeHollows", "c1100_Lantern_AwakeHollows.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Left", "c1100_Lantern_Turn_Left.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Right", "c1100_Lantern_Turn_Right.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Left_Twice", "c1100_Lantern_Turn_Left_Twice.FBX", { Inter, false });
	MainRenderer->CreateFBXAnimation("c1100_Lantern_Turn_Right_Twice", "c1100_Lantern_Turn_Right_Twice.FBX", { Inter, false });
}

void Monster_Hollow::SettingRootMotion()
{
	MainRenderer->SetRootMotionComponent(Capsule.get());
	//MainRenderer->SetRootMotion("c1100_Idle1");
	//MainRenderer->SetRootMotion("c1100_Idle2");
	//MainRenderer->SetRootMotion("c1100_Idle3");
	//MainRenderer->SetRootMotion("c1100_Pray1");
	//MainRenderer->SetRootMotion("c1100_Pray2");
	//MainRenderer->SetRootMotion("c1100_Pray3");
	MainRenderer->SetRootMotion("c1100_PrayToIdle1");
	MainRenderer->SetRootMotion("c1100_PrayToIdle2");
	MainRenderer->SetRootMotion("c1100_PrayToIdle3");
	//MainRenderer->SetRootMotion("c1100_Idle2ToIdle1");
	//MainRenderer->SetRootMotion("c1100_Idle1ToIdle2");
	//MainRenderer->SetRootMotion("c1100_Idle2ToIdle3");
	//MainRenderer->SetRootMotion("c1100_Idle3ToIdle2");
	MainRenderer->SetRootMotion("c1100_Walk_Front");
	MainRenderer->SetRootMotion("c1100_Walk_Back");
	MainRenderer->SetRootMotion("c1100_Walk_Left");
	MainRenderer->SetRootMotion("c1100_Walk_Right");
	MainRenderer->SetRootMotion("c1100_Walk_Front3");
	MainRenderer->SetRootMotion("c1100_Walk_Back3");
	MainRenderer->SetRootMotion("c1100_Walk_Left3");
	MainRenderer->SetRootMotion("c1100_Walk_Right3");
	MainRenderer->SetRootMotion("c1100_Run");
	MainRenderer->SetRootMotion("c1100_Run3");
	MainRenderer->SetRootMotion("c1100_Scout");
	MainRenderer->SetRootMotion("c1100_RH_VerticalSlash");
	MainRenderer->SetRootMotion("c1100_RH_HorizontalSlash");
	MainRenderer->SetRootMotion("c1100_RH_ChargingSting");
	MainRenderer->SetRootMotion("c1100_RH_RunToSting");
	MainRenderer->SetRootMotion("c1100_LH_Fist");
	MainRenderer->SetRootMotion("c1100_TH_VerticalSlash");
	MainRenderer->SetRootMotion("c1100_RH_ComboAttack");
	//MainRenderer->SetRootMotion("c1100_RH_ChargingSlash");
	MainRenderer->SetRootMotion("c1100_RH_Sting");
	MainRenderer->SetRootMotion("c1100_RH_TwinSlash");
	MainRenderer->SetRootMotion("c1100_Turn_Left2");
	MainRenderer->SetRootMotion("c1100_Turn_Right2");
	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice2");
	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice2");
	MainRenderer->SetRootMotion("c1100_Turn_Left");
	MainRenderer->SetRootMotion("c1100_Turn_Right");
	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice");
	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice");
	MainRenderer->SetRootMotion("c1100_Turn_Left3");
	MainRenderer->SetRootMotion("c1100_Turn_Right3");
	MainRenderer->SetRootMotion("c1100_Turn_Left_Twice3");
	MainRenderer->SetRootMotion("c1100_Turn_Right_Twice3");
	//MainRenderer->SetRootMotion("c1100_Hit_Front");
	//MainRenderer->SetRootMotion("c1100_Hit_Back");
	//MainRenderer->SetRootMotion("c1100_Hit_Left");
	//MainRenderer->SetRootMotion("c1100_Hit_Right");
	//MainRenderer->SetRootMotion("c1100_Guard");
	//MainRenderer->SetRootMotion("c1100_AttackFail");
	//MainRenderer->SetRootMotion("c1100_GuardBreak");
	//MainRenderer->SetRootMotion("c1100_Parrying");
	MainRenderer->SetRootMotion("c1100_HitToDeath");
	//MainRenderer->SetRootMotion("c1100_Death");
	MainRenderer->SetRootMotion("c1100_BurnToDeath");
	MainRenderer->SetRootMotion("c1100_BackAttackHit");
	MainRenderer->SetRootMotion("c1100_AfterGuardBreakHit");
	MainRenderer->SetRootMotion("c1100_PrayToBeScared1");
	MainRenderer->SetRootMotion("c1100_PrayToBeScared2");
	MainRenderer->SetRootMotion("c1100_PrayToBeScared3");
	MainRenderer->SetRootMotion("c1100_BeScaredToIdle");
	//MainRenderer->SetRootMotion("c1100_BeScared");

	//MainRenderer->SetRootMotion("c1100_Spear_Idle1");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle2");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle3");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle2ToIdle1");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle1ToIdle2");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle2ToIdle3");
	//MainRenderer->SetRootMotion("c1100_Spear_Idle3ToIdle2");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Front2");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Back2");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Left2");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Right2");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Front3");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Back3");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Left3");
	MainRenderer->SetRootMotion("c1100_Spear_Walk_Right3");
	MainRenderer->SetRootMotion("c1100_Spear_Run2");
	MainRenderer->SetRootMotion("c1100_Spear_Run3");
	MainRenderer->SetRootMotion("c1100_Spear_Scout");
	MainRenderer->SetRootMotion("c1100_Spear_Pike1");
	MainRenderer->SetRootMotion("c1100_Spear_Pike2");
	MainRenderer->SetRootMotion("c1100_Spear_StepAndPike");
	MainRenderer->SetRootMotion("c1100_Spear_Swing");
	MainRenderer->SetRootMotion("c1100_Spear_RunToPike");
	MainRenderer->SetRootMotion("c1100_Spear_ShieldCharge");
	MainRenderer->SetRootMotion("c1100_Spear_TriplePike");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left2");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right2");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice2");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice2");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left1");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right1");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice1");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice1");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left3");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right3");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Left_Twice3");
	MainRenderer->SetRootMotion("c1100_Spear_Turn_Right_Twice3");
	//MainRenderer->SetRootMotion("c1100_Spear_Hit_Front");
	//MainRenderer->SetRootMotion("c1100_Spear_Hit_Back");
	//MainRenderer->SetRootMotion("c1100_Spear_Hit_Left");
	//MainRenderer->SetRootMotion("c1100_Spear_Hit_Right");
	//MainRenderer->SetRootMotion("c1100_Spear_Guard");
	//MainRenderer->SetRootMotion("c1100_Spear_AttackFail");
	//MainRenderer->SetRootMotion("c1100_Spear_GuardBreak");
	//MainRenderer->SetRootMotion("c1100_Spear_Parrying");

	MainRenderer->SetRootMotion("c1100_BrokenSword_RH_VerticalSlash");
	MainRenderer->SetRootMotion("c1100_BrokenSword_RH_HorizontalSlash");
	MainRenderer->SetRootMotion("c1100_BrokenSword_TH_VerticalSlash");
	MainRenderer->SetRootMotion("c1100_BrokenSword_RH_ComboAttack");
	MainRenderer->SetRootMotion("c1100_BrokenSword_RH_RunToSlash");

	MainRenderer->SetRootMotion("c1100_Lantern_Idle");
	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Front");
	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Back");
	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Left");
	MainRenderer->SetRootMotion("c1100_Lantern_Walk_Right");
	MainRenderer->SetRootMotion("c1100_Lantern_Run");
	MainRenderer->SetRootMotion("c1100_Lantern_Scout");
	MainRenderer->SetRootMotion("c1100_Lantern_AwakeHollows");
	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Left");
	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Right");
	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Left_Twice");
	MainRenderer->SetRootMotion("c1100_Lantern_Turn_Right_Twice");
}

void Monster_Hollow::FindTarget()
{
	if (true == IsTargeting())
	{
		return;
	}

	if (nullptr == RecognizeCollision)
	{
		MsgBoxAssert("충돌체 없음.");
		return;
	}

	std::shared_ptr<GameEngineActor> OtherActor;

	RecognizeCollision->Collision(Enum_CollisionOrder::Player, [&OtherActor](std::vector<GameEngineCollision*>& _Other)
		{
			for (GameEngineCollision* OtherCol : _Other)
			{
				if (nullptr == OtherCol)
				{
					MsgBoxAssert("OtherCol 없음.");
					return;
				}

				OtherActor = OtherCol->GetActor()->GetDynamic_Cast_This<GameEngineActor>();

				if (nullptr == OtherActor)
				{
					MsgBoxAssert("OtherActor 실패.");
					return;
				}

			}
		});

	bool FindValue = (nullptr != OtherActor);
	if (FindValue)
	{
		RecognizeCollision->Off();
		SetTargeting(OtherActor.get());
	}
}

bool Monster_Hollow::IsTargetInAngle(float _fAngle) const
{
	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

	if (AbsTargetAngle < _fAngle)
	{
		return true;
	}

	return false;
}

void Monster_Hollow::RotToTarget(float _Delta)
{
	/*const float fRotDir = BaseActor::GetRotDir_f();
	const float RotAngle = fRotDir * 300.0f * _Delta;

	Capsule->AddWorldRotation(float4(0.0f, RotAngle, 0.0f));*/

	BaseActor::RotToTarget(_Delta, 150.0f, 500.0f);
}



//void Monster_Hollow::MeshOnOffSwitch(Enum_Hollow_MeshIndex _Index)
//{
//	MainRenderer->GetRenderUnits()[static_cast<int>(_Index)][0]->OnOffSwitch();
//}

void Monster_Hollow::SoundLoad()
{
	GameEngineDirectory Dir;
	Dir.SetCurrentPath();
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Sound\\c1100");
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (int i = 0; i < AllFile.size(); i++)
	{
		GameEngineSound::Sound3DLoad(AllFile[i].GetStringPath());
	}
}

void Monster_Hollow::SettingSoundFrameEvent()
{
	MainRenderer->SetFrameEvent("c1100_Idle1", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			// float4 자리에 Spine Bone Position 넣을것.
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle2", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//GameEngineSound::Sound3DPlay("c110008000.wav", float4);
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle3", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//GameEngineSound::Sound3DPlay("c110008000.wav", float4);
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Pray1", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//GameEngineSound::Sound3DPlay("c110008008.wav", float4);
			GameEngineSound::Sound3DPlay("c110008008.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Pray2", 49, [&](GameContentsFBXRenderer* _Renderer)
		{
			//GameEngineSound::Sound3DPlay("c110008008.wav", float4);
			GameEngineSound::Sound3DPlay("c110008008.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Pray3", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//GameEngineSound::Sound3DPlay("c110008008.wav", float4);
			GameEngineSound::Sound3DPlay("c110008008.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle2ToIdle1", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle2ToIdle1", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle1ToIdle2", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle1ToIdle2", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle2ToIdle3", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle3ToIdle2", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Idle3ToIdle2", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle1", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle1", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006100
			GameEngineSound::Sound3DPlay("c110006100.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle1", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle2", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006100
			GameEngineSound::Sound3DPlay("c110006100.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle2", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle3", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle3", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006100
			GameEngineSound::Sound3DPlay("c110006100.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToIdle3", 42, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front3", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Front3", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back3", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Back3", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left3", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Left3", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right3", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Walk_Right3", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run3", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run3", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Run3", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Scout", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Scout", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Scout", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_VerticalSlash", 91, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 25, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 62, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 75, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_HorizontalSlash", 85, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 42, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 47, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 59, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 101, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 102, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 122, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_ChargingSting", 137, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 38, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 45, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 82, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 94, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 102, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 127, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_RunToSting", 146, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006100
			GameEngineSound::Sound3DPlay("c110006100.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 60, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 97, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_TH_VerticalSlash", 107, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_Sting", 99, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006100
			GameEngineSound::Sound3DPlay("c110006100.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 64, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_RH_TwinSlash", 99, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left2", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left2", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left2", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right2", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right2", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right2", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice2", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice2", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice2", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice2", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice2", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice2", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left3", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left3", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left3", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right3", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right3", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right3", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice3", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice3", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Left_Twice3", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice3", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice3", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Turn_Right_Twice3", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Front", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Front", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Front", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Front", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Back", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Back", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Back", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Back", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Back", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Left", 33, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Hit_Right", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});
	MainRenderer->SetFrameEvent("c1100_Hit_Right", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});
	MainRenderer->SetFrameEvent("c1100_Hit_Right", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});
	MainRenderer->SetFrameEvent("c1100_Hit_Right", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});
	MainRenderer->SetFrameEvent("c1100_Hit_Right", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});
	MainRenderer->SetFrameEvent("c1100_Hit_Right", 35, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Guard", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AttackFail", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AttackFail", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999987
			//kill-kick
			GameEngineSound::Sound3DPlay("kill-kick.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AttackFail", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AttackFail", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AttackFail", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999986
			GameEngineSound::Sound3DPlay("c999999986.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_GuardBreak", 49, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Parrying", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999991
			// kill_successx2
			GameEngineSound::Sound3DPlay("kill-successx2.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Parrying", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Parrying", 48, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999997
			//kill3
			GameEngineSound::Sound3DPlay("kill3.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008003
			GameEngineSound::Sound3DPlay("c110008003.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 62, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004001
			GameEngineSound::Sound3DPlay("c110004001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 63, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006502
			GameEngineSound::Sound3DPlay("c110006502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_HitToDeath", 82, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006501
			GameEngineSound::Sound3DPlay("c110006501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 64, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 71, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 73, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 76, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006501
			GameEngineSound::Sound3DPlay("c110006501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004001
			GameEngineSound::Sound3DPlay("c110004001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 79, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006502
			GameEngineSound::Sound3DPlay("c110006502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 109, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 124, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 131, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 146, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackHit", 160, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackDeath", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999997
			//kill3
			GameEngineSound::Sound3DPlay("kill3.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackDeath", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008003
			GameEngineSound::Sound3DPlay("c110008003.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BackAttackDeath", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004101
			GameEngineSound::Sound3DPlay("c110004101.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 34, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 62, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004101
			GameEngineSound::Sound3DPlay("c110004101.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 111, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004001
			GameEngineSound::Sound3DPlay("c110004001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 115, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006501
			GameEngineSound::Sound3DPlay("c110006501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 118, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006502
			GameEngineSound::Sound3DPlay("c110006502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 127, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006501
			GameEngineSound::Sound3DPlay("c110006501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 134, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 150, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 160, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakHit", 179, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakDeath", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008003
			GameEngineSound::Sound3DPlay("c110008003.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_AfterGuardBreakDeath", 65, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110004101
			GameEngineSound::Sound3DPlay("c110004101.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToBeScared1", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008009
			GameEngineSound::Sound3DPlay("c110008009.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToBeScared2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008009
			GameEngineSound::Sound3DPlay("c110008009.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_PrayToBeScared3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008009
			GameEngineSound::Sound3DPlay("c110008009.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScaredToIdle", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScaredToIdle", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScaredToIdle", 52, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScared", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScared", 59, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BeScared", 123, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});


	//Spear
	MainRenderer->SetFrameEvent("c1100_Spear_Idle1", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle3", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle1", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle1", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle1", 35, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006503
			GameEngineSound::Sound3DPlay("c110006503.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle1Toidle2", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle1Toidle2", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle1Toidle2", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005502
			GameEngineSound::Sound3DPlay("c110005502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle3", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle3", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005502
			GameEngineSound::Sound3DPlay("c110005502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle2Toidle3", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle3Toidle2", 5, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle3Toidle2", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Idle3Toidle2", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005502
			GameEngineSound::Sound3DPlay("c110005502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front2", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front2", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back2", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back2", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left2", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left2", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right2", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right2", 35, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front3", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Front3", 44, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back3", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Back3", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left3", 34, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Left3", 62, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right3", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008004
			GameEngineSound::Sound3DPlay("c110008004.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right3", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Walk_Right3", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run2", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run2", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run2", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run3", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run2", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Run2", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Scout", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Scout", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Scout", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike1", 49, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Pike2", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 34, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 58, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 70, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 75, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 89, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 117, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_StepAndPike", 138, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 47, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 72, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Swing", 84, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 23, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 76, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_RunToPike", 95, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 52, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});


	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 55, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 60, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 70, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006001
			GameEngineSound::Sound3DPlay("c110006001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_TriplePike", 84, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left2", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left2", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left2", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right2", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right2", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right2", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice2", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice2", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice2", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice2", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice2", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice2", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left1", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left1", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left1", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right1", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right1", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right1", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice1", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice1", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice1", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice1", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice1", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice1", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left3", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left3", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left3", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right3", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right3", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right3", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice3", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice3", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Left_Twice3", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice3", 12, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice3", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Turn_Right_Twice3", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Front", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Front", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Front", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Front", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Back", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Back", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Back", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Back", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Back", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Left", 33, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999999
			//damage1
			GameEngineSound::Sound3DPlay("damage1.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008002
			GameEngineSound::Sound3DPlay("c110008002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 6, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Hit_Right", 33, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Guard", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Guard", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005502
			GameEngineSound::Sound3DPlay("c110005502.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999987
			//kill-kick
			GameEngineSound::Sound3DPlay("kill-kick.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 2, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 4, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_AttackFail", 38, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999986
			GameEngineSound::Sound3DPlay("c999999986.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 36, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 56, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_GuardBreak", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Parrying", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//999999991
			// kill_successx2
			GameEngineSound::Sound3DPlay("kill-successx2.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Parrying", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Parrying", 48, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Spear_Parrying", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	//BrokenSword
	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006002
			GameEngineSound::Sound3DPlay("c110006002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 40, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 17, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_VerticalSlash", 93, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006002
			GameEngineSound::Sound3DPlay("c110006002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 21, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 35, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 66, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_HorizontalSlash", 95, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006002
			GameEngineSound::Sound3DPlay("c110006002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006500
			GameEngineSound::Sound3DPlay("c110006500.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 60, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 65, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 77, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 98, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 103, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 112, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 129, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_TH_VerticalSlash", 149, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 41, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 46, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 47, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 51, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 61, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 62, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 70, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 71, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 80, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 88, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006000
			GameEngineSound::Sound3DPlay("c110006000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 90, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 95, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 103, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 115, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 133, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 136, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 163, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005504
			GameEngineSound::Sound3DPlay("c110005504.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 180, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 198, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 222, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_ComboAttack", 259, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008001
			GameEngineSound::Sound3DPlay("c110008001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110005501
			GameEngineSound::Sound3DPlay("c110005501.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110003001
			GameEngineSound::Sound3DPlay("c110003001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110006002
			GameEngineSound::Sound3DPlay("c110006002.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 47, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 53, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 57, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008005
			GameEngineSound::Sound3DPlay("c110008005.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 78, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 96, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 144, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_BrokenSword_RH_RunToSlash", 204, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	//Lantern
	MainRenderer->SetFrameEvent("c1100_Lantern_Idle", 26, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_IdleToStay", 19, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_IdleToStay", 24, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_StayToIdle", 8, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_StayToIdle", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Front", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Front", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Front", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Front", 28, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Back", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Back", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Back", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Back", 37, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Left", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Left", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Left", 39, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Right", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Right", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Right", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Walk_Right", 35, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Run", 9, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008007
			GameEngineSound::Sound3DPlay("c110008007.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Run", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Run", 14, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Run", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110002001
			GameEngineSound::Sound3DPlay("c110002001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Scout", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Scout", 16, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Scout", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Scout", 45, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 27, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008006
			GameEngineSound::Sound3DPlay("c110008006.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 41, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 54, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 65, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 68, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 139, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 142, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_AwakeHollows", 151, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right", 10, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right", 30, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left_Twice", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left_Twice", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left_Twice", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left_Twice", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Left_Twice", 31, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right_Twice", 3, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110008000
			GameEngineSound::Sound3DPlay("c110008000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right_Twice", 11, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right_Twice", 22, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001
			GameEngineSound::Sound3DPlay("c110001001.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right_Twice", 29, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110009000
			GameEngineSound::Sound3DPlay("c110009000.wav", Transform.GetWorldPosition());
		});

	MainRenderer->SetFrameEvent("c1100_Lantern_Turn_Right_Twice", 32, [&](GameContentsFBXRenderer* _Renderer)
		{
			//110001001c
			GameEngineSound::Sound3DPlay("c110001001c.wav", Transform.GetWorldPosition());
		});
}
