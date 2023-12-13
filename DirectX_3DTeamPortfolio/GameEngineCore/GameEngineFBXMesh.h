#pragma once
#include "GameEngineResources.h"
#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineFBX.h"


class FbxExIW
{
public:
	int Index;
	double Weight;
};


class FbxExMaterialSettingData : public GameEngineSerializObject
{
public:
	std::string Name;
	// 픽셀쉐이더에서 그냥 최종색상에 곱해주면 되는 색상.
	float4			 DifColor;
	float4			 AmbColor; // 빛
	float4			 SpcColor; // 빛
	float4			 EmvColor; // 빛
	float			 SpecularPower;		// 빛의 강도
	float			 TransparencyFactor;	// 빛의 강도
	float			 Shininess;			// 빛의 강도
	std::string DifTexturePath;	// 텍스처경로 
	std::string NorTexturePath; // 텍스처경로
	std::string SpcTexturePath; // 텍스처경로

	std::string DifTextureName;	// 텍스처경로 
	std::string NorTextureName; // 텍스처경로
	std::string SpcTextureName; // 텍스처경로

public:
	void Write(GameEngineSerializer& _File) override
	{
		_File << Name;
		_File << AmbColor; // 빛
		_File << SpcColor; // 빛
		_File << EmvColor; // 빛
		_File << SpecularPower;
		_File << TransparencyFactor;
		_File << Shininess;
		_File << DifTexturePath;	// 텍스처
		_File << NorTexturePath; // 텍스처
		_File << SpcTexturePath; // 텍스처
		_File << DifTextureName;	// 텍스처
		_File << NorTextureName; // 텍스처
		_File << SpcTextureName; // 텍스처
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> Name;
		_File >> AmbColor; // 빛
		_File >> SpcColor; // 빛
		_File >> EmvColor; // 빛
		_File >> SpecularPower;
		_File >> TransparencyFactor;
		_File >> Shininess;
		_File >> DifTexturePath;	// 텍스처
		_File >> NorTexturePath; // 텍스처
		_File >> SpcTexturePath; // 텍스처
		_File >> DifTextureName;	// 텍스처
		_File >> NorTextureName; // 텍스처
		_File >> SpcTextureName; // 텍스처
	}


public:
	FbxExMaterialSettingData() {}
	~FbxExMaterialSettingData() {}
};


struct FbxRenderUnitInfo : public GameEngineSerializObject
{
public:
	int VectorIndex;
	int IsLodLv;
	bool IsLod;

	float4 MinBoundBox;
	float4 MaxBoundBox;
	float4 BoundScaleBox;

	//       자신의 정보를 
	//       들고 있던 node
	//       의 mesh
	//       이매쉬에서  이점들을 빼냈다라고 보면 됩니다.
	//       얻어온 점들에 대한 모든 정보이고.
	//       만약 필요하다면 더 얻어야 할수도 있다.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       애니메이션이 있다면 채워져 있을겁니다.
	std::map<FbxMesh*, std::map<int, std::vector<FbxExIW>>> MapWI;

	// 버텍스 정보는 무조건 
	std::vector<GameEngineVertex> Vertexs;

	// 머리
	std::vector<std::vector<unsigned int>> Indexs;

	std::vector<FbxExMaterialSettingData> MaterialData;


	std::shared_ptr<GameEngineVertexBuffer> VertexBuffer;
	// 정점은 1개지만 그걸 연결하는 방식이 n개야
	// 이러한 방식을 서브셋 방식이라고 한다.
	std::vector< std::shared_ptr<GameEngineIndexBuffer>> IndexBuffers;

	std::vector<std::shared_ptr<class GameEngineMesh>> Meshs;

	FbxRenderUnitInfo() :
		IsLod(false),
		IsLodLv(-1),
		VertexBuffer(nullptr)
	{
	}

	~FbxRenderUnitInfo()
	{
		//for (size_t i = 0; i < GameEngineVertexBuffers.size(); i++)
		//{
		//	if (nullptr == GameEngineVertexBuffers[i])
		//	{
		//		continue;
		//	}
		//	delete GameEngineVertexBuffers[i];
		//	GameEngineVertexBuffers[i] = nullptr;
		//}

		//// 서브셋 때문에
		//for (size_t i = 0; i < GameEngineIndexBuffers.size(); i++)
		//{
		//	for (size_t j = 0; j < GameEngineIndexBuffers[i].size(); j++)
		//	{
		//		if (nullptr == GameEngineIndexBuffers[i][j])
		//		{
		//			continue;
		//		}
		//		delete GameEngineIndexBuffers[i][j];
		//		GameEngineIndexBuffers[i][j] = nullptr;
		//	}
		//}

	}

	void Write(GameEngineSerializer& _File) override
	{
		_File << VectorIndex;
		_File << IsLodLv;
		_File << IsLod;
		_File << MinBoundBox;
		_File << MaxBoundBox;
		_File << BoundScaleBox;
		_File << Vertexs;
		_File << Indexs;
		_File << MaterialData;

	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> VectorIndex;
		_File >> IsLodLv;
		_File >> IsLod;
		_File >> MinBoundBox;
		_File >> MaxBoundBox;
		_File >> BoundScaleBox;
		_File >> Vertexs;
		_File >> Indexs;
		_File >> MaterialData;

	}
};

struct FbxExMeshInfo : public GameEngineSerializObject
{
	// 지오메트리 정보
	fbxsdk::FbxMesh* Mesh;
	// 이 매쉬를 가진 핵심 노드의 이름이 뭔가.
	std::string Name;
	bool bTriangulated;
	unsigned __int64 UniqueId;
	// 삼각형이 몇개인가
	int FaceNum;
	int VertexNum;
	int MaterialNum;
	bool bIsSkeletalMesh;
	std::string SkeletonRoot;
	int SkeletonElemNum;
	bool bIsLodGroup;
	std::string LODGroupName;
	int LodLevel;
	int MorphNum;

	FbxExMeshInfo()
	{
		Name;
		UniqueId = 0;
		FaceNum = 0;
		VertexNum = 0;
		bTriangulated = false;
		MaterialNum = 0;
		bIsSkeletalMesh = false;
		SkeletonRoot;
		SkeletonElemNum = 0;
		bIsLodGroup = false;
		LODGroupName;
		LodLevel = -1;
		MorphNum = 0;
	}

	void Write(GameEngineSerializer& _File) override
	{
		_File << Name;
		_File << bTriangulated;
		_File << UniqueId;
		_File << FaceNum;
		_File << VertexNum;
		_File << MaterialNum;
		_File << bIsSkeletalMesh;
		_File << SkeletonRoot;
		_File << SkeletonElemNum;
		_File << bIsLodGroup;
		_File << LODGroupName;
		_File << LodLevel;
		_File << MorphNum;
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> Name;
		_File >> bTriangulated;
		_File >> UniqueId;
		_File >> FaceNum;
		_File >> VertexNum;
		_File >> MaterialNum;
		_File >> bIsSkeletalMesh;
		_File >> SkeletonRoot;
		_File >> SkeletonElemNum;
		_File >> bIsLodGroup;
		_File >> LODGroupName;
		_File >> LodLevel;
		_File >> MorphNum;
	}
};

// 설명 :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineResources<GameEngineFBXMesh>
{
public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFBXMesh> Load(std::string_view _Path)
	{
		GameEnginePath FilePath(_Path);
		return Load(_Path, FilePath.GetFileName());
	}

	static std::shared_ptr<GameEngineFBXMesh> Load(std::string_view& _Path, std::string_view _Name);
	
	void Initialize();
	
	int GetRenderUnitCount()
	{
		return static_cast<int>(RenderUnitInfos.size());
	}

	int GetSubSetCount(size_t _IndexBufferIndex)
	{
		return static_cast<int>(RenderUnitInfos[_IndexBufferIndex].Indexs.size());
	}

	//                                                버텍스버퍼        인덱스버퍼
	std::shared_ptr<class GameEngineMesh> GetGameEngineMesh(int _MeshIndex, int _SubSetIndex);

protected:

private:
	std::vector<FbxExMeshInfo> MeshInfos;
	std::vector<FbxRenderUnitInfo> RenderUnitInfos;

	void LoadMesh(std::string_view& _Path, std::string_view _Name);
	void MeshLoad();
	void MeshNodeCheck();
	void VertexBufferCheck();

	fbxsdk::FbxNode* RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind);
	fbxsdk::FbxNode* FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind);
	fbxsdk::FbxNode* RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode);
	fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* Node);
	bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);

	void FbxRenderUnitInfoMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnitInfo* _RenderData);
	std::string MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);

	void LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadUV(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int VertexCount, int _Index);
};

