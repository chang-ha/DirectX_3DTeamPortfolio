#include "PreCompile.h"
#include "BaseMonster.h"

#include "ContentsMath.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"

class MonsterInitial
{
private:
	MonsterInitial() 
	{
		Init(); 
	}

	~MonsterInitial() {}

	void Init();

private:
	static MonsterInitial s_MonsterInit;

};

void MonsterInitial::Init()
{
	BaseMonster::FlagIndex.insert(std::make_pair(Enum_MonsterStatus::HitValue, Enum_MonsterFlag::HitValue));
	BaseMonster::FlagIndex.insert(std::make_pair(Enum_MonsterStatus::GaurdingValue, Enum_MonsterFlag::GaurdingValue));
	BaseMonster::FlagIndex.insert(std::make_pair(Enum_MonsterStatus::DeathValue, Enum_MonsterFlag::DeathValue));
	BaseMonster::FlagIndex.insert(std::make_pair(Enum_MonsterStatus::JumpPossible, Enum_MonsterFlag::JumpPossible));
	BaseMonster::FlagIndex.insert(std::make_pair(Enum_MonsterStatus::ParryPossible, Enum_MonsterFlag::ParryPossible));
}



std::unordered_map<Enum_MonsterStatus, Enum_MonsterFlag> BaseMonster::FlagIndex;
MonsterInitial MonsterInitial::s_MonsterInit;
BaseMonster::BaseMonster() 
{
}

BaseMonster::~BaseMonster() 
{
}

void BaseMonster::Start()
{
	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);

	Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void BaseMonster::Update(float _Delta)
{
	MainState.Update(_Delta);
}

void BaseMonster::Release()
{
	MainRenderer = nullptr;
	SocketCollisions.clear();
}



void BaseMonster::AddWDirection(float _Degree)
{
	Transform.AddWorldRotation(float4(0.0f, 0.0f, _Degree));
}

void BaseMonster::SetWDirection(float _Degree)
{
	Transform.SetWorldRotation(float4(0.0f, 0.0f, _Degree));
}

float BaseMonster::GetWDirection() const
{
	return Transform.GetWorldRotationEuler().Z;
}


int BaseMonster::FindFlag(Enum_MonsterStatus _Status) const
{
	if (auto FindIter = FlagIndex.find(_Status); FindIter != FlagIndex.end())
	{
		return static_cast<int>(FindIter->second);
	}

	return static_cast<int>(Enum_MonsterFlag::None);
}

bool BaseMonster::GetFlag(Enum_MonsterStatus _Flag) const
{
	return (Flags / FindFlag(_Flag)) % 2;
}

void BaseMonster::SetFlag(Enum_MonsterStatus _Flag, bool _Value)
{
	AddFlag(_Flag);

	if (false == _Value)
	{
		Flags -= FindFlag(_Flag);
	}
}

void BaseMonster::AddFlag(Enum_MonsterStatus _Flag)
{
	Flags |= FindFlag(_Flag);
}

void BaseMonster::SubFlag(Enum_MonsterStatus _Flag)
{
	SetFlag(_Flag, false);
}

void BaseMonster::DebugFlag()
{
	bool HitValue = GetFlag(Enum_MonsterStatus::HitValue);
	bool GaurdingValue = GetFlag(Enum_MonsterStatus::GaurdingValue);
	bool DeathValue = GetFlag(Enum_MonsterStatus::DeathValue);
	bool JumpPossible = GetFlag(Enum_MonsterStatus::JumpPossible);
	bool ParryPossible = GetFlag(Enum_MonsterStatus::ParryPossible);
	int a = 0;
}


void BaseMonster::AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum)
{
	BoneIndex.insert(std::make_pair(_BoneType, _BoneNum));
}

/// <summary>
/// �������� ������ �ؽÿ� �� �ε����� ���ν�Ų �����͸� ��ȯ�մϴ�.
/// </summary>
/// <param name="_BoneType">�ؽ� ����</param>
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
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[GetBoneIndex(Enum_BoneType::B_01_RightHand)];
}

std::shared_ptr<BoneSocketCollision> BaseMonster::CreateSocketCollision(int _Order, Enum_BoneType _Type, std::string _ColName)
{
	int SocketIndex = GetBoneIndex(_Type);
	if (auto FindIter = SocketCollisions.find(SocketIndex); FindIter != SocketCollisions.end())
	{
		MsgBoxAssert("�̹� �����ϴ� �浹ü�� �����Ϸ� �߽��ϴ�.");
		return nullptr;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetName(_ColName);
	NewCol->SetBoneIndex(SocketIndex);
	NewCol->SetSocket(&GetBoneMatrixToType(_Type));
	NewCol->Off();
	SocketCollisions.insert(std::make_pair(SocketIndex, NewCol));
	return NewCol;
}

std::shared_ptr<BoneSocketCollision> BaseMonster::GetSocketCollision(int _Index)
{
	if (auto FindIter = SocketCollisions.find(_Index); FindIter != SocketCollisions.end())
	{
		return FindIter->second;
	}

	MsgBoxAssert("�������� �ʴ� �浹ü�� �����Ϸ� �߽��ϴ�.");
	return nullptr;
}

std::shared_ptr<BoneSocketCollision> BaseMonster::FindSocketCollision(Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	return GetSocketCollision(SocketIndex);
}

std::string BaseMonster::GetEventPath(int _ID)
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

bool BaseMonster::LoadEvent(int _ID)
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