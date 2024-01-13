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
MonsterInitial MonsterInitial::MonsterInit;
BaseMonster::BaseMonster() 
{
}

BaseMonster::~BaseMonster() 
{
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

void BaseMonster::Start()
{
	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	MainRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	MainRenderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
	 
	RAttackCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster);
	RAttackCollision->Transform.SetLocalScale({ 50.0f, 50.0f, 50.0f });
}

void BaseMonster::Update(float _Delta)
{
	MainState.Update(_Delta);
}



void BaseMonster::Release()
{
	MainRenderer = nullptr;
	RAttackCollision = nullptr;
}



bool BaseMonster::IsFlag(Enum_MonsterFlag _Flag) const
{
	return (Flag / _Flag) % 2;
}

void BaseMonster::SetFlag(Enum_MonsterFlag _Flag, bool _Value)
{
	AddFlag(_Flag);

	if (false == _Value)
	{
		Flag -= _Flag;
	}
}

void BaseMonster::AddFlag(Enum_MonsterFlag _Flag)
{
	Flag |= _Flag;
}

void BaseMonster::SubFlag(Enum_MonsterFlag _Flag)
{
	SetFlag(_Flag, false);
}