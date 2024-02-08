#include "PreCompile.h"
#include "AnimationInfoGUI.h"

#include "BaseMonster.h"
#include "FrameEventHelper.h"
#include "BoneSocketCollision.h"

#include "SoundFrameEvent.h"
#include "BoneSoundFrameEvent.h"
#include "CollisionUpdateFrameEvent.h"
#include "TurnSpeedFrameEvent.h"

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
	CreateEventTree<BoneSoundEventTree>("BSound");
	CreateEventTree<CollisionEventTree>("Collision Switch");
	CreateEventTree<TurnSpeedEventTree>("Turn Speed");
}

void AnimationInfoGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowActorList(_Level);
	TransformEditor();
	AnimationList( _Level, _DeltaTime);
	BoneEditor();
}

void AnimationInfoGUI::LevelEnd()
{
	SelectActor = nullptr;
	ActorNames.clear();
	CObjectNames.clear();
	ActorChange();
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
			std::string ObjectName = Object->GetName();
			if (ObjectName.empty())
			{
				continue;
			}

			ActorNames.push_back(ObjectName);
			CObjectNames.push_back(ActorNames[Cnt].c_str());
			Cnt++;
		}
	}

	static int SelectActorIndex = 0;

	if (CObjectNames.empty())
	{
		return;
	}

	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<BaseActor>>& ObjectGroup = _Level->GetObjectGroupConvert<BaseActor>(Enum_UpdateOrder::Monster);
		for (const std::shared_ptr<BaseActor>& Object : ObjectGroup)
		{
			if (CObjectNames[SelectActorIndex] == Object->GetName())
			{
				SelectActor = Object.get();
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

void AnimationInfoGUI::AnimationList(class GameEngineLevel* _Level, float _DeltaTime)
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

		if (ImGui::ListBox("Aniamtion Name", &AnimationIndex, &CAnimationNames[0], static_cast<int>(CAnimationNames.size())))
		{
			const char* SelectAnimationName = CAnimationNames.at(AnimationIndex);
			SelectActor->GetFBXRenderer()->ChangeAnimation(SelectAnimationName);
			SelectAnimation = SelectActor->GetFBXRenderer()->GetCurAnimation();
			AnimationChange();
		}

		EventEditor(_Level, _DeltaTime);

		ImGui::TreePop();
	}
}

void AnimationInfoGUI::AnimationChange()
{
	for (std::shared_ptr<EventTree>& Tree : EventTrees)
	{
		Tree->ChangeAnimation();
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

		GameEnginePath EventPath = GameEnginePath(Path);
		EventPath.MoveChild(AniName);
		EventPath.ChangeExtension(FrameEventHelper::GetExtName());

		SelectAnimation->EventHelper = FrameEventHelper::CreateTempRes(EventPath.GetStringPath(), SelectAnimation.get()).get();
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
			std::string EventName = std::string("Frame:") + std::to_string(Object->GetFrame()) + " / " + Object->GetTypeString();
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

void BoneSoundEventTree::Start()
{

}

void BoneSoundEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 모르고 사용할 수 없습니다.");
		return;
	}

	if (BoneNames.empty())
	{
		const std::shared_ptr<GameEngineFBXMesh>& Mesh = Parent->SelectActor->GetFBXRenderer()->GetFBXMesh();
		int BoneCnt = static_cast<int>(Mesh->GetBoneCount());

		BoneNames.resize(BoneCnt);
		CBoneNames.resize(BoneCnt);

		for (int i = 0; i < BoneCnt; i++)
		{
			BoneNames[i] = std::to_string(i) + "." + Mesh->FindBoneToIndex(i)->Name;
			CBoneNames[i] = BoneNames[i].c_str();
		}
	}

	if (CSoundFileList.empty())
	{
		return;
	}

	FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;

	// 몇번째 프레임에
	ImGui::InputInt("Start Frame", &SelectStartFrame, Parent->SelectAnimation->Start, Parent->SelectAnimation->End);

	ImGui::Combo("BoneList", &BoneIndex, &CBoneNames[0], static_cast<int>(CBoneNames.size()));
	ImGui::Combo("SoundList", &SoundIndex, &CSoundFileList[0], static_cast<int>(CSoundFileList.size()));

	if (ImGui::Button("CreateEvent"))
	{
		std::string ScrFileName = CSoundFileList[SoundIndex];
		std::shared_ptr<BoneSoundFrameEvent> BSEvent = BoneSoundFrameEvent::CreateEventObject(SelectStartFrame, BoneIndex, ScrFileName);
		EventHelper->SetEvent(BSEvent);
	}
}

void BoneSoundEventTree::LoadSoundList()
{
	std::string IDName = Parent->SelectActor->GetIDName();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources");
	Dir.MoveChild("Sound");

	if (false == GameEngineDirectory::IsExist(Dir.GetStringPath() + "\\" + IDName))
	{
		return;
	}

	Dir.MoveChild(IDName);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".wav" });

	if (Files.empty())
	{
		return;
	}

	int FileSize = static_cast<int>(Files.size());

	SoundFileList.reserve(FileSize);
	CSoundFileList.reserve(FileSize);

	for (int i = 0; i < FileSize; i++)
	{
		GameEngineFile& pFile = Files[i];
		SoundFileList.push_back(pFile.GetFileName());
		CSoundFileList.push_back(SoundFileList[i].c_str());
	}
}

void BoneSoundEventTree::ChangeActor()
{
	BoneNames.clear();
	CBoneNames.clear();
	SoundFileList.clear();
	CSoundFileList.clear();
	BoneIndex = 0;
	SoundIndex = 0;
}

void BoneSoundEventTree::ChangeAnimation()
{
	SoundFileList.clear();
	CSoundFileList.clear();

	LoadSoundList();

	SoundIndex = 0;
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

	static std::vector<int> SelectFrames;
	if (SelectFrames.empty())
	{
		SelectFrames.resize(2);
	}

	static int SelectCol = 0;

	int StartFrame = static_cast<int>(Parent->SelectAnimation->Start);
	int EndFrame = static_cast<int>(Parent->SelectAnimation->End);

	ImGui::SliderInt2("Start To End Frame", &SelectFrames[0], StartFrame, EndFrame);
	ImGui::Combo("Collision List", &SelectCol, &CColNames[0], static_cast<int>(CColNames.size()));

	if (ImGui::Button("Create Event"))
	{
		bool IsCreatable = (SelectFrames[0] < SelectFrames[1]);
		if (IsCreatable)
		{
			std::map<int, std::shared_ptr<BoneSocketCollision>>& Collisions = Parent->SelectActor->GetCollisions();
			for (std::pair<const int, std::shared_ptr<BoneSocketCollision>>& Pair : Collisions)
			{
				if (CColNames[SelectCol] == Pair.second->GetName())
				{
					FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;
					std::shared_ptr<CollisionUpdateFrameEvent> CEvent = CollisionUpdateFrameEvent::CreateEventObject(SelectFrames[0], SelectFrames[1], Pair.second);
					EventHelper->SetEvent(CEvent);
				}
			}
		}
		else
		{
			OutputDebugStringA("시작 프레임이 끝 프레임보다 크거나 같으면 이벤트를 생성할 수 없습니다. \n");
		}
	}
}

void CollisionEventTree::ChangeActor()
{
	ColNames.clear();
	CColNames.clear();
}

void TurnSpeedEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	static std::vector<int> SelectFrames;
	if (SelectFrames.empty())
	{
		SelectFrames.resize(2);
	}

	int StartFrame = static_cast<int>(Parent->SelectAnimation->Start);
	int EndFrame = static_cast<int>(Parent->SelectAnimation->End);

	ImGui::SliderInt2("Start To End Frame", &SelectFrames[0], StartFrame, EndFrame);
	ImGui::InputInt("Turn Speed", &TurnSpeedValue);

	if (ImGui::Button("Create Event"))
	{
		bool IsFrameOk = (SelectFrames[0] < SelectFrames[1]);
		if (IsFrameOk)
		{
			FrameEventHelper* EventHelper = Parent->SelectAnimation->EventHelper;
			std::shared_ptr<TurnSpeedFrameEvent> Event = TurnSpeedFrameEvent::CreateEventObject(SelectFrames[0], SelectFrames[1], static_cast<float>(TurnSpeedValue));
			EventHelper->SetEvent(Event);
		}
		else
		{
			OutputDebugStringA("시작 프레임이 끝 프레임보다 크거나 같으면 이벤트를 생성할 수 없습니다. \n");
		}
	}
}