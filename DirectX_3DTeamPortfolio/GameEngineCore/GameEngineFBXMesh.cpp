#include "PreCompile.h"
#include "GameEngineFBXMesh.h"
#include "GameEngineMesh.h"
#include "GameEngineVertexBuffer.h"

GameEngineFBXMesh::GameEngineFBXMesh() 
{
}

GameEngineFBXMesh::~GameEngineFBXMesh() 
{

}

const FbxExMaterialSettingData& GameEngineFBXMesh::GetMaterialSettingData(size_t _MeshIndex, size_t _SubIndex)
{
	if (RenderUnitInfos.size() <= _MeshIndex)
	{
		MsgBoxAssert("�������� �ʴ� ���� ����Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	FbxRenderUnitInfo& Unit = RenderUnitInfos[_MeshIndex];

	if (Unit.MaterialData.size() <= _SubIndex)
	{
		MsgBoxAssert("�������� �ʴ� ���������� �������� �߽��ϴ�.");
	}

	return Unit.MaterialData[_SubIndex];
}

std::shared_ptr<GameEngineFBXMesh> GameEngineFBXMesh::Load(std::string_view& _Path, std::string_view _Name)
{
	std::shared_ptr<GameEngineFBXMesh> Res = CreateRes(_Name);
	Res->SetPath(_Path);
	Res->LoadMesh(_Path, _Name);
	return Res;
}

void GameEngineFBXMesh::LoadMesh(std::string_view& _Path, std::string_view _Name)
{
	// Initialize();
	// 
}

void GameEngineFBXMesh::Initialize()
{
	if (0 != RenderUnitInfos.size())
	{
		return;
	}

	GameEngineFile File = GameEngineFile(GetPath());

	FBXMeshName = File.GetFileName();

	File.ChangeExtension("MeshFBX");

	if (true == File.IsExits())
	{
		File.Open(FileOpenType::Read, FileDataType::Binary);
		GameEngineSerializer Ser;
		File.DataAllRead(Ser);
		Ser >> FBXMeshName;
		Ser >> MeshInfos;
		Ser >> RenderUnitInfos;
		Ser >> AllBones;

		for (int i = 0; i < AllBones.size(); i++)
		{
			AllFindMap[AllBones[i].Name] = &AllBones[i];
		}
		return;
	}


	FBXInit(GetPath());
	MeshLoad();
	// CreateBoneStructuredBuffer();


	GameEngineSerializer Ser;
	Ser << FBXMeshName;
	Ser << MeshInfos;
	Ser << RenderUnitInfos;
	Ser << AllBones;

	File.Open(FileOpenType::Write, FileDataType::Binary);
	File.Write(Ser);
}

void GameEngineFBXMesh::CreateBoneStructuredBuffer()
{
	AllBoneStructuredBuffers = std::make_shared<GameEngineStructuredBuffer>();
	AllBoneStructuredBuffers->CreateResize(sizeof(float4x4), static_cast<int>(AllBones.size()), StructuredBufferType::SRV_ONLY, nullptr);
}

std::shared_ptr<GameEngineMesh> GameEngineFBXMesh::GetGameEngineMesh(int _MeshIndex, int _SubSetIndex)
{
	if (RenderUnitInfos.size() <= _MeshIndex)
	{
		MsgBoxAssert("�������� �ʴ� ���� ����Ʈ������ �Ž��� ������� �߽��ϴ�.");
	}

	FbxRenderUnitInfo& Unit = RenderUnitInfos[_MeshIndex];

	if (nullptr == Unit.VertexBuffer)
	{
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Create(Unit.Vertexs);

		if (nullptr == VertexBuffer)
		{
			MsgBoxAssert("FBX ���ؽ� ���� ���� ����.");
		}

		Unit.VertexBuffer = VertexBuffer;
	}

	if (Unit.Indexs.size() <= _SubSetIndex)
	{
		MsgBoxAssert("�������� �ʴ� ������� ������� �߽��ϴ�, �ε��� ���۸� �����Ҽ� �����ϴ�.");
	}

	if (Unit.IndexBuffers.empty())
	{
		Unit.IndexBuffers.resize(Unit.Indexs.size());
	}

	if (nullptr == Unit.IndexBuffers[_SubSetIndex])
	{
		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Create(Unit.Indexs[_SubSetIndex]);

		if (nullptr == IndexBuffer)
		{
			MsgBoxAssert("�������� �ʴ� ������� ������� �߽��ϴ�, �ε��� ���۸� �����Ҽ� �����ϴ�.");
		}

		Unit.IndexBuffers[_SubSetIndex] = IndexBuffer;
	}

	if (true == Unit.Meshs.empty())
	{
		Unit.Meshs.resize(Unit.Indexs.size());
	}
	
	if (nullptr == Unit.Meshs[_SubSetIndex])
	{
		Unit.Meshs[_SubSetIndex] = GameEngineMesh::Create(Unit.VertexBuffer, Unit.IndexBuffers[_SubSetIndex]);
	}
	
	// �ؽ�ó�� �ε��ؾ� �Ѵ�.
	return Unit.Meshs[_SubSetIndex];
}

void GameEngineFBXMesh::MeshLoad()
{
	std::string Path = GetPath().data();
	MeshNodeCheck();
	VertexBufferCheck();
	ImportBone();

	AllBones; // ������ü
	AllFindMap;
	RenderUnitInfos;
	MeshInfos;
	int a = 0;
}

fbxsdk::FbxAMatrix GameEngineFBXMesh::ComputeTotalMatrix(fbxsdk::FbxNode* Node)
{
	fbxsdk::FbxAMatrix Geometry;
	fbxsdk::FbxVector4 Translation, Rotation, Scaling;
	Translation = Node->GetGeometricTranslation(fbxsdk::FbxNode::eSourcePivot);
	Rotation = Node->GetGeometricRotation(fbxsdk::FbxNode::eSourcePivot);
	Scaling = Node->GetGeometricScaling(fbxsdk::FbxNode::eSourcePivot);
	Geometry.SetT(Translation);
	Geometry.SetR(Rotation);
	Geometry.SetS(Scaling);

	fbxsdk::FbxAMatrix& GlobalTransform = Scene->GetAnimationEvaluator()->GetNodeGlobalTransform(Node);
	return GlobalTransform * Geometry;
}


bool GameEngineFBXMesh::IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix)
{
	fbxsdk::FbxVector4 Scale = TotalMatrix.GetS();
	int NegativeNum = 0;

	if (Scale[0] < 0) NegativeNum++;
	if (Scale[1] < 0) NegativeNum++;
	if (Scale[2] < 0) NegativeNum++;

	return NegativeNum == 1 || NegativeNum == 3;
}


std::string GameEngineFBXMesh::MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName)
{
	fbxsdk::FbxProperty TexturePro = pMtrl->FindProperty(_FactorName);

	std::string Str;
	if (true == TexturePro.IsValid())
	{
		fbxsdk::FbxObject* pFileTex = TexturePro.GetFbxObject();

		int iTexCount = TexturePro.GetSrcObjectCount<FbxFileTexture>();

		if (iTexCount > 0)
		{
			FbxFileTexture* pFileTex = TexturePro.GetSrcObject<FbxFileTexture>(0);

			if (nullptr != pFileTex)
			{
				Str = pFileTex->GetFileName();
			}
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}

	return Str;
}

float GameEngineFBXMesh::MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName)
{
	double dFactor = 0;
	FbxProperty FactorPro = pMtrl->FindProperty(_FactorName);

	if (true == FactorPro.IsValid())
	{
		dFactor = FactorPro.Get<FbxDouble>();
	}

	return (float)dFactor;
}


float4 GameEngineFBXMesh::MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName)
{
	FbxDouble3 vResult(0, 0, 0);
	double dFactor = 0;
	FbxProperty ColorPro = pMtrl->FindProperty(_ColorName);
	FbxProperty FactorPro = pMtrl->FindProperty(_FactorName);

	if (true == ColorPro.IsValid() && true == FactorPro.IsValid())
	{
		vResult = ColorPro.Get<FbxDouble3>();
		dFactor = FactorPro.Get<FbxDouble>();

		if (dFactor != 1)
		{
			vResult[0] *= dFactor;
			vResult[1] *= dFactor;
			vResult[2] *= dFactor;
		}
	}

	return float4((float)vResult[0], (float)vResult[1], (float)vResult[2]);
}

void GameEngineFBXMesh::FbxRenderUnitInfoMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnitInfo* _RenderData)
{
	int MtrlCount = _Node->GetMaterialCount();

	if (MtrlCount > 0)
	{
		std::vector<FbxExMaterialSettingData>& MatrialSet = _RenderData->MaterialData;

		// ?2����

		for (int i = 0; i < MtrlCount; i++)
		{
			fbxsdk::FbxSurfaceMaterial* pMtrl = _Node->GetMaterial(i);

			if (nullptr == pMtrl)
			{
				MsgBoxAssert("if (nullptr == pMtrl) ���׸��� ������ �������� �ʽ��ϴ�");
				continue;
			}

			FbxExMaterialSettingData& MatData = MatrialSet.emplace_back();
			MatData.Name = pMtrl->GetName();
			// fbxsdk::FbxSurfaceMaterial::sDiffuse = 0x00007ff61122bf40 "DiffuseColor"
			// fbxsdk::FbxSurfaceMaterial::sDiffuseFactor = 0x00007ff61122bf50 "DiffuseFactor"
			MatData.DifColor = MaterialColor(pMtrl, "DiffuseColor", "DiffuseFactor");
			MatData.AmbColor = MaterialColor(pMtrl, "AmbientColor", "AmbientFactor");
			MatData.SpcColor = MaterialColor(pMtrl, "SpecularColor", "SpecularFactor");
			MatData.EmvColor = MaterialColor(pMtrl, "EmissiveColor", "EmissiveFactor");
			MatData.SpecularPower = MaterialFactor(pMtrl, "SpecularFactor");
			// fbxsdk::FbxSurfaceMaterial::sShininess = 0x00007ff61122bf80 "ShininessExponent"
			// fbxsdk::FbxSurfaceMaterial::sTransparencyFactor = 0x00007ff61122bfd8 "TransparencyFactor"
			MatData.Shininess = MaterialFactor(pMtrl, "ShininessExponent");
			MatData.TransparencyFactor = MaterialFactor(pMtrl, "TransparencyFactor");

			MatData.DifTexturePath = MaterialTex(pMtrl, "DiffuseColor");
			MatData.NorTexturePath = MaterialTex(pMtrl, "NormalMap");
			MatData.SpcTexturePath = MaterialTex(pMtrl, "SpecularColor");

			MatData.DifTextureName = GameEnginePath::GetFileName(MatData.DifTexturePath);
			MatData.NorTextureName = GameEnginePath::GetFileName(MatData.NorTexturePath);
			MatData.SpcTextureName = GameEnginePath::GetFileName(MatData.SpcTexturePath);
		}

	}
	else {
		// MsgAssert("�Ž��� ���������� ������ �������� �ʽ��ϴ�.");
	}

}


void GameEngineFBXMesh::LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementNormalCount();

	if (0 == iCount)
	{
		MsgBoxAssert("GetElementNormalCount�� ������ �Դϴ�.");
	}


	FbxGeometryElementNormal* pElement = _Mesh->GetElementNormal();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}
	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("���� ����� ó���Ҽ� ���� ����Դϴ�.");
		}
	}

	FbxVector4 Normal = pElement->GetDirectArray().GetAt(iDataIndex);

	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	Normal = conversionMeshMatrix.MultT(Normal);

	_ArrVtx[_Index].NORMAL.X = (float)Normal.mData[0];
	_ArrVtx[_Index].NORMAL.Y = (float)Normal.mData[1];
	_ArrVtx[_Index].NORMAL.Z = -(float)Normal.mData[2];
	_ArrVtx[_Index].NORMAL.W = (float)Normal.mData[3];
	// _ArrVtx[_Index].Normal.w = 0.0f;
	_ArrVtx[_Index].NORMAL.Normalize();
}


void GameEngineFBXMesh::LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementTangentCount();

	if (0 == iCount)
	{
		return;
	}
	FbxGeometryElementTangent* pElement = _Mesh->GetElementTangent();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}
	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("���� ����� ó���Ҽ� ���� ����Դϴ�.");
		}
	}

	FbxVector4 Tangent = pElement->GetDirectArray().GetAt(iDataIndex);


	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	Tangent = conversionMeshMatrix.MultT(Tangent);


	_ArrVtx[_Index].TANGENT.X = (float)Tangent.mData[0];
	_ArrVtx[_Index].TANGENT.Y = (float)Tangent.mData[1];
	_ArrVtx[_Index].TANGENT.Z = -(float)Tangent.mData[2];
	_ArrVtx[_Index].TANGENT.W = (float)Tangent.mData[3];
	_ArrVtx[_Index].TANGENT.Normalize();
}


void GameEngineFBXMesh::LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementBinormalCount();

	if (0 == iCount)
	{
		return;

	}

	FbxGeometryElementBinormal* pElement = _Mesh->GetElementBinormal();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}

	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("���� ����� ó���Ҽ� ���� ����Դϴ�.");
		}
	}

	FbxVector4 BiNormal = pElement->GetDirectArray().GetAt(iDataIndex);

	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	BiNormal = conversionMeshMatrix.MultT(BiNormal);


	_ArrVtx[_Index].BINORMAL.X = (float)BiNormal.mData[0];
	_ArrVtx[_Index].BINORMAL.Y = (float)BiNormal.mData[1];
	_ArrVtx[_Index].BINORMAL.Z = -(float)BiNormal.mData[2];
	_ArrVtx[_Index].BINORMAL.W = (float)BiNormal.mData[3];
	_ArrVtx[_Index].BINORMAL.Normalize();
}

void GameEngineFBXMesh::VertexBufferCheck()
{
	int meshInfoSize = static_cast<int>(MeshInfos.size());
	for (int meshInfoIndex = 0; meshInfoIndex < meshInfoSize; ++meshInfoIndex)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(meshInfoIndex);
		fbxsdk::FbxNode* pMeshNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* pMesh = meshInfo.Mesh;

		FbxRenderUnitInfo& RenderUnit = RenderUnitInfos.emplace_back();
		RenderUnit.VectorIndex = meshInfoIndex;

		if (RenderUnit.MapWI.end() == RenderUnit.MapWI.find(pMesh))
		{
			RenderUnit.MapWI.insert(std::make_pair(pMesh, std::map<int, std::vector<FbxExIW>>()));
		}

		RenderUnit.IsLod = meshInfo.bIsLodGroup;
		RenderUnit.IsLodLv = meshInfo.LodLevel;
		std::vector<GameEngineVertex>& VtxData = RenderUnit.Vertexs;
		std::vector<std::vector<UINT>>& IdxData = RenderUnit.Indexs;

		// ���ؽ� ��������.
		int controlPointsCount = pMesh->GetControlPointsCount();
		VtxData.resize(controlPointsCount);

		fbxsdk::FbxVector4* pControlPoints = pMesh->GetControlPoints();

		fbxsdk::FbxAMatrix meshMatrix = ComputeTotalMatrix(pMeshNode);

		if (false == meshInfo.bIsSkeletalMesh)
		{
			// �ִϸ޸��̼��� ��쿡�� �ִϸ��̼��� Ư���� �������� ������� ���ؽ��� ��ȯ�ؼ� �޾ƾ� �ϴµ�.
			meshMatrix = JointMatrix * meshMatrix;
		}

		// bool isOddNegativeScale = IsOddNegativeScale(meshMatrix);

		for (int controlPointIndex = 0; controlPointIndex < controlPointsCount; ++controlPointIndex)
		{
			fbxsdk::FbxVector4 controlPoint = pControlPoints[controlPointIndex];

			fbxsdk::FbxVector4 calculateControlPoint = meshMatrix.MultT(controlPoint);

			VtxData[controlPointIndex].POSITION = FbxVecToTransform(calculateControlPoint);
			VtxData[controlPointIndex].POSITION.W = 1.0f;

			if (RenderUnit.MaxBoundBox.X < VtxData[controlPointIndex].POSITION.X) { RenderUnit.MaxBoundBox.X = VtxData[controlPointIndex].POSITION.X; }
			if (RenderUnit.MaxBoundBox.Y < VtxData[controlPointIndex].POSITION.Y) { RenderUnit.MaxBoundBox.Y = VtxData[controlPointIndex].POSITION.Y; }
			if (RenderUnit.MaxBoundBox.Z < VtxData[controlPointIndex].POSITION.Z) { RenderUnit.MaxBoundBox.Z = VtxData[controlPointIndex].POSITION.Z; }

			if (RenderUnit.MinBoundBox.X > VtxData[controlPointIndex].POSITION.X) { RenderUnit.MinBoundBox.X = VtxData[controlPointIndex].POSITION.X; }
			if (RenderUnit.MinBoundBox.Y > VtxData[controlPointIndex].POSITION.Y) { RenderUnit.MinBoundBox.Y = VtxData[controlPointIndex].POSITION.Y; }
			if (RenderUnit.MinBoundBox.Z > VtxData[controlPointIndex].POSITION.Z) { RenderUnit.MinBoundBox.Z = VtxData[controlPointIndex].POSITION.Z; }
		}

		RenderUnit.BoundScaleBox.X = RenderUnit.MaxBoundBox.X - RenderUnit.MinBoundBox.X;
		RenderUnit.BoundScaleBox.Y = RenderUnit.MaxBoundBox.Y - RenderUnit.MinBoundBox.Y;
		RenderUnit.BoundScaleBox.Z = RenderUnit.MaxBoundBox.Z - RenderUnit.MinBoundBox.Z;

		FbxRenderUnitInfoMaterialSetting(pMeshNode, &RenderUnit);

		// ���׸��� 
		fbxsdk::FbxGeometryElementMaterial* pGeometryElementMaterial = pMesh->GetElementMaterial();

		// ��Ƽ������ 4����� ����µ� 4���� �״ϱ�.
		int materialCount = pMeshNode->GetMaterialCount();
		IdxData.resize(materialCount);

		// �븻�� 
		// UV����� ���ɴϴ�.
		// �븻 UV����� ���� ����� �ٸ��� �־ �Ʒ��� ���� ������� �������� �и��ؼ� ���� ���;� �մϴ�.
		UINT VtxId = 0;
		int nPolygonCount = pMesh->GetPolygonCount();

		for (int PolygonIndex = 0; PolygonIndex < nPolygonCount; ++PolygonIndex)
		{
			int PolygonSize = pMesh->GetPolygonSize(PolygonIndex);

			if (3 != PolygonSize)
			{
				MsgBoxAssert("�ﰢ���� �ƴ� ���� �߰߉���ϴ�.");
			}

			int IndexArray[3] = { 0, };
			for (int PositionInPolygon = 0; PositionInPolygon < PolygonSize; ++PositionInPolygon)
			{
				int ControlPointIndex = pMesh->GetPolygonVertex(PolygonIndex, PositionInPolygon);
				IndexArray[PositionInPolygon] = ControlPointIndex;

				LoadNormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
				LoadTangent(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
				LoadBinormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);

				int Count = pMesh->GetLayerCount();

				//FMeshDescription* MeshDescription = StaticMesh->GetMeshDescription(LODIndex);
				//FStaticMeshAttributes Attributes(*MeshDescription);
				LoadUV(pMesh, meshMatrix, VtxData, pMesh->GetTextureUVIndex(PolygonIndex, PositionInPolygon), VtxId, ControlPointIndex);

				++VtxId;
			}

			// �ε��������� �ٷ��� ���� ������ �ǰ�.
			int materialId = pGeometryElementMaterial->GetIndexArray().GetAt(PolygonIndex);
			IdxData[materialId].push_back(IndexArray[0]);
			IdxData[materialId].push_back(IndexArray[2]);
			IdxData[materialId].push_back(IndexArray[1]);
		}

		RenderUnit.FbxVertexMap.insert(std::make_pair(pMesh, &VtxData));
	}

	MeshInfos;
	RenderUnitInfos;
	int a = 0;
}


void GameEngineFBXMesh::LoadUV(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int VertexCount, int _Index)
{
	// pMesh->GetTextureUVIndex(PolygonIndex, PositionInPolygon), VtxId, ControlPointIndex

	int iCount = _Mesh->GetElementUVCount();

	if (0 == iCount)
	{
		return;
	}

	float4 result;

	FbxGeometryElementUV* pElement = _Mesh->GetElementUV();
	int iDataIndex = VtxId;
	switch (pElement->GetMappingMode())
		//switch (vertexTangnet->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (pElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result.X = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[0]);
			result.Y = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[1]);
			// result.z = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[2]);
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pElement->GetIndexArray().GetAt(_Index);
			result.X = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[0]);
			result.Y = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[1]);
			// result.z = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[2]);
		}
		break;
		default:
		{
		}
		break;
		}
		break;

	case FbxGeometryElement::eByPolygonVertex:
		switch (pElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result.X = static_cast<float>(pElement->GetDirectArray().GetAt(VtxId).mData[0]);
			result.Y = static_cast<float>(pElement->GetDirectArray().GetAt(VtxId).mData[1]);
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pElement->GetIndexArray().GetAt(VertexCount);
			result.X = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[0]);
			result.Y = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[1]);
		}
		break;
		default:
		{
		}
		break;
		}
		break;
	}

	// _ArrVtx[_Index].TEXCOORD.x = 0.0f;
	// _ArrVtx[_Index].TEXCOORD.y = 0.0f;
	_ArrVtx[_Index].TEXCOORD.X = (float)result.X;
	//// _ArrVtx[_Index].TEXCOORD.y = (float)result.y;
	_ArrVtx[_Index].TEXCOORD.Y = 1.0f - (float)result.Y;
	_ArrVtx[_Index].TEXCOORD.Z = 0.0f;
	_ArrVtx[_Index].TEXCOORD.W = 0.0f;
}

fbxsdk::FbxNode* GameEngineFBXMesh::RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode)
{
	if (nullptr == parentNode)
	{
		return nullptr;
	}
	// �̰� ���� �Ž� Ÿ������ �˷��ִ� ����ü.
	fbxsdk::FbxNodeAttribute* attribute = parentNode->GetNodeAttribute();
	if (nullptr != attribute && attribute->GetAttributeType() == fbxsdk::FbxNodeAttribute::eLODGroup)
	{
		return parentNode;
	}
	return RecursiveFindParentLodGroup(parentNode->GetParent());
}

fbxsdk::FbxNode* GameEngineFBXMesh::FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind)
{
	if (NodeLodGroup->GetChildCount() < LodIndex)
	{
		MsgBoxAssert("�߸��� �ε���");
		return nullptr;
	}
	fbxsdk::FbxNode* childNode = NodeLodGroup->GetChild(LodIndex);
	if (nullptr == childNode)
	{
		return nullptr;
	}
	return RecursiveGetFirstMeshNode(childNode, NodeToFind);
}


fbxsdk::FbxNode* GameEngineFBXMesh::RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind)
{
	if (Node == nullptr)
	{
		return nullptr;
	}

	if (Node->GetMesh() != nullptr)
	{
		return Node;
	}

	for (int ChildIndex = 0; ChildIndex < Node->GetChildCount(); ++ChildIndex)
	{
		fbxsdk::FbxNode* MeshNode = RecursiveGetFirstMeshNode(Node->GetChild(ChildIndex), NodeToFind);
		if (NodeToFind == nullptr)
		{
			if (MeshNode != nullptr)
			{
				return MeshNode;
			}
		}
		else if (MeshNode == NodeToFind)
		{
			return MeshNode;
		}
	}
	return nullptr;
}


bool GameEngineFBXMesh::RetrievePoseFromBindPose(fbxsdk::FbxScene* pScene, const std::vector<fbxsdk::FbxNode*>& NodeArray, fbxsdk::FbxArray<fbxsdk::FbxPose*>& PoseArray)
{
	const int PoseCount = pScene->GetPoseCount();
	for (int PoseIndex = 0; PoseIndex < PoseCount; PoseIndex++)
	{
		fbxsdk::FbxPose* CurrentPose = pScene->GetPose(PoseIndex);

		if (CurrentPose && CurrentPose->IsBindPose())
		{
			std::string PoseName = CurrentPose->GetName();
			fbxsdk::FbxStatus Status;

			for (auto Current : NodeArray)
			{
				std::string CurrentName = Current->GetName();
				fbxsdk::NodeList pMissingAncestors, pMissingDeformers, pMissingDeformersAncestors, pWrongMatrices;

				if (CurrentPose->IsValidBindPoseVerbose(Current, pMissingAncestors, pMissingDeformers, pMissingDeformersAncestors, pWrongMatrices, 0.0001, &Status))
				{
					PoseArray.Add(CurrentPose);
					break;
				}
				else
				{
					for (int i = 0; i < pMissingAncestors.GetCount(); i++)
					{
						fbxsdk::FbxAMatrix mat = pMissingAncestors.GetAt(i)->EvaluateGlobalTransform(FBXSDK_TIME_ZERO);
						CurrentPose->Add(pMissingAncestors.GetAt(i), mat);
					}

					pMissingAncestors.Clear();
					pMissingDeformers.Clear();
					pMissingDeformersAncestors.Clear();
					pWrongMatrices.Clear();

					if (CurrentPose->IsValidBindPose(Current))
					{
						PoseArray.Add(CurrentPose);
						break;
					}
					else
					{
						fbxsdk::FbxNode* ParentNode = Current->GetParent();
						while (ParentNode)
						{
							fbxsdk::FbxNodeAttribute* Attr = ParentNode->GetNodeAttribute();
							if (Attr && Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eNull)
							{
								break;
							}

							ParentNode = ParentNode->GetParent();
						}

						if (ParentNode && CurrentPose->IsValidBindPose(ParentNode))
						{
							PoseArray.Add(CurrentPose);
							break;
						}
						else
						{
							std::string ErrorString = Status.GetErrorString();
							std::string CurrentName = Current->GetName();

							break;
							//MsgAssertString(ErrorString + "_" + CurrentName);
						}
					}
				}
			}
		}
	}

	return (PoseArray.Size() > 0);
}



fbxsdk::FbxNode* GameEngineFBXMesh::GetRootSkeleton(fbxsdk::FbxScene* pScene, fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNode* RootBone = Link;

	while (RootBone && RootBone->GetParent())
	{
		bool bIsBlenderArmatureBone = false;

		fbxsdk::FbxNodeAttribute* Attr = RootBone->GetParent()->GetNodeAttribute();
		if (Attr &&
			(Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh ||
				(Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eNull && !bIsBlenderArmatureBone) ||
				Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eSkeleton) &&
			RootBone->GetParent() != pScene->GetRootNode())
		{
			if (Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh)
			{
				fbxsdk::FbxMesh* Mesh = (fbxsdk::FbxMesh*)Attr;
				if (Mesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin) > 0)
				{
					break;
				}
			}

			RootBone = RootBone->GetParent();
		}
		else
		{
			break;
		}
	}

	return RootBone;
}


bool GameEngineFBXMesh::IsBone(fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNodeAttribute* Attr = Link->GetNodeAttribute();
	if (Attr)
	{
		fbxsdk::FbxNodeAttribute::EType AttrType = Attr->GetAttributeType();
		if (AttrType == fbxsdk::FbxNodeAttribute::eSkeleton ||
			AttrType == fbxsdk::FbxNodeAttribute::eMesh ||
			AttrType == fbxsdk::FbxNodeAttribute::eNull)
		{
			return true;
		}
	}

	return false;
}


bool GameEngineFBXMesh::IsNull(fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNodeAttribute* Attr = Link->GetNodeAttribute();
	if (Attr)
	{
		fbxsdk::FbxNodeAttribute::EType AttrType = Attr->GetAttributeType();
		if (AttrType == fbxsdk::FbxNodeAttribute::eNull)
		{
			return true;
		}
	}
	return false;
}


void GameEngineFBXMesh::RecursiveBuildSkeleton(fbxsdk::FbxNode* Link, std::vector<fbxsdk::FbxNode*>& OutSortedLinks)
{
	if (IsBone(Link))
	{
		if (false == IsNull(Link))
		{
			OutSortedLinks.push_back(Link);
		}
		int ChildIndex;
		for (ChildIndex = 0; ChildIndex < Link->GetChildCount(); ChildIndex++)
		{
			RecursiveBuildSkeleton(Link->GetChild(ChildIndex), OutSortedLinks);
		}
	}
}

void GameEngineFBXMesh::BuildSkeletonSystem(fbxsdk::FbxScene* pScene, std::vector<fbxsdk::FbxCluster*>& ClusterArray, std::vector<fbxsdk::FbxNode*>& OutSortedLinks)
{
	fbxsdk::FbxNode* Link;
	std::vector<fbxsdk::FbxNode*> RootLinks;
	size_t ClusterIndex;
	for (ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
	{
		Link = ClusterArray[ClusterIndex]->GetLink();
		if (Link)
		{
			Link = GetRootSkeleton(pScene, Link);
			size_t LinkIndex;
			for (LinkIndex = 0; LinkIndex < RootLinks.size(); LinkIndex++)
			{
				if (Link == RootLinks[static_cast<int>(LinkIndex)])
				{
					break;
				}
			}

			if (LinkIndex == RootLinks.size())
			{
				RootLinks.push_back(Link);
			}
		}
	}

	for (size_t LinkIndex = 0; LinkIndex < RootLinks.size(); LinkIndex++)
	{
		RecursiveBuildSkeleton(RootLinks[LinkIndex], OutSortedLinks);
	}
}


bool GameEngineFBXMesh::ImportBone()
{
	std::string Path = GetPath().data();

	if (0 != AllBones.size())
	{
		return false;
	}


	size_t meshCount = MeshInfos.size();
	if (0 == meshCount)
	{
		return false;
	}

	// �̰� ��Ű�� ���� ������ �ִ� �༮.
	std::vector<fbxsdk::FbxNode*> MeshNodeArray;

	// ��Ű�� ���� ������ �� ����ִ�. �̰� ������ ���� �Լ�
	std::vector<std::vector<fbxsdk::FbxCluster*>> ClusterArray;
	fbxsdk::FbxNode* Link = nullptr;
	int SkelType = 0;

	ClusterArray.resize(MeshInfos.size());

	// �����Ӵ� n���� Ŭ�����͸� ������ �ְ�
	// Ŭ�����ʹ� ��Ű��(���ؽ��� ����޴� ���� ���� ������ ������ �ִ�.)
	for (size_t meshindex = 0; meshindex < meshCount; ++meshindex)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(meshindex);

		fbxsdk::FbxNode* pNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* FbxMesh = meshInfo.Mesh;

		MeshNodeArray.push_back(pNode);
		const int SkinDeformerCount = FbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);
		for (int DeformerIndex = 0; DeformerIndex < SkinDeformerCount; DeformerIndex++)
		{
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)FbxMesh->GetDeformer(DeformerIndex, fbxsdk::FbxDeformer::eSkin);
			for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ClusterIndex++)
			{
				ClusterArray[meshindex].push_back(Skin->GetCluster(ClusterIndex));
			}
		}
	}

	if (0 == ClusterArray.size())
	{
		return false;
	}

	// ������ Ŭ�����͵鿡 ����Ǿ��ִ� ������ �����ϱ� �����Ѵ�.
	for (size_t Clusterindex = 0; Clusterindex < ClusterArray.size(); Clusterindex++)
	{
		// AllBones.emplace_back();
		if (0 == ClusterArray[Clusterindex].size())
		{
			continue;
		}

		// Ŭ�����Ϳ� ����� ������ ���δ� ����� ���� �ǰ�.
		std::vector<fbxsdk::FbxNode*> SortedLinks;

		fbxsdk::FbxNode* SkeletalMeshNode = nullptr;
		SkeletalMeshNode = MeshNodeArray[Clusterindex];

		fbxsdk::PoseList PoseArray;

		// �ִϸ��̼��� ���ʿ��� ������� �����ϰ� ����ȭ�ϴ� �۾��� ��ģ��.
		if (RetrievePoseFromBindPose(Scene, MeshNodeArray, PoseArray) == false)
		{
			const int PoseCount = Scene->GetPoseCount();
			for (int PoseIndex = PoseCount - 1; PoseIndex >= 0; --PoseIndex)
			{
				fbxsdk::FbxPose* CurrentPose = Scene->GetPose(PoseIndex);

				if (CurrentPose && CurrentPose->IsBindPose())
				{
					Scene->RemovePose(PoseIndex);
					CurrentPose->Destroy();
				}
			}

			Manager->CreateMissingBindPoses(Scene);
			if (RetrievePoseFromBindPose(Scene, MeshNodeArray, PoseArray) == false)
			{
				// MsgAssert("Recreating bind pose failed.");
			}
		}

		BuildSkeletonSystem(Scene, ClusterArray[Clusterindex], SortedLinks);

		std::map<fbxsdk::FbxNode*, std::set<fbxsdk::FbxCluster*>> ClusterSet;

		for (int ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
		{
			for (size_t i = 0; i < ClusterArray[ClusterIndex].size(); i++)
			{
				fbxsdk::FbxCluster* Cluster = ClusterArray[ClusterIndex][i];
				ClusterSet[Cluster->GetLink()].insert(ClusterArray[ClusterIndex][i]);;
			}
		}


		// ���� ���ٴ� �̾߱�.
		if (SortedLinks.size() == 0)
		{
			continue;
		}

		std::map<fbxsdk::FbxString, int> m_NameBoneCheck;
		size_t LinkIndex;

		for (LinkIndex = 0; LinkIndex < SortedLinks.size(); ++LinkIndex)
		{
			Link = SortedLinks[LinkIndex];
			m_NameBoneCheck.insert(std::make_pair(Link->GetName(), 0));

			for (size_t AltLinkIndex = LinkIndex + 1; AltLinkIndex < SortedLinks.size(); ++AltLinkIndex)
			{
				fbxsdk::FbxNode* AltLink = SortedLinks[AltLinkIndex];

				fbxsdk::FbxString tempLinkName = Link->GetName();
				fbxsdk::FbxString tempAltLinkName = AltLink->GetName();

				std::map<fbxsdk::FbxString, int>::iterator FindBoneNameIter = m_NameBoneCheck.find(tempAltLinkName);

				// ���� �̸��� ���� �־
				// ���� ���� ��ġ�� �̸��� �������ش�.
				if (FindBoneNameIter != m_NameBoneCheck.end())
				{
					fbxsdk::FbxString newName = FindBoneNameIter->first;
					newName += "_";
					newName += (++FindBoneNameIter->second);

					// ���࿡ �ٲ�µ��� ��ģ �� �־�
					std::map<fbxsdk::FbxString, int>::iterator RevertIter = m_NameBoneCheck.find(newName);

					while (RevertIter != m_NameBoneCheck.find(newName))
					{
						newName = FindBoneNameIter->first;
						newName += "_";
						newName += (++FindBoneNameIter->second);
						RevertIter = m_NameBoneCheck.find(newName);
					}

					// ��ġ�� �̸��� ��ũ�� �� ���̸��� �ٲٸ�
					// ������ ������ ���� ���õ� ��������
					// �� �̸����� ���ɰ��̹Ƿ� ������ �ʿ䰡 ��������.
					AltLink->SetName(newName.Buffer());
				}
			}
		}


		// ���������� SortedLinks���� ���� �ǹ��ִ� �����鸸 ����ִ�.
		// ���� ������ ���� 
		fbxsdk::FbxArray<fbxsdk::FbxAMatrix> GlobalsPerLink;
		GlobalsPerLink.Grow(static_cast<int>(SortedLinks.size()));
		GlobalsPerLink[0] = ConvertMatrix;

		bool GlobalLinkFoundFlag;
		fbxsdk::FbxVector4 LocalLinkT;
		fbxsdk::FbxQuaternion LocalLinkQ;
		fbxsdk::FbxVector4	LocalLinkS;
		fbxsdk::FbxVector4 GlobalLinkT;
		fbxsdk::FbxQuaternion GlobalLinkQ;
		fbxsdk::FbxVector4	GlobalLinkS;

		bool bAnyLinksNotInBindPose = false;
		std::string LinksWithoutBindPoses;
		int NumberOfRoot = 0;

		int RootIdx = -1;

		if (0 == AllBones.size())
		{
			for (size_t i = 0; i < SortedLinks.size(); i++)
			{
				Bone& tempBoneData = AllBones.emplace_back();
				tempBoneData.Index = static_cast<int>(AllBones.size() - 1);
			}
		}

		for (LinkIndex = 0; LinkIndex < SortedLinks.size(); LinkIndex++)
		{
			Link = SortedLinks[LinkIndex];

			int ParentIndex = -1;
			fbxsdk::FbxNode* LinkParent = Link->GetParent();
			if (LinkIndex)
			{
				for (int ll = 0; ll < LinkIndex; ++ll)
				{
					fbxsdk::FbxNode* Otherlink = SortedLinks[ll];
					if (Otherlink == LinkParent)
					{
						ParentIndex = ll;
						break;
					}
				}
			}

			if (ParentIndex == -1)
			{
				++NumberOfRoot;
				RootIdx = static_cast<int>(LinkIndex);
				//	unreal ������ ��Ʈ�� �ϳ��� ��������� 
				//	����Ƽ������ �������� ����ؼ� ���� �ڵ带 ������
				/*if (NumberOfRoot > 1)
				{
					AMSG(L"�������� ��Ʈ");
				}*/
			}

			GlobalLinkFoundFlag = false;
			if (!SkelType)
			{
				if (PoseArray.GetCount())
				{
					for (int PoseIndex = 0; PoseIndex < PoseArray.GetCount(); PoseIndex++)
					{
						int PoseLinkIndex = PoseArray[PoseIndex]->Find(Link);
						if (PoseLinkIndex >= 0)
						{
							fbxsdk::FbxMatrix NoneAffineMatrix = PoseArray[PoseIndex]->GetMatrix(PoseLinkIndex);
							fbxsdk::FbxAMatrix Matrix = *(fbxsdk::FbxAMatrix*)(double*)&NoneAffineMatrix;
							GlobalsPerLink[static_cast<int>(LinkIndex)] = Matrix;
							GlobalLinkFoundFlag = true;
							break;
						}
					}
				}

				if (!GlobalLinkFoundFlag)
				{

					std::map<fbxsdk::FbxNode*, std::set<fbxsdk::FbxCluster*>>::iterator FindIter = ClusterSet.find(Link);

					if (FindIter != ClusterSet.end())
					{
						for (fbxsdk::FbxCluster* Cluster : FindIter->second)
						{
							Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
							GlobalLinkFoundFlag = true;
							break;
						}
					}

					//for (int ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
					//{
					//	//fbxsdk::FbxCluster* Cluster = ClusterArray[0][ClusterIndex];
					//	//if (Link == Cluster->GetLink())
					//	//{
					//	//	Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
					//	//	GlobalLinkFoundFlag = true;
					//	//	break;
					//	//}

					//	for (size_t i = 0; i < ClusterArray[ClusterIndex].size(); i++)
					//	{
					//		fbxsdk::FbxCluster* Cluster = ClusterArray[ClusterIndex][i];
					//		if (Link == Cluster->GetLink())
					//		{
					//			Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
					//			GlobalLinkFoundFlag = true;
					//			break;
					//		}
					//	}
					//}
				}
			}

			if (!GlobalLinkFoundFlag)
			{
				GlobalsPerLink[static_cast<int>(LinkIndex)] = Link->EvaluateGlobalTransform();
			}

			GlobalsPerLink[static_cast<int>(LinkIndex)] = GlobalsPerLink[static_cast<int>(LinkIndex)];
			if (LinkIndex &&
				-1 != ParentIndex)
			{
				fbxsdk::FbxAMatrix	Matrix;
				Matrix = GlobalsPerLink[static_cast<int>(ParentIndex)].Inverse() * GlobalsPerLink[static_cast<int>(LinkIndex)];
				LocalLinkT = Matrix.GetT();
				LocalLinkQ = Matrix.GetQ();
				LocalLinkS = Matrix.GetS();
				GlobalLinkT = GlobalsPerLink[static_cast<int>(LinkIndex)].GetT();
				GlobalLinkQ = GlobalsPerLink[static_cast<int>(LinkIndex)].GetQ();
				GlobalLinkS = GlobalsPerLink[static_cast<int>(LinkIndex)].GetS();
			}
			else
			{
				GlobalLinkT = LocalLinkT = GlobalsPerLink[static_cast<int>(LinkIndex)].GetT();
				GlobalLinkQ = LocalLinkQ = GlobalsPerLink[static_cast<int>(LinkIndex)].GetQ();
				GlobalLinkS = LocalLinkS = GlobalsPerLink[static_cast<int>(LinkIndex)].GetS();
			}

			Bone& Bone = AllBones[static_cast<int>(LinkIndex)];
			Bone.Name = GameEngineString::ToUpperReturn(Link->GetName());

			if (false == AllFindMap.contains(Link->GetName()))
			{
				AllFindMap[Link->GetName()] = &Bone;
			}

			JointPos& BonePosData = Bone.BonePos;
			fbxsdk::FbxSkeleton* Skeleton = Link->GetSkeleton();
			if (Skeleton)
			{
				BonePosData.Length = (float)Skeleton->LimbLength.Get();
				BonePosData.XSize = (float)Skeleton->Size.Get();
				BonePosData.YSize = (float)Skeleton->Size.Get();
				BonePosData.ZSize = (float)Skeleton->Size.Get();
			}
			else
			{
				BonePosData.Length = 1.;
				BonePosData.XSize = 100.;
				BonePosData.YSize = 100.;
				BonePosData.ZSize = 100.;
			}

			Bone.ParentIndex = ParentIndex;
			Bone.NumChildren = 0;
			for (int ChildIndex = 0; ChildIndex < Link->GetChildCount(); ChildIndex++)
			{
				fbxsdk::FbxNode* Child = Link->GetChild(ChildIndex);
				if (IsBone(Child))
				{
					Bone.NumChildren++;
				}
			}

			BonePosData.SetTranslation(LocalLinkT);
			BonePosData.SetRotation(LocalLinkQ);
			BonePosData.SetScale(LocalLinkS);
			BonePosData.SetGlobalTranslation(GlobalLinkT);
			BonePosData.SetGlobalRotation(GlobalLinkQ);
			BonePosData.SetGlobalScale(GlobalLinkS);
			BonePosData.BuildMatrix();
		}





	}

	for (size_t i = 0; i < AllBones.size(); i++)
	{
		if (AllFindMap.end() == AllFindMap.find(AllBones[i].Name))
		{
			AllFindMap.insert(std::make_pair(AllBones[i].Name, &AllBones[i]));
			continue;
		}

		std::multimap<std::string, Bone*>::iterator it, itlow, itup;

		itlow = AllFindMap.lower_bound(AllBones[i].Name);  // itlow points to b
		itup = AllFindMap.upper_bound(AllBones[i].Name);   // itup points to e (not d)

		int Count = 0;
		for (it = itlow; it != itup; ++it)
		{
			++Count;
		}

		std::string Name = AllBones[i].Name + std::to_string(Count);
		AllFindMap.insert(std::make_pair(GameEngineString::ToUpperReturn(Name), &AllBones[i]));
	}


	LoadSkinAndCluster();

	return true;
}

void GameEngineFBXMesh::ImportCluster()
{
	size_t meshCount = MeshInfos.size();
	if (0 == meshCount)
	{
		return;
	}

	// �׳� �̶� �ٽ�����.
	for (size_t n = 0; n < meshCount; ++n)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(n);
		fbxsdk::FbxNode* pNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* FbxMesh = meshInfo.Mesh;
		const int SkinDeformerCount = FbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);

		std::vector<FbxClusterData>& vecClusterData = ClusterData.emplace_back();

		// ?????????????????
		// ������ �������� �ٲ��ڵ�� ���� ���̵� ����Ʈ�� ����ų���𸨴ϴ�.
		if (0 == SkinDeformerCount)
		{
			continue;
		}

		for (int DeformerIndex = 0; DeformerIndex < SkinDeformerCount; DeformerIndex++)
		{
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)FbxMesh->GetDeformer(DeformerIndex, fbxsdk::FbxDeformer::eSkin);
			for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ClusterIndex++)
			{
				vecClusterData.push_back(FbxClusterData());
				FbxClusterData& clusterData = vecClusterData[vecClusterData.size() - 1];
				clusterData.Cluster = Skin->GetCluster(ClusterIndex);
				clusterData.Mesh = FbxMesh;
				clusterData.LinkName = clusterData.Cluster->GetLink()->GetName();
			}
		}
	}
}

Bone* GameEngineFBXMesh::FindBoneToIndex(int _Index)
{
	if (0 == AllBones.size())
	{
		ImportBone();
	}

	return &AllBones[_Index];
}

Bone* GameEngineFBXMesh::FindBone(std::string _Name)
{
	if (0 == AllBones.size())
	{
		ImportBone();
	}

	if (0 == AllFindMap.size())
	{
		MsgBoxAssert("���� ã�� �۾��� ���� ���� �Ž��Դϴ�");
	}

	if (AllFindMap.end() == AllFindMap.find(_Name))
	{
		return nullptr;
	}

	return AllFindMap[_Name];

}

void GameEngineFBXMesh::LoadSkinAndCluster()
{
	ImportCluster();

	for (int i = 0; i < RenderUnitInfos.size(); ++i)
	{
		FbxRenderUnitInfo& RenderInfo = RenderUnitInfos[i];
		std::vector<FbxClusterData>& ClusterInfo = ClusterData[i];

		// Ŭ�����ʹ� ����ġ ������ �ε��� ������ ������ �ִµ�
		// Ŭ�����͸� ���ؼ� ������ ��������
		LoadAnimationVertexData(&RenderInfo, ClusterInfo);

		// ��¥ ����ġ�� ����Ѵ�.
		CalAnimationVertexData(RenderInfo);
	}
}

void GameEngineFBXMesh::CalAnimationVertexData(FbxRenderUnitInfo& _DrawSet)
{
	for (auto& _WISet : _DrawSet.MapWI)
	{
		std::vector<GameEngineVertex>* Ptr = &_DrawSet.Vertexs;

		if (nullptr == Ptr)
		{
			MsgBoxAssert("���ؽ� �����Ϳ� ������ ����ġ �����Ͱ� ��Ī���� �ʽ��ϴ�.");
		}

		std::vector<GameEngineVertex>& VertexData = *Ptr;

		for (auto& _WI : _WISet.second)
		{
			double dWeight = 0.0;
			for (int n = 0; n < _WI.second.size(); ++n)
			{
				dWeight += _WI.second[n].Weight;
			}

			for (int n = 0; n < _WI.second.size(); ++n)
			{
				_WI.second[n].Weight /= dWeight;
			}

			if (_WI.second.size() > 4)
			{
				std::sort(_WI.second.begin(), _WI.second.end(),
					[](const FbxExIW& _Left, const FbxExIW& _Right) {
						return _Left.Weight > _Right.Weight;
					}
				);

				double dInterPolate = 0.0;

				std::vector<FbxExIW>::iterator IterErase = _WI.second.begin() + 4;
				for (; IterErase != _WI.second.end(); ++IterErase)
				{
					dInterPolate += IterErase->Weight;
				}
				IterErase = _WI.second.begin() + 4;

				_WI.second.erase(IterErase, _WI.second.end());
				_WI.second[0].Weight += dInterPolate;
			};

			float Weight[4] = { 0.0f };
			int Index[4] = { 0 };

			for (size_t i = 0; i < _WI.second.size(); i++)
			{
				Weight[i] = (float)_WI.second[i].Weight;
				Index[i] = _WI.second[i].Index;
			}

			memcpy_s(VertexData[_WI.first].WEIGHT.Arr1D, sizeof(float4), Weight, sizeof(float4));
			memcpy_s(VertexData[_WI.first].BLENDINDICES, sizeof(float4), Index, sizeof(float4));
		}
	}
}


void GameEngineFBXMesh::DrawSetWeightAndIndexSetting(FbxRenderUnitInfo* _DrawSet, fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxCluster* _Cluster, int _BoneIndex)
{
	if (nullptr == _DrawSet)
	{
		return;
	}

	int iIndexCount = _Cluster->GetControlPointIndicesCount();

	for (size_t i = 0; i < iIndexCount; i++)
	{
		FbxExIW IW;
		IW.Index = _BoneIndex;

		IW.Weight = _Cluster->GetControlPointWeights()[i];
		int ControlPointIndices = _Cluster->GetControlPointIndices()[i];

		_DrawSet->MapWI[_Mesh][ControlPointIndices].push_back(IW);
	}
}

void GameEngineFBXMesh::LoadAnimationVertexData(FbxRenderUnitInfo* _MeshSet, const std::vector<FbxClusterData>& vecClusterData)
{
	for (auto& clusterData : vecClusterData)
	{
		if (nullptr == clusterData.Cluster->GetLink())
		{
			continue;
		}

		std::string StrBoneName = clusterData.LinkName;
		Bone* pBone = FindBone(StrBoneName);
		if (nullptr == pBone)
		{
			continue;
		}

		DrawSetWeightAndIndexSetting(_MeshSet, clusterData.Mesh, clusterData.Cluster, pBone->Index);
	}
}


void GameEngineFBXMesh::MeshNodeCheck()
{
	int geometryCount = Scene->GetGeometryCount();
	for (int i = 0; i < geometryCount; i++)
	{
		fbxsdk::FbxGeometry* geoMetry = Scene->GetGeometry(i);
		fbxsdk::FbxNode* geoMetryNode = geoMetry->GetNode();


		if (nullptr == geoMetry)
		{
			continue;
		}

		// �̾Ƴ� �ֵ��߿��� �� Ÿ����
		// if (geoMetry->GetAttributeType() != fbxsdk::FbxNodeAttribute::eSkeleton)

		if (geoMetry->GetAttributeType() != fbxsdk::FbxNodeAttribute::eMesh)
		{
			continue;
		}

		// �̷��� 
		FbxExMeshInfo& Info = MeshInfos.emplace_back();


		if (geoMetry->GetName()[0] != '\0')
		{
			Info.Name = GameEngineString::AnsiToUTF8(geoMetry->GetName());
		}
		else {
			Info.Name = nullptr != geoMetryNode ? GameEngineString::AnsiToUTF8(geoMetryNode->GetName()) : "None";
		}

		Info.Mesh = reinterpret_cast<fbxsdk::FbxMesh*>(geoMetry);

		Info.bTriangulated = Info.Mesh->IsTriangleMesh();
		Info.MaterialNum = geoMetryNode ? geoMetryNode->GetMaterialCount() : 0;
		Info.FaceNum = Info.Mesh->GetPolygonCount();
		Info.VertexNum = Info.Mesh->GetControlPointsCount();
		Info.UniqueId = Info.Mesh->GetUniqueID();

		// ���� ���� ����.
		// LodGroup�� �����ϴ� �ڵ�
		Info.LODGroupName = "";

		if (nullptr != geoMetryNode)
		{
			fbxsdk::FbxNode* ParentNode = RecursiveFindParentLodGroup(geoMetryNode->GetParent());
			if (ParentNode != nullptr && ParentNode->GetNodeAttribute()
				&& ParentNode->GetNodeAttribute()->GetAttributeType() == fbxsdk::FbxNodeAttribute::eLODGroup)
			{
				Info.LODGroupName = GameEngineString::AnsiToUTF8(ParentNode->GetName());
				Info.bIsLodGroup = true;
				for (int LODIndex = 0; LODIndex < ParentNode->GetChildCount(); LODIndex++)
				{
					fbxsdk::FbxNode* MeshNode = FindLODGroupNode(ParentNode, LODIndex, geoMetryNode);
					if (geoMetryNode == MeshNode)
					{
						Info.LodLevel = LODIndex;
						break;
					}
				}
			}
		}

		// �����Ӹ� �����մϴ�.
		// �����Ӵ� ���� �Ž��� �̾��ִ� ����� �մϴ�.
		// ������ ī��Ʈ�� 0�� �ƴ϶�°�.
		if (Info.Mesh->GetDeformerCount(FbxDeformer::eSkin) > 0)
		{
			Info.bIsSkeletalMesh = true;
			Info.MorphNum = Info.Mesh->GetShapeCount();
			// �Ž��� ��Ű��
			// �Ž��� �������� ���� �����ϱ� ���� ���ؽ��� ����ġ���� ������ ������ �ִ� �༮.
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)Info.Mesh->GetDeformer(0, FbxDeformer::eSkin);
			int ClusterCount = Skin->GetClusterCount();
			fbxsdk::FbxNode* Link = NULL;
			for (int ClusterId = 0; ClusterId < ClusterCount; ++ClusterId)
			{
				fbxsdk::FbxCluster* Cluster = Skin->GetCluster(ClusterId);
				// ���� ����� 
				Link = Cluster->GetLink();
				while (Link && Link->GetParent() && Link->GetParent()->GetSkeleton())
				{
					Link = Link->GetParent();
				}

				if (Link != NULL)
				{
					break;
				}
			}

			// Info.SkeletonRoot = nullptr != Link ? GameEngineString::UTF8ToAnsiReturn(Link->GetName()) : "None";

			// ���̷����� �����Ѵٴ°� ���ϴ� ��.
			Info.SkeletonRoot = nullptr != Link ? Link->GetName() : "None";
			Info.SkeletonElemNum = nullptr != Link ? Link->GetChildCount(true) : 0;

			//if (nullptr != Link)
			//{
			//	fbxsdk::FbxTimeSpan AnimTimeSpan(fbxsdk::FBXSDK_TIME_INFINITE, fbxsdk::FBXSDK_TIME_MINUS_INFINITE);
			//	Link->GetAnimationInterval(AnimTimeSpan);
			//	GlobalTimeSpan.UnionAssignment(AnimTimeSpan);
			//}
		}
		else
		{
			Info.bIsSkeletalMesh = false;
			Info.SkeletonRoot = "";
		}
	}
}