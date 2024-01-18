#include "PreCompile.h"
#include "GameContentsFBXRenderer.h"
#include "FrameEventHelper.h"

void GameContentsFBXAnimationInfo::Reset()
{
	CurFrameTime = 0.0f;
	CurFrame = 0;
	PlayTime = 0.0f;
	IsStart = false;
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
		EventHelper = pEventHelper.get();
		EventHelper->Initialze(this);
		return;
	}
}

void GameContentsFBXAnimationInfo::Update(float _DeltaTime)
{
	if (false == ParentRenderer->Pause)
	{
		IsEnd = false;

		if (false == IsStart)
		{
			if (nullptr != EventHelper)
			{
				EventHelper->PlayEvents(CurFrame);
			}

			IsStart = true;
		}

		// 0.1��¥�� 
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
	}

	if (nullptr != EventHelper)
	{
		EventHelper->UpdateEvent(_DeltaTime);
	}

	unsigned int NextFrame = CurFrame;
	++NextFrame;

	if (NextFrame >= End)
	{
		NextFrame = 0;
		
		if (Loop == false)
		{
			NextFrame = End;
		}

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
		AnimationBoneData[i].Scale = float4::LerpClamp(CurData.S, NextData.S, FrameRatio);
		AnimationBoneData[i].RotQuaternion = float4::SLerpQuaternionClamp(CurData.Q, NextData.Q, FrameRatio);
		AnimationBoneData[i].Pos = float4::LerpClamp(CurData.T, NextData.T, FrameRatio);

		if (false == ParentRenderer->BlendBoneMatrixs.empty())
		{
			float BlendRatio = PlayTime / BlendIn;
			if (BlendRatio < 1.0f)
			{
				float4x4& BoneData = ParentRenderer->BlendBoneMatrixs[i];
				float4 BlendScale;
				float4 BlendQuaternion;
				float4 BlendPos;
				BoneData.Decompose(BlendScale, BlendQuaternion, BlendPos);

				AnimationBoneData[i].Scale = float4::LerpClamp(BlendScale, AnimationBoneData[i].Scale, BlendRatio);
				AnimationBoneData[i].RotQuaternion = float4::SLerpQuaternionClamp(BlendQuaternion, AnimationBoneData[i].RotQuaternion, BlendRatio);
				AnimationBoneData[i].Pos = float4::LerpClamp(BlendPos, AnimationBoneData[i].Pos, BlendRatio);
			}
			else
			{
				ParentRenderer->BlendReset();
			}
		}

		float4x4 Mat = float4x4::Affine(AnimationBoneData[i].Scale, AnimationBoneData[i].RotQuaternion, AnimationBoneData[i].Pos);

		AnimationBoneNotOffSet[i] = Mat;
		AnimationBoneMatrix[i] = BoneData->BonePos.Offset * Mat;
	}

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
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
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
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
		}

		Unit->ShaderResHelper.SetTexture("NormalTexture", Tex);
	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
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
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
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
		BlendBoneMatrixs = AnimationBoneNotOffset;
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
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
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
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
		}

		Unit->ShaderResHelper.SetTexture("NormalTexture", Tex);
	}

	if (Unit->ShaderResHelper.IsTexture("SpecularTexture"))
	{
		const FbxExMaterialSettingData& MatData = FBXMesh->GetMaterialSettingData(_RenderUnitInfoIndex, _SubSetIndex);

		if ("" == MatData.NorTextureName)
		{
			MsgBoxAssert("�ؽ�ó ������ ���� FBX�Ž��� �ؽ�ó�� ����ϴ� ��Ƽ������ ����߽��ϴ�.");
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
			MsgBoxAssert("FBX�Ž��� �ؽ�ó ���� �ε忡 �����߽��ϴ�.");
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
	BlendBoneMatrixs.clear();
}