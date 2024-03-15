#include "PreCompile.h"
#include "UIPlayerGaugeBar.h"
#include "PlayerValue.h"

UIPlayerGaugeBar::UIPlayerGaugeBar()
{
}

UIPlayerGaugeBar::~UIPlayerGaugeBar()
{
}

//BarStruct* BarStruct::BackBar;

#define First_Bar_Pos float4(105, 420)

void UIPlayerGaugeBar::Start()
{
	float MaxHp = PlayerValue::GetValue()->GetMaxHp();
	float MaxMp = PlayerValue::GetValue()->GetMaxMp();
	float MaxStamina = PlayerValue::GetValue()->GetMaxStamina();


	HpBar = CreateBarActor(Enum_BarType::Hp, MaxHp);
	MpBar = CreateBarActor(Enum_BarType::Mp, MaxMp);
	StaminaBar = CreateBarActor(Enum_BarType::Stamina, MaxStamina);
	
	GameEngineInput::AddInputObject(this);
}

void UIPlayerGaugeBar::Update(float _Delta)
{
	if (GameEngineInput::IsDown('0', this))
	{
		PlayerValue::GetValue()->SetMaxHp(700.0f);
		PlayerValue::GetValue()->SetHp(700.0f);
		HpBar->SetTotalGauge(700.0f);

		PlayerValue::GetValue()->SetMaxMp(500.0f);
		MpBar->SetTotalGauge(500.0f);
	}
}

void UIPlayerGaugeBar::Release()
{
	for (std::pair<const Enum_BarType, UIUnit*>& Pair : GaugeBars)
	{
		Pair.second->Death();
	}

	GaugeBars.clear();
}

#define BarGap 16.0f

UIUnit* UIPlayerGaugeBar::CreateBarActor(Enum_BarType _Type, float _TotalSize)
{
	std::shared_ptr<UIUnit> UIBarUnit = GetLevel()->CreateActor<UIUnit>();

	UIUnit* pBars = UIBarUnit.get();

	GaugeBars.insert(std::make_pair(_Type, pBars));
	size_t GaugeBarSize = GaugeBars.size();

	// Pos
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();

	float4 Pos = First_Bar_Pos -WindowScale.X + float4(0.0f, - BarGap * (GaugeBarSize - 1));
	UIBarUnit->Transform.SetWorldPosition(Pos);
	UIBarUnit->SetBarType(_Type);
	UIBarUnit->SetBarSprite(_Type);
	UIBarUnit->SetTotalGauge(_TotalSize);
	UIBarUnit->SetGauge(1.0f);

	return pBars;
}

UIUnit* UIPlayerGaugeBar::FindBar(Enum_BarType _Type)
{
	if (!GaugeBars.contains(_Type))
	{
		MsgBoxAssert("찾고있는 Bar 타입이 없습니다.");
	}

	return GaugeBars[_Type];
}

void UIPlayerGaugeBar::FindAndSetGauge(Enum_BarType _Type, float _Value)
{
	UIUnit* BarSet = FindBar(_Type);
	if (nullptr == BarSet)
	{
		MsgBoxAssert("null인 BarSet이 들어왔습니다.");
	}

	BarSet->SetGauge(_Value);
}