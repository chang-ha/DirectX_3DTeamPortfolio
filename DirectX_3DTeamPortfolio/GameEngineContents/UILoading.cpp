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
	BackRenderer->SetSprite("LoadingTemp.png");
	BackRenderer->SetImageScale(GlobalValue::GetWinScale());
	// BackRenderer->GetColorData().MulColor = float4::ZERO;

	Off();
}

void UILoading::Update(float _Delta)
{

}

void UILoading::Release()
{
	BackRenderer = nullptr;
}
