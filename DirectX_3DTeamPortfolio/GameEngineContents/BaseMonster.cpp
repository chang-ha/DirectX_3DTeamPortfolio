#include "PreCompile.h"
#include "BaseMonster.h"

#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"

class MonsterInitial
{
public:
	MonsterInitial()
	{
		Init();
	}

	~MonsterInitial() {} 

private:
	void Init()
	{
		BaseMonster::MonsterTypes.insert(std::make_pair("LothricKn", Enum_MonsterType::LothricKn));
	}

	static MonsterInitial MonsterInit;
};



std::map<std::string, Enum_MonsterType> BaseMonster::MonsterTypes;
MonsterInitial MonsterInitial::MonsterInit;
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

float4x4& BaseMonster::GetBoneMatrixToIndex(Enum_BoneType _BoneType)
{
	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	return BoneMats[GetBoneIndex(Enum_BoneType::B_01_RightHand)];
}


std::shared_ptr<BoneSocketCollision> BaseMonster::FindAndCreateSocketCollision(int _Order, Enum_BoneType _Index)
{
	int SocketIndex = GetBoneIndex(_Index);
	if (auto FindIter = Collisions.find(SocketIndex); FindIter != Collisions.end())
	{
		return FindIter->second;
	}

	std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Order);
	NewCol->SetSocket(&GetBoneMatrixToIndex(_Index));
	Collisions.insert(std::make_pair(SocketIndex, NewCol));
	return NewCol;
}

std::string BaseMonster::GetTypeName(std::string_view _Name)
{
	if (auto search = MonsterTypes.find(_Name.data()); search != MonsterTypes.end())
	{
		int Type = static_cast<int>(search->second);
		std::string TypeName = std::string("c") + std::to_string(Type);
		return TypeName;
	}

	return std::string();
}

std::string BaseMonster::GetEventPath(std::string_view _Name)
{
	std::string TypeName = GetTypeName(_Name);
	if (TypeName.empty())
	{
		return std::string();
	}

	GameEnginePath path;
	path.MoveParentToExistsChild("ContentsResources");
	path.MoveChild("ContentsResources");
	path.MoveChild("Mesh");
	path.MoveChild(TypeName);
	path.MoveChild("Animation");
	return path.GetStringPath();
}

void BaseMonster::EventLoad()
{
	GameEngineDirectory Dir(GetEventPath(GetName()));
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".Event" });
	for (GameEngineFile& pFile : Files)
	{
		FrameEventHelper::Load(pFile.GetStringPath());
	}
}
