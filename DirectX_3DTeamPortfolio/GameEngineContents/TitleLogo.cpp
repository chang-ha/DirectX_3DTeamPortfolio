#include "PreCompile.h"
#include "TitleLogo.h"

#include "LoadingLevel.h"

#include "MainUIActor.h"

TitleLogo::TitleLogo()
{

}

TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	BanDaiNamco_Logo = CreateComponent<GameEngineSpriteRenderer>();
	BanDaiNamco_Logo->SetSprite("BanDaiNaco_Logo.Png");
	BanDaiNamco_Logo->SetImageScale({ WindowScale.X , WindowScale.Y });
	BanDaiNamco_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 500.0f });
	BanDaiNamco_Logo->On();

	FromSoft_Logo = CreateComponent<GameEngineSpriteRenderer>();
	FromSoft_Logo->SetSprite("FromSoftLogo.Png");
	FromSoft_Logo->SetImageScale({ 1024, 1024 });
	FromSoft_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 300.0f });
	FromSoft_Logo->GetColorData().MulColor.A = 0.0f;

	DarkSouls_Logo = CreateComponent<GameEngineSpriteRenderer>();
	DarkSouls_Logo->SetSprite("DarkSoulsLogo.Png");
	DarkSouls_Logo->AutoSpriteSizeOn();
	DarkSouls_Logo->Transform.SetLocalPosition({ 0.0f, 50.0f, 500.0f });
	DarkSouls_Logo->GetColorData().MulColor.A = 0.0f;

	Inc_Logo = CreateComponent<GameEngineSpriteRenderer>();
	Inc_Logo->SetSprite("Title_IncLogo.Png");
	Inc_Logo->AutoSpriteSizeOn();
	Inc_Logo->Transform.SetLocalPosition({ 0.0f, -250.0f, 500.0f });
	Inc_Logo->Off();

	AnyButtonBack = CreateComponent<GameEngineSpriteRenderer>();
	AnyButtonBack->SetSprite("AnyButtonBack.Png");
	AnyButtonBack->AutoSpriteSizeOn();
	AnyButtonBack->SetAutoScaleRatio(0.45f);
	//AnyButtonBack->Transform.SetLocalPosition({ 0.0f, -119.95f, 505.0f });
	AnyButtonBack->Transform.SetLocalPosition({ 0.0f, -120.0f, 505.0f });
	AnyButtonBack->GetColorData().MulColor.A = 0.0f;

	FontRender = CreateComponent<GameEngineUIRenderer>();
	FontRender->SetText(GlobalValue::OptimusFont, "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
	FontRender->Transform.SetLocalPosition({ 0.0f, -111.0f, 500.0f });
	FontRender->Off();

	GameEngineInput::AddInputObject(this);
}

void TitleLogo::Update(float _Delta)
{
	Time += _Delta;
	if (Time >= 2.0f)
	{
		BanDaiNamco_Logo->GetColorData().MulColor.A -= _Delta * 0.5f;
	}

	if (Time >= FromSoftLogoTime)
	{
		BanDaiNamco_Logo->Off();
		FromSoft_Logo->GetColorData().MulColor.A += _Delta * 0.5f;
	}

	if (Time >= 8.0f)
	{
		FromSoft_Logo->Off();
		DarkSouls_Logo->GetColorData().MulColor.A += _Delta * 0.5f;
	}

	if (DarkSouls_Logo->GetColorData().MulColor.A >= 1.0f && AnyBack == false)
	{
		Inc_Logo->On();
		FontRender->On();
		AnyBack = true;
	}

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
		FontRender->SetText(GlobalValue::OptimusFont, "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
		AnyButtonBack->GetColorData().MulColor.A += _Delta * 0.5f;
	}

	if (FontScale >= 25.0f)
	{
		LoadingLevel::LoadingFlag = Enum_LevelFlag::Loading_Resouce;
		GameEngineCore::ChangeLevel("LoadingLevel");
	}
}

void TitleLogo::Release()
{
	DarkBack = nullptr;
	BanDaiNamco_Logo = nullptr;
	FromSoft_Logo = nullptr;
	DarkSouls_Logo = nullptr;
	Inc_Logo = nullptr;
	FontRender = nullptr;
	AnyButtonBack = nullptr;
}