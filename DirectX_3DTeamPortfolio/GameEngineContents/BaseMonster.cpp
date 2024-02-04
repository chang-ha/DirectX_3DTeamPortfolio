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

float BaseMonster::ConvertDistance_eTof(Enum_TargetDist _eTDist) const
{
	MsgBoxAssert("자식에서 재정의해야하는 함수입니다.");
	return 0.0f;
}

bool BaseMonster::IsTargetInRange(Enum_TargetDist _eTDist)
{
	const float fRange = ConvertDistance_eTof(_eTDist);
	const float fCheckDist = fRange * W_SCALE;
	const float fTargetDist = BaseActor::GetTargetDistance();

	if (fTargetDist < fCheckDist)
	{
		return true;
	}

	return false;
}