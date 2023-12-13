#pragma once

#include <GameEngineCore/ThirdParty/FBX/inc/fbxsdk.h>

#pragma comment(lib, "zlib-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "libfbxsdk-md.lib")

struct FBXNodeInfo
{
public:
	std::string_view Name;
	fbxsdk::FbxNode* Node;
};


// ���� :
class GameEngineFBX
{
public:
	// constrcuter destructer
	GameEngineFBX();
	~GameEngineFBX();

	// delete Function
	GameEngineFBX(const GameEngineFBX& _Other) = delete;
	GameEngineFBX(GameEngineFBX&& _Other) noexcept = delete;
	GameEngineFBX& operator=(const GameEngineFBX& _Other) = delete;
	GameEngineFBX& operator=(GameEngineFBX&& _Other) noexcept = delete;

	void SetPath(std::string_view _Path)
	{
		Path = _Path;
	}

	std::string GetPath()
	{
		return Path;
	}

	std::vector<FBXNodeInfo> CheckAllNode();
	void RecursiveAllNode(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/);


	float4 FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector);

protected:
	fbxsdk::FbxManager* Manager = nullptr;

	fbxsdk::FbxIOSettings* IOSetting = nullptr;
	fbxsdk::FbxImporter* Importer = nullptr;
	fbxsdk::FbxScene* Scene = nullptr;
	fbxsdk::FbxNode* RootNode = nullptr;

	fbxsdk::FbxAMatrix ConvertMatrix; // ���� �ٲ� ������ ��ȯ��Ű�� ���� ���
	fbxsdk::FbxAMatrix JointMatrix; // ���� ��� ����
	fbxsdk::FbxVector4 AxisVector; // �Ž��� �⺻���� �ٶ󺸴� ���⺤��

	void FBXInit(std::string_view _Path);
	bool FBXSystemInitialize(std::string_view _Path);
	bool FBXConvertScene();

private:
	std::string Path;
};

