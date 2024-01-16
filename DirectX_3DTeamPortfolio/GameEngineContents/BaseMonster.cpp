#include "PreCompile.h"
#include "BaseMonster.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"

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
	Collisions.clear();
}



bool BaseMonster::IsOnFlag(Enum_MonsterFlag _Flag) const
{
	return (Flags / _Flag) % 2;
}

void BaseMonster::SetFlag(Enum_MonsterFlag _Flag, bool _Value)
{
	AddFlag(_Flag);

	if (false == _Value)
	{
		Flags -= _Flag;
	}
}

void BaseMonster::AddFlag(Enum_MonsterFlag _Flag)
{
	Flags |= _Flag;
}

void BaseMonster::SubFlag(Enum_MonsterFlag _Flag)
{
	SetFlag(_Flag, false);
}


void BaseMonster::SetBoneIndex(Enum_BoneType _BoneType, int _BoneNum)
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
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[GetBoneIndex(Enum_BoneType::B_01_RightHand)];
}


std::shared_ptr<BoneSocketCollision> BaseMonster::FindAndCreateSocketCollision(int _Order, Enum_BoneType _Type)
{
	int SocketIndex = GetBoneIndex(_Type);
	if (auto FindIter = Collisions.find(SocketIndex); FindIter != Collisions.end())
	{
		return FindIter->second;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetName(std::to_string(SocketIndex));
	NewCol->SetBoneIndex(SocketIndex);
	NewCol->SetSocket(&GetBoneMatrixToType(_Type));
	NewCol->Off();
	Collisions.insert(std::make_pair(SocketIndex, NewCol));
	return NewCol;
}

std::shared_ptr<BoneSocketCollision> BaseMonster::CreateSocketCollision(int _Order, Enum_BoneType _Type, std::string _ColName)
{
	int SocketIndex = GetBoneIndex(_Type);
	if (auto FindIter = Collisions.find(SocketIndex); FindIter != Collisions.end())
	{
		MsgBoxAssert("이미 존재하는 충돌체를 생성하려 했습니다.");
		return nullptr;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetName(_ColName);
	NewCol->SetBoneIndex(SocketIndex);
	NewCol->SetSocket(&GetBoneMatrixToType(_Type));
	NewCol->Off();
	Collisions.insert(std::make_pair(SocketIndex, NewCol));
	return NewCol;
}

std::shared_ptr<BoneSocketCollision> BaseMonster::GetSocketCollision(int _Index)
{
	if (auto FindIter = Collisions.find(_Index); FindIter != Collisions.end())
	{
		return FindIter->second;
	}

	MsgBoxAssert("존재하지 않는 충돌체를 참조하려 했습니다.");
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