#include "PreCompile.h"
#include "TreeWindow.h"
#include "AnimationInfoGUI.h"
#include "DummyGUI.h"
#include "MonsterInfoGUI.h"
#include "LightGUI.h"
#include "HBAOGUI.h"
#include "LUTGUI.h"
#include "BloomGUI.h"
#include "FogGUI.h"
#include "FireGUI.h"


void TreeWindow::Start()
{
	CreateRootTree();
}

void RootTree::Start()
{
	CreateTree<AnimationInfoGUI>("Actor Editor");
	CreateTree<DummyGUI>("Dummy Editor");
	CreateTree<MonsterInfoGUI>("Monster GUI");
	CreateTree<LightGUI>("Light Editor");
	CreateTree<HBAOGUI>("HBAO Editor");
	CreateTree<LUTGUI>("LUT Editor");
	CreateTree<BloomGUI>("Bloom Editor");
	CreateTree<FogGUI>("Fog Editor");
	CreateTree<FireGUI>("Fire Editor");
}

void TreeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level != Level)
	{
		Root->AllLevelEnd();
		Level = _Level;
	}

	Root->AllOnGUI(_Level, _DeltaTime);


	//ÇÁ·¹ÀÓ
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

void TreeObject::Init(std::shared_ptr<TreeObject> _Object)
{
	_Object->Start();
} 

void TreeObject::AllOnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	for (const std::shared_ptr<TreeObject>& Object : ChildTrees)
	{
		std::string ObjectName = Object->GetName().data();
		if (ImGui::TreeNode(ObjectName.c_str()))
		{
			Object->OnGUI(_Level, _DeltaTime);
			Object->AllOnGUI(_Level, _DeltaTime);
			ImGui::TreePop();
		}
	}
}

void TreeObject::AllLevelEnd()
{
	for (std::shared_ptr<TreeObject>& Tree : ChildTrees)
	{
		Tree->AllLevelEnd();
		Tree->LevelEnd();
	}
}