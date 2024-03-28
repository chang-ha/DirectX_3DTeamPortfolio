#include "PreCompile.h"
#include "TitleLogo.h"

#include "MainUIActor.h"
#include "TitleButton.h"

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


}

#define ButtonFontStartYPos -84.0f
#define ButtonYDistance 32.0f
// 버튼 만들기
#include <stdlib.h>
void TitleLogo::ButtonCreate()
{
	Buttons.reserve(2);
	ButtonActor = CreateComponent<TitleButton>(Enum_UpdateOrder::UI);
	ButtonActor->CreateButton(2);

	for (int i = 0; i < Buttons.capacity(); i++)
	{
		//std::shared_ptr<TitleButton> TButton = CreateComponent<TitleButton>(Enum_UpdateOrder::UI);
		
		/*std::shared_ptr<GameEngineUIRenderer> Button = CreateComponent<GameEngineUIRenderer>(Enum_UpdateOrder::UI);
		Button->SetText(GlobalValue::OptimusFont, "GAME START", FontScale, float4::WHITE, FW1_CENTER);
		Button->Transform.SetLocalPosition(float4(0.0f, ButtonFontStartYPos - (ButtonYDistance * i)));*/
		
		//Buttons.push_back(TButton);
		Buttons.push_back(ButtonActor);
	}

	ButtonActor->ChangeButtonText(GameStart, "GAME START");
	ButtonActor->ChangeButtonText(GameExit, "GAME EXIT");

	Buttons[GameStart]->SetButtonFunction([=]() { GameEngineCore::ChangeLevel("Stage_Lothric"); });
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
	Inc_Logo->On();
	AnyButtonFont->On();
	AnyBack = true;

	DarkSouls_Logo->GetColorData().MulColor.A = 0.0f;
}

void TitleLogo::Update_EndLogo(float _Delta, GameEngineState* _State)
{
	DarkSouls_Logo->GetColorData().MulColor.A += _Delta * 0.5f;

	if (_State->GetStateTime() >= LogoChangeTime)
	{
		_State->ChangeState(eLogoState::AnyButton);
		return;
	}
}
void TitleLogo::End_EndLogo(GameEngineState* _State)
{

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
}

void TitleLogo::Start_Done(GameEngineState* _State)
{

}




#define ButtonBackStartYPos -92.5f
#define ButtonBackYDistance 32.0f

// 버튼 State
void TitleLogo::Start_ButtonActor(GameEngineState* _State)
{
	Buttons[GameStart]->On();
	Buttons[GameExit]->On();

	ButtonActor->On();

	AnyButtonBack->Transform.SetLocalPosition(float4(0.0f, ButtonBackStartYPos));
}

void TitleLogo::Update_ButtonActor(float _Delta, GameEngineState* _State)
{
	ButtonOperation();

	if (GameEngineInput::IsDown('E', this))
	{
		//GameEngineCore::ChangeLevel("Stage_Lothric");
		return;
	}
}
void TitleLogo::End_ButtonActor(GameEngineState* _State)
{
	Buttons[GameStart]->Off();
	Buttons[GameExit]->Off();
}

void TitleLogo::ButtonOperation()
{
	if (GameEngineInput::IsDown('E', this))
	{
		Buttons[GameExit]->ButtonTrigger();
	}

	if (GameEngineInput::IsDown(VK_UP, this))
	{
		AnyButtonBack->Transform.SetWorldPosition(float4(0.0f, ButtonBackStartYPos));
	}

	if (GameEngineInput::IsDown(VK_DOWN, this))
	{
		AnyButtonBack->Transform.SetWorldPosition(float4(0.0f, ButtonBackStartYPos - ButtonBackYDistance));
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