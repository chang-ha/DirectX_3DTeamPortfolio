#include "PreCompile.h"
#include "TitleButton.h"

TitleButton::TitleButton()
{

}

TitleButton::~TitleButton()
{

}

void TitleButton::Start()
{
	FontScale = 20.0f;
	


}
void TitleButton::Update(float _Delta)
{

}

#define ButtonFontStartYPos -84.0f
#define ButtonYDistance 32.0f
void TitleButton::CreateButton(int _Value)
{
	Buttons.reserve(_Value);
	
	for (int i = 0; i < Buttons.capacity(); i++)
	{
		std::shared_ptr<GameEngineUIRenderer> ButtonFont = CreateComponent<GameEngineUIRenderer>(Enum_UpdateOrder::UI);
		ButtonFont->SetText(GlobalValue::OptimusFont, "GAME START", FontScale, float4::WHITE, FW1_CENTER);
		ButtonFont->Transform.SetLocalPosition(float4(0.0f, ButtonFontStartYPos - (ButtonYDistance * i)));
		
		Buttons.push_back(ButtonFont);
	}
	Off();
}

void TitleButton::ChangeButtonText(int _Value, const std::string& _Name)
{
	Buttons[_Value]->ChangeText(_Name);
}

void TitleButton::ButtonTrigger()
{
	if (nullptr != Event)
	{
		Event();
	}

	Off();
}

void TitleButton::Release()
{
	Buttons.clear();
}

//GameEngineCore::ChangeLevel("Stage_Lothric");
//exit(0);