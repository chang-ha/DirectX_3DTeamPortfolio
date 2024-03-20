#include "PreCompile.h"
#include "UIEquipFrame.h"

UIEquipFrame::UIEquipFrame()
{

}

UIEquipFrame::~UIEquipFrame()
{

}

void UIEquipFrame::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	FixPos = { -WindowScale.X + 170.0f , -300.0f };

	{
		Equip_Frame = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackTexture);
		Equip_Frame->SetSprite("EquipFrame.Png");
		Equip_Frame->AutoSpriteSizeOn();
		Equip_Frame->SetAutoScaleRatio(0.9f);
	}
}

void UIEquipFrame::SetEquipSprite(Enum_EquipType _Type)
{
	if (nullptr == Equip)
	{
		MsgBoxAssert("��� ��������� ����ä�� ��� �̹����� �����Ϸ� �����ϴ�.");
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
		MsgBoxAssert("Ÿ���� ���������� ���� ��� ���Խ��ϴ�.");
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