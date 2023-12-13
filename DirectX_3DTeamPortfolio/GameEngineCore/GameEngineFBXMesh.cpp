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

	FBXInit(GetPath());
	MeshLoad();

	
}

std::shared_ptr<GameEngineMesh> GameEngineFBXMesh::GetGameEngineMesh(int _MeshIndex, int _SubSetIndex)
{
	if (RenderUnitInfos.size() <= _MeshIndex)
	{
		MsgBoxAssert("존재하지 않는 랜더 유니트인포로 매쉬를 만들려고 했습니다.");
	}

	FbxRenderUnitInfo& Unit = RenderUnitInfos[_MeshIndex];

	if (nullptr == Unit.VertexBuffer)
	{
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Create(Unit.Vertexs);

		if (nullptr == VertexBuffer)
		{
			MsgBoxAssert("FBX 버텍스 버퍼 생성 실패.");
		}

		Unit.VertexBuffer = VertexBuffer;
	}

	if (Unit.Indexs.size() <= _SubSetIndex)
	{
		MsgBoxAssert("존재하지 않는 서브셋을 만들려고 했습니다, 인덱스 버퍼를 생성할수 없습니다.");
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
			MsgBoxAssert("존재하지 않는 서브셋을 만들려고 했습니다, 인덱스 버퍼를 생성할수 없습니다.");
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
	
	// 텍스처도 로드해야 한다.
	return Unit.Meshs[_SubSetIndex];
}

void GameEngineFBXMesh::MeshLoad()
{
	std::string Path = GetPath().data();
	MeshNodeCheck();
	VertexBufferCheck();
	//ImportBone();

	//AllBones; // 본정보체
	//AllFindMap;
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

		// ?2개면

		for (int i = 0; i < MtrlCount; i++)
		{
			fbxsdk::FbxSurfaceMaterial* pMtrl = _Node->GetMaterial(i);

			if (nullptr == pMtrl)
			{
				MsgBoxAssert("if (nullptr == pMtrl) 메테리얼 정보가 존재하지 않습니다");
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
		// MsgAssert("매쉬는 존재하지만 재질은 존재하지 않습니다.");
	}

}


void GameEngineFBXMesh::LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementNormalCount();

	if (0 == iCount)
	{
		MsgBoxAssert("GetElementNormalCount가 여러개 입니다.");
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
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
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
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
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
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
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

		// 버텍스 개수에요.
		int controlPointsCount = pMesh->GetControlPointsCount();
		VtxData.resize(controlPointsCount);

		fbxsdk::FbxVector4* pControlPoints = pMesh->GetControlPoints();

		fbxsdk::FbxAMatrix meshMatrix = ComputeTotalMatrix(pMeshNode);

		if (false == meshInfo.bIsSkeletalMesh)
		{
			// 애니메메이션일 경우에는 애니메이션의 특수한 본정보를 기반으로 버텍스를 전환해서 받아야 하는데.
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

		// 메테리얼 
		fbxsdk::FbxGeometryElementMaterial* pGeometryElementMaterial = pMesh->GetElementMaterial();

		// 머티리얼이 4개라면 서브셋도 4개일 테니까.
		int materialCount = pMeshNode->GetMaterialCount();
		IdxData.resize(materialCount);

		// 노말과 
		// UV등등을 얻어옵니다.
		// 노말 UV등등은 매핑 방식이 다를수 있어서 아래와 같은 방법으로 정점과는 분리해서 따로 얻어와야 합니다.
		UINT VtxId = 0;
		int nPolygonCount = pMesh->GetPolygonCount();

		for (int PolygonIndex = 0; PolygonIndex < nPolygonCount; ++PolygonIndex)
		{
			int PolygonSize = pMesh->GetPolygonSize(PolygonIndex);

			if (3 != PolygonSize)
			{
				MsgBoxAssert("삼각형이 아닌 면이 발견됬습니다.");
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

			// 인덱스정보는 다래와 같이 얻어오면 되고.
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
	// 이게 무슨 매쉬 타입인지 알려주는 정보체.
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
		MsgBoxAssert("잘못된 인덱스");
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

		// 뽑아낸 애들중에서 그 타입이
		// if (geoMetry->GetAttributeType() != fbxsdk::FbxNodeAttribute::eSkeleton)

		if (geoMetry->GetAttributeType() != fbxsdk::FbxNodeAttribute::eMesh)
		{
			continue;
		}

		// 이렇게 
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

		// 보통 쓸모가 없다.
		// LodGroup을 조사하는 코드
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

		// 디포머를 조사합니다.
		// 디포머는 본과 매쉬를 이어주는 기능을 합니다.
		// 디포머 카운트가 0이 아니라는건.
		if (Info.Mesh->GetDeformerCount(FbxDeformer::eSkin) > 0)
		{
			Info.bIsSkeletalMesh = true;
			Info.MorphNum = Info.Mesh->GetShapeCount();
			// 매쉬의 스키닝
			// 매쉬가 끊어지는 것을 방지하기 위한 버텍스의 가중치등의 정보를 가지고 있는 녀석.
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)Info.Mesh->GetDeformer(0, FbxDeformer::eSkin);
			int ClusterCount = Skin->GetClusterCount();
			fbxsdk::FbxNode* Link = NULL;
			for (int ClusterId = 0; ClusterId < ClusterCount; ++ClusterId)
			{
				fbxsdk::FbxCluster* Cluster = Skin->GetCluster(ClusterId);
				// 서로 연결된 
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

			// 스켈레톤이 존재한다는걸 말하는 것.
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