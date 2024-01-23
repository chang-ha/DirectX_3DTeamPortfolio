#include "PreCompile.h"
#include "BaseActor.h"

#include "ContentsMath.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"


class ContentsActorInitial
{
private:
	ContentsActorInitial()
	{
		Init();
	}

	~ContentsActorInitial() {}

	void Init();

private:
	static ContentsActorInitial s_ActorInit;

};

void ContentsActorInitial::Init()
{
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorStatus::HitValue, Enum_ActorFlag::HitValue));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorStatus::GaurdingValue, Enum_ActorFlag::GaurdingValue));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorStatus::DeathValue, Enum_ActorFlag::DeathValue));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorStatus::JumpPossible, Enum_ActorFlag::JumpPossible));
	BaseActor::FlagIndex.insert(std::make_pair(Enum_ActorStatus::ParryPossible, Enum_ActorFlag::ParryPossible));
}



std::unordered_map<Enum_ActorStatus, Enum_ActorFlag> BaseActor::FlagIndex;
ContentsActorInitial ContentsActorInitial::s_ActorInit;
BaseActor::BaseActor()
{
}

BaseActor::~BaseActor()
{
}

void BaseActor::Start()
{
	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);

	Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void BaseActor::Update(float _Delta)
{
	MainState.Update(_Delta);
}

void BaseActor::Release()
{
	MainRenderer = nullptr;
	SocketCollisions.clear();
}



void BaseActor::AddWDirection(float _Degree)
{
	Transform.AddWorldRotation(float4(0.0f, 0.0f, _Degree));
}

void BaseActor::SetWDirection(float _Degree)
{
	Transform.SetWorldRotation(float4(0.0f, 0.0f, _Degree));
}

float BaseActor::GetWDirection() const
{
	return Transform.GetWorldRotationEuler().Z;
}


int BaseActor::FindFlag(Enum_ActorStatus _Status) const
{
	if (auto FindIter = FlagIndex.find(_Status); FindIter != FlagIndex.end())
	{
		return static_cast<int>(FindIter->second);
	}

	return static_cast<int>(Enum_ActorFlag::None);
}

bool BaseActor::GetFlag(Enum_ActorStatus _Flag) const
{
	return (Flags / FindFlag(_Flag)) % 2;
}

void BaseActor::SetFlag(Enum_ActorStatus _Flag, bool _Value)
{
	AddFlag(_Flag);

	if (false == _Value)
	{
		Flags -= FindFlag(_Flag);
	}
}

void BaseActor::AddFlag(Enum_ActorStatus _Flag)
{
	Flags |= FindFlag(_Flag);
}

void BaseActor::SubFlag(Enum_ActorStatus _Flag)
{
	SetFlag(_Flag, false);
}

void BaseActor::DebugFlag()
{
	bool HitValue = GetFlag(Enum_ActorStatus::HitValue);
	bool GaurdingValue = GetFlag(Enum_ActorStatus::GaurdingValue);
	bool DeathValue = GetFlag(Enum_ActorStatus::DeathValue);
	bool JumpPossible = GetFlag(Enum_ActorStatus::JumpPossible);
	bool ParryPossible = GetFlag(Enum_ActorStatus::ParryPossible);
	int a = 0;
}


void BaseActor::AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum)
{
	BoneIndex.insert(std::make_pair(_BoneType, _BoneNum));
}

/// <summary>
/// 엔진에서 정의한 해시와 본 인덱스를 매핑시킨 데이터를 반환합니다.
/// </summary>
/// <param name="_BoneType">해시 정보</param>
/// <returns> Default Value : 0 </returns>
int BaseActor::GetBoneIndex(Enum_BoneType _BoneType)
{
	std::unordered_map<Enum_BoneType, int>::const_iterator FindIter = BoneIndex.find(_BoneType);
	if (FindIter == BoneIndex.end())
	{
		return 0;
	}

	return FindIter->second;
}

float4x4& BaseActor::GetBoneMatrixToType(Enum_BoneType _BoneType)
{
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[GetBoneIndex(Enum_BoneType::B_01_RightHand)];
}

std::shared_ptr<BoneSocketCollision> BaseActor::CreateSocketCollision(int _Order, Enum_BoneType _Type, std::string _ColName)
{
	int SocketIndex = GetBoneIndex(_Type);
	if (auto FindIter = SocketCollisions.find(SocketIndex); FindIter != SocketCollisions.end())
	{
		MsgBoxAssert("이미 존재하는 충돌체를 생성하려 했습니다.");
		return nullptr;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetName(_ColName);
	NewCol->SetBoneIndex(SocketIndex);
	NewCol->SetCollisionType(ColType::SPHERE3D);
	NewCol->SetSocket(&GetBoneMatrixToType(_Type));
	NewCol->Off();
	SocketCollisions.insert(std::make_pair(SocketIndex, NewCol));
	return NewCol;
}

std::shared_ptr<BoneSocketCollision> BaseActor::GetSocketCollision(int _Index)
{
	if (auto FindIter = SocketCollisions.find(_Index); FindIter != SocketCollisions.end())
	{
		return FindIter->second;
	}

	MsgBoxAssert("존재하지 않는 충돌체를 참조하려 했습니다.");
	return nullptr;
}

std::shared_ptr<BoneSocketCollision> BaseActor::FindSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	return GetSocketCollision(SocketIndex);
}

std::string BaseActor::GetEventPath(int _ID)
{
	if (EMPTY_ID == _ID)
	{
		return std::string();
	}

	std::string IDName = std::string("c") + std::to_string(_ID);

	GameEnginePath path;
	path.MoveParentToExistsChild("ContentsResources");
	path.MoveChild("ContentsResources");
	path.MoveChild("Mesh");
	path.MoveChild(IDName);
	path.MoveChild("Animation");
	return path.GetStringPath();
}

bool BaseActor::LoadEvent(int _ID)
{
	std::string Path = GetEventPath(_ID);
	if (Path.empty())
	{
		return false;
	}

	GameEngineDirectory Dir(Path);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ FrameEventHelper::GetExtName().data() });
	for (GameEngineFile& pFile : Files)
	{
		FrameEventHelper::Load(pFile.GetStringPath());
	}

	return true;
}