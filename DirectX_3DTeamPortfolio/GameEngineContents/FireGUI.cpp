#include "PreCompile.h"
#include "FireGUI.h"
#include "ContentsFireRenderer.h"

FireGUI::FireGUI() 
{
}

FireGUI::~FireGUI()
{
}

void FireGUI::Start()
{
}

void FireGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowList(_Level);
	FireEditor();
}

void FireGUI::LevelEnd()
{
}

void FireGUI::ShowList(GameEngineLevel* _Level)
{
}

void FireGUI::FireEditor()
{
	if (ContentsFireRenderer::MainFire != nullptr)
	{
		FireInfo Info = ContentsFireRenderer::MainFire->FireInfoValue;

		bool callback = false;


		ImGui::SliderFloat("TimeScale", &ContentsFireRenderer::MainFire->TimeScale, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds1", &Info.scrollSpeeds1, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds2", &Info.scrollSpeeds2, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds3", &Info.scrollSpeeds3, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales1", &Info.scales1, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales2", &Info.scales2, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales3", &Info.scales3, 0.0f, 5.0f);


		callback = ImGui::SliderFloat3("distortion1", &Info.distortion1.X, -0.0f, 1.0f);
		callback = ImGui::SliderFloat3("distortion2", &Info.distortion2.X, -0.0f, 1.0f);
		callback = ImGui::SliderFloat3("distortion3", &Info.distortion3.X, -0.0f, 1.0f);

		callback = ImGui::SliderFloat("distortionScale", &Info.distortionScale, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("distortionBias", &Info.distortionBias, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("perturbscale", &Info.perturbscale, 0.0f, 5.0f);


		
			ContentsFireRenderer::MainFire->FireInfoValue = Info;
		
	}
}
