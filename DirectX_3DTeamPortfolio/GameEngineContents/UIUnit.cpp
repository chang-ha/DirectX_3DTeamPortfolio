#include "PreCompile.h"
#include "UIUnit.h"
#include "PlayerValue.h"

#include "Player.h"

UIUnit::UIUnit()
{

}

UIUnit::~UIUnit()
{

}

void UIUnit::Start()
{
	L_Bar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackBar);
	L_Bar->SetSprite("Bar_Left.Png");
	L_Bar->SetPivotType(PivotType::Left);

	C_Bar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackBar);
	C_Bar->SetSprite("Bar_Center.Png");
	C_Bar->SetPivotType(PivotType::Left);

	R_Bar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackBar);
	R_Bar->SetSprite("Bar_Right.Png");
	R_Bar->SetPivotType(PivotType::Left);

	GaugeBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackGauge);

	LBarScale = L_Bar->GetSprite()->GetSpriteData(0).Texture->GetScale();
}

void UIUnit::SetParent(Player* _PlayerObject)
{
	pPlayer = _PlayerObject;
}

void UIUnit::Update(float _Delta)
{
	float PlayerGaugeValue = 0.0f;
	if (Type == Enum_BarType::Hp)
	{
		PlayerGaugeValue = static_cast<float>(pPlayer->GetHp());
	}
	if (Type == Enum_BarType::Mp)
	{
		PlayerGaugeValue = PlayerValue::GetValue()->GetMp();
	}
	if (Type == Enum_BarType::Stamina)
	{
		PlayerGaugeValue = static_cast<float>(pPlayer->GetStamina());
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

	const float GaugeRatio = RenderGauge / RenderTotalGauge;
	SetGauge(GaugeRatio);
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
		MsgBoxAssert("�������ٰ� ��������� ����ü�� �������� �̹����� �����Ϸ� �߽��ϴ�.");
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
		MsgBoxAssert("Ÿ���� ���������� ���� �������ٰ� ���Խ��ϴ�.");
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
		MsgBoxAssert("TotalGauge�� ������ Bar�� �����ϴ�.");
		return;
	}

	RenderGauge = RenderTotalGauge = _Value;

	float4 LBarScale = L_Bar->GetSprite()->GetSpriteData(0).Texture->GetScale();
	float4 CBarScale = C_Bar->GetSprite()->GetSpriteData(0).Texture->GetScale();
	float4 GaugeOriginScale = GaugeBar->GetSprite()->GetSpriteData(0).Texture->GetScale();
	float FullRatio = RenderTotalGauge / CBarScale.X;

	PixelGauge = GaugeOriginScale.X;

	// 1.0f �� Value�� ������
	C_Bar->AutoSpriteSizeOn();
	C_Bar->SetAutoScaleRatio(float4{ FullRatio , 1.0f });
	C_Bar->Transform.SetLocalPosition(LBarScale.X);
	R_Bar->Transform.SetLocalPosition(RenderTotalGauge + LBarScale.X);

}

// Ǯ�� ���� 1.0f
void UIUnit::SetGauge(float _Value)
{
	if (nullptr == GaugeBar)
	{
		MsgBoxAssert("������ �������ٸ� ã�� �� �߽��ϴ�.");
		return;
	}

	const float TotalRatio = RenderTotalGauge / PixelGauge;
	const float RenderGaugeRatio = _Value * TotalRatio;

	GaugeBar->AutoSpriteSizeOn();
	GaugeBar->SetAutoScaleRatio(float4(RenderGaugeRatio, 1.0f));
}