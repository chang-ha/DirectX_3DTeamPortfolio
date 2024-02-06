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
}
