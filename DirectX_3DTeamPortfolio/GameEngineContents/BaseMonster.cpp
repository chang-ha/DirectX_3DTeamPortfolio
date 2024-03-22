#include "PreCompile.h"
#include "BaseMonster.h"

#include "MonsterHpBar.h"
#include "PatrolPath.h"

BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	BaseActor::Start();

	// Physx Component
	if (nullptr == Capsule)
	{
		Capsule = CreateComponent<GameEnginePhysXCapsule>();
		Capsule->PhysXComponentInit(50.0f, 50.0f);
		Capsule->SetPositioningComponent();
		Capsule->SetFiltering(Enum_CollisionOrder::Monster);
	}
}

void BaseMonster::Update(float _Delta)
{
	BaseActor::Update(_Delta);
}

void BaseMonster::Release()
{
	BaseActor::Release();
	PathObject = nullptr;
}

bool BaseMonster::CheckAnimationName(std::string _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	UpperName += ".FBX";

	std::string_view name = MainRenderer->GetCurAnimation()->Aniamtion->GetName();

	if (MainRenderer->GetCurAnimation()->Aniamtion->GetName() == UpperName)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BaseMonster::GravityOn()
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("�������� �ʴ� ������ ��ü�� ����Ϸ� �߽��ϴ�.");
		return;
	}

	Capsule->GravityOn();
}

void BaseMonster::GravityOff()
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("�������� �ʴ� ������ ��ü�� ����Ϸ� �߽��ϴ�.");
		return;
	}

	Capsule->GravityOff();
}

void BaseMonster::SetPatrolPath(const std::vector<float4>& _Paths, int _Index /*= 0*/, bool _IsOneWay /*= false*/)
{
	if (nullptr == PathObject)
	{
		PathObject = std::make_unique<PatrolPath>();
	}

	PathObject->Init(_Paths, _Index, _IsOneWay);
}

float BaseMonster::ConvertDistance_eTof(Enum_TargetDist _eTDist) const
{
	MsgBoxAssert("�ڽĿ��� �������ؾ��ϴ� �Լ��Դϴ�.");
	return 0.0f;
}

bool BaseMonster::TargetRangeCmp(Enum_TargetDist _eTDist, Enum_TargetDist _eCompareDist) const
{
	int iTargetDist = static_cast<int>(_eTDist);
	int iCompareDist = static_cast<int>(_eCompareDist);
	return (iTargetDist <= iCompareDist);
}

bool BaseMonster::IsTargetInRange(Enum_TargetDist _eTDist)
{
	const float fRange = ConvertDistance_eTof(_eTDist);
	const float fCheckDist = fRange * W_SCALE;
	const float fTargetDist = BaseActor::GetTargetDistance();
	return (fTargetDist < fCheckDist);
}

void BaseMonster::LoadRes3DSound(std::string_view _LoadCheck) const
{
	if (nullptr == GameEngineSound::Find3DSound(_LoadCheck))
	{
		std::string IdName = GetIDName();
	
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound");
		Dir.MoveChild(IdName);

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineSound::Sound3DLoad(pFile.GetStringPath());
		}
	}
}


bool BaseMonster::GetHit(const HitParameter& _Para /*= HitParameter()*/)
{
	if (nullptr == _Para.pAttacker)
	{
		MsgBoxAssert("�����ڸ� �𸣰� ����� �� ���� ����Դϴ�.");
		return false;
	}

	if (true == Hit.IsHit())
	{
		return false;
	}

	BaseActor* pAttacker = _Para.pAttacker;

	const int AttackerAtt = pAttacker->GetAtt();
	const int Stiffness = _Para.iStiffness;

	Stat.AddPoise(-Stiffness);
	if (0 >= Stat.GetPoise())
	{
		SetFlag(Enum_ActorFlag::Break_Posture, true);
		Stat.SetPoise(0);
	}

	const int Damage = HitFormula(AttackerAtt);
	Stat.AddHp(Damage);
	Hit.SetHit(true);

	if (nullptr != pAttacker)
	{
		SetTargeting(pAttacker);
	}

	Hit.SetHitDir(_Para.eDir);

	return true;
}

bool BaseMonster::GetHitToShield(const HitParameter& _Para /*= HitParameter()*/)
{
	if (nullptr == _Para.pAttacker)
	{
		MsgBoxAssert("�������� �����͸� �𸣰� ����� �� ���� ����Դϴ�.");
		return false;
	}

	if (true == Hit.IsHit())
	{
		return false;
	}

	BaseActor* pAttacker = _Para.pAttacker;

	// �и�����
	if (true == IsFlag(Enum_ActorFlag::Parrying))
	{
		pAttacker->SetHit(true);
		pAttacker->SetFlag(Enum_ActorFlag::Break_Posture, true);
		return true;
	}

	if (true == IsFlag(Enum_ActorFlag::Guarding))
	{
		const int AttackerAtt = pAttacker->GetAtt();
		const int Stiffness = _Para.iStiffness;
		Stat.AddPoise(-Stiffness);
		if (0 >= Stat.GetPoise())
		{
			SetFlag(Enum_ActorFlag::Guard_Break, true);
			Stat.SetPoise(0);

		}
		else
		{
			const int PassPoise = 50;
			if (Stiffness < PassPoise)
			{
				pAttacker->SetHit(true);
				pAttacker->SetFlag(Enum_ActorFlag::Block_Shield, true);
			}
			
			Hit.SetGuardSuccesss(true);
		}

		const int FinalDamage = GuardHitFormula(AttackerAtt);
		Stat.AddHp(FinalDamage);
		Hit.SetHit(true);

		return true;
	}

	return false;
}


static constexpr float STAB_RECOGNITION_RANGE = 1.5f;
static constexpr float STAB_POS_RANGE = 0.8f;
static constexpr float STAB_ANGLE = 45.0f;

bool BaseMonster::FrontStabCheck(const float4& _WPos, float _RotY) const
{
	if (true == IsFlag(Enum_ActorFlag::Groggy))
	{
		const float4 MyPos = Transform.GetWorldPosition();
		const float4 MyRot = Transform.GetWorldRotationEuler();
		const float4 MyXZDirVector = float4::VectorRotationToDegY(float4::FORWARD, MyRot.Y);
		const float4 OtherXZDirVector = float4::VectorRotationToDegY(float4::FORWARD, _RotY);

		// Y PosCheck << Y ���� üũ �ؾߵ�

		float4 VectorToOther = MyPos - _WPos;
		VectorToOther.Y = 0;

		const float Dist = ContentsMath::GetVector3Length(VectorToOther).X;
		const float Dot = float4::DotProduct3D(MyXZDirVector, OtherXZDirVector);
		const float Deg = ContentsMath::DotNormalizeReturnDeg(Dot);

		bool RangeCheck = (Dist < STAB_RECOGNITION_RANGE * W_SCALE);
		bool DirCheck = (Deg < STAB_ANGLE);
		return (RangeCheck && DirCheck);
	}

	return false;
}

bool BaseMonster::BackStabCheck(const float4& _WPos, float _RotY) const
{
	const float4 MyPos = Transform.GetWorldPosition();
	const float4 MyRot = Transform.GetWorldRotationEuler();
	const float4 MyXZDirVector = float4::VectorRotationToDegY(float4::FORWARD, MyRot.Y);
	const float4 OtherXZDirVector = float4::VectorRotationToDegY(float4::FORWARD, _RotY);

	// Y PosCheck << Y ���� üũ �ؾߵ�

	float4 VectorToOther = MyPos - _WPos;
	VectorToOther.Y = 0;

	const float Dist = ContentsMath::GetVector3Length(VectorToOther).X;
	const float Dot = float4::DotProduct3D(MyXZDirVector, OtherXZDirVector);
	const float Deg = ContentsMath::DotNormalizeReturnDeg(Dot);
	const float SemiCircle = CIRCLE * 0.5f;
	const float BackStabAngle = SemiCircle - STAB_ANGLE;

	bool RangeCheck = (Dist < STAB_RECOGNITION_RANGE * W_SCALE);
	bool DirCheck = (Deg > BackStabAngle);
	return (RangeCheck && DirCheck);
}

float4 BaseMonster::GetBackStabPosition()
{
	SetFlag(Enum_ActorFlag::BackStab, true);
	Hit.SetHit(true);

	const float4 MyPos = Transform.GetWorldPosition();
	const float4 MyRot = Transform.GetWorldRotationEuler();
	const float4 BackDirVector = float4::VectorRotationToDegY(float4::BACKWARD, MyRot.Y);
	const float StabDist = W_SCALE * STAB_POS_RANGE;
	const float4 RelativePos = BackDirVector * StabDist;
	const float4 OtherPos = RelativePos + MyPos;
	return OtherPos;
}

float4 BaseMonster::GetFrontStabPosition()
{
	if (true == IsFlag(Enum_ActorFlag::Groggy))
	{
		const float4 MyPos = Transform.GetWorldPosition();
		const float4 MyRot = Transform.GetWorldRotationEuler();
		const float4 DirVector = float4::VectorRotationToDegY(float4::FORWARD, MyRot.Y);
		const float StabDist = W_SCALE * STAB_POS_RANGE;
		const float4 RelativePos = DirVector * StabDist;
		const float4 OtherPos = RelativePos + MyPos;
		return OtherPos;
	}

	return false;
}

void BaseMonster::CreateMonsterUI(int _BoneHeadIndex)
{
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �������� �ʽ��ϴ�. Bone����� ������ �� �����ϴ�.");
		return;
	}

	const std::vector<AnimationBoneData>& BoneDatas = MainRenderer->GetBoneDatas();
	const AnimationBoneData& Data = BoneDatas.at(_BoneHeadIndex);

	MonsterUI = GetLevel()->CreateActor<MonsterHpBar>(Enum_UpdateOrder::UI);
	MonsterUI->InitUIPosition(this, &Data.Pos);
}