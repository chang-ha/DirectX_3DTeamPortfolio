#include "PreCompile.h"
#include "AnimationInfoGUI.h"

#include "BaseMonster.h"
#include "BaseActor.h"

#include "FrameEventHelper.h"
#include "BoneSoundFrameEvent.h"
#include "DummyPolySoundFrameEvent.h"
#include "CenterBodySoundFrameEvent.h"
#include "BoneSocketCollision.h"
#include "CollisionUpdateFrameEvent.h"
#include "TurnSpeedFrameEvent.h"

#include "DS3DummyData.h"



void DummyPolyStruct::Init(BaseActor* _pActor, int _Flag)
{
	if (nullptr == _pActor)
	{
		MsgBoxAssert("존재하지 않는 액터를 참조하려 했습니다.");
		return;
	}

	int MaxInt = (static_cast<int>(eDPFlag::Max) - 1) * 2;
	if (_Flag >= MaxInt)
	{
		MsgBoxAssert("Flag의 최대값을 넘겼습니다.");
		return;
	}

	Flag = _Flag;
	IDName = _pActor->GetIDName();
}

bool DummyPolyStruct::IsFlag(eDPFlag _BitFlag)
{
	return IsFlag(static_cast<int>(_BitFlag));
}

bool DummyPolyStruct::IsFlag(int _BitFlag)
{
	return BitMethod::IsOnFlag(Flag, _BitFlag);
}

void DummyPolyStruct::OutUsingImguiScope()
{
	if (IsFlag(eDPFlag::Tree))
	{
		ImGui::TreePop();
	}
}

void DummyPolyStruct::AutoLoadDummyPolyRefID()
{
	if (DummyPolyRefIndexCheck.empty())
	{
		if (IDName.empty())
		{
			MsgBoxAssert("액터의 ID Name이 잘못되어있습니다.");
			OutUsingImguiScope();
			return;
		}

		const std::shared_ptr<DS3DummyData>& pDPData = DS3DummyData::Find(IDName);
		if (nullptr == pDPData)
		{
			MsgBoxAssert("존재하지않는 자료입니다. 더미데이터를 Mesh폴더에 로드해주세요.");
			OutUsingImguiScope();
			return;
		}

		std::vector<DummyData> DPDatas = pDPData->GetDummyDatas();

		for (const DummyData& Data : DPDatas)
		{
			DummyPolyRefIndexCheck.insert(Data.ReferenceID);
		}

		int Cnt = 0;

		DummyPolyRefIndexs.reserve(DummyPolyRefIndexCheck.size());
		CDummyPolyRefIndexs.reserve(DummyPolyRefIndexCheck.size());
		for (int Index : DummyPolyRefIndexCheck)
		{
			DummyPolyRefIndexs.push_back(std::to_string(Index));
			CDummyPolyRefIndexs.push_back(DummyPolyRefIndexs[Cnt].c_str());
			Cnt++;
		}
	}
}

void DummyPolyStruct::AutoLoadDummyPolyAttachBoneIndex()
{
	if (false == CDummyPolyRefIndexs.empty())
	{
		if (ImGui::Combo("Ref ID", &Dummy_RefIndex, &CDummyPolyRefIndexs[0], static_cast<int>(CDummyPolyRefIndexs.size())))
		{
			DpLoaderRefReset();

			int RefIndex = std::stoi(DummyPolyRefIndexs[Dummy_RefIndex]);

			const std::shared_ptr<DS3DummyData>& pDPData = DS3DummyData::Find(IDName);
			if (nullptr == pDPData)
			{
				MsgBoxAssert("존재하지않는 자료입니다. 터지면 김태훈에게 문의하세요.");
				OutUsingImguiScope();
				return;
			}

			DummyPolyDatas = pDPData->GetRefAllData(RefIndex);

			int Cnt = 0;

			DummyPolyAttachIndexs.clear();
			CDummyPolyAttachIndexs.clear();
			DummyPolyAttachIndexs.reserve(DummyPolyDatas.size());
			CDummyPolyAttachIndexs.reserve(DummyPolyDatas.size());

			for (const std::pair<int, DummyData>& Pair : DummyPolyDatas)
			{
				DummyPolyAttachIndexs.push_back(std::to_string(Pair.first));
				CDummyPolyAttachIndexs.push_back(DummyPolyAttachIndexs[Cnt].c_str());
				Cnt++;
			}
		}
	}
}

void DummyPolyStruct::ComboDummyPolyAttachBoneIndex()
{
	if (false == CDummyPolyAttachIndexs.empty())
	{
		if (ImGui::Combo("Attach Bone Index", &Dummy_ParentIndex, &CDummyPolyAttachIndexs[0], static_cast<int>(CDummyPolyAttachIndexs.size())))
		{
			DpLoaderAttachReset();

			const std::shared_ptr<DS3DummyData>& pDPData = DS3DummyData::Find(IDName);
			if (nullptr == pDPData)
			{
				MsgBoxAssert("존재하지않는 자료입니다. 터지면 김태훈에게 문의하세요.");
				OutUsingImguiScope();
				return;
			}

			int RefIndex = std::stoi(DummyPolyRefIndexs[Dummy_RefIndex]);
			int ParentIndex = std::stoi(DummyPolyAttachIndexs[Dummy_ParentIndex]);

			SelectDPData = pDPData->GetDummyData(RefIndex, ParentIndex);
		}
	}
}

void DummyPolyStruct::DpLoaderAllReset()
{
	DpLoaderRefReset();

	IDName.clear();
	DummyPolyRefIndexs.clear();
	CDummyPolyRefIndexs.clear();
	DummyPolyRefIndexCheck.clear();
	Dummy_RefIndex = -1;
}

void DummyPolyStruct::DpLoaderRefReset()
{
	DpLoaderAttachReset();

	Dummy_ParentIndex = -1;
	DummyPolyAttachIndexs.clear();
	CDummyPolyAttachIndexs.clear();

	DummyPolyDatas.clear();
}

void DummyPolyStruct::DpLoaderAttachReset()
{
	SelectDPData = nullptr;
}


AnimationInfoGUI::AnimationInfoGUI() 
{
}

AnimationInfoGUI::~AnimationInfoGUI() 
{
}


void AnimationInfoGUI::Start()
{
	CreateEventTree<TotalEventTree>("Total Events");
	CreateEventTree<BoneSoundEventTree>("Bone Sound");
	CreateEventTree<DPSoundEventTree>("Dummy Poly Sound");
	CreateEventTree<CollisionEventTree>("Collision Switch");
	CreateEventTree<TurnSpeedEventTree>("Turn Speed");
}

void AnimationInfoGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowActorList(_Level);
	TransformEditor();
	AnimationList( _Level, _DeltaTime);
	BoneEditor();
	DummyEditor();
}

void AnimationInfoGUI::LevelEnd()
{
	SelectActor = nullptr;
	ActorNames.clear();
	CObjectNames.clear();
	ActorChange();
	DummyEditorReset();
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
	DummyEditorReset();
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
			const std::shared_ptr<GameContentsFBXRenderer>& pRenderer = SelectActor->GetFBXRenderer();
			if (nullptr == pRenderer)
			{
				MsgBoxAssert("렌더러가 존재하지 않습니다.");
				return;
			}
			const float4 RendererRot = pRenderer->Transform.GetWorldRotationEuler(); 

			float4 MeshGlobalRot = pRenderer->GetFBXMesh()->FindBoneToIndex(SelectBone)->BonePos.GlobalRotation;
			float4 MeshGlobalPos = pRenderer->GetFBXMesh()->FindBoneToIndex(SelectBone)->BonePos.GlobalTranslation;

			const std::vector<AnimationBoneData>& BoneDatas = pRenderer->GetBoneDatas();
			const AnimationBoneData& BData = BoneDatas.at(SelectBone);
			std::vector<float4x4>& BoneMats = pRenderer->GetBoneSockets();
			float4x4 WorldMat = pRenderer->Transform.GetConstTransformDataRef().WorldMatrix;
			float4x4& BoneMatrix = BoneMats[SelectBone];

			ImGui::SliderFloat3("Model Scale", &BoneS.X, 1.0f, 100.0f, "%.f");
			ImGui::SliderFloat3("Model Rot", &BoneRot.X, 0.0f, 360.0f, "%.f");
			ImGui::SliderFloat3("Model Pos", &BonePos.X, 0.0f, 1.f, "%.3f");

			float4x4 BoneWMatrix = BoneMatrix* WorldMat;
			float4 BS;
			float4 BQ;
			float4 BT;
			BoneWMatrix.Decompose(BS, BQ, BT);
			float4 BEuler = BQ.QuaternionToEulerDeg();

			const float4 BoneWPos = BonePos * BoneMatrix * WorldMat;

			static float GUIBoneRot = 0.0f;
			ImGui::SliderFloat("Bone Rot", &GUIBoneRot, 0.0f, 360.0f, "%.f");

			float4 Quat  = BData.RotQuaternion;
			float4x4 BMat = Quat.QuaternionToMatrix();
			float4x4 affine = float4x4::Affine(float4::ONE, Quat, float4::ZERO);
			const float4 Euler = Quat.QuaternionToEulerDeg();

			const float4 Rot4 = Euler + RendererRot;
			float4x4 LocalMat = affine* WorldMat;
			GameEngineDebug::DrawBox3D(BoneS, BEuler, BT, float4(0.25f, 0.75f, 0.75f));
		}

		ImGui::TreePop();
	}
}

void AnimationInfoGUI::DummyEditor()
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (ImGui::TreeNode("DummyPoly Editor"))
	{
		if (!GameEngineLevel::IsDebug)
		{
			ImGui::TreePop();
			return;
		}

		int Flag = DummyPolyStruct::eDPFlag::Tree;
		DpLoader.Init(SelectActor, Flag);

		DpLoader.AutoLoadDummyPolyRefID();
		DpLoader.AutoLoadDummyPolyAttachBoneIndex();
		DpLoader.ComboDummyPolyAttachBoneIndex();

		const DummyData* pDPData = DpLoader.GetDummyDataPointer();
		if (nullptr == pDPData)
		{
			ImGui::TreePop();
			return;
		}

		if (nullptr != pDPData)
		{
			const std::shared_ptr<GameContentsFBXRenderer>& pRenderer = SelectActor->GetFBXRenderer();
			if (nullptr == pRenderer)
			{
				MsgBoxAssert("렌더러가 존재하지 않습니다.");
				ImGui::TreePop();
				return;
			}

			int AttachIndex = pDPData->AttachBoneIndex;

			std::vector<float4x4>& BoneMats = pRenderer->GetBoneSockets();
			float4x4 WorldMatrix = pRenderer->Transform.GetConstTransformDataRef().WorldMatrix;
			float4x4 BoneMatrix = BoneMats.at(AttachIndex);

			const float4 BoneWPos = float4::ZERO * BoneMatrix * WorldMatrix;

			float4x4 FinDpMat;

			static bool ReverseCheck = false;
			ImGui::Checkbox("DummyPoly Pos Reverse",&ReverseCheck);
			if (ReverseCheck)
			{
				FinDpMat = pDPData->Local_ReversePos;
			}
			else
			{
				FinDpMat = pDPData->Local;
			}

			float4x4 FinMat = FinDpMat * BoneMatrix* WorldMatrix;
			float4 WS;
			float4 WQ;
			float4 WT;
			FinMat.Decompose(WS, WQ, WT);
			float4 WDeg = WQ.QuaternionToEulerDeg();

			ImGui::SliderFloat3("Dummy Poly Scale", &DummyS.X, 1.0f, 300.0f, "%.f");

			ContentsDebug::DistanceCheck(BoneWPos, 5.0f, float4(1.f, 0.f, 0.25f));
			GameEngineDebug::DrawBox3D(DummyS, WDeg, WT, float4(0.25f, 1.f, 0.75f));
			GameEngineDebug::DrawBox3D(float4::ONE, WDeg, WT, float4(0.25f, 1.f, 0.75f));
		}

		ImGui::TreePop();
	}
}

void AnimationInfoGUI::DummyEditorReset()
{
	DpLoader.DpLoaderAllReset();
}

void AnimationInfoGUI::BoneCollisionEditor()
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (ImGui::TreeNode("Socket Col Editor"))
	{
		if (!GameEngineLevel::IsDebug)
		{
			ImGui::TreePop();
			return;
		}

		const std::shared_ptr<GameContentsFBXRenderer>& pRenderer = SelectActor->GetFBXRenderer();
		if (nullptr == pRenderer)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다.");
			ImGui::TreePop();
			return;
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

BaseActor* EventTree::GetSelectActor() const
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 지정해주지 않았습니다.");
		return nullptr;
	}

	BaseActor* pActor = Parent->SelectActor;
	return pActor;
}

GameContentsFBXAnimationInfo* EventTree::GetSelectAnimation() const
{
	if (nullptr == Parent)
	{
		MsgBoxAssert("부모를 지정해주지 않았습니다.");
		return nullptr;
	}

	class GameContentsFBXAnimationInfo* pAnimation = Parent->SelectAnimation.get();
	return pAnimation;
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

void SoundEventTree::ChangeActor()
{
	LoadSoundList();
}

void SoundEventTree::LoadSoundList()
{
	BaseActor* pActor = Parent->SelectActor;
	if (nullptr == pActor)
	{
		return;
	}

	if (false == SoundFileList.empty() || false == CSoundFileList.empty())
	{
		SoundFileList.clear();
		CSoundFileList.clear();
	}

	std::string IDName = pActor->GetIDName();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources");
	Dir.MoveChild("Sound");
	Dir.AppendPath(IDName);
	if (false == Dir.IsExits())
	{
		return;
	}

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
	ImGui::SliderInt("Start Frame", &SelectStartFrame, Parent->SelectAnimation->Start, Parent->SelectAnimation->End);

	ImGui::Combo("BoneList", &BoneIndex, &CBoneNames[0], static_cast<int>(CBoneNames.size()));
	ImGui::Combo("SoundList", &SoundIndex, &CSoundFileList[0], static_cast<int>(CSoundFileList.size()));

	if (ImGui::Button("CreateEvent"))
	{
		std::string ScrFileName = CSoundFileList[SoundIndex];
		std::shared_ptr<BoneSoundFrameEvent> BSEvent = BoneSoundFrameEvent::CreateEventObject(SelectStartFrame, BoneIndex, ScrFileName);
		EventHelper->SetEvent(BSEvent);
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

void DPSoundEventTree::OnGUI(GameEngineLevel* _Level, float _Delta)
{
	BaseActor* pActor = EventTree::GetSelectActor();
	if (nullptr == pActor)
	{
		MsgBoxAssert("존재하지 않는 값을 반환하려 했습니다");
		return;
	}

	int Flag = DummyPolyStruct::eDPFlag::Tree;
	DpLoader.Init(pActor, Flag);

	DpLoader.AutoLoadDummyPolyRefID();
	DpLoader.AutoLoadDummyPolyAttachBoneIndex();
	DpLoader.ComboDummyPolyAttachBoneIndex();

	const DummyData* pDPData = DpLoader.GetDummyDataPointer();
	if (nullptr != pDPData)
	{
		if (CSoundFileList.empty())
		{
			return;
		}

		GameContentsFBXAnimationInfo* pAnimation = EventTree::GetSelectAnimation();
		if (nullptr == pAnimation)
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 이벤트를 세팅하려 했습니다");
			return;
		}
		FrameEventHelper* EventHelper = pAnimation->EventHelper;

		// 몇번째 프레임에
		ImGui::SliderInt("Start Frame", &SelectStartFrame, pAnimation->Start, pAnimation->End);

		ImGui::Combo("SoundList", &SoundIndex, &CSoundFileList[0], static_cast<int>(CSoundFileList.size()));

		if (ImGui::Button("CreateEvent"))
		{
			int RefID = pDPData->ReferenceID;
			int AttachBoneIndex = pDPData->AttachBoneIndex;
			std::string SoundFileName = CSoundFileList[SoundIndex];
			std::shared_ptr<DummyPolySoundFrameEvent> DPSEvent = DummyPolySoundFrameEvent::CreateEventObject(SelectStartFrame, SoundFileName, RefID, AttachBoneIndex);
			EventHelper->SetEvent(DPSEvent);
		}
	}
}

void DPSoundEventTree::ChangeActor()
{
	DpLoader.DpLoaderAllReset();
	LoadSoundList();
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