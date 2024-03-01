#include "PreCompile.h"
#include "BaseMonster.h"

#include "MonsterHpBar.h"

BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	BaseActor::Start();

	MonsterUI = GetLevel()->CreateActor<MonsterHpBar>();
}

void BaseMonster::Update(float _Delta)
{
	BaseActor::Update(_Delta);
}

void BaseMonster::Release()
{
	BaseActor::Release();
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

void BaseMonster::AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum)
{
	BoneIndex.insert(std::make_pair(_BoneType, _BoneNum));
}

/// <summary>
/// 엔진에서 정의한 해시와 본 인덱스를 매핑시킨 데이터를 반환합니다.
/// </summary>
/// <param name="_BoneType">해시 정보</param>
/// <returns> Default Value : 0 </returns>
int BaseMonster::GetBoneIndex(Enum_BoneType _BoneType)
{
	std::unordered_map<Enum_BoneType, int>::const_iterator FindIter = BoneIndex.find(_BoneType);
	if (FindIter == BoneIndex.end())
	{
		return 0;
	}

	return FindIter->second;
}

float4x4& BaseMonster::GetBoneMatrixToType(Enum_BoneType _BoneType)
{
	int Index = GetBoneIndex(_BoneType);
	return GetBoneMatrixToIndex(Index);
}

std::shared_ptr<BoneSocketCollision> BaseMonster::FindSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	return GetSocketCollision(SocketIndex);
}

void BaseMonster::OnSocketCollisionInt(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	OnSocketCollision(SocketIndex);
}

void BaseMonster::OffSocketCollisionInt(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	OffSocketCollision(SocketIndex);
}

void BaseMonster::GravityOn()
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("존재하지 않는 피직스 객체를 사용하려 했습니다.");
		return;
	}

	Capsule->GravityOn();
}

void BaseMonster::GravityOff()
{
	if (nullptr == Capsule)
	{
		MsgBoxAssert("존재하지 않는 피직스 객체를 사용하려 했습니다.");
		return;
	}

	Capsule->GravityOff();
}

float BaseMonster::ConvertDistance_eTof(Enum_TargetDist _eTDist) const
{
	MsgBoxAssert("자식에서 재정의해야하는 함수입니다.");
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
		MsgBoxAssert("공격자를 모르고 사용할 수 없는 기능입니다.");
		return false;
	}

	if (true == Hit.IsHit())
	{
		return false;
	}

	BaseActor* pAttacker = _Para.pAttacker;

	const int AttackerAtt = pAttacker->GetAtt();
	const int Stiffness = _Para.iStiffness;

	Stat.AddPoise(Stiffness);
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
		MsgBoxAssert("공격자의 포인터를 모르고 사용할 수 없는 기능입니다.");
		return false;
	}

	if (true == Hit.IsHit())
	{
		return false;
	}

	BaseActor* pAttacker = _Para.pAttacker;

	// 패링상태
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
		Stat.AddPoise(Stiffness);
		if (0 >= Stat.GetPoise())
		{
			SetFlag(Enum_ActorFlag::Guard_Break, true);
			Stat.SetPoise(0);
		}
		else
		{
			Hit.SetGuardSuccesss(true);
		}

		const int FinalDamage = GuardHitFormula(AttackerAtt);
		Stat.AddHp(FinalDamage);
		Hit.SetHit(true);

		return true;
	}

	return false;
}