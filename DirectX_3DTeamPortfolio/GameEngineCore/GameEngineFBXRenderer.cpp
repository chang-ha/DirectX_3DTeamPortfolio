#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"



void GameEngineFBXAnimationInfo::Reset()
{
	CurFrameTime = 0.0f;
	CurFrame = 0;
	PlayTime = 0.0f;
	// Start = 0;
}

void GameEngineFBXAnimationInfo::Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index)
{
	// GameENgineFBXAnimation의 행렬 정보가 완전해지는것은 
	// CalFbxExBoneFrameTransMatrix가 호출되고 난 후입니다.
	// 애니메이션의 행렬이 계산되는겁니다.

	_Animation->AnimationMatrixLoad(_Mesh, _Name, _Index);
	Aniamtion = _Animation;
	FBXAnimationData = Aniamtion->GetAnimationData(_Index);
	Start = static_cast<UINT>(FBXAnimationData->TimeStartCount);
	End = static_cast<UINT>(FBXAnimationData->TimeEndCount);
	Mesh = _Mesh;
	Aniamtion = _Animation;

	Start = 0;
	End = static_cast<unsigned int>(FBXAnimationData->TimeEndCount);
}

void GameEngineFBXAnimationInfo::Update(float _DeltaTime)
{
	if (false == ParentRenderer->Pause)
	{
		// 0.1초짜리 
		CurFrameTime += _DeltaTime;
		PlayTime += _DeltaTime;

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

			if (CurFrame >= End)
			{
				if (true == Loop)
				{
					CurFrame = Start;
				}
				else 
				{
					--CurFrame;
				}
			}
		}
	}

	unsigned int NextFrame = CurFrame;
	++NextFrame;

	if (NextFrame >= End)
	{
		NextFrame = 0;
	}

	if (CurFrame >= End)
	{
		CurFrame = 0;
	}

	std::vector<float4x4>& AnimationBoneMatrix = ParentRenderer->AnimationBoneMatrixs;
	std::vector<float4x4>& AnimationBoneNotOffSet = ParentRenderer->AnimationBoneNotOffset;
	std::vector<AnimationBoneData>& AnimationBoneData = ParentRenderer->AnimationBoneDatas;

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

		// CurFrameTime 분명히 잘못되었다.
		AnimationBoneData[i].Scale = float4::LerpClamp(CurData.S, NextData.S, CurFrameTime);
		AnimationBoneData[i].RotQuaternion = float4::SLerpQuaternionClamp(CurData.Q, NextData.Q, CurFrameTime);
		AnimationBoneData[i].Pos = float4::LerpClamp(CurData.T, NextData.T, CurFrameTime);

		float4x4 Mat = float4x4::Affine(AnimationBoneData[i].Scale, AnimationBoneData[i].RotQuaternion, AnimationBoneData[i].Pos);

		AnimationBoneNotOffSet[i] = Mat;
		AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
	}

}



GameEngineFBXRenderer::GameEngineFBXRenderer() 
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer() 
{
}

void GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material)
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

void GameEngineFBXRenderer::SetBigFBXMesh(std::string_view _Name, std::string_view _Material)
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

	FindFBXMesh->BigFBXInitialize();

	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		SetFBXMesh(Name, _Material, UnitCount);
	}
}

// 랜더 유니트를 하나씩 
void GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex = 0)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	FindFBXMesh->Initialize();
	for (int SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(_RenderUnitInfoIndex); SubSetCount++)
	{
		SetFBXMesh(_Name, _Material, _RenderUnitInfoIndex, SubSetCount);
	}
}


std::shared_ptr<GameEngineRenderUnit> GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex)
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
		for (int i = 0;  i < FBXMesh->GetRenderUnitCount();  i++)
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

	return Unit;
}

std::shared_ptr<GameEngineFBXAnimationInfo> GameEngineFBXRenderer::FindAnimation(std::string_view _AnimationName)
{
	if (false == Animations.contains(std::string(_AnimationName)))
	{
		return nullptr;
	}

	return Animations[std::string(_AnimationName)];
}

void GameEngineFBXRenderer::CreateFBXAnimation(const std::string_view _AnimationName, const std::string_view _AnimationFBX, const AnimationCreateParams& _Params, int _Index)
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

	std::shared_ptr<GameEngineFBXAnimationInfo> NewAnimation = std::make_shared<GameEngineFBXAnimationInfo>();
	// 이때 애니메이션을 진짜 로드 한다.
	NewAnimation->Init(FBXMesh, AnimationFBX, _AnimationName, _Index);
	NewAnimation->ParentRenderer = this;
	NewAnimation->Inter = _Params.Inter;
	NewAnimation->Loop = _Params.Loop;
	NewAnimation->Reset();

	RenderBaseInfoValue.IsAnimation = 1;

	Animations.insert(std::make_pair(UpperName, NewAnimation));
}

void GameEngineFBXRenderer::ChangeAnimation(const std::string_view _AnimationName, bool _Force)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션을 재생하려고 했습니다.");
		return;
	}

	std::shared_ptr<GameEngineFBXAnimationInfo> Ptr = Animations[UpperName];

	if (false == _Force && CurAnimation == Ptr)
	{
		return;
	}

	CurAnimation = Ptr;
}

void GameEngineFBXRenderer::Update(float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);
	}
}

std::map<std::string, std::shared_ptr<GameEngineFBXAnimationInfo>>& GameEngineFBXRenderer::GetAnimationInfos()
{
	return Animations;
}