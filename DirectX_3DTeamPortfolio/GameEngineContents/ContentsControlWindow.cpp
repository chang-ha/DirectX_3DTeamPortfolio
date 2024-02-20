#include "PreCompile.h"
#include "ContentsControlWindow.h"
#include "Player.h"

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
	Tabs.push_back(std::make_shared<TestTabB>("Player"));
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
	size_t a = _Level->GetObjectGroupInt(0).size();

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

void TestTabB::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int BoneIndex = Player::Main_Player->Bone_index_01;
	ImGui::InputInt("SPos", &BoneIndex);
	Player::Main_Player->Bone_index_01 = BoneIndex;

	float4 Pos = Player::Main_Player->Weapon->Transform.GetLocalPosition();
	ImGui::DragFloat4("SPos", Pos.Arr1D);

	float4 Rot = Player::Main_Player->Weapon->Transform.GetLocalRotationEuler();
	ImGui::DragFloat4("SRot", Rot.Arr1D);

	Player::Main_Player->Weapon->Transform.SetLocalPosition(Pos);
	Player::Main_Player->Weapon->Transform.SetLocalRotation(Rot);

}
