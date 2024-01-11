#include "PreCompile.h"
#include "CommonMonster.h"

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
		CommonMonster::MonsterTypes.insert(std::make_pair("LothricKn", Enum_MonsterType::LothricKn));
	}

	static MonsterInitial MonsterInit;
};



std::map<std::string, Enum_MonsterType> CommonMonster::MonsterTypes;
MonsterInitial MonsterInitial::MonsterInit;
CommonMonster::CommonMonster() 
{
}

CommonMonster::~CommonMonster() 
{
}


std::string CommonMonster::GetTypeName()
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

std::string CommonMonster::GetEventPath()
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

void CommonMonster::EventLoad()
{
	GameEngineDirectory Dir(GetEventPath());
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".Event" });
	for (GameEngineFile& pFile : Files)
	{
		FrameEventHelper::Load(pFile.GetStringPath());
	}
}

void CommonMonster::Start()
{
	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	MainRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	MainRenderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void CommonMonster::Release()
{
	MainRenderer = nullptr;
}