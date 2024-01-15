#include "PreCompile.h"
#include "AnimationInfoGUI.h"

#include "BaseMonster.h"
#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"
#include "CollisionUpdateFrameEvent.h"

AnimationInfoGUI::AnimationInfoGUI() 
{
}

AnimationInfoGUI::~AnimationInfoGUI() 
{
}


void AnimationInfoGUI::Start()
{
	CreateEventTree<TotalEventTree>("Total Events");
	CreateEventTree<SoundEventTree>("Sound");
	CreateEventTree<CollisionEventTree>("Collision Switch");
}

void AnimationInfoGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowActorList(_Level);
	TransformEditor();
	AnimationList();
	BoneEditor();
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
	BoneNames.clear();
	CBoneNames.clear();
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

		const std::vector<std::shared_ptr<BaseMonster>>& MonsterGroup = _Level->GetObjectGroupConvert<BaseMonster>(Enum_UpdateOrder::Monster);
		for (const std::shared_ptr<BaseMonster>& Monster : MonsterGroup)
		{
			if (CObjectNames[SelectActorIndex] == Monster->GetName())
			{
				SelectActor = Monster.get();
				ActorChange();
			}
		}
	}
}

void AnimationInfoGUI::ActorChange()
{
	for (std::shared_ptr<EventTree>& Tree : EventTrees)
	{
		Tree->ChangeActor();
	}

	AnimationNames.clear();
	CAnimationNames.clear();
	BoneNames.clear();
	CBoneNames.clear();
	SelectAnimation = nullptr;
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

void AnimationInfoGUI::BoneEditor()
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (BoneNames.empty())
	{
		const std::shared_ptr<GameEngineFBXMesh>& Mesh = SelectActor->GetFBXRenderer()->GetFBXMesh();
		int BoneCnt = static_cast<int>(Mesh->GetBoneCount());

		BoneNames.resize(BoneCnt);
		CBoneNames.resize(BoneCnt);

		for (int i = 0; i < BoneCnt; i++)
		{
			BoneNames[i] = std::to_string(i) + "." + Mesh->FindBoneToIndex(i)->Name;
			CBoneNames[i] = BoneNames[i].c_str();
		}
	}

	if (ImGui::TreeNode("Bone Editor"))
	{
		static int SelectBone = 0;

		ImGui::Combo("Bone", &SelectBone, &CBoneNames[0], static_cast<int>(CBoneNames.size()));

		if (GameEngineLevel::IsDebug)
		{
			std::vector<float4x4>& BoneMats = SelectActor->GetFBXRenderer()->GetBoneSockets();
			float4x4 WorldMat = SelectActor->Transform.GetConstTransformDataRef().WorldMatrix;
			float4x4& BoneMatrix = BoneMats[SelectBone];
			WorldMat = BoneMatrix * WorldMat;
			float4 wBoneScale;
			float4 wBoneQuat;
			float4 wBonePos;
			WorldMat.Decompose(wBoneScale, wBoneQuat, wBonePos);
			GameEngineDebug::DrawSphere2D(wBoneScale, wBoneQuat, wBonePos, float4::RED);
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
		std::string Path = SelectActor->GetEventPath(SelectActor->GetID());
		if (Path.empty())
		{
			return;
		}

		std::string_view AniName = SelectAnimation->Aniamtion->GetName();
		int Frame = static_cast<int>(SelectAnimation->End + 1);

		GameEnginePath EventPath = GameEnginePath(Path);
		EventPath.MoveChild(AniName);
		EventPath.ChangeExtension(FrameEventHelper::GetExtName());

		SelectAnimation->EventHelper = FrameEventHelper::CreateTempRes(EventPath.GetStringPath(), Frame).get();
	}

	ImGui::Separator();

	if (ImGui::TreeNode("Frame Event Editor"))
	{
		for (const std::shared_ptr<EventTree>& Tree : EventTrees)
		{
			if (ImGui::TreeNode(Tree->GetName().c_str()))
			{
				Tree->OnGUI(_Level, _DeltaTime);
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

void TotalEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;
	std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& AllEvents = EventHelper->GetAllEvents();
	if (AllEvents.empty())
	{
		return;
	}

	if (ImGui::Button("Save Data"))
	{
		EventHelper->SaveFile();
	}

	ImGui::Text("Erase Event");

	std::shared_ptr<FrameEventObject> SelectObject;

	int Cnt = 0;
	for (std::pair<const int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : AllEvents)
	{
		std::list<std::shared_ptr<FrameEventObject>>& EventGroup = Pair.second;
		for (const std::shared_ptr<FrameEventObject>& Object : EventGroup)
		{
			++Cnt;
			std::string EventName = std::to_string(Cnt) + ". Frame: " + std::to_string(Object->GetFrame());
			if (ImGui::Button(EventName.c_str()))
			{
				SelectObject = Object;
			}
		}
	}

	if (nullptr != SelectObject)
	{
		EventHelper->PopEvent(SelectObject);
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
		std::string ScrFileName = CSoundFileList[SelectSoundItem];
		std::shared_ptr<SoundFrameEvent> SEvent = SoundFrameEvent::CreateEventObject(SelectStartFrame, ScrFileName);
		EventHelper->SetEvent(SEvent);
	}
}


void CollisionEventTree::Start()
{
}

void CollisionEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (CColNames.empty())
	{
		std::map<int, std::shared_ptr<BoneSocketCollision>>& Collisions = Parent->SelectActor->GetCollisions();
		size_t Size = Collisions.size();
		ColNames.reserve(Size);
		CColNames.reserve(Size);

		int Cnt = 0;

		for (std::pair<const int, std::shared_ptr<BoneSocketCollision>>& Pair : Collisions)
		{
			ColNames.push_back(Pair.second->GetName());
			CColNames.push_back(ColNames[Cnt].c_str());
			++Cnt;
		}
	}

	static std::vector<int> Frames;
	Frames.resize(2);
	static int SelectCol = 0;

	int StartFrame = static_cast<int>(Parent->SelectAnimation->Start);
	int EndFrame = static_cast<int>(Parent->SelectAnimation->End);

	ImGui::SliderInt2("Start To End Frame", &Frames[0], StartFrame, EndFrame);
	ImGui::Combo("Collision List", &SelectCol, &CColNames[0], static_cast<int>(CColNames.size()));

	if (ImGui::Button("Create Event"))
	{
		std::map<int, std::shared_ptr<BoneSocketCollision>>& Collisions = Parent->SelectActor->GetCollisions();
		for (std::pair<const int, std::shared_ptr<BoneSocketCollision>>& Pair : Collisions)
		{
			if (CColNames[SelectCol] == Pair.second->GetName())
			{
				FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;
				std::shared_ptr<CollisionUpdateFrameEvent> CEvent = CollisionUpdateFrameEvent::CreateEventObject(Frames[0], Frames[1], Pair.second);
				EventHelper->SetEvent(CEvent);
			}
		}
	}
}

void CollisionEventTree::ChangeActor()
{
	CColNames.clear();
	CColNames.clear();
}