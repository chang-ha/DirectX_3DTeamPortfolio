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
	// �ȼ����̴����� �׳� �������� �����ָ� �Ǵ� ����.
	float4			 DifColor;
	float4			 AmbColor; // ��
	float4			 SpcColor; // ��
	float4			 EmvColor; // ��
	float			 SpecularPower;		// ���� ����
	float			 TransparencyFactor;	// ���� ����
	float			 Shininess;			// ���� ����
	std::string DifTexturePath;	// �ؽ�ó��� 
	std::string NorTexturePath; // �ؽ�ó���
	std::string SpcTexturePath; // �ؽ�ó���

	std::string DifTextureName;	// �ؽ�ó��� 
	std::string NorTextureName; // �ؽ�ó���
	std::string SpcTextureName; // �ؽ�ó���

public:
	void Write(GameEngineSerializer& _File) override
	{
		_File << Name;
		_File << AmbColor; // ��
		_File << SpcColor; // ��
		_File << EmvColor; // ��
		_File << SpecularPower;
		_File << TransparencyFactor;
		_File << Shininess;
		_File << DifTexturePath;	// �ؽ�ó
		_File << NorTexturePath; // �ؽ�ó
		_File << SpcTexturePath; // �ؽ�ó
		_File << DifTextureName;	// �ؽ�ó
		_File << NorTextureName; // �ؽ�ó
		_File << SpcTextureName; // �ؽ�ó
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> Name;
		_File >> AmbColor; // ��
		_File >> SpcColor; // ��
		_File >> EmvColor; // ��
		_File >> SpecularPower;
		_File >> TransparencyFactor;
		_File >> Shininess;
		_File >> DifTexturePath;	// �ؽ�ó
		_File >> NorTexturePath; // �ؽ�ó
		_File >> SpcTexturePath; // �ؽ�ó
		_File >> DifTextureName;	// �ؽ�ó
		_File >> NorTextureName; // �ؽ�ó
		_File >> SpcTextureName; // �ؽ�ó
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

	//       �ڽ��� ������ 
	//       ��� �ִ� node
	//       �� mesh
	//       �̸Ž�����  �������� ���´ٶ�� ���� �˴ϴ�.
	//       ���� ���鿡 ���� ��� �����̰�.
	//       ���� �ʿ��ϴٸ� �� ���� �Ҽ��� �ִ�.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       �ִϸ��̼��� �ִٸ� ä���� �����̴ϴ�.
	std::map<FbxMesh*, std::map<int, std::vector<FbxExIW>>> MapWI;

	// ���ؽ� ������ ������ 
	std::vector<GameEngineVertex> Vertexs;

	// �Ӹ�
	std::vector<std::vector<unsigned int>> Indexs;

	std::vector<FbxExMaterialSettingData> MaterialData;


	std::shared_ptr<GameEngineVertexBuffer> VertexBuffer;
	// ������ 1������ �װ� �����ϴ� ����� n����
	// �̷��� ����� ����� ����̶�� �Ѵ�.
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

		//// ����� ������
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
	// ������Ʈ�� ����
	fbxsdk::FbxMesh* Mesh;
	// �� �Ž��� ���� �ٽ� ����� �̸��� ����.
	std::string Name;
	bool bTriangulated;
	unsigned __int64 UniqueId;
	// �ﰢ���� ��ΰ�
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

// ���� :
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

	//                                                ���ؽ�����        �ε�������
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

