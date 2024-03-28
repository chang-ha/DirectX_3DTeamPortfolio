#include "PreCompile.h"
#include "TitleLogo.h"

#include "MainUIActor.h"
#include "TitleButton.h"
#include "LoadingLevel.h"

TitleLogo::TitleLogo()
{

}

TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	if (nullptr == GameEngineSprite::Find("BanDaiNaco_Logo.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("DarkSoulsIII_Main_Menu_Theme.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound\\UI");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineSound::SoundLoad(pFiles.GetStringPath());
		}
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	BanDaiNamco_Logo = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI);
	BanDaiNamco_Logo->SetSprite("BanDaiNaco_Logo.Png");
	BanDaiNamco_Logo->SetImageScale({ WindowScale.X , WindowScale.Y });
	BanDaiNamco_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 500.0f });
	BanDaiNamco_Logo->On();

	FromSoft_Logo = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI);
	FromSoft_Logo->SetSprite("FromSoftLogo.Png");
	FromSoft_Logo->SetImageScale({ 1024, 1024 });
	FromSoft_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 300.0f });
	FromSoft_Logo->GetColorData().MulColor.A = 0.0f;

	DarkSouls_Logo = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI);
	DarkSouls_Logo->SetSprite("DarkSoulsLogo.Png");
	DarkSouls_Logo->AutoSpriteSizeOn();
	DarkSouls_Logo->Transform.SetLocalPosition({ 0.0f, 50.0f, 500.0f });
	DarkSouls_Logo->GetColorData().MulColor.A = 0.0f;

	Inc_Logo = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI);
	Inc_Logo->SetSprite("Title_IncLogo.Png");
	Inc_Logo->AutoSpriteSizeOn();
	Inc_Logo->Transform.SetLocalPosition({ 0.0f, -250.0f, 500.0f });
	Inc_Logo->Off();

	AnyButtonBack = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI_BackTexture);
	AnyButtonBack->SetSprite("AnyButtonBack.Png");
	AnyButtonBack->AutoSpriteSizeOn();
	AnyButtonBack->SetAutoScaleRatio(0.45f);
	AnyButtonBack->Transform.SetLocalPosition({ 0.0f, -120.0f, 505.0f });
	AnyButtonBack->GetColorData().MulColor.A = 0.0f;

	AnyButtonFont = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	AnyButtonFont->SetText(GlobalValue::OptimusFont, "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
	AnyButtonFont->Transform.SetLocalPosition({ 0.0f, -111.0f, 500.0f });
	AnyButtonFont->Off();

	GameEngineInput::AddInputObject(this);

	///// State
	CreateStateParameter BanDaiState;
	BanDaiState.Stay = std::bind(&TitleLogo::Update_BanDai, this, std::placeholders::_1, std::placeholders::_2);
	BanDaiState.End = std::bind(&TitleLogo::End_BanDai, this, std::placeholders::_1);

	CreateStateParameter FromSoftState;
	FromSoftState.Stay = std::bind(&TitleLogo::Update_FromSoft, this, std::placeholders::_1, std::placeholders::_2);
	FromSoftState.End = std::bind(&TitleLogo::End_FromSoft, this, std::placeholders::_1);

	CreateStateParameter DarkSoulState;
	DarkSoulState.Stay = std::bind(&TitleLogo::Update_DarkSoul, this, std::placeholders::_1, std::placeholders::_2);
	DarkSoulState.End = std::bind(&TitleLogo::End_DarkSoul, this, std::placeholders::_1);

	CreateStateParameter AnyButtonState;
	AnyButtonState.Stay = std::bind(&TitleLogo::Update_AnyButton, this, std::placeholders::_1, std::placeholders::_2);
	AnyButtonState.End = std::bind(&TitleLogo::End_AnyButton, this, std::placeholders::_1);

	CreateStateParameter EndLogoState;
	EndLogoState.Start = std::bind(&TitleLogo::Start_EndLogo, this, std::placeholders::_1);
	EndLogoState.Stay = std::bind(&TitleLogo::Update_EndLogo, this, std::placeholders::_1, std::placeholders::_2);
	EndLogoState.End = std::bind(&TitleLogo::End_EndLogo, this, std::placeholders::_1);

	CreateStateParameter DoneState;
	DoneState.Start = std::bind(&TitleLogo::Start_Done, this, std::placeholders::_1);


	Logostate.CreateState(eLogoState::BanDai, BanDaiState);
	Logostate.CreateState(eLogoState::FromSoft, FromSoftState);
	Logostate.CreateState(eLogoState::DarkSoul, DarkSoulState);
	Logostate.CreateState(eLogoState::AnyButton, AnyButtonState);
	Logostate.CreateState(eLogoState::EndLogo, EndLogoState);
	Logostate.CreateState(eLogoState::Done, DoneState);


	Logostate.ChangeState(eLogoState::BanDai);

	// 버튼만들기
	ButtonCreate();

	CreateStateParameter BStartButton;
	BStartButton.Start = std::bind(&TitleLogo::Start_ButtonActor, this, std::placeholders::_1);
	BStartButton.Stay = std::bind(&TitleLogo::Update_ButtonActor, this, std::placeholders::_1, std::placeholders::_2);
	BStartButton.End = std::bind(&TitleLogo::End_ButtonActor, this, std::placeholders::_1);

	ButtonState.CreateState(eButtonState::ButtonActor, BStartButton);
	ButtonState.CreateState(eButtonState::Done, {});
}

void TitleLogo::Update(float _Delta)
{
	Logostate.Update(_Delta);

	ButtonState.Update(_Delta);
}

void TitleLogo::Release()
{
	DarkBack = nullptr;
	BanDaiNamco_Logo = nullptr;
	FromSoft_Logo = nullptr;
	DarkSouls_Logo = nullptr;
	Inc_Logo = nullptr;
	AnyButtonBack = nullptr;
	AnyButtonFont = nullptr;

	Buttons.clear();
	ButtonActor = nullptr;
}

#define ButtonFontStartYPos -84.0f
#define ButtonYDistance 32.0f
#define ButtonCount 2
// 버튼 만들기
#include <stdlib.h>
void TitleLogo::ButtonCreate()
{
	Buttons.reserve(ButtonCount);
	ButtonCheckNum = 0;


	for (int i = 0; i < Buttons.capacity(); i++)
	{
		ButtonActor = CreateComponent<TitleButton>(Enum_UpdateOrder::UI);
		Buttons.push_back(ButtonActor);
	}

	ButtonActor->CreateButton(ButtonCount);

	ButtonActor->ChangeButtonText(GameStart, "GAME START");
	ButtonActor->ChangeButtonText(GameExit, "GAME EXIT");

	Buttons[GameStart]->SetButtonFunction([=]() { LoadingLevel::LoadingFlag = Enum_LevelFlag::Loading_Resouce;
	GameEngineCore::ChangeLevel("LoadingLevel"); });
	Buttons[GameExit]->SetButtonFunction([=]() {GameEngineCore::MainWindow.WindowLoopOff(); });
}

// State
constexpr float LogoChangeTime = 4.0f;
void TitleLogo::Update_BanDai(float _Delta, GameEngineState* _State)
{
	SkipButton(_State, (eLogoState::FromSoft));

	if (_State->GetStateTime() >= LogoChangeTime)
	{
		_State->ChangeState(eLogoState::FromSoft);
		return;
	}

	if (_State->GetStateTime() >= 2.0f)
	{
		BanDaiNamco_Logo->GetColorData().MulColor.A -= _Delta * 0.5f;
	}
}

void TitleLogo::Update_FromSoft(float _Delta, GameEngineState* _State)
{
	SkipButton(_State, (eLogoState::DarkSoul));

	if (_State->GetStateTime() >= LogoChangeTime)
	{
		_State->ChangeState(eLogoState::DarkSoul);
		return;
	}

	FromSoft_Logo->GetColorData().MulColor.A += _Delta * 0.5f;
}
void TitleLogo::Update_DarkSoul(float _Delta, GameEngineState* _State)
{
	SkipButton(_State, (eLogoState::AnyButton));

	DarkSouls_Logo->GetColorData().MulColor.A += _Delta * 0.5f;
	if (_State->GetStateTime() >= LogoChangeTime)
	{
		_State->ChangeState(eLogoState::AnyButton);
		return;
	}
}
void TitleLogo::Update_AnyButton(float _Delta, GameEngineState* _State)
{
	ButtonFlash(_Delta, _State);
}

// 엔딩시 오는 곳
void TitleLogo::Start_EndLogo(GameEngineState* _State)
{
	ButtonActor->Off();

	Inc_Logo->Off();
	AnyButtonBack->Off();

	DarkSouls_Logo->GetColorData().MulColor.A = 0.1f;
	FontEnter = false;

	DarkSouls_Logo->GetAutoScaleRatio();
}

void TitleLogo::Update_EndLogo(float _Delta, GameEngineState* _State)
{
	if (_State->GetStateTime() >= 2.0f)
	{
		DarkLogoAddScale(-0.07f * _Delta);
	}
	else
	{
		DarkLogoAddScale(0.07f * _Delta);
	}

	DarkSouls_Logo->GetColorData().MulColor.A += _Delta * 0.2f;

	if (_State->GetStateTime() >= LogoChangeTime)
	{
		_State->ChangeState(eLogoState::AnyButton);
		return;
	}
}
void TitleLogo::End_EndLogo(GameEngineState* _State)
{
	Inc_Logo->On();

	AnyButtonFont->Transform.SetLocalPosition({ 0.0f, -111.0f, 500.0f });
	AnyButtonFont->ChangeFontScale(FontScale);
	AnyButtonFont->On();

	AnyButtonBack->Transform.SetLocalPosition({ 0.0f, -120.0f, 505.0f });
	AnyButtonBack->On();

	DarkSouls_Logo->GetColorData().MulColor.A = 1.0f;
}



void TitleLogo::End_BanDai(GameEngineState* _State)
{
	BanDaiNamco_Logo->Off();
}
void TitleLogo::End_FromSoft(GameEngineState* _State)
{
	FromSoft_Logo->Off();
}
void TitleLogo::End_DarkSoul(GameEngineState* _State)
{
	Inc_Logo->On();
	AnyButtonFont->On();
	AnyBack = true;

	DarkSouls_Logo->GetColorData().MulColor.A = 1.0f;
}
void TitleLogo::End_AnyButton(GameEngineState* _State)
{
	AnyButtonFont->Off();
	FontScale = 20.0f;
	AnyButtonFont->ChangeFontScale(FontScale);
	AnyButtonBack->GetColorData().MulColor.A = 0.5f;
}

void TitleLogo::Start_Done(GameEngineState* _State)
{

}


#define ButtonBackStartYPos -92.5f
#define ButtonBackYDistance 32.0f

// 버튼 State
void TitleLogo::Start_ButtonActor(GameEngineState* _State)
{
	ButtonActor->On();

	AnyButtonBack->Transform.SetLocalPosition(float4(0.0f, ButtonBackStartYPos));
}

void TitleLogo::Update_ButtonActor(float _Delta, GameEngineState* _State)
{
	ButtonOperation();
}
void TitleLogo::End_ButtonActor(GameEngineState* _State)
{
}

void TitleLogo::ButtonOperation()
{
	if (ButtonCheckNum < 0)
	{
		ButtonCheckNum = ButtonCount - 1;
	}
	if (ButtonCheckNum > ButtonCount - 1)
	{
		ButtonCheckNum = 0;
	}

	if (GameEngineInput::IsDown(VK_RETURN, this) || GameEngineInput::IsDown('E', this) || GameEngineInput::IsDown(VK_SPACE, this))
	{
		MainUIActor::SoundPlay("GAMESTART.wav");
		ButtonState.ChangeState(eButtonState::Done);
		Buttons[ButtonCheckNum]->ButtonTrigger();
	}
	
	AnyButtonBack->Transform.SetWorldPosition(float4(0.0f, ButtonBackStartYPos - (ButtonBackYDistance * ButtonCheckNum)));
	
	if (GameEngineInput::IsDown(VK_UP, this))
	{
		ButtonCheckNum -= 1;
	}
	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		ButtonCheckNum += 1;
	}
}


void TitleLogo::ButtonFlash(float _Delta, GameEngineState* _State)
{
	if (AnyBack == true && AnyBackColor == false)
	{
		AnyButtonBack->GetColorData().MulColor.A += _Delta * 0.5f;
	}
	if (AnyBackColor == true)
	{
		AnyButtonBack->GetColorData().MulColor.A -= _Delta * 0.5f;
	}
	if (AnyButtonBack->GetColorData().MulColor.A >= 0.5f)
	{
		AnyBackColor = true;
	}
	if (AnyButtonBack->GetColorData().MulColor.A <= 0.0f)
	{
		AnyBackColor = false;
	}

	if (DarkSouls_Logo->GetColorData().MulColor.A >= 1.0f && FontEnter == false &&
		GameEngineInput::IsDownAnyKey() == true)
	{
		MainUIActor::SoundPlay("GAMESTART.wav");
		FontEnter = true;
	}
	if (FontEnter == true)
	{
		FontScale += 4.0f * _Delta;
		AnyButtonFont->Transform.AddLocalPosition(float4(0.0f, 2.0f * _Delta));
		AnyButtonFont->SetText(GlobalValue::OptimusFont, "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
		AnyButtonBack->GetColorData().MulColor.A += _Delta * 0.5f;
	}

	if (FontScale >= 25.0f)
	{
		FontEnter = false;
		ButtonState.ChangeState(eButtonState::ButtonActor);
		_State->ChangeState(eLogoState::Done);
		return;
	}
}


void TitleLogo::Ending()
{
	Logostate.ChangeState(eLogoState::EndLogo);
}

void TitleLogo::SkipButton(GameEngineState* _State, eLogoState _StateName)
{
	if(GameEngineInput::IsDown('E', this))
	{
		_State->ChangeState(_StateName);
		return;
	}
}

// 다크소울 로고 이미지만 스케일변경
void TitleLogo::DarkLogoAddScale(const float4& _Value)
{
	const float4 Scale = _Value + DarkSouls_Logo->GetAutoScaleRatio();
	DarkSouls_Logo->SetAutoScaleRatio(Scale);
}