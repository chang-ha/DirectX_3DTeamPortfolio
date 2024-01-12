#include "PreCompile.h"
#include "MonsterGUI.h"

#include "CommonMonster.h"
#include "FrameEventHelper.h"
#include "TestLevel_Monster.h"
#include "Monster_LothricKn.h"


void SoundFrameEventTab::Init()
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

void SoundFrameEventTab::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 모르고 사용할 수 없습니다.");
		return;
	}

	FrameEventHelper* EventHelper = Parent->CurAnimationInfo->EventHelper;

	ImGui::SliderInt("Start Frame", &SelectStartFrame, Parent->CurAnimationInfo->Start, Parent->CurAnimationInfo->End);
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

// 나중에 Core GUI로 합칠 예정
void MonsterGUI::Start()
{
	CreateEventTab<SoundFrameEventTab>("Sound Event");
}

// _Level == TestLevel_Monster 
void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (bool MonsterCountTestCode = true)
	{
		ShowLothricKnCount(_Level);
	}

	if (nullptr == CurLevel)
	{
		CurLevel = static_cast<TestLevel_Monster*>(_Level);
	}

	if (true == CObjectNames.empty())
	{
		CopyObjectName();
	}

	ShowObjectNameList();

	if (nullptr != SelectActor)
	{
		if (true == SelectActor->IsDeath())
		{
			SelectActor = nullptr;
			AnimationNames.clear();
			return;
		}

		TransformEdit();

		if (true == AnimationNames.empty())
		{
			CopyAnimationName();
		}

		if (ImGui::ListBox("Aniamtion Name", &SelectAnimationIndex, &CAnimationNames[0], static_cast<int>(CAnimationNames.size())))
		{
			const char* SelectAnimationName = CAnimationNames.at(SelectAnimationIndex);
			SelectActor->GetFBXRenderer()->ChangeAnimation(SelectAnimationName);
			CurAnimationInfo = SelectActor->GetFBXRenderer()->GetCurAnimation();
		}

		if (nullptr != CurAnimationInfo)
		{
			if (nullptr == CurAnimationInfo->EventHelper)
			{
				std::string Path = SelectActor->GetEventPath();
				if (false == Path.empty())
				{
					std::string_view AniName = CurAnimationInfo->Aniamtion->GetName();
					int Frame = static_cast<int>(CurAnimationInfo->End);

					GameEnginePath EventPath = GameEnginePath(Path);
					EventPath.MoveChild(AniName);
					EventPath.ChangeExtension(FrameEventHelper::GetExtName());

					CurAnimationInfo->EventHelper = FrameEventHelper::CreateTempRes(EventPath.GetStringPath(), Frame).get();
				}
			}

			ImGui::Separator();

			for (const std::shared_ptr<EventTree>& EventTab : EventInfos)
			{
				if (ImGui::TreeNode(EventTab->GetName().c_str()))
				{
					EventTab->OnGUI(_Level, _DeltaTime);
					ImGui::TreePop();
				}
			}

			if (ImGui::TreeNode("Collision Node"))
			{
				const std::vector<float4x4>& BoneMats = SelectActor->GetFBXRenderer()->GetBoneMatrixs();
				static int CurBoneNum = 0;
				static float fFlowTime = 0.0f;
				fFlowTime += _DeltaTime;
				if (fFlowTime > 0.2f)
				{
					fFlowTime -= 0.2f;
					
					int BoneSize = static_cast<int>(BoneMats.size());
					

					++CurBoneNum;
					if (CurBoneNum >= BoneSize)
					{
						CurBoneNum = 0;
					}
				}

				float4x4 Mat = BoneMats.at(CurBoneNum);
				float4 Scale;
				float4 Quat;
				float4 Pos;
				Mat.Decompose(Scale, Quat, Pos);
				Pos *= 50.0f;

				std::shared_ptr<GameEngineCollision> RCol = SelectActor->GetRAttackCollision();
				RCol->Transform.SetLocalRotation(Quat);
				RCol->Transform.SetLocalPosition(Pos);

				ImGui::TreePop();
			}
		}

		RenderUnitSwitch();
	}

	ImGui::Separator();

	if (bool TestCode = false)
	{
		if (ImGui::TreeNode("Mesh Editor"))
		{
			if (ImGui::TreeNode("Animation Tree"))
			{
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		if (ImGui::BeginTabBar("Eidtor"))
		{
			if (ImGui::BeginTabItem("Setting"))
			{
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Help"))
			{
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
}

void MonsterGUI::TransformEdit()
{
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
}

void MonsterGUI::ShowLothricKnCount(GameEngineLevel* _Level)
{
	std::vector<std::shared_ptr<Monster_LothricKn>> Monsters = _Level->GetObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	if (true == Monsters.empty())
	{
		return;
	}

	int MonsterCount = static_cast<int>(Monsters.size());
	ImGui::Text(std::string("ObjectCount : " + std::to_string(MonsterCount)).c_str());
}

void MonsterGUI::ShowObjectNameList()
{
	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<CommonMonster>>& MonsterGroup = CurLevel->GetObjectGroupConvert<CommonMonster>(Enum_UpdateOrder::Monster);
		for (const std::shared_ptr<CommonMonster>& Monster : MonsterGroup)
		{
			if (CObjectNames[SelectActorIndex] == Monster->GetName())
			{
				SelectActor = Monster.get();
				AnimationNames.clear();
				CAnimationNames.clear();
				CurAnimationInfo = nullptr;
			}
		}
	}
}

void MonsterGUI::RenderUnitSwitch()
{
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& RenderUnits = SelectActor->GetFBXRenderer()->GetRenderUnits();
	const int IndexCount = static_cast<int>(RenderUnits.size());
	for (int i = 0; i < IndexCount; i++)
	{
		if (ImGui::Button(std::to_string(i).c_str()))
		{
			RenderUnits[i][0]->OnOffSwitch();
		}
	}
}

void MonsterGUI::CopyObjectName()
{
	const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = CurLevel->GetObjectGroupInt(static_cast<int>(Enum_UpdateOrder::Monster));

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


void MonsterGUI::CopyAnimationName()
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

void MonsterGUI::Release()
{
	CurAnimationInfo = nullptr;
	SelectActor = nullptr;
	ActorNames.clear();
	CObjectNames.clear();
	AnimationNames.clear();
	CAnimationNames.clear();
}
