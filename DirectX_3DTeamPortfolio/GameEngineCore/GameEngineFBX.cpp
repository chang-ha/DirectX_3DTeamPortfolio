#include "PreCompile.h"
#include "GameEngineFBX.h"

float4 GameEngineFBX::FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseVector.mData[0];
	Vec.Arr1D[1] = (float)_BaseVector.mData[1];
	Vec.Arr1D[2] = -(float)_BaseVector.mData[2];
	Vec.Arr1D[3] = (float)_BaseVector.mData[3];
	return Vec;
}

GameEngineFBX::GameEngineFBX() 
{
}

GameEngineFBX::~GameEngineFBX() 
{
	if (nullptr != Scene)
	{
		Scene->Destroy();
		Scene = nullptr;
	}
	if (nullptr != Importer)
	{
		Importer->Destroy();
		Importer = nullptr;
	}
	if (nullptr != IOSetting)
	{
		IOSetting->Destroy();
		IOSetting = nullptr;
	}
	if (nullptr != Manager)
	{
		Manager->Destroy();
		Manager = nullptr;
	}
}

void GameEngineFBX::FBXInit(std::string_view _Path)
{
	if (false == FBXSystemInitialize(_Path))
	{
		MsgBoxAssert("FBX �ý��� �̴ϼȶ���� �����߽��ϴ�");
	}

	FBXConvertScene();

	return;
}

std::vector<FBXNodeInfo> GameEngineFBX::CheckAllNode()
{
	std::vector<FBXNodeInfo> AllNode;

	RecursiveAllNode(RootNode, [&](fbxsdk::FbxNode* _Node)
		{
			FBXNodeInfo& _NodeInfo = AllNode.emplace_back();

			_NodeInfo.Name = _Node->GetName();
			_NodeInfo.Node = _Node;
		});

	return AllNode;

}

void GameEngineFBX::RecursiveAllNode(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/)
{
	if (nullptr != _Function)
	{
		_Function(_Node);
	}

	fbxsdk::FbxNodeAttribute* Info = _Node->GetNodeAttribute();

	if (nullptr != Info)
	{
		fbxsdk::FbxNodeAttribute::EType Type = Info->GetAttributeType();
	}


	int Count = _Node->GetChildCount();

	for (int i = 0; i < Count; i++)
	{
		fbxsdk::FbxNode* Node = _Node->GetChild(i);
		RecursiveAllNode(Node, _Function);
	}

}

bool GameEngineFBX::FBXSystemInitialize(std::string_view _Path)
{
	// fbx���� ����ϴ� �⺻����� �����ϴ� �������̽�
	Manager = fbxsdk::FbxManager::Create();

	if (nullptr == Manager)
	{
		MsgBoxAssert("FBX �Ŵ��� ������ �����߽��ϴ�.");
		return false;
	}

	// �˰�ġ�°� �ƴմϴ�
	// ���� �ڵ忡 �̷��� �������Ѵٰ� �ؼ� ���� �׷��� �Ѱͻ�
	IOSetting = fbxsdk::FbxIOSettings::Create(Manager, IOSROOT);

	Importer = fbxsdk::FbxImporter::Create(Manager, "");

	if (false ==
		Importer->Initialize(GameEngineString::AnsiToUTF8(_Path).c_str(), -1, IOSetting))
	{
		Importer->Destroy();
		IOSetting->Destroy();
		MsgBoxAssert("FBX �ε� �̴ϼȶ����� ����.");
		return false;
	}

	// ����ִ� scene�� �����
	Scene = fbxsdk::FbxScene::Create(Manager, "");

	if (nullptr == Scene)
	{
		MsgBoxAssert("FBX ������ ����.");
		return false;
	}

	// ����ִ� Scene�� �⺻���� ������ ��� ä��ϴ�.
	if (false == Importer->Import(Scene))
	{
		MsgBoxAssert("FBX ����Ʈ ����.");
		return false;
	}

	return true;

	// Scene->GetRootNode()
}

bool GameEngineFBX::FBXConvertScene()
{
	AxisVector = { 0.0f, 0.0f, 0.0f, 1.0f };

	// ���� �ٽ� ������ �Ǵµ�.
	// �������� �ٲܷ��� ����� �ڵ�
	fbxsdk::FbxAxisSystem::EFrontVector FrontVector = (fbxsdk::FbxAxisSystem::EFrontVector)-fbxsdk::FbxAxisSystem::eParityOdd;
	fbxsdk::FbxAxisSystem::EUpVector UpVector = fbxsdk::FbxAxisSystem::eYAxis;
	fbxsdk::FbxAxisSystem::ECoordSystem CooreSystem = fbxsdk::FbxAxisSystem::ECoordSystem::eRightHanded;

	// ���̷�Ʈ ��
	fbxsdk::FbxAxisSystem EngineAxisSystem(UpVector, FrontVector, CooreSystem);

	// �Ž��� ������
	fbxsdk::FbxAxisSystem SourceAxisSystem = Scene->GetGlobalSettings().GetAxisSystem();

	if (SourceAxisSystem != EngineAxisSystem)
	{
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(Scene);

		// scene ��ü�� �� ������ ������.
		EngineAxisSystem.ConvertScene(Scene);

		fbxsdk::FbxAMatrix SourceMatrix;
		SourceAxisSystem.GetMatrix(SourceMatrix);

		fbxsdk::FbxAMatrix EngineMatrix;
		EngineAxisSystem.GetMatrix(EngineMatrix);

		// ��Ʈ������ ���ͼ� ���ο� ������ ������ �Ҽ� �ִ� ����� �������.
		ConvertMatrix = SourceMatrix.Inverse() * EngineMatrix;
	}

	int OriginUpSign = 0;
	int OriginFrontSign = 0;
	int EngineUpSign = 0;
	int EngineFrontSign = 0;

	fbxsdk::FbxAxisSystem::EFrontVector OriginFrontVector = SourceAxisSystem.GetFrontVector(OriginFrontSign);
	fbxsdk::FbxAxisSystem::EFrontVector EngineFrontVector = EngineAxisSystem.GetFrontVector(EngineFrontSign);

	fbxsdk::FbxAxisSystem::EUpVector OriginUpVector = SourceAxisSystem.GetUpVector(OriginUpSign);
	fbxsdk::FbxAxisSystem::EUpVector EngineUpVector = EngineAxisSystem.GetUpVector(EngineUpSign);

	fbxsdk::FbxAxisSystem::ECoordSystem  OriginCoordSystem = SourceAxisSystem.GetCoorSystem();
	fbxsdk::FbxAxisSystem::ECoordSystem  EngineCoordSystem = EngineAxisSystem.GetCoorSystem();

	if (OriginUpVector == EngineUpVector && OriginUpSign == EngineUpSign)
	{
		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == EngineUpVector && OriginUpSign != EngineUpSign)
	{
		if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
		{
			AxisVector.mData[1] += 180;
		}
		else
		{
			AxisVector.mData[0] += 180;
		}

		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
	{
		//origin up vector �� x up vector �϶��� ���� ���������� ���ߴ�.

		AxisVector.mData[1] += OriginUpSign * 90;
	}
	else
	{
		AxisVector.mData[0] += OriginUpSign * 90;
		if (OriginUpSign != EngineFrontSign)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += OriginUpSign * 180;
		}
	}

	JointMatrix.SetR(AxisVector);

	if (true == JointMatrix.IsIdentity())
	{
		JointMatrix = ConvertMatrix;
	}

	// �ִϸ��̼� ��ĵ� �� ����
	Scene->GetAnimationEvaluator()->Reset();

	RootNode = Scene->GetRootNode();

	fbxsdk::FbxGeometryConverter Con(Manager);

	// �⺻������ ��� FBX�� �������� ���� �ﰢ������ �ȵǾ��ִ� �����ε�
	// �� �ﰢ���� �Լ��� ���ؼ� �� ���ؽ����� �츮�� ����� �� �ִ� ������ ������ش�.
	if (false == Con.Triangulate(Scene, true))
	{
		MsgBoxAssert("�ﰢȭ�� �����߽��ϴ�.");
	}

	return true;
	// �̰ͱ��� �ؾ� �غ� ������.
}