#include "PreCompile.h"
#include "TitleLogo.h"

TitleLogo::TitleLogo()
{

}

TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	DarkBack = CreateComponent<GameEngineSpriteRenderer>();
	DarkBack->SetSprite("Dark.Png");
	DarkBack->AutoSpriteSizeOn();
	DarkBack->SetAutoScaleRatio(2.0f);
	DarkBack->Transform.SetLocalPosition({ 0.0f, 0.0f, 510.0f });

	BanDaiNamco_Logo = CreateComponent<GameEngineSpriteRenderer>();
	BanDaiNamco_Logo->SetSprite("BanDaiNaco_Logo.Png");
	BanDaiNamco_Logo->AutoSpriteSizeOn();
	BanDaiNamco_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 500.0f });
	BanDaiNamco_Logo->On();

	FromSoft_Logo = CreateComponent<GameEngineSpriteRenderer>();
	FromSoft_Logo->SetSprite("FromSoftLogo.Png");
	FromSoft_Logo->AutoSpriteSizeOn();
	FromSoft_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 500.0f });
	FromSoft_Logo->GetColorData().MulColor.A = 0.0f;

	DarkSouls_Logo = CreateComponent<GameEngineSpriteRenderer>();
	DarkSouls_Logo->SetSprite("DarkSoulsLogo.Png");
	DarkSouls_Logo->AutoSpriteSizeOn();
	DarkSouls_Logo->Transform.SetLocalPosition({ 0.0f, 0.0f, 500.0f });
	DarkSouls_Logo->GetColorData().MulColor.A = 0.0f;

	Inc_Logo = CreateComponent<GameEngineSpriteRenderer>();
	Inc_Logo->SetSprite("Title_IncLogo.Png");
	Inc_Logo->AutoSpriteSizeOn();
	Inc_Logo->Transform.SetLocalPosition({ 0.0f, -250.0f, 500.0f });
	Inc_Logo->Off();

	AnyButtonBack = CreateComponent<GameEngineSpriteRenderer>();
	AnyButtonBack->SetSprite("AnyButtonBack.Png");
	AnyButtonBack->AutoSpriteSizeOn();
	AnyButtonBack->SetAutoScaleRatio(0.4f);
	AnyButtonBack->Transform.SetLocalPosition({ 0.0f, -133.0f, 505.0f });
	AnyButtonBack->GetColorData().MulColor.A = 0.0f;

	FontRender = CreateComponent<GameEngineUIRenderer>();
	FontRender->SetText("OptimusBold", "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
	FontRender->Transform.SetLocalPosition({ 0.0f, -150.0f, 500.0f });
	FontRender->Off();

	GameEngineInput::AddInputObject(this);
}

void TitleLogo::Update(float _Delta)
{
	Time += _Delta;
	if (Time >= BanDaiLogoTime)
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



	if (DarkSouls_Logo->GetColorData().MulColor.A >= 1.0f && GameEngineInput::IsDown(VK_RETURN, this) && FontEnter == false)
	{
		FontEnter = true;
	}
	if (FontEnter == true)
	{
		FontScale += 5.0f * _Delta;
		FontRender->SetText("OptimusBold", "PRESS ANY BUTTON", FontScale, float4{ 1, 1, 1, 1 }, FW1_CENTER);
		AnyButtonBack->GetColorData().MulColor.A += _Delta * 0.5f;
		AnyButtonBack->Transform.AddLocalScale(0.1f * _Delta);
	}

	if (FontScale >= 25.0f)
	{
		FontRender->Off();
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}