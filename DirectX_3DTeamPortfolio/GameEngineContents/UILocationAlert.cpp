#include "PreCompile.h"
#include "UILocationAlert.h"

UILocationAlert::UILocationAlert() 
{
}

UILocationAlert::~UILocationAlert() 
{
}

void UILocationAlert::Start() 
{

	// 언더바 : 알파값
	UnderBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	UnderBar->GetColorData().PlusColor = float4::ONE;
	UnderBar->Off();

	// Bar State
	CreateStateParameter IdleState;
	IdleState.Start = std::bind(&::UILocationAlert::Start_Idle, this, std::placeholders::_1);
	IdleState.Stay = std::bind(&::UILocationAlert::Update_Idle, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&::UILocationAlert::Start_Appear, this, std::placeholders::_1);
	AppearState.Stay = std::bind(&::UILocationAlert::Update_Appear, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter DisAppearState;
	DisAppearState.Stay = std::bind(&UILocationAlert::Update_DisAppear, this, std::placeholders::_1, std::placeholders::_2);
	DisAppearState.End = std::bind(&UILocationAlert::End_DisAppear, this, std::placeholders::_1);

	MainState.CreateState(eState::Idle, IdleState);
	MainState.CreateState(eState::Appear, AppearState);
	MainState.CreateState(eState::DisAppear, DisAppearState);


	// 폰트 텍스처
	FontTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	FontTexture->SetSprite("Lothric_Wall.png");
	FontTexture->Transform.SetLocalPosition(float4(0, 50.0f));
	FontTexture->AutoSpriteSizeOn();
	FontTexture->SetAutoScaleRatio(2.0f);
	FontTexture->Off();
}

void UILocationAlert::Update(float _Delta) 
{
	MainState.Update(_Delta);
}

void UILocationAlert::Release() 
{
	FontTexture = nullptr;
	UnderBar = nullptr;
	AlertLoCollision = nullptr;
}

void UILocationAlert::Reset() 
{
	MainState.ChangeState(eState::Idle);
}

void UILocationAlert::SetCollision(const float4& _Pos, const float4& _Scale, float _Rot)
{
	// CollisionOrder 지정
	AlertLoCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::EventCol);
	AlertLoCollision->SetCollisionType(ColType::SPHERE3D);
	AlertLoCollision->SetCollisionColor(float4::BLUE);
	AlertLoCollision->Transform.SetLocalPosition(_Pos);
	AlertLoCollision->Transform.SetLocalScale(_Scale);
	AlertLoCollision->Transform.SetLocalRotation(float4(0.0f, _Rot));
	//AlertLoCollision->On();

	MainState.ChangeState(eState::Idle);
}

//State
static constexpr float FadeTime = 2.0f;
static constexpr float AppearStateTime = 4.0f;

// State_Idle
void UILocationAlert::Start_Idle(GameEngineState* _Parent)
{
	//On();
	AlertLoCollision->On();
	SetGamma(0.0f);
}

void UILocationAlert::Update_Idle(float _Delta, GameEngineState* _Parent)
{
	// 콜리전 이벤트

	AlertLoCollision->Collision(Enum_CollisionOrder::Player, [&](std::vector<GameEngineCollision*> _CollisionGroup)
		{
			MainState.ChangeState(eState::Appear);
			return;
		}
	);
}


void UILocationAlert::Start_Appear(GameEngineState* _Parent)
{
	AlertLoCollision->Off();
	FontTexture->On();
	GameEngineSound::SoundPlay("New_Location_Sound_Effect.wav");
}

void UILocationAlert::Update_Appear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	SetGamma(StateTime);

	if (StateTime >= AppearStateTime)
	{
		_Parent->ChangeState(eState::DisAppear);
		return;
	}
}


void UILocationAlert::Update_DisAppear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	if (StateTime <= FadeTime)
	{
		const float Ratio = (FadeTime - StateTime) / FadeTime;
		SetGamma(Ratio);
	}
}

void UILocationAlert::End_DisAppear(GameEngineState* _Parent)
{
	Off();
}

void UILocationAlert::SetGamma(float _Ratio)
{
	const float Ratio = std::clamp(_Ratio, 0.0f, 1.0f);
	FontTexture->GetColorData().MulColor.A = Ratio;
	UnderBar->GetColorData().MulColor.A = Ratio;
}