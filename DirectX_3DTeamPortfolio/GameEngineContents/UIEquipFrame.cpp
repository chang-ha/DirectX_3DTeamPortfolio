#include "PreCompile.h"
#include "UIEquipFrame.h"

UIEquipFrame::UIEquipFrame()
{

}

UIEquipFrame::~UIEquipFrame()
{

}

#define XDistance 110.0f
#define YDistance 80.0f

void UIEquipFrame::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	FixPos = { -WindowScale.X + 170.0f , -300.0f };

	{
		Equip_Frame = CreateComponent<GameEngineUIRenderer>();
		Equip_Frame->SetSprite("EquipFrame.Png");
		Equip_Frame->AutoSpriteSizeOn();
	}
}

void UIEquipFrame::SetEquipSprite(Enum_EquipType _Type)
{
	if (nullptr == Equip)
	{
		MsgBoxAssert("장비가 만들어지지 않은채로 장비 이미지를 지정하려 헀습니다.");
	}

	std::string SpriteName;

	switch (_Type)
	{
	case Enum_EquipType::Magic:
		SpriteName = "Magic";
		break;
	case Enum_EquipType::Shield:
		SpriteName = "Shield";
		break;
	case Enum_EquipType::Sword:
		SpriteName = "Sword";
		break;
	case Enum_EquipType::Este:
		SpriteName = "Este";
		break;
	default:
		MsgBoxAssert("타입을 지정해주지 않은 장비가 들어왔습니다.");
		break;
	}

	SpriteName += ".Png";

	Equip->Transform.SetLocalPosition(Equip_Frame->Transform.GetLocalPosition());
	Equip->SetSprite(SpriteName);
}


void UIEquipFrame::Release()
{
	Equip_Frame = nullptr;
	Equip = nullptr;
}