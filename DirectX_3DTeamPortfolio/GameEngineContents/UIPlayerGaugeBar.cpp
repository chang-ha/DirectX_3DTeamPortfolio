#include "PreCompile.h"
#include "UIPlayerGaugeBar.h"
#include "PlayerValue.h"

#include "Player.h"

UIPlayerGaugeBar::UIPlayerGaugeBar()
{
	GameEngineInput::AddInputObject(this);
}

UIPlayerGaugeBar::~UIPlayerGaugeBar()
{
}

//BarStruct* BarStruct::BackBar;

#define First_Bar_Pos float4(105, 420)

void UIPlayerGaugeBar::Start()
{

}

void UIPlayerGaugeBar::Init(Player* _PlayerObject)
{
	if (nullptr == _PlayerObject)
	{
		MsgBoxAssert("존재하지 않는 플레이어 주소입니다.");
		return;
	}

	pPlayer = _PlayerObject;

	const float MaxHp = static_cast<float>(pPlayer->Get_Max_Hp());
	const float MaxMp = PlayerValue::GetValue()->GetMaxMp();
	const float MaxStamina = static_cast<float>(pPlayer->Get_Max_Stamina());

	HpBar = CreateBarActor(Enum_BarType::Hp, MaxHp, pPlayer);
	MpBar = CreateBarActor(Enum_BarType::Mp, MaxMp, pPlayer);
	StaminaBar = CreateBarActor(Enum_BarType::Stamina, MaxStamina, pPlayer);

	// 확인용
	// float Hp = PlayerObject->Main_Player->GetHp();
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

UIUnit* UIPlayerGaugeBar::CreateBarActor(Enum_BarType _Type, float _TotalSize, Player* _PlayerObject)
{
	std::shared_ptr<UIUnit> UIBarUnit = GetLevel()->CreateActor<UIUnit>(Enum_UpdateOrder::UI);
	UIBarUnit->SetParent(_PlayerObject);

	UIUnit* pBars = UIBarUnit.get();

	GaugeBars.insert(std::make_pair(_Type, pBars));
	size_t GaugeBarSize = GaugeBars.size();

	// Pos
	const float4 HScale = GameEngineCore::MainWindow.GetScale().Half();
	const float4 BarOrder_StartPos = float4(0.0f, -BarGap * static_cast<float>(GaugeBarSize - 1));
	const float4 BarPos = First_Bar_Pos - HScale.X + BarOrder_StartPos;

	UIBarUnit->Transform.SetWorldPosition(BarPos);
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