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
		MsgBoxAssert("FBX 시스템 이니셜라이즈에 실패했습니다");
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
	// fbx에서 사용하는 기본기능을 제공하는 인터페이스
	Manager = fbxsdk::FbxManager::Create();

	if (nullptr == Manager)
	{
		MsgBoxAssert("FBX 매니저 생성에 실패했습니다.");
		return false;
	}

	// 알고치는게 아닙니다
	// 예제 코드에 이렇게 만들어야한다고 해서 나도 그렇게 한것뿐
	IOSetting = fbxsdk::FbxIOSettings::Create(Manager, IOSROOT);

	Importer = fbxsdk::FbxImporter::Create(Manager, "");

	if (false ==
		Importer->Initialize(GameEngineString::AnsiToUTF8(_Path).c_str(), -1, IOSetting))
	{
		Importer->Destroy();
		IOSetting->Destroy();
		MsgBoxAssert("FBX 로드 이니셜라이즈 실패.");
		return false;
	}

	// 비엉있는 scene을 만들고
	Scene = fbxsdk::FbxScene::Create(Manager, "");

	if (nullptr == Scene)
	{
		MsgBoxAssert("FBX 씬생성 실패.");
		return false;
	}

	// 비어있는 Scene에 기본적인 내용을 모두 채웁니다.
	if (false == Importer->Import(Scene))
	{
		MsgBoxAssert("FBX 임포트 실패.");
		return false;
	}

	return true;

	// Scene->GetRootNode()
}

bool GameEngineFBX::FBXConvertScene()
{
	AxisVector = { 0.0f, 0.0f, 0.0f, 1.0f };

	// 내가 다시 돌리면 되는데.
	// 쓸데없이 바꿀려고 노력한 코드
	fbxsdk::FbxAxisSystem::EFrontVector FrontVector = (fbxsdk::FbxAxisSystem::EFrontVector)-fbxsdk::FbxAxisSystem::eParityOdd;
	fbxsdk::FbxAxisSystem::EUpVector UpVector = fbxsdk::FbxAxisSystem::eYAxis;
	fbxsdk::FbxAxisSystem::ECoordSystem CooreSystem = fbxsdk::FbxAxisSystem::ECoordSystem::eRightHanded;

	// 다이렉트 축
	fbxsdk::FbxAxisSystem EngineAxisSystem(UpVector, FrontVector, CooreSystem);

	// 매쉬의 정면축
	fbxsdk::FbxAxisSystem SourceAxisSystem = Scene->GetGlobalSettings().GetAxisSystem();

	if (SourceAxisSystem != EngineAxisSystem)
	{
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(Scene);

		// scene 전체를 내 축으로 돌린다.
		EngineAxisSystem.ConvertScene(Scene);

		fbxsdk::FbxAMatrix SourceMatrix;
		SourceAxisSystem.GetMatrix(SourceMatrix);

		fbxsdk::FbxAMatrix EngineMatrix;
		EngineAxisSystem.GetMatrix(EngineMatrix);

		// 매트릭스를 얻어와서 새로운 축으로 컨버전 할수 있는 행렬을 만들었다.
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
		//origin up vector 가 x up vector 일때를 아직 만나보지를 못했다.

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

	// 애니메이션 행렬도 다 리셋
	Scene->GetAnimationEvaluator()->Reset();

	RootNode = Scene->GetRootNode();

	fbxsdk::FbxGeometryConverter Con(Manager);

	// 기본적으로 모든 FBX는 랜더링을 위한 삼각측량이 안되어있는 상태인데
	// 이 삼각측량 함수를 통해서 각 버텍스들을 우리가 사용할 수 있는 구조로 만들어준다.
	if (false == Con.Triangulate(Scene, true))
	{
		MsgBoxAssert("삼각화에 실패했습니다.");
	}

	return true;
	// 이것까지 해야 준비가 끝난다.
}