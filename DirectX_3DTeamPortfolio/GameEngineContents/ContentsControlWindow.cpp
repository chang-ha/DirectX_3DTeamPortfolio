#include "PreCompile.h"
#include "ContentsControlWindow.h"


void TestTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	
	std::string MousePos = GameEngineCore::MainWindow.GetMousePos().ToString();

	if (ImGui::Button(MousePos.c_str()))
	{

	}

	if (ImGui::Button("Collision OnOff"))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}

	std::list<std::shared_ptr<GameEngineObject>> ObjectLists = _Level->GetObjectGroupInt(0);

	std::vector<std::shared_ptr<GameEngineObject>> Objects;

	for (std::shared_ptr<GameEngineObject> Ptr : ObjectLists)
	{
		Objects.push_back(Ptr);
	}


	if (Objects.size())
	{
		std::vector<std::string> Names;

		for (std::shared_ptr<GameEngineObject> Ptr : Objects)
		{
			Names.push_back(Ptr->GetName());
		}

		//Names.push_back("aaaa");
		//Names.push_back("bbbb");

		std::vector<const char*> CNames;

		for (size_t i = 0; i < Names.size(); i++)
		{
			CNames.push_back(Names[i].c_str());
		}

		if (ImGui::ListBox("ObjectList", &Select, &CNames[0], static_cast<int>(Names.size())))
		{
			SelectObject = Objects[Select];
		}

		if (nullptr != SelectObject)
		{
			if (ImGui::Button("Select Object Off"))
			{
				SelectObject->Off();
			}

		}
	}
}


void ContentsControlWindow::Start()
{
	Tabs.push_back(std::make_shared<LevelChangeTab>("LevelChangeTab"));
	CurTab = Tabs[0];
	Tabs.push_back(std::make_shared<TestTab>("Test"));
	Tabs.push_back(std::make_shared<TestTabA>("ADAD"));
	//Tabs.push_back(std::make_shared<MapEditorTab>("MapEditor"));
	
}

void LevelChangeTab::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
	}
}


void ContentsControlWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	for (size_t i = 0; i < Tabs.size(); i++)
	{
		ImGui::SameLine();
		if (ImGui::Button(Tabs[i]->Name.c_str()))
		{
			CurTab = Tabs[i];
		}
	}

	if (nullptr != CurTab)
	{
		CurTab->OnGUI(_Level, _DeltaTime);
	}
}

void TestTabA::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::vector<std::string> Names;

	std::vector<const char*> CNames;
	int a = _Level->GetObjectGroupInt(0).size();

	for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : _Level->GetMainCamera()->GetRenderers())
	{
		std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;

		for (std::shared_ptr<class GameEngineRenderer>& Renderer : RendererList)
		{
			Names.push_back(Renderer->GetName());
		}
	}

	for (size_t i = 0; i < Names.size(); i++)
	{
		CNames.push_back(Names[i].c_str());
	}

	/*for (size_t i = 0; i < _Level->GetMainCamera()->Renderers[0].size(); i++)
	{
		_Level->GetMainCamera()->Renderers[i];
	}*/






	if (ImGui::ListBox("Off_list", &Select, &CNames[0], static_cast<int>(Names.size())))
	{
		for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : _Level->GetMainCamera()->GetRenderers())
		{
			std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;




			for (std::shared_ptr<class GameEngineRenderer>& Renderer : RendererList)
			{
				if (Renderer->GetName() == CNames[Select])
				{
					Renderer->Off();
				}
			}
		}
	}

	if (ImGui::ListBox("On_list", &Select, &CNames[0], static_cast<int>(Names.size())))
	{
		for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : _Level->GetMainCamera()->GetRenderers())
		{
			std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;


			for (std::shared_ptr<class GameEngineRenderer>& Renderer : RendererList)
			{
				if (Renderer->GetName() == CNames[Select])
				{
					Renderer->On();
				}
			}
		}
	}

	if (nullptr != SelectObject)
	{
		if (ImGui::Button("Select Object Off"))
		{
			SelectObject->Off();
		}
	}

}
