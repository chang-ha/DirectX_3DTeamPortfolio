#include "PreCompile.h"
#include "AnimationInfoGUI.h"

#include "CommonMonster.h"
#include "FrameEventHelper.h"

AnimationInfoGUI::AnimationInfoGUI() 
{
}

AnimationInfoGUI::~AnimationInfoGUI() 
{
}


void AnimationInfoGUI::Start()
{
	CreateEventTree<SoundEventTree>("Sound Event Editor");
}

void AnimationInfoGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowActorList(_Level);
	TransformEditor();
	AnimationList();
	EventEditor(_Level, _DeltaTime);
}

void AnimationInfoGUI::LevelEnd()
{
	SelectActor = nullptr;
	SelectAnimation = nullptr;
	ActorNames.clear();
	CObjectNames.clear();
	AnimationNames.clear();
	CAnimationNames.clear();
}

void AnimationInfoGUI::ShowActorList(GameEngineLevel* _Level)
{
	if (true == CObjectNames.empty())
	{
		const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = _Level->GetObjectGroupInt(static_cast<int>(Enum_UpdateOrder::Monster));
		if (ObjectGroup.empty())
		{
			return;
		}

		CObjectNames.reserve(ObjectGroup.size());
		ActorNames.reserve(ObjectGroup.size());
		int Cnt = 0;

		for (const std::shared_ptr<GameEngineObject>& Object : ObjectGroup)
		{
			ActorNames.push_back(Object->GetName());
			CObjectNames.push_back(ActorNames[Cnt].c_str());
			Cnt++;
		}
	}

	static int SelectActorIndex = 0;

	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<CommonMonster>>& MonsterGroup = _Level->GetObjectGroupConvert<CommonMonster>(Enum_UpdateOrder::Monster);
		for (const std::shared_ptr<CommonMonster>& Monster : MonsterGroup)
		{
			if (CObjectNames[SelectActorIndex] == Monster->GetName())
			{
				SelectActor = Monster.get();
				AnimationNames.clear();
				CAnimationNames.clear();
				SelectAnimation = nullptr;
			}
		}
	}
}

void AnimationInfoGUI::TransformEditor()
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (ImGui::TreeNode("Transform Editor"))
	{
		if (true == SelectActor->IsDeath())
		{
			SelectActor = nullptr;
			AnimationNames.clear();

			ImGui::TreePop();
			return;
		}

		Size = SelectActor->Transform.GetLocalScale().X;
		Rot = SelectActor->Transform.GetLocalRotationEuler();
		Pos = SelectActor->Transform.GetLocalPosition();

		if (ImGui::InputFloat("Set Scale", &Size))
		{
			SelectActor->Transform.SetLocalScale(float4(Size, Size, Size));
		}

		if (ImGui::InputFloat3("Set Rotation", &Rot.X))
		{
			SelectActor->Transform.SetLocalRotation(Rot);
		}

		if (ImGui::InputFloat3("Set Pos", &Pos.X))
		{
			SelectActor->Transform.SetLocalPosition(Pos);
		}

		ImGui::TreePop();
	}
}

void AnimationInfoGUI::AnimationList()
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (ImGui::TreeNode("Animation List"))
	{
		if (true == AnimationNames.empty())
		{
			std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& Animations = SelectActor->GetFBXRenderer()->GetAnimationInfos();
			AnimationNames.reserve(Animations.size());
			CAnimationNames.reserve(Animations.size());

			int CurIndex = 0;
			for (std::pair<const std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& _Pair : Animations)
			{
				AnimationNames.push_back(_Pair.first);
				CAnimationNames.push_back(AnimationNames[CurIndex].c_str());
				CurIndex++;
			}
		}

		static int SelectAnimationIdex = 0;

		if (ImGui::ListBox("Aniamtion Name", &SelectAnimationIdex, &CAnimationNames[0], static_cast<int>(CAnimationNames.size())))
		{
			const char* SelectAnimationName = CAnimationNames.at(SelectAnimationIdex);
			SelectActor->GetFBXRenderer()->ChangeAnimation(SelectAnimationName);
			SelectAnimation = SelectActor->GetFBXRenderer()->GetCurAnimation();
		}

		ImGui::TreePop();
	}
}

void AnimationInfoGUI::EventEditor(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == SelectAnimation)
	{
		return;
	}

	if (nullptr == SelectAnimation->EventHelper)
	{
		std::string Path = SelectActor->GetEventPath();
		if (false == Path.empty())
		{
			std::string_view AniName = SelectAnimation->Aniamtion->GetName();
			int Frame = static_cast<int>(SelectAnimation->End);

			GameEnginePath EventPath = GameEnginePath(Path);
			EventPath.MoveChild(AniName);
			EventPath.ChangeExtension(FrameEventHelper::GetExtName());

			SelectAnimation->EventHelper = FrameEventHelper::CreateTempRes(EventPath.GetStringPath(), Frame).get();
		}
	}

	ImGui::Separator();

	for (const std::shared_ptr<EventTree>& Tree : EventTrees)
	{
		if (ImGui::TreeNode(Tree->GetName().c_str()))
		{
			Tree->OnGUI(_Level, _DeltaTime);
			ImGui::TreePop();
		}
	}
}

void SoundEventTree::Start()
{
	// Test SoundList
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("TestSoundFile");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".wav" });
		SoundFileList.reserve(Files.size());
		CSoundFileList.reserve(Files.size());
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& pFile = Files[i];
			GameEngineSound::SoundLoad(pFile.GetStringPath());
			SoundFileList.push_back(pFile.GetFileName());
			CSoundFileList.push_back(SoundFileList[i].c_str());
		}
	}
}
void SoundEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 모르고 사용할 수 없습니다.");
		return;
	}

	FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;

	ImGui::SliderInt("Start Frame", &SelectStartFrame, Parent->SelectAnimation->Start, Parent->SelectAnimation->End);
	ImGui::Combo("SoundList", &SelectSoundItem, &CSoundFileList[0], static_cast<int>(CSoundFileList.size()));
	if (ImGui::Button("CreateEvent"))
	{
		int Frame = SelectStartFrame;
		std::string ScrFileName = CSoundFileList[SelectSoundItem];
		EventHelper->CreateSoundEvent(Frame, ScrFileName);
	}

	ImGui::SameLine();

	if (ImGui::Button("Save Data"))
	{
		EventHelper->SaveFile();
	}

	ImGui::Separator();

	std::list<std::shared_ptr<SoundFrameEvent>>& SEvents = EventHelper->GetSoundEvents();
	if (SEvents.empty())
	{
		return;
	}


	std::shared_ptr<SoundFrameEvent> SelectEvent;
	for (const std::shared_ptr<SoundFrameEvent>& SEvent : SEvents)
	{
		int StartFrame = SEvent->GetFrame();
		std::string EventName = std::to_string(StartFrame) + SEvent->GetSoundName().data();
		if (ImGui::Button(EventName.c_str()))
		{
			SelectEvent = SEvent;
		}
	}
	if (nullptr != SelectEvent)
	{
		EventHelper->PopEvent(SelectEvent);
	}
}
