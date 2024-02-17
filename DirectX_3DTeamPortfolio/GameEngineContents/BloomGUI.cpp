#include "PreCompile.h"
#include "BloomGUI.h"
#include "BloomEffect.h"

BloomGUI::BloomGUI() 
{
}

BloomGUI::~BloomGUI()
{
}

void BloomGUI::Start()
{
}

void BloomGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	Editor(_Level);
}

void BloomGUI::LevelEnd()
{
}

void BloomGUI::Editor(GameEngineLevel* _Level)
{
	ImGui::SliderFloat("Threshold", &BloomEffect::BloomInfoValue.Threshold, 0.0f, 1.0f);

}
