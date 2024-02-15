#include "PreCompile.h"
#include "TreeWindow.h"
#include "AnimationInfoGUI.h"
#include "MonsterInfoGUI.h"
#include "DummyGUI.h"
#include "LightGUI.h"
#include "HBAOGUI.h"
#include "LUTGUI.h"


void TreeWindow::Start()
{
	CreateRootTree();
}

void RootTree::Start()
{
	CreateTree<AnimationInfoGUI>("Actor Editor");
	CreateTree<MonsterInfoGUI>("Monster Info");
	CreateTree<DummyGUI>("Dummy GUI");
	CreateTree<LightGUI>("Light Editor");
	CreateTree<HBAOGUI>("HBAO Editor");
	CreateTree<LUTGUI>("LUT Editor");
}

void TreeWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (_Level != Level)
	{
		Root->AllLevelEnd();
		Level = _Level;
	}

	Root->AllOnGUI(_Level, _DeltaTime);
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