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

void GameContentsFBXAnimationInfo::Reset()
{
	CurFrameTime = 0.0f;
	CurFrame = 0;
	PlayTime = 0.0f;
	bOnceStart = false;
	IsEnd = false;


	if (nullptr != EventHelper)
	{
		EventHelper->EventReset();
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
	End = static_cast<unsigned int>(FBXAnimationData->TimeEndCount);

	float TotalTime = static_cast<float>(End) * Inter;
	if (BlendIn > TotalTime)
	{
		BlendIn = TotalTime;
	}

	std::string EventName = FrameEventHelper::GetConvertFileName(_Animation->GetName());
	std::shared_ptr<FrameEventHelper> pEventHelper = FrameEventHelper::Find(EventName);
	if (nullptr != pEventHelper)
	{
		pEventHelper->Initialze(this);
		EventHelper = pEventHelper.get();
		return;
	}
}

void GameContentsFBXAnimationInfo::Update(float _DeltaTime)
{
	bool PauseCheck = ParentRenderer->Pause;
	bool NotLoopEndCheck = IsEnd && !Loop;
	if (PauseCheck || NotLoopEndCheck)
	{
		return;
	}

	IsEnd = false;

	if (false == bOnceStart)
	{
		if (nullptr != EventHelper)
		{
			EventHelper->PlayEvents(CurFrame);
		}

		bOnceStart = true;
	}

	// 0.1초짜리 
	CurFrameTime += _DeltaTime;
	PlayTime += _DeltaTime;
	RootMotionUpdate(_DeltaTime);

	while (CurFrameTime >= Inter)
	{
		//   2.0         0.1
		CurFrameTime -= Inter;
		++CurFrame;

		if (false == bOnceStart && CurFrame == 0)
		{
			bOnceStart = true;
			bOnceEnd = false;
		}

		bool DoneCheck = false;

		if (CurFrame > End)
		{
			IsEnd = true;

			if (true == Loop)
			{
				CurFrame = Start;
			}
			else
			{
				--CurFrame;
			}
		}

		if (nullptr != EventHelper)
		{
			EventHelper->PlayEvents(CurFrame);
		}
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
			MsgBoxAssert("로드가 안된 애니메이션을 행렬계산 하려고 했습니다.");
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
			}
			else
			{
				ParentRenderer->BlendReset();
			}
		}

		float4x4 Mat = float4x4::Affine(AnimationBoneDatas[i].Scale, AnimationBoneDatas[i].RotQuaternion, AnimationBoneDatas[i].Pos);
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
		AnimationBoneNotOffSet[i] = Mat;
		AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
	}


	if (nullptr != EventHelper)
	{
		EventHelper->UpdateEvent(_DeltaTime);
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
	float4 DifPos = float4::ZERONULL; // operator내부에서 w값을 바꿔버림
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
		CurFramePos = RootMotionFrames[tCurFrame];
		++NextFrame;
		NextFramePos = RootMotionFrames[NextFrame];
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
		CurFramePos = RootMotionFrames[tCurFrame];
		++NextFrame;
		NextFramePos = RootMotionFrames[NextFrame];

		if (NextFrame == End)
		{
			CurFrameTimeValue = 0.f;
		}
	}

	DifPos = NextFramePos - CurFramePos;
	DifPos.W = NextFramePos.W - CurFramePos.W;

	LerpVector = float4::LerpClamp(LerpStart, DifPos, CurFrameTimeValue / Inter);
	MotionVector += LerpVector;
	MotionVector.W += LerpVector.W;

	MotionVector.X *= 10000.f;
	MotionVector.Y *= 10000.f;
	MotionVector.Z *= 10000.f;

	if (true == mRootMotionData.IsRotation)
	{
		ParentRenderer->RootMotionComponent->AddWorldRotation(float4(0.f, MotionVector.W * GameEngineMath::R2D, 0.f, 0.f));
	}

	switch (mRootMotionData.RootMotionMode)
	{
	case Enum_RootMotionMode::StartDir:
		ParentRenderer->RootMotionComponent->MoveForce(MotionVector, mRootMotionData.RootMotion_StartDir, true);
		break;
	case Enum_RootMotionMode::RealTimeDir:
		ParentRenderer->RootMotionComponent->MoveForce(MotionVector, true);
		break;
	default:
		MsgBoxAssert("존재하지 않는 루트모션 모드입니다.");
		break;
	}

	mRootMotionData.MoveFrameTime = CurFrameTimeValue;
}


GameContentsFBXRenderer::GameContentsFBXRenderer()
{
}

GameContentsFBXRenderer::~GameContentsFBXRenderer()
{
}

void GameContentsFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material)
{
	Name = _Name;

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("로드하지 않은 FBX 매쉬를 사용하려고 했습니다");
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

	// FBX.0 찾는다면 

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(Name);

	if (nullptr == FindFBXMesh)
	{
		Name += std::to_string(0);
		FindFBXMesh = GameEngineFBXMesh::Find(Name);
	}

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("로드하지 않은 FBX 매쉬를 사용하려고 했습니다");
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
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}

	if (FBXMesh->GetPath() != FindFBXMesh->GetPath())
	{
		MsgBoxAssert("이미 세팅이 완료된 FBXRenderer에 다른 FBX mesh를 세팅하려고 했습니다.");
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
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
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
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("DiffuseTexture", DifTex);
	}

	if (Unit->ShaderResHelper.IsTexture("NormalTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.NorTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.NorTextureName);

		if (nullptr == Tex)
		{
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("NormalTexture", Tex);
	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.SpcTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.NorTextureName);

		if (nullptr == Tex)
		{
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("SpecularTexture", Tex);
	}

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
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (nullptr != FindAnimation(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션 입니다");
		return;
	}

	std::string AniUpperName = GameEngineString::ToUpperReturn(_AnimationFBX);
	std::shared_ptr<GameEngineFBXAnimation> AnimationFBX = GameEngineFBXAnimation::Find(AniUpperName);

	if (nullptr == AnimationFBX)
	{
		MsgBoxAssert("존재하지 않는 애니메이션 FBX로 애니메이션을 만들려고 했습니다");
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

	RenderBaseInfoValue.IsAnimation = 1;

	Animations.insert(std::make_pair(UpperName, NewAnimation));
}

void GameContentsFBXRenderer::ChangeAnimation(const std::string_view _AnimationName, bool _Force)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션을 재생하려고 했습니다.");
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
			BlendBoneData = AnimationBoneDatas;
		}

		CurAnimation->Reset();
	}

	CurAnimation = Ptr;
}

void GameContentsFBXRenderer::Update(float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);
	}
}


// 맵 분할
std::shared_ptr<GameEngineRenderUnit> GameContentsFBXRenderer::SetMapFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("존재하지 않는 FBXMesh를 세팅했습니다");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}

	if (FBXMesh->GetPath() != FindFBXMesh->GetPath())
	{
		MsgBoxAssert("이미 세팅이 완료된 FBXRenderer에 다른 FBX mesh를 세팅하려고 했습니다.");
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
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
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
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("DiffuseTexture", DifTex);
	}

	if (Unit->ShaderResHelper.IsTexture("NormalTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.NorTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.NorTextureName);

		if (nullptr == Tex)
		{
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("NormalTexture", Tex);
	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("텍스처 정보가 없는 FBX매쉬에 텍스처를 사용하는 머티리얼을 사용했습니다.");
		}

		if (nullptr == GameEngineTexture::Find(MatData.SpcTextureName))
		{
			GameEnginePath Path = GameEnginePath(FBXMesh->GetPath().c_str());
			std::string TexturePath = Path.GetFolderPath() + "\\" + MatData.NorTextureName;
			GameEngineTexture::Load(TexturePath, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
		}

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(MatData.NorTextureName);

		if (nullptr == Tex)
		{
			MsgBoxAssert("FBX매쉬에 텍스처 정보 로드에 실패했습니다.");
		}

		Unit->ShaderResHelper.SetTexture("SpecularTexture", Tex);
	}

	return Unit;
}

std::shared_ptr<GameEngineFBXMesh> GameContentsFBXRenderer::GetFBXMesh(std::string_view _Name)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	return FindFBXMesh;
}

// 분할 로드 테스트 보류
void GameContentsFBXRenderer::TestSetBigFBXMesh(std::string_view _Name, std::string_view _Material)
{
	Name = _Name;

	// FBX.0 찾는다면 

	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(Name);

	if (nullptr == FindFBXMesh)
	{
		Name += std::to_string(0);
		FindFBXMesh = GameEngineFBXMesh::Find(Name);
	}

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("로드하지 않은 FBX 매쉬를 사용하려고 했습니다");
	}

	FindFBXMesh->TestBigFBXInitialize();

	//리턴 FindFBXMesh 리턴해주고

	// 랜더유닛 수와 이름이 필요함
	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetMapDatasCount(); UnitCount++)
	{
		SetFBXMesh(Name, _Material, UnitCount);
	}
}

void GameContentsFBXRenderer::BlendReset()
{
	BlendBoneData.clear();
}

void GameContentsFBXRenderer::SetRootMotion(std::string_view _AniName, std::string_view _FileName, Enum_RootMotionMode _Mode, bool _RootMotion)
{
	// 추후 직렬화로 자체포멧 추가 예정

	std::string UpperName = GameEngineString::ToUpperReturn(_AniName.data());
	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 루트 모션을 세팅할 수 없습니다.");
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
		MsgBoxAssert("루트모션 경로가 잘못되었습니다. 애니메이션 파일과 같은 경로에 놔주세요.");
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
		MsgBoxAssert("RootMotion이 존재하지 않는 애니메이션 입니다.");
	}

	size_t NumStartIndex = DataString.find("numelements", DataPos);

	size_t NumEndIndex = DataString.find("\"", NumStartIndex + 13);

	std::string NumberString = std::string(DataString, NumStartIndex + 13, NumEndIndex - (NumStartIndex + 13));

	int FrameCount = std::stoi(NumberString);

	if (AniInfo->FBXAnimationData->AniFrameData[0].BoneMatData.size() != FrameCount)
	{
		MsgBoxAssert("애니메이션 프레임수가 일치하지 않습니다. 잘못된 애니메이션일 수 있습니다.");
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
		MsgBoxAssert("존재하지 않는 애니메이션에 루트 모션모드를 세팅할 수 없습니다.");
	}

	std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = Animations[UpperName];
	AniInfo->mRootMotionData.RootMotionMode = _Mode;
}
