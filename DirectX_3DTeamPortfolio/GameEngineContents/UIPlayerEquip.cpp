#include "PreCompile.h"
#include "UIPlayerEquip.h"

UIPlayerEquip::UIPlayerEquip()
{
}

UIPlayerEquip::~UIPlayerEquip()
{
}

#define ImgaeRatio 0.7f
void UIPlayerEquip::Start()
{
	{
		MagicFrame = CreatEquipActor(Enum_EquipType::Magic);
	}

	{
		SwordFrame = CreatEquipActor(Enum_EquipType::Sword);

		Sword = CreateComponent<GameEngineUIRenderer>();
		Sword->SetSprite("Sword.Png");
		Sword->AutoSpriteSizeOn();
		Sword->SetAutoScaleRatio(ImgaeRatio);
		Sword->Transform.SetLocalPosition(SwordFrame->Transform.GetWorldPosition());
	}

	{
		ShieldFrame = CreatEquipActor(Enum_EquipType::Shield);

		Shield = CreateComponent<GameEngineUIRenderer>();
		Shield->SetSprite("Shield.Png");
		Shield->AutoSpriteSizeOn();
		Shield->SetAutoScaleRatio(ImgaeRatio);
		Shield->Transform.SetLocalPosition(ShieldFrame->Transform.GetWorldPosition());
	}

	{
		EsteFrame = CreatEquipActor(Enum_EquipType::Este);

		EsteBack = CreateComponent<GameEngineUIRenderer>();
		EsteBack->SetSprite("Sword.Png");
		EsteBack->AutoSpriteSizeOn();
		EsteBack->SetAutoScaleRatio(ImgaeRatio);
		EsteBack->Transform.SetLocalPosition(EsteFrame->Transform.GetWorldPosition());

		Este = CreateComponent<GameEngineUIRenderer>();
		Este->SetSprite("EsteBottle_Full.Png");
		Este->AutoSpriteSizeOn();
		Este->SetAutoScaleRatio(ImgaeRatio);
		Este->Transform.SetLocalPosition(EsteFrame->Transform.GetWorldPosition());

		float EstePosY =  Este->GetSprite()->GetSpriteData(0).GetScale().hY();

		EsteFont = CreateComponent<GameEngineUIRenderer>();
		EsteFont->SetText(GlobalValue::OptimusFont, "에스트 병", 14.0f, float4{ 1, 1, 1, 1, }, FW1_CENTER);
		EsteFont->On();
		EsteFont->Transform.SetLocalPosition({ EsteFrame->Transform.GetWorldPosition().X,
			EsteFrame->Transform.GetWorldPosition().Y - EstePosY * ImgaeRatio });

		EsteCount = CreateComponent<GameEngineUIRenderer>();
		EsteCount->SetText(GlobalValue::OptimusFont, std::to_string(CurEsteCount), 15.0f, float4{1, 1, 1, 1,}, FW1_CENTER);
		EsteCount->On();
		EsteCount->Transform.SetLocalPosition({ EsteFrame->Transform.GetWorldPosition().X + 37.0f,
			EsteFrame->Transform.GetWorldPosition().Y - 57.0f });

	}

	GameEngineInput::AddInputObject(this);
}

void UIPlayerEquip::Update(float _Delta)
{

	if (GameEngineInput::IsDown('0', this))
	{
		CurEsteCount++;
	}

	if (GameEngineInput::IsDown('-', this))
	{
		CurEsteCount--;
	}

	EsteCount->SetText(GlobalValue::OptimusFont, std::to_string(CurEsteCount), 15.0f, float4{ 1, 1, 1, 1, }, FW1_CENTER);
	ChangeEsteImage();
}

void UIPlayerEquip::ChangeEsteImage()
{
	StandardEste = ceil(MaxEsteCount / 3.0f);

	if (StandardEste >= CurEsteCount && CurEsteCount > 0)
	{
		Este->SetSprite("EsteBottl_S.Png");
		return;
	}
	else if ((StandardEste * 2) >= CurEsteCount && CurEsteCount > StandardEste)
	{
		Este->SetSprite("EsteBottl_M.Png");
		return;
	}
	else if (CurEsteCount <= 0)
	{
		Este->SetSprite("EsteBottle_Empty.Png");
		return;
	}
	else
	{
		Este->SetSprite("EsteBottle_Full.Png");
		return;
	}
}

void UIPlayerEquip::Release()
{
	for (std::pair<const Enum_EquipType, UIEquipFrame*>& Pair : EquipMent)
	{
		Pair.second->Death();
	}

	EquipMent.clear();
}

#define XDistance 80.0f
#define YDistance 57.0f
UIEquipFrame* UIPlayerEquip::CreatEquipActor(Enum_EquipType _Type)
{
	std::shared_ptr<UIEquipFrame> UIFrame = GetLevel()->CreateActor<UIEquipFrame>();

	UIEquipFrame* pFrame = UIFrame.get();

	EquipMent.insert(std::make_pair(_Type, pFrame));

	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	FixPos = { -WindowScale.X + 170.0f , -200.0f };

	switch (_Type)
	{
	case Enum_EquipType::Magic:
		UIFrame->Transform.SetWorldPosition({ FixPos.X, FixPos.Y + YDistance });
		break;
	case Enum_EquipType::Shield:
		UIFrame->Transform.SetWorldPosition({ FixPos.X - XDistance, FixPos.Y });
		break;
	case Enum_EquipType::Sword:
		UIFrame->Transform.SetWorldPosition({FixPos.X + XDistance, FixPos.Y});
		break;
	case Enum_EquipType::Este:
		UIFrame->Transform.SetWorldPosition({ FixPos.X, FixPos.Y - YDistance });

		Equip_Este_Sub = CreateComponent<GameEngineUIRenderer>();
		Equip_Este_Sub->SetSprite("Este_Sub.Png");
		Equip_Este_Sub->AutoSpriteSizeOn();
		Equip_Este_Sub->SetAutoScaleRatio(ImgaeRatio);
		Equip_Este_Sub->Transform.SetLocalPosition({ FixPos.X + XDistance  , FixPos.Y - YDistance });
		Equip_Este_Sub->SetPivotType(PivotType::RightUp);
		break;
	default:
		break;
	}

	return pFrame;
}

UIEquipFrame* UIPlayerEquip::FindFrame(Enum_EquipType _Type)
{
	if (!EquipMent.contains(_Type))
	{
		MsgBoxAssert("찾고있는 Equip 타입이 없습니다.");
	}

	return EquipMent[_Type];
}