#include "PreCompile.h"
#include "UILoading.h"

UILoading::UILoading() 
{
}

UILoading::~UILoading() 
{
}


void UILoading::Start()
{
	BackRenderer = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	BackRenderer->SetImageScale(GlobalValue::GetWinScale());
	BackRenderer->GetColorData().MulColor = float4::ZERO;
}

void UILoading::Update(float _Delta)
{

}

void UILoading::Release()
{
	BackRenderer = nullptr;
}
