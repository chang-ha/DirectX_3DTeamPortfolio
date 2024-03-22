#include "PreCompile.h"
#include "UISystemManager.h"

UISystemManager::UISystemManager()
{

}

UISystemManager::~UISystemManager()
{

}


void UISystemManager::Start()
{
	Window = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackTexture);
	Window->SetSprite("Interaction3.png");
	Window->Transform.SetLocalPosition(float4(-2.0f, -279.0f));

	Font = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	Font->SetText(GlobalValue::OptimusFont, "", 20.0f, float4::WHITE);
	Font->Transform.SetLocalPosition(float4(-96.0f, -265.0f, -1.f));


	// State
	CreateStateParameter FadeInState;
	FadeInState.Start = std::bind(&::UISystemManager::FadeIn_Start, this, std::placeholders::_1);
	FadeInState.Stay = std::bind(&::UISystemManager::FadeIn_Update, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter FadeOutState;
	FadeOutState.Stay = std::bind(&UISystemManager::FdaeOut_Update, this, std::placeholders::_1, std::placeholders::_2);

	MainState.CreateState(eState::FadeIn, FadeInState);
	MainState.CreateState(eState::FadeOut, FadeOutState);

	Off();
}

void UISystemManager::Update(float _Delta)
{
	MainState.Update(_Delta);
}

void UISystemManager::LevelEnd(GameEngineLevel* _NextLevel)
{
	Off();
}

void UISystemManager::OnSystem(Enum_SystemType _Type)
{
	std::string Text;
	switch (_Type)
	{
	case Enum_SystemType::Object_bonfire:
		Text = " : 화톳불에서 휴식한다";
		break;
	case Enum_SystemType::Object_Ladder:
		Text = " : 사다리를 탄다.";
		break;
	case Enum_SystemType::Object_FogWall:
		Text = " : 안개속으로 들어간다";
		break;
	default:
		break;
	}


	MainState.ChangeState(eState::FadeIn);

	Font->ChangeText(Text);
}

void UISystemManager::OffSystem()
{
	MainState.ChangeState(eState::FadeOut);
}

static constexpr float FadeTime = 0.2f;
void UISystemManager::FadeIn_Start(GameEngineState* _Parent)
{
	SetGamma(0.0f);

	On();
}

void UISystemManager::FadeIn_Update(float _Delta, GameEngineState* _Parent)
{
	GammaValue += _Delta / FadeTime;
	SetGamma(GammaValue);
}
void UISystemManager::FdaeOut_Update(float _Delta, GameEngineState* _Parent)
{
	if (Window->GetColorData().MulColor.A <= 0.0f)
	{
		Off();
		return;
	}
	
	GammaValue -= _Delta / FadeTime;
	SetGamma(GammaValue);
}

void UISystemManager::SetGamma(float _Ratio)
{
	GammaValue = std::clamp(_Ratio, 0.0f, 0.999f);
	ContentsDebug::NUllCheck(Window.get());
	ContentsDebug::NUllCheck(Font.get());
	Window->GetColorData().MulColor.A = GammaValue;
	Font->SetTextAlpha(GammaValue);
}