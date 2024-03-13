#include "PreCompile.h"
#include "LUTGUI.h"
#include "LUTEffect.h"



LUTGUI::LUTGUI() 
{
}

LUTGUI::~LUTGUI()
{
}

void LUTGUI::Start()
{
}

void LUTGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	LUTEditor(_Level);
}

void LUTGUI::LevelEnd()
{
	CObjectNames.clear();
}

void LUTGUI::LUTEditor(GameEngineLevel* _Level)
{
	if (CObjectNames.empty() == true)
	{

		CObjectNames.resize(LUTEffect::LUTNames.size());

		for (size_t i = 0; i < LUTEffect::LUTNames.size(); i++)
		{
			CObjectNames[i] = LUTEffect::LUTNames[i].c_str();
		}
	}

	static int SelectLUTIndex = 0;

	if (ImGui::ListBox("LUTList", &SelectLUTIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string LUTName = CObjectNames[SelectLUTIndex];
		if (true == LUTName.empty())
		{
			return;
		}

		LUTEffect::SetCurLUTNameValue(LUTName);
	}

	std::string Frame = std::to_string(1.0f / GameEngineCore::MainTime.GetDeltaTime());

	ImGui::Text(Frame.c_str());

	static std::string FrameSelect = "Off";
	static int FrameCount = 0;
	static float FrameSecond = 0.0f;
	static int FrameResult = 0;


	FrameSecond += GameEngineCore::MainTime.GetDeltaTime();
	FrameCount++;




	if (ImGui::Button("FrameCatch"))
	{
		FrameSelect = Frame;
	}
	ImGui::Text(FrameSelect.c_str());

	if (FrameSecond >= 1.0f)
	{
		FrameResult = FrameCount;
		FrameCount = 0;
		FrameSecond -= 1.0f;
	}

	std::string Frame2 = "Average Frame: " + std::to_string(FrameResult);

	ImGui::Text(Frame2.c_str());
}
