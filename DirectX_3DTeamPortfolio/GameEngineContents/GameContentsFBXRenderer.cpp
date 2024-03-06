#include "PreCompile.h"
#include "GameContentsFBXRenderer.h"
#include "FrameEventHelper.h"

void GameContentsFBXAnimationInfo::RootMotionOff()
{
	mRootMotionData.RootMotion = false;
	ParentRenderer->RootMotionComponent->ResetMove(Enum_Axies::All);
}

void GameContentsFBXAnimationInfo::SwitchRootMotion()
{
	mRootMotionData.RootMotion = !mRootMotionData.RootMotion;
	ParentRenderer->RootMotionComponent->ResetMove(Enum_Axies::All);
}

void GameContentsFBXAnimationInfo::EventCall(UINT _Frame)
{
	if (true == FrameEventFunction.contains(Frames[_Frame]))
	{
		std::multimap<int, std::function<void(GameContentsFBXRenderer*)>>::iterator StartIter = FrameEventFunction.lower_bound(_Frame);
		std::multimap<int, std::function<void(GameContentsFBXRenderer*)>>::iterator EndIter = FrameEventFunction.upper_bound(_Frame);
		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second(ParentRenderer);
		}
	}
}

std::string_view GameContentsFBXAnimationInfo::GetAnimationName() const
{
	if (nullptr == Aniamtion)
	{
		MsgBoxAssert("�ִϸ��̼��� �ε����� �ʰ� ����� �� ���� ����Դϴ�.");
		return nullptr;
	}

	return Aniamtion->GetName();
}

void GameContentsFBXAnimationInfo::Reset()
{
	CurFrameTime = 0.0f;
	CurFrame = 0;
	PlayTime = 0.0f;
	IsStart = false;
	IsEnd = false;
	bOnceStart = false;

	if (nullptr != FrameEventInfo)
	{
		FrameEventInfo->EventReset();
	}
}

void GameContentsFBXAnimationInfo::Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index)
{
	_Animation->AnimationMatrixLoad(_Mesh, _Name, _Index);
	Aniamtion = _Animation;
	FBXAnimationData = Aniamtion->GetAnimationData(_Index);
	Start = static_cast<UINT>(FBXAnimationData->TimeStartCount);
	End = static_cast<UINT>(FBXAnimationData->TimeEndCount);
	Mesh = _Mesh;
	Aniamtion = _Animation;

	Start = 0;

	float TotalTime = static_cast<float>(End) * Inter;
	if (BlendIn > TotalTime)
	{
		BlendIn = TotalTime;
	}

	std::string EventName = FrameEventHelper::GetConvertFileName(_Animation->GetName());
	std::shared_ptr<FrameEventHelper> pEventHelper = FrameEventHelper::Find(EventName);
	if (nullptr == pEventHelper)
	{
		pEventHelper = FrameEventHelper::Load(this);
		if (nullptr == pEventHelper)
		{
			return;
		}
	}

	FrameEventInfo = pEventHelper->Initialze(this);
}

void GameContentsFBXAnimationInfo::Update(float _DeltaTime)
{
	ParentRenderer->bFrameChange = false;

	bool PauseCheck = ParentRenderer->Pause;
	bool NotLoopEndCheck = IsEnd && !Loop;
	if (PauseCheck || NotLoopEndCheck)
	{
		return;
	}

	IsEnd = false;

	if (false == IsStart)
	{
		if (nullptr != FrameEventInfo)
		{
			FrameEventInfo->PlayEvents(CurFrame);
		}

		IsStart = true;
	}

	if (true == EventCheck && false == IsEnd)
	{
		EventCall(CurFrame);
		EventCheck = false;
	}

	// 0.1��¥�� 
	CurFrameTime += _DeltaTime;
	PlayTime += _DeltaTime;
	RootMotionUpdate(_DeltaTime);

	while (CurFrameTime >= Inter)
	{
		ParentRenderer->bFrameChange = true;

		//   2.0         0.1
		CurFrameTime -= Inter;
		++CurFrame;

		EventCheck = true;

		if (false == bOnceStart && CurFrame == 0)
		{
			bOnceStart = true;
			bOnceEnd = false;
		}

		bool DoneCheck = false;

		if (CurFrame > End)
		{
			if (nullptr != EndEvent && false == IsEnd)
			{
				EndEvent(ParentRenderer);
			}

			IsEnd = true;

			if (true == Loop)
			{
				CurFrame = Start;
			}
			else
			{
				--CurFrame;
				if (nullptr != ParentRenderer->RootMotionComponent)
				{
					ParentRenderer->RootMotionComponent->ResetMove(Enum_Axies::X | Enum_Axies::Z);
				}
			}
		}

		if (nullptr != FrameEventInfo)
		{
			FrameEventInfo->PlayEvents(CurFrame);
		}

		if (nullptr != FrameChangeFunction)
		{
			FrameChangeFunction(CurFrame);
		}
	}

	if (nullptr != FrameEventInfo)
	{
		FrameEventInfo->UpdateEvent(_DeltaTime);
	}

	unsigned int NextFrame = CurFrame;
	++NextFrame;

	if (NextFrame > End)
	{
		NextFrame = Start;

		if (Loop == false)
		{
			NextFrame = End;
		}
	}

	std::vector<float4x4>& AnimationBoneMatrix = ParentRenderer->AnimationBoneMatrixs;
	std::vector<float4x4>& AnimationBoneNotOffSet = ParentRenderer->AnimationBoneNotOffset;
	std::vector<AnimationBoneData>& AnimationBoneDatas = ParentRenderer->AnimationBoneDatas;

	for (int i = 0; i < AnimationBoneMatrix.size(); i++)
	{
		if (true == FBXAnimationData->AniFrameData.empty())
		{
			MsgBoxAssert("�ε尡 �ȵ� �ִϸ��̼��� ��İ�� �Ϸ��� �߽��ϴ�.");
			continue;
		}

		Bone* BoneData = ParentRenderer->FBXMesh->FindBoneToIndex(i);

		if (true == FBXAnimationData->AniFrameData[i].BoneMatData.empty())
		{
			AnimationBoneMatrix[i] = float4x4::Affine(BoneData->BonePos.GlobalScale, BoneData->BonePos.GlobalRotation, BoneData->BonePos.GlobalRotation);
			continue;
		}

		FbxExBoneFrameData& CurData = FBXAnimationData->AniFrameData[i].BoneMatData[CurFrame];
		FbxExBoneFrameData& NextData = FBXAnimationData->AniFrameData[i].BoneMatData[NextFrame];

		float FrameRatio = CurFrameTime / Inter;
		AnimationBoneDatas[i].Scale = float4::LerpClamp(CurData.S, NextData.S, FrameRatio);
		AnimationBoneDatas[i].RotQuaternion = float4::SLerpQuaternionClamp(CurData.Q, NextData.Q, FrameRatio);
		AnimationBoneDatas[i].Pos = float4::LerpClamp(CurData.T, NextData.T, FrameRatio);

		if (false == ParentRenderer->BlendBoneData.empty())
		{
			float BlendRatio = PlayTime / BlendIn;

			if (BlendRatio < 1.0f)
			{
				AnimationBoneData& BoneData = ParentRenderer->BlendBoneData[i];

				AnimationBoneDatas[i].Scale = float4::LerpClamp(BoneData.Scale, AnimationBoneDatas[i].Scale, BlendRatio);
				AnimationBoneDatas[i].RotQuaternion = float4::SLerpQuaternionClamp(BoneData.RotQuaternion, AnimationBoneDatas[i].RotQuaternion, BlendRatio);
				AnimationBoneDatas[i].Pos = float4::LerpClamp(BoneData.Pos, AnimationBoneDatas[i].Pos, BlendRatio);

				if (false == ParentRenderer->NotBlendBoneIndexs.empty())
				{
					for (int Index : ParentRenderer->NotBlendBoneIndexs)
					{
						if (i == Index)
						{
							AnimationBoneDatas[i].Pos = float4::LerpClamp(ParentRenderer->Prev_BoneDate.Pos, AnimationBoneDatas[i].Pos, BlendRatio);
						}
						else
						{
							AnimationBoneDatas[i].Pos = float4::LerpClamp(BoneData.Pos, AnimationBoneDatas[i].Pos, BlendRatio);
						}
					}
				}
			}
			else
			{
				ParentRenderer->BlendReset();
			}
		}

		const std::vector<AnimationBoneData>& OtherBoneData = ParentRenderer->MultiBlendBoneData;
		if (false == OtherBoneData.empty())
		{
			const float BlendRatio = ParentRenderer->MultiBlendRatio;
			AnimationBoneDatas[i].Scale = float4::LerpClamp(OtherBoneData[i].Scale, AnimationBoneDatas[i].Scale, BlendRatio);
			AnimationBoneDatas[i].RotQuaternion = float4::SLerpQuaternionClamp(OtherBoneData[i].RotQuaternion, AnimationBoneDatas[i].RotQuaternion, BlendRatio);
			AnimationBoneDatas[i].Pos = float4::LerpClamp(OtherBoneData[i].Pos, AnimationBoneDatas[i].Pos, BlendRatio);
		}

		float4x4 Mat = float4x4::Affine(AnimationBoneDatas[i].Scale, AnimationBoneDatas[i].RotQuaternion, AnimationBoneDatas[i].Pos);
		
		AnimationBoneNotOffSet[i] = Mat;
		AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
	}
}

void GameContentsFBXAnimationInfo::Release()
{
	if (nullptr != FrameEventInfo)
	{
		FrameEventInfo->EventRelease();
		FrameEventInfo = nullptr;
	}
}

void GameContentsFBXAnimationInfo::SetBlendTime(float _Value)
{
	float TotalTime = Inter* (End + 1);
	if (TotalTime < _Value)
	{
		BlendIn = TotalTime;
	}
	else
	{
		BlendIn = _Value;
	}
}

void GameContentsFBXAnimationInfo::RootMotionUpdate(float _Delta)
{
	// Root Motion
	if (false == mRootMotionData.RootMotion)
	{
		return;
	}

	if (nullptr == ParentRenderer->RootMotionComponent)
	{
		return;
	}

	if (0 == CurFrame)
	{
		mRootMotionData.RootMotion_StartDir = ParentRenderer->RootMotionComponent->GetDir();
	}
	int tCurFrame = CurFrame;
	int NextFrame = CurFrame + 1;

	if (CurFrame == End)
	{
		return;
	}

	float4 CurFramePos = RootMotionFrames[tCurFrame];
	float4 NextFramePos = RootMotionFrames[NextFrame];
	float4 LerpStart = float4::ZERONULL;
	float4 DifPos = float4::ZERONULL; // operator���ο��� w���� �ٲ����
	float4 MotionVector = float4::ZERONULL;
	float4 LerpVector = float4::ZERONULL;

	float CurFrameTimeValue = _Delta;

	if (Inter <= CurFrameTimeValue + mRootMotionData.MoveFrameTime)
	{
		DifPos = NextFramePos - CurFramePos;
		DifPos.W = NextFramePos.W - CurFramePos.W;

		LerpVector = float4::LerpClamp(LerpStart, DifPos, (Inter - mRootMotionData.MoveFrameTime) / Inter);
		MotionVector += LerpVector;
		MotionVector.W += LerpVector.W;

		CurFrameTimeValue -= (Inter - mRootMotionData.MoveFrameTime);

		++tCurFrame;
		if (tCurFrame == End)
		{
			CurFrameTimeValue = 0.f;
		}
		else
		{
			CurFramePos = RootMotionFrames[tCurFrame];
			++NextFrame;
			NextFramePos = RootMotionFrames[NextFrame];
		}
	}

	while (Inter <= CurFrameTimeValue)
	{
		DifPos = NextFramePos - CurFramePos;
		DifPos.W = NextFramePos.W - CurFramePos.W;

		LerpVector = float4::LerpClamp(LerpStart, DifPos, 1.0f);
		MotionVector += LerpVector;
		MotionVector.W += LerpVector.W;

		CurFrameTimeValue -= Inter;

		++tCurFrame;
		if (tCurFrame == End)
		{
			CurFrameTimeValue = 0.f;
		}
		else
		{
			CurFramePos = RootMotionFrames[tCurFrame];
			++NextFrame;
			NextFramePos = RootMotionFrames[NextFrame];
		}
	}

	DifPos = NextFramePos - CurFramePos;
	DifPos.W = NextFramePos.W - CurFramePos.W;

	LerpVector = float4::LerpClamp(LerpStart, DifPos, CurFrameTimeValue / Inter);
	MotionVector += LerpVector;
	MotionVector.W += LerpVector.W;

	MotionVector.X *= mRootMotionData.MoveRatio_X;
	MotionVector.Y *= mRootMotionData.MoveRatio_Y;
	MotionVector.Z *= mRootMotionData.MoveRatio_Z;

	if (true == mRootMotionData.IsRotation)
	{
		ParentRenderer->RootMotionComponent->AddWorldRotation(float4(0.f, MotionVector.W * GameEngineMath::R2D, 0.f, 0.f));
	}

	switch (mRootMotionData.RootMotionMode)
	{
	case Enum_RootMotionMode::StartDir:
		ParentRenderer->RootMotionComponent->MoveForce(MotionVector, mRootMotionData.RootMotion_StartDir, false);
		break;
	case Enum_RootMotionMode::RealTimeDir:
		ParentRenderer->RootMotionComponent->MoveForce(MotionVector, false);
		break;
	default:
		MsgBoxAssert("�������� �ʴ� ��Ʈ��� ����Դϴ�.");
		break;
	}

	mRootMotionData.MoveFrameTime = CurFrameTimeValue;
}


void MultiBlendAnimationInfo::SetInfo(const std::shared_ptr<GameContentsFBXAnimationInfo>& _AnimationInfo)
{
	if (nullptr == _AnimationInfo)
	{
		MsgBoxAssert("�ִϸ��̼� ������ �������� �ʴµ� ����� ����Ϸ��߽��ϴ�.");
		return;
	}

	FBXAnimationData = _AnimationInfo->FBXAnimationData;
	AnimationName = _AnimationInfo->Aniamtion->GetName();
	End = _AnimationInfo->End;
	Inter = _AnimationInfo->Inter;

	Reset();
}

void MultiBlendAnimationInfo::Reset()
{
	CurFrameTime = 0.0f;
	PlayTime = 0.0f;
	CurFrame = 0;
	IsEnd = false;
}

void MultiBlendAnimationInfo::Done()
{
	IsEnd = true;
	ParentRenderer->MultiBlendBoneData.clear();
}

void MultiBlendAnimationInfo::Update(float _DeltaTime)
{
	bool PauseCheck = ParentRenderer->Pause;
	bool EndCheck = IsEnd;
	if (PauseCheck || EndCheck)
	{
		return;
	}

	CurFrameTime += _DeltaTime;
	PlayTime += _DeltaTime;

	while (CurFrameTime >= Inter)
	{
		CurFrameTime -= Inter;
		++CurFrame;

		if (CurFrame > End)
		{
			Done();
		}
	}

	unsigned int NextFrame = CurFrame;
	++NextFrame;

	if (NextFrame > End)
	{
		NextFrame = End;
	}

	std::vector<AnimationBoneData>& BlendBoneDatas = ParentRenderer->MultiBlendBoneData;

	for (int i = 0; i < static_cast<int>(FBXAnimationData->AniFrameData.size()); i++)
	{
		if (true == FBXAnimationData->AniFrameData.empty())
		{
			MsgBoxAssert("�ε尡 �ȵ� �ִϸ��̼��� ��İ�� �Ϸ��� �߽��ϴ�.");
			continue;
		}

		FbxExBoneFrameData& CurData = FBXAnimationData->AniFrameData[i].BoneMatData[CurFrame];
		FbxExBoneFrameData& NextData = FBXAnimationData->AniFrameData[i].BoneMatData[NextFrame];

		float FrameRatio = CurFrameTime / Inter;
		BlendBoneDatas[i].Scale = float4::LerpClamp(CurData.S, NextData.S, FrameRatio);
		BlendBoneDatas[i].RotQuaternion = float4::SLerpQuaternionClamp(CurData.Q, NextData.Q, FrameRatio);
		BlendBoneDatas[i].Pos = float4::LerpClamp(CurData.T, NextData.T, FrameRatio);
	}
}


GameContentsFBXRenderer::GameContentsFBXRenderer()
{
}

GameContentsFBXRenderer::~GameContentsFBXRenderer()
{
}

void GameContentsFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, RenderPath _RenderPath)
{
	Name = _Name;
	DefalutRenderPathValue = _RenderPath;

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�ε����� ���� FBX �Ž��� ����Ϸ��� �߽��ϴ�");
	}

	FindFBXMesh->Initialize();

	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		SetFBXMesh(_Name, _Material, UnitCount);
	}
}

void GameContentsFBXRenderer::SetMapFBXMesh(std::string_view _Name, std::string_view _Material)
{
	Name = _Name;

	// FBX.0 ã�´ٸ� 

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(Name);

	if (nullptr == FindFBXMesh)
	{
		Name += std::to_string(0);
		FindFBXMesh = GameEngineFBXMesh::Find(Name);
	}

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�ε����� ���� FBX �Ž��� ����Ϸ��� �߽��ϴ�");
	}

	FindFBXMesh->MapFBXInitialize();

	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		SetFBXMesh(Name, _Material, UnitCount);
	}
}

void GameContentsFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex = 0)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	FindFBXMesh->Initialize();
	for (int SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(_RenderUnitInfoIndex); SubSetCount++)
	{
		SetFBXMesh(_Name, _Material, _RenderUnitInfoIndex, SubSetCount);
	}
}

std::shared_ptr<GameEngineRenderUnit> GameContentsFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�������� �ʴ� FBXMesh�� �����߽��ϴ�");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}

	if (FBXMesh->GetPath() != FindFBXMesh->GetPath())
	{
		MsgBoxAssert("�̹� ������ �Ϸ�� FBXRenderer�� �ٸ� FBX mesh�� �����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	FindFBXMesh->Initialize();


	if (true == RenderUnits.empty())
	{
		RenderUnits.resize(FBXMesh->GetRenderUnitCount());
		for (int i = 0; i < FBXMesh->GetRenderUnitCount(); i++)
		{
			int Count = FindFBXMesh->GetSubSetCount(i);
			RenderUnits[i].resize(Count);
		}
	}


	// _RenderUnitInfoIndex, int _SubSetIndex
	if (nullptr == RenderUnits[_RenderUnitInfoIndex][_SubSetIndex])
	{
		RenderUnits[_RenderUnitInfoIndex][_SubSetIndex] = CreateAndFindRenderUnit(-1);
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = RenderUnits[_RenderUnitInfoIndex][_SubSetIndex];
	std::shared_ptr<GameEngineMesh> Mesh = FindFBXMesh->GetGameEngineMesh(_RenderUnitInfoIndex, _SubSetIndex);

	Unit->SetMesh(Mesh);

	//üũ�� ���׸���
	Unit->SetMaterial(_Material);
	Unit->Camerapushback(DefalutRenderPathValue);


	if (Unit->ShaderResHelper.IsStructedBuffer("ArrAniMationMatrix"))
	{
		Unit->RenderUnitBaseInfoValue.IsAnimation = 1;
	}
	else
	{

		Unit->RenderUnitBaseInfoValue.IsAnimation = 0;
	}
	
	const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);
	std::shared_ptr<GameEngineTexture> NorTex;
	std::shared_ptr<GameEngineTexture> SpcTex;
	std::string MaterialOrigin = _Material.data();


	if (Unit->ShaderResHelper.IsTexture("NormalTexture"))
	{

		if ("" == MatData.NorTextureName)
		{
			RenderBaseInfoValue.IsNormal = 0;
			Unit->RenderUnitBaseInfoValue.IsNormal = 0;
			MaterialOrigin += "_NorX";
		}
		else
		{
			NorTex = GameEngineTexture::Find(MatData.NorTextureName);
			if (nullptr == NorTex)
			{
				GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
				std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
				if (GameEnginePath::IsFileExist(TexturePath))
				{
					NorTex = GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
				}
				 //= GameEngineTexture::Find(MatData.NorTextureName);
			}
			


			if (nullptr == NorTex)
			{
				//��ũ�ҿ�� ������ �������� �ұ��ϰ� �ؽ��İ� ���ų� �ҷ��ü� ���� ���
				RenderBaseInfoValue.IsNormal = 0;
				Unit->RenderUnitBaseInfoValue.IsNormal = 0;
				MaterialOrigin += "_NorX";
			}
			else
			{
				RenderBaseInfoValue.IsNormal = 1;
				Unit->RenderUnitBaseInfoValue.IsNormal = 1;
			}
		}



	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.SpcTextureName)
		{
			RenderBaseInfoValue.IsSpecular = 0;
			Unit->RenderUnitBaseInfoValue.IsSpecular = 0;
			MaterialOrigin += "_SpcX";
		}
		else
		{

			SpcTex = GameEngineTexture::Find(MatData.SpcTextureName);

			if (nullptr == SpcTex)
			{
				GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
				std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.SpcTextureName;
				if (GameEnginePath::IsFileExist(TexturePath))
				{
					SpcTex = GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
				}

				//SpcTex = GameEngineTexture::Find(MatData.SpcTextureName);
			}



			if (nullptr == SpcTex)
			{
				//��ũ�ҿ�� ���Ŀ� ��ΰ� �������� �ұ��ϰ� �ؽ��İ� ���ų� �ҷ��ü� ���� ���
				RenderBaseInfoValue.IsSpecular = 0;
				Unit->RenderUnitBaseInfoValue.IsSpecular = 0;
				MaterialOrigin += "_SpcX";
			}
			else
			{
				RenderBaseInfoValue.IsSpecular = 1;
				Unit->RenderUnitBaseInfoValue.IsSpecular = 1;

			}
		}


	}


	std::shared_ptr< GameEngineMaterial> Matptr = GameEngineMaterial::Find(MaterialOrigin);

	if (nullptr == Matptr)
	{
		MsgBoxAssert("���� ���� �ؽ��ĸ� ����ϴ� ���� �����Դϴ�. �׿� �´� �븻 ����ŧ�� �ؽ��ĸ� ������ּ���. �װ� �ƴ϶�� ���ػ����� �����ּ���.");
	}
	Unit->SetMaterial(Matptr);

	if (Unit->RenderUnitBaseInfoValue.IsAnimation == 1)
	{
		if (0 >= AnimationBoneMatrixs.size())
		{
			size_t Size = FBXMesh->GetBoneCount();
			AnimationBoneMatrixs.resize(Size);
			AnimationBoneNotOffset.resize(Size);
			AnimationBoneDatas.resize(Size);
		}

		std::shared_ptr<GameEngineStructuredBuffer> Buffer
			= Unit->ShaderResHelper.GetStructedBuffer("ArrAniMationMatrix", ShaderType::Vertex);

		int Size = static_cast<int>(FBXMesh->GetBoneCount());
		Buffer->CreateResize(sizeof(float4x4), Size, StructuredBufferType::SRV_ONLY);

		Unit->ShaderResHelper.SetStructedBufferLink("ArrAniMationMatrix", AnimationBoneMatrixs);
	}

	if (Unit->ShaderResHelper.IsTexture("DiffuseTexture"))
	{

		RenderBaseInfoValue.IsDiffuse = 1;
		Unit->RenderUnitBaseInfoValue.IsDiffuse = 1;

		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.DifTextureName)
		{
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.DifTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.DifTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> DifTex = GameEngineTexture::Find(MatData.DifTextureName);

		if (nullptr == DifTex)
		{
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
		}


		Unit->ShaderResHelper.SetTexture("DiffuseTexture", DifTex);
	}


	if (Unit->RenderUnitBaseInfoValue.IsNormal == 1)
	{
		Unit->ShaderResHelper.SetTexture("NormalTexture", NorTex);
	}


	if (Unit->RenderUnitBaseInfoValue.IsSpecular == 1)
	{
		Unit->ShaderResHelper.SetTexture("SpecularTexture", SpcTex);
	}


	//���׸��� �ѹ��� üũ

	return Unit;
}

std::shared_ptr<GameContentsFBXAnimationInfo> GameContentsFBXRenderer::FindAnimation(std::string_view _AnimationName)
{
	if (false == Animations.contains(std::string(_AnimationName)))
	{
		return nullptr;
	}

	return Animations[std::string(_AnimationName)];
}

void GameContentsFBXRenderer::CreateFBXAnimation(const std::string_view _AnimationName, const std::string_view _AnimationFBX, const AnimationCreateParams& _Params, int _Index)
{
	if (nullptr == FBXMesh)
	{
		MsgBoxAssert("��� FBX�� ���õǾ� ���� �ʽ��ϴ�");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (nullptr != FindAnimation(UpperName))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼� �Դϴ�");
		return;
	}

	std::string AniUpperName = GameEngineString::ToUpperReturn(_AnimationFBX);
	std::shared_ptr<GameEngineFBXAnimation> AnimationFBX = GameEngineFBXAnimation::Find(AniUpperName);

	if (nullptr == AnimationFBX)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼� FBX�� �ִϸ��̼��� ������� �߽��ϴ�");
		return;
	}

	std::shared_ptr<GameContentsFBXAnimationInfo> NewAnimation = std::make_shared<GameContentsFBXAnimationInfo>();
	NewAnimation->ParentRenderer = this;
	NewAnimation->Init(FBXMesh, AnimationFBX, _AnimationName, _Index);
	if (0.0f == _Params.Inter)
	{
		NewAnimation->Inter = 1.0f / 30.0f;
	}
	else
	{
		NewAnimation->Inter = _Params.Inter;
	}
	NewAnimation->Loop = _Params.Loop;
	NewAnimation->Reset();

	for (size_t i = 0; i < NewAnimation->FBXAnimationData->AniFrameData[0].BoneMatData.size(); i++)
	{
		NewAnimation->Frames.push_back(static_cast<unsigned int>(i));
	}

	RenderBaseInfoValue.IsAnimation = 1;

	Animations.insert(std::make_pair(UpperName, NewAnimation));
}

void GameContentsFBXRenderer::ChangeAnimation(const std::string_view _AnimationName, bool _Force)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<GameContentsFBXAnimationInfo> Ptr = Animations[UpperName];

	if (false == _Force && CurAnimation == Ptr)
	{
		return;
	}

	if (nullptr != CurAnimation)
	{
		if (0.0f != CurAnimation->PlayTime) 
		{
			if (false == NotBlendBoneIndexs.empty())
			{
				AnimationBoneData Data = AnimationBoneDatas[*NotBlendBoneIndexs.begin()];
				Prev_BoneDate.Pos = Data.Pos;
			}

			BlendBoneData = AnimationBoneDatas;
		}

		CurAnimation->Reset();

		if (nullptr != CurAnimation->FrameChangeFunction)
		{
			CurAnimation->FrameChangeFunction(CurAnimation->CurFrame);
		}
	}

	CurAnimation = Ptr;
	if (nullptr != CurAnimation->AnimationChangeFunction)
	{
		CurAnimation->AnimationChangeFunction();
	}

	if (nullptr != MultiBlendAnimation)
	{
		MultiBlendAnimation->Done();
	}

	if (nullptr == RootMotionComponent)
	{
		return;
	}

	if (false == RootMotionComponent->IsInit())
	{
		return;
	}

	if (true == CurAnimation->IsRootMotion())
	{
		return;
	}

	RootMotionComponent->ResetMove(Enum_Axies::X | Enum_Axies::Z);
}

void GameContentsFBXRenderer::Update(float _DeltaTime)
{
	if (nullptr != MultiBlendAnimation && MultiBlendAnimation->IsUpdate())
	{
		MultiBlendAnimation->Update(_DeltaTime);
	}

	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);
	}
}

void GameContentsFBXRenderer::Release()
{
	for (const std::pair<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& Pair : Animations)
	{
		Pair.second->Release();
	}
}


// �� ����
std::shared_ptr<GameEngineRenderUnit> GameContentsFBXRenderer::SetMapFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�������� �ʴ� FBXMesh�� �����߽��ϴ�");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}

	if (FBXMesh->GetPath() != FindFBXMesh->GetPath())
	{
		MsgBoxAssert("�̹� ������ �Ϸ�� FBXRenderer�� �ٸ� FBX mesh�� �����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	FindFBXMesh->Initialize();


	RenderUnits.resize(FBXMesh->GetRenderUnitCount());
	for (int i = 0; i < FBXMesh->GetRenderUnitCount(); i++)
	{
		int Count = FindFBXMesh->GetSubSetCount(i);
		RenderUnits[i].resize(Count);
	}

	// _RenderUnitInfoIndex, int _SubSetIndex
	if (nullptr == RenderUnits[_RenderUnitInfoIndex][_SubSetIndex])
	{
		RenderUnits[_RenderUnitInfoIndex][_SubSetIndex] = CreateAndFindRenderUnit(-1);
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = RenderUnits[_RenderUnitInfoIndex][_SubSetIndex];
	std::shared_ptr<GameEngineMesh> Mesh = FindFBXMesh->GetGameEngineMesh(_RenderUnitInfoIndex, _SubSetIndex);

	Unit->SetMesh(Mesh);
	Unit->SetMaterial(_Material);


	if (Unit->ShaderResHelper.IsStructedBuffer("ArrAniMationMatrix"))
	{
		if (0 >= AnimationBoneMatrixs.size())
		{
			size_t Size = FBXMesh->GetBoneCount();
			AnimationBoneMatrixs.resize(Size);
			AnimationBoneNotOffset.resize(Size);
			AnimationBoneDatas.resize(Size);
		}

		std::shared_ptr<GameEngineStructuredBuffer> Buffer
			= Unit->ShaderResHelper.GetStructedBuffer("ArrAniMationMatrix", ShaderType::Vertex);

		int Size = static_cast<int>(FBXMesh->GetBoneCount());
		Buffer->CreateResize(sizeof(float4x4), Size, StructuredBufferType::SRV_ONLY);

		Unit->ShaderResHelper.SetStructedBufferLink("ArrAniMationMatrix", AnimationBoneMatrixs);

	}

	if (Unit->ShaderResHelper.IsTexture("DiffuseTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.DifTextureName)
		{
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.DifTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.DifTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> DifTex = GameEngineTexture::Find(MatData.DifTextureName);

		if (nullptr == DifTex)
		{
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
		}

		Unit->ShaderResHelper.SetTexture("DiffuseTexture", DifTex);
	}

	if (Unit->ShaderResHelper.IsTexture("NormalTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			RenderBaseInfoValue.IsNormal = 0;
		}
		else
		{
			if (nullptr == GameEngineTexture::Find(MatData.NorTextureName))
			{
				GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
				std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
				if (GameEnginePath::IsFileExist(TexturePath))
				{
					GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
				}
			}
			

			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.NorTextureName);

			if (nullptr == Tex)
			{
				//��ũ�ҿ�� ������ �������� �ұ��ϰ� �ؽ��İ� ���ų� �ҷ��ü� ���� ���
				RenderBaseInfoValue.IsNormal = 0;
			}
			else
			{

				RenderBaseInfoValue.IsNormal = 1;

				Unit->ShaderResHelper.SetTexture("NormalTexture", Tex);
			}
		}


	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.SpcTextureName)
		{
			RenderBaseInfoValue.IsSpecular = 0;
		}
		else
		{

			if (nullptr == GameEngineTexture::Find(MatData.SpcTextureName))
			{
				GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
				std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.SpcTextureName;
				if (GameEnginePath::IsFileExist(TexturePath))
				{
					GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
				}
			}

			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.SpcTextureName);


			if (nullptr == Tex)
			{
				//��ũ�ҿ�� ���Ŀ� ��ΰ� �������� �ұ��ϰ� �ؽ��İ� ���ų� �ҷ��ü� ���� ���
				RenderBaseInfoValue.IsSpecular = 0;
			}
			else
			{
				RenderBaseInfoValue.IsSpecular = 1;

				Unit->ShaderResHelper.SetTexture("SpecularTexture", Tex);
			}
		}
	}

	return Unit;
}

std::shared_ptr<GameEngineFBXMesh> GameContentsFBXRenderer::GetFBXMesh(std::string_view _Name)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	return FindFBXMesh;
}

// ���� �ε� �׽�Ʈ ����
void GameContentsFBXRenderer::TestSetBigFBXMesh(std::string_view _Name, std::string_view _Material)
{
	Name = _Name;

	// FBX.0 ã�´ٸ� 

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(Name);

	if (nullptr == FindFBXMesh)
	{
		Name += std::to_string(0);
		FindFBXMesh = GameEngineFBXMesh::Find(Name);
	}

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�ε����� ���� FBX �Ž��� ����Ϸ��� �߽��ϴ�");
	}

	FindFBXMesh->TestBigFBXInitialize();

	//���� FindFBXMesh �������ְ�

	// �������� ���� �̸��� �ʿ���
	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetMapDatasCount(); UnitCount++)
	{
		SetFBXMesh(Name, _Material, UnitCount);
	}
}

void GameContentsFBXRenderer::BlendReset()
{
	BlendBoneData.clear();
}

void GameContentsFBXRenderer::SetBlendTime(std::string_view _AnimationName, float _fBlendTime)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	const std::shared_ptr<GameContentsFBXAnimationInfo>& AnimInfo = FindAnimation(UpperName);
	if (nullptr == AnimInfo)
	{
		std::string AnimName = _AnimationName.data();
		MsgBoxAssert(AnimName + "�ش� �̸��� ���� �ִϸ��̼��� �������� �ʽ��ϴ�.");
		return;
	}

	AnimInfo->SetBlendTime(_fBlendTime);
}

void GameContentsFBXRenderer::SetBlendTime(std::string_view _AnimationName, int _iBlendFrame)
{
	float fBlendTime = static_cast<float>(_iBlendFrame)* ONE_FRAME_DTIME;
	SetBlendTime(_AnimationName, fBlendTime);
}

void GameContentsFBXRenderer::AddNotBlendBoneIndex(int _Index)
{
	if (NotBlendBoneIndexs.contains(_Index))
	{
		return;
	}

	NotBlendBoneIndexs.insert(_Index);
}

void GameContentsFBXRenderer::SetMultiBlend(std::string_view _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	const std::shared_ptr<GameContentsFBXAnimationInfo>& AnimInfo = FindAnimation(UpperName);
	if (nullptr == AnimInfo)
	{
		std::string AnimName = _AnimationName.data();
		MsgBoxAssert(AnimName + "�ش� �̸��� ���� �ִϸ��̼��� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == MultiBlendAnimation)
	{
		MultiBlendAnimation = std::make_unique<MultiBlendAnimationInfo>();
		MultiBlendBoneData.resize(AnimationBoneDatas.size());
	}

	MultiBlendAnimation->SetInfo(AnimInfo);
}

void GameContentsFBXRenderer::SetRootMotion(std::string_view _AniName, std::string_view _FileName, Enum_RootMotionMode _Mode, bool _RootMotion)
{
	// ���� ����ȭ�� ��ü���� �߰� ����

	std::string UpperName = GameEngineString::ToUpperReturn(_AniName.data());
	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� ��Ʈ ����� ������ �� �����ϴ�.");
	}

	GameEngineFile File;
	std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = Animations[UpperName];
	File = GameEngineFile(AniInfo->Aniamtion->GetPath());
	if ("" == _FileName.data())
	{
		File.ChangeExtension("XML");
	}
	else
	{
		File.MoveParent();
		File.MoveChild(_FileName.data());
	}

	if (false == File.IsExits())
	{
		MsgBoxAssert("��Ʈ��� ��ΰ� �߸��Ǿ����ϴ�. �ִϸ��̼� ���ϰ� ���� ��ο� ���ּ���.");
	}

	AniInfo->mRootMotionData.RootMotion = _RootMotion;
	AniInfo->mRootMotionData.RootMotionMode = _Mode;

	File.Open(FileOpenType::Read, FileDataType::Text);

	GameEngineSerializer Serial;
	File.DataAllRead(Serial);

	std::string DataString = Serial.GetDataPtr<const char*>();
	size_t DataPos = DataString.rfind("hkaDefaultAnimatedReferenceFrame");
	if (std::string::npos == DataPos)
	{
		MsgBoxAssert("RootMotion�� �������� �ʴ� �ִϸ��̼� �Դϴ�.");
	}

	size_t NumStartIndex = DataString.find("numelements", DataPos);

	size_t NumEndIndex = DataString.find("\"", NumStartIndex + 13);

	std::string NumberString = std::string(DataString, NumStartIndex + 13, NumEndIndex - (NumStartIndex + 13));

	int FrameCount = std::stoi(NumberString);

	if (AniInfo->FBXAnimationData->AniFrameData[0].BoneMatData.size() != FrameCount)
	{
		MsgBoxAssert("�ִϸ��̼� �����Ӽ��� ��ġ���� �ʽ��ϴ�. �߸��� �ִϸ��̼��� �� �ֽ��ϴ�.");
	}

	size_t VectorStart = DataString.find("(", NumEndIndex);

	AniInfo->RootMotionFrames.reserve(FrameCount);

	size_t ValueStart = VectorStart + 1;
	size_t ValueEnd = 0;
	for (int i = 0; i < FrameCount; i++)
	{
		float4 RootMotionVector = float4::ZERO;
		for (int j = 0; j < 4; j++)
		{
			std::string Value = "";

			switch (j)
			{
			case 0:
				ValueEnd = DataString.find(" ", ValueStart);
				Value = std::string(DataString, ValueStart, ValueEnd - ValueStart);
				RootMotionVector.X = -std::stof(Value);
				ValueStart = ValueEnd + 1;
				break;
			case 1:
				ValueEnd = DataString.find(" ", ValueStart);
				Value = std::string(DataString, ValueStart, ValueEnd - ValueStart);
				RootMotionVector.Y = std::stof(Value);
				ValueStart = ValueEnd + 1;
				break;
			case 2:
				ValueEnd = DataString.find(" ", ValueStart);
				Value = std::string(DataString, ValueStart, ValueEnd - ValueStart);
				RootMotionVector.Z = -std::stof(Value);
				ValueStart = ValueEnd + 1;
				break;
			case 3:
				ValueEnd = DataString.find(")", ValueStart);
				Value = std::string(DataString, ValueStart, ValueEnd - ValueStart);
				RootMotionVector.W = std::stof(Value);
				ValueStart = DataString.find("(", ValueEnd) + 1;
				AniInfo->RootMotionFrames.push_back(RootMotionVector);
				break;
			default:
				break;
			}
		}
	}


	File.Close();
}

void GameContentsFBXRenderer::SetRootMotionMode(std::string_view _AniName, Enum_RootMotionMode _Mode)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniName.data());
	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� ��Ʈ ��Ǹ�带 ������ �� �����ϴ�.");
	}

	std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = Animations[UpperName];
	AniInfo->mRootMotionData.RootMotionMode = _Mode;
}

void GameContentsFBXRenderer::SetRootMotionMoveRatio(std::string_view _AniName, float _Ratio_X /*= -1*/, float _Ratio_Z /*= -1*/, float _Ratio_Y /*= -1*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AniName.data());
	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼��Դϴ�.");
	}

	std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = Animations[UpperName];

	if (-1 != _Ratio_X)
	{
		AniInfo->mRootMotionData.MoveRatio_X = _Ratio_X;
	}

	if (-1 != _Ratio_Y)
	{
		AniInfo->mRootMotionData.MoveRatio_Y = _Ratio_Y;
	}

	if (-1 != _Ratio_Z)
	{
		AniInfo->mRootMotionData.MoveRatio_Z = _Ratio_Z;
	}
}

void GameContentsFBXRenderer::SetAllRootMotionMoveRatio(float _Ratio_X /*= -1*/, float _Ratio_Z /*= -1*/, float _Ratio_Y /*= -1*/)
{
	for (std::pair<const std::string, std::shared_ptr<GameContentsFBXAnimationInfo>> _Pair : Animations)
	{
		SetRootMotionMoveRatio(_Pair.first, _Ratio_X, _Ratio_Y, _Ratio_Z);
	}
}


AnimationBoneData GameContentsFBXRenderer::GetBoneData(std::string_view _Name)
{
	Bone* Ptr = FBXMesh->FindBone(_Name);

	AnimationBoneData Data;

	if (nullptr == Ptr)
	{
		MsgBoxAssert(std::string(_Name) + "�������� �ʴ� ���� �����͸� ã������ �߽��ϴ�");
		return Data;
	}

	// �ִϸ��̼��� ���ð����� �������̴�.
	Data = GetBoneData(Ptr->Index);

	return Data;
}


void GameContentsFBXRenderer::SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameContentsFBXRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>::iterator FindIter = Animations.find(UpperName);

	std::shared_ptr<GameContentsFBXAnimationInfo> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction.insert(std::make_pair(_Frame, _Function));
}

void GameContentsFBXRenderer::SetStartEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>::iterator FindIter = Animations.find(UpperName);

	std::shared_ptr<GameContentsFBXAnimationInfo> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction.insert(std::make_pair(0, _Function));
}

void GameContentsFBXRenderer::SetEndEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>::iterator FindIter = Animations.find(UpperName);

	std::shared_ptr<GameContentsFBXAnimationInfo> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->EndEvent = _Function;
}

void GameContentsFBXRenderer::SetAnimationChangeEvent(std::string_view _AnimationName, std::function<void()> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>::iterator FindIter = Animations.find(UpperName);

	std::shared_ptr<GameContentsFBXAnimationInfo> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->AnimationChangeFunction = _Function;
}


void GameContentsFBXRenderer::SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(int _FrameIndex)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>::iterator FindIter = Animations.find(UpperName);

	std::shared_ptr<GameContentsFBXAnimationInfo> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameChangeFunction = _Function;
}

void GameContentsFBXRenderer::SetFrameChangeFunctionAll(std::function<void(int _FrameIndex)> _Function)
{
	for (std::pair<const std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& _Pair : Animations)
	{
		_Pair.second->FrameChangeFunction = _Function;
	}
}
