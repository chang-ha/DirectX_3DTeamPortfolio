#include "PreCompile.h"
#include "UIUnit.h"
#include "PlayerValue.h"

UIUnit::UIUnit()
{

}

UIUnit::~UIUnit()
{

}

void UIUnit::Start()
{
	L_Bar = CreateComponent<GameEngineUIRenderer>();
	L_Bar->SetSprite("Bar_Left.Png");
	L_Bar->SetPivotType(PivotType::Left);

	LBarScale = L_Bar->GetSprite()->GetSpriteData(0).GetScale();
	C_Bar = CreateComponent<GameEngineUIRenderer>();
	C_Bar->SetSprite("Bar_Center.Png");
	C_Bar->SetPivotType(PivotType::Left);

	float4 CBarScale = C_Bar->GetSprite()->GetSpriteData(0).GetScale();
	float4 LCScale = LBarScale + CBarScale;

	R_Bar = CreateComponent<GameEngineUIRenderer>();
	R_Bar->SetSprite("Bar_Right.Png");
	R_Bar->SetPivotType(PivotType::Left);


	GaugeBar = CreateComponent<GameEngineUIRenderer>();
}

void UIUnit::Update(float _Delta)
{

	if (Type == Enum_BarType::Hp)
	{
		PlayerGaugeValue = PlayerValue::GetValue()->GetHp();
	}
	if (Type == Enum_BarType::Mp)
	{
		PlayerGaugeValue = PlayerValue::GetValue()->GetMp();
	}
	if (Type == Enum_BarType::Stamina)
	{
		PlayerGaugeValue = PlayerValue::GetValue()->GetStamina();
	}

	if (PlayerGaugeValue == RenderGauge)
	{
		return;
	}

	if (PlayerGaugeValue < RenderGauge)
	{
		RenderGauge -= RenderSpeed * _Delta;
		if (PlayerGaugeValue > RenderGauge)
		{
			RenderGauge = PlayerGaugeValue;
		}
	}
	else if (PlayerGaugeValue > RenderGauge)
	{
		RenderGauge += RenderSpeed * _Delta;

		if (PlayerGaugeValue < RenderGauge)
		{
			RenderGauge = PlayerGaugeValue;
		}
	}

	SetGauge(RenderGauge);

	//CurHp = PlayerValue::GetValue()->GetHp();
	//SetGauge(PlayerGaugeValue);

	//////  

}

void UIUnit::Release()
{
	L_Bar = nullptr;
	C_Bar = nullptr;
	R_Bar = nullptr;

	GaugeBar = nullptr;
}


void UIUnit::SetBarSprite(Enum_BarType _Type)
{
	if (nullptr == GaugeBar)
	{
		MsgBoxAssert("게이지바가 만들어지지 않은체로 게이지바 이미지를 지정하려 했습니다.");
	}

	std::string SpriteName;

	switch (_Type)
	{
	case Enum_BarType::Hp:
		SpriteName = "MinHpBar";
		break;
	case Enum_BarType::Mp:
		SpriteName = "MinMpBar";
		break;
	case Enum_BarType::Stamina:
		SpriteName = "MinStaminaBar";
		break;
	default:
		MsgBoxAssert("타입을 지정해주지 않은 게이지바가 들어왔습니다.");
		break;
	}
	SpriteName += ".Png";

	GaugeBar->Transform.SetLocalPosition({ LBarScale.X, 0.0f });
	GaugeBar->SetSprite(SpriteName);
	GaugeBar->SetPivotType(PivotType::Left);
}

void UIUnit::SetTotalGauge(float _Value)
{
	if (nullptr == C_Bar ||
		nullptr == L_Bar ||
		nullptr == R_Bar)
	{
		MsgBoxAssert("TotalGauge를 지정할 Bar가 없습니다.");
		return;
	}

	float4 LBarScale = L_Bar->GetSprite()->GetSpriteData(0).GetScale();
	float4 CBarScale = C_Bar->GetSprite()->GetSpriteData(0).GetScale();

	CBarScale.X;

	// 1.0f 를 Value의 비율로
	float Value = _Value / 100.0f;
	C_Bar->AutoSpriteSizeOn();
	C_Bar->SetAutoScaleRatio(float4{ Value, 1.0f });
	C_Bar->Transform.SetLocalPosition(LBarScale.X);
	R_Bar->Transform.SetLocalPosition(CBarScale.X * Value + LBarScale.X);

}

void UIUnit::SetGauge(float _Value)
{
	if (nullptr == GaugeBar)
	{
		MsgBoxAssert("조절할 게이지바를 찾지 못 했습니다.");
		return;
	}

	GaugeBar->AutoSpriteSizeOn();
	GaugeBar->SetAutoScaleRatio(float4(_Value * 5.4f / 100.0f, 1.0f));
}

void UIUnit::Reset()
{

}
