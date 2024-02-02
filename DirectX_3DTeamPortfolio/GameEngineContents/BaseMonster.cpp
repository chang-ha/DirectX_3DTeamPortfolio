#include "PreCompile.h"
#include "BaseMonster.h"


BaseMonster::BaseMonster()
{

}

BaseMonster::~BaseMonster()
{

}

void BaseMonster::Start()
{
	BaseActor::Start();
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