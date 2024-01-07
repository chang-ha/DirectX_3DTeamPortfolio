#include "PreCompile.h"
#include "CommonMonster.h"

class MonsterInitial
{
public:
	MonsterInitial()
	{
		Init();
		int MonsterNum = static_cast<int>(CommonMonster::GetMonsterType("LothricKn"));
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