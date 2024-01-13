#include "PreCompile.h"
#include "BaseMonster.h"

#include "FrameEventHelper.h"

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
std::map<Enum_BoneType, int> BaseMonster::BoneIndex;
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
	RAttackCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster);

	Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void BaseMonster::Update(float _Delta)
{
	MainState.Update(_Delta);

	std::vector<float4x4>& BoneMats = GetFBXRenderer()->GetBoneSockets();
	if (nullptr != RAttackCollision 
		&& true == RAttackCollision->IsUpdate())
	{
		RAttackCollision->Transform.SetLocalMatrix(BoneMats[GetBoneIndex(Enum_BoneType::B_01_RightHand)]);
	}
}



void BaseMonster::Release()
{
	MainRenderer = nullptr;
	RAttackCollision = nullptr;
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
	std::map<Enum_BoneType, int>::iterator FindIter = BoneIndex.find(_BoneType);
	if (FindIter == BoneIndex.end())
	{
		return 0;
	}

	return FindIter->second;
}


std::string BaseMonster::GetTypeName()
{
	std::string TypeName = "c";

	if (auto search = MonsterTypes.find(GetName()); search != MonsterTypes.end())
	{
		int Type = static_cast<int>(search->second);
		TypeName += std::to_string(Type);
		return TypeName;
	}

	return std::string();
}

std::string BaseMonster::GetEventPath()
{
	GameEnginePath path;
	std::string TypeName = GetTypeName();
	if (TypeName.empty())
	{
		return std::string();
	}

	path.MoveParentToExistsChild("ContentsResources");
	path.MoveChild("ContentsResources");
	path.MoveChild("Mesh");
	path.MoveChild(TypeName);
	path.MoveChild("Animation");
	return path.GetStringPath();
}

void BaseMonster::EventLoad()
{
	GameEngineDirectory Dir(GetEventPath());
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".Event" });
	for (GameEngineFile& pFile : Files)
	{
		FrameEventHelper::Load(pFile.GetStringPath());
	}
}