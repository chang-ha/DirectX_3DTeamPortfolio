#include "PreCompile.h"
#include "HBAOGUI.h"
#include <GameEngineCore\GameEngineAO.h>

HBAOGUI::HBAOGUI() 
{
}

HBAOGUI::~HBAOGUI()
{
}

void HBAOGUI::Start()
{
}

void HBAOGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	HBAOEditor(_Level);
}

void HBAOGUI::LevelEnd()
{
}

void HBAOGUI::HBAOEditor(GameEngineLevel* _Level)
{
	float AORadius = 2.f;
	float AOBias = 0.2f;
	bool BlurAO = true;
	float BlurSharpness = 32.f;
	float PowerExponent = 2.f;
	float SmallScaleAO = 1.f;
	float LargeScaleAO = 1.f;

	//if (ImGui::TreeNode("HBAO Editor"))
	//{
		ImGui::InputFloat("AOBias", &GameEngineAO::HBAOInfosValue.AOBias);

		ImGui::InputFloat("AORadius", &GameEngineAO::HBAOInfosValue.AORadius);

		ImGui::InputFloat("SmallScaleAO", &GameEngineAO::HBAOInfosValue.SmallScaleAO);

		ImGui::InputFloat("LargeScaleAO", &GameEngineAO::HBAOInfosValue.LargeScaleAO);

		ImGui::InputFloat("PowerExponent", &GameEngineAO::HBAOInfosValue.PowerExponent);

		ImGui::InputFloat("BlurSharpness", &GameEngineAO::HBAOInfosValue.BlurSharpness);


		//ImGui::TreePop();
	//}

	
}
