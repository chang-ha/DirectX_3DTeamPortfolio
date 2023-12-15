#include "PreCompile.h"
#include "GameEngineFBXAnimation.h"
#include <GameEngineBase/GameEngineFile.h>

GameEngineFBXAnimation::GameEngineFBXAnimation() 
{
}

GameEngineFBXAnimation::~GameEngineFBXAnimation() 
{
}

std::shared_ptr<GameEngineFBXAnimation> GameEngineFBXAnimation::Load(std::string_view& _Path, std::string_view _Name)
{
	std::shared_ptr<GameEngineFBXAnimation> Res = CreateRes(_Name);
	Res->SetPath(_Path);
	return Res;
}


void GameEngineFBXAnimation::AnimationMatrixLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, const std::string_view& _Name, int _AnimationIndex)
{
	Initialize();

	if (0 == AnimationDatas.size())
	{
		MsgBoxAssert("�ִϸ��̼� �����Ͱ� �������� �ʴ� �Ž��� �ִϸ��̼��� ������� �߽��ϴ�");
		return;
	}

	if (0 != AnimationDatas[_AnimationIndex].AniFrameData.size())
	{
		// ��� ������ �� ������.
		// �̹� �ε尡 ���� �༮�̾�.
		return;
	}

	// �� ������ŭ �ִϸ��̼� ����� Ȯ���Ѵ�.
	AnimationDatas[_AnimationIndex].AniFrameData.resize(_Mesh->GetBoneCount());

	if (nullptr == _Mesh->RootNode)
	{
		// ???�̰� 
		// ���߿� �ؾ��Ұ� ����. 
		MsgBoxAssert("FBX ���Ž��� �ε尡 �ȵ� �����Դϴ�.");
		// GameEngineFile File = _Mesh->GetPath();
	}

	ProcessAnimationLoad(_Mesh, _Mesh->RootNode, _AnimationIndex);
}

void GameEngineFBXAnimation::ProcessAnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index)
{
	// �ڴ�
	//FbxExAniData& userAniData = AnimationDatas.at(userAniDataIndex);
	//fbxsdk::FbxLongLong fbxTime = userAniData.EndTime.Get() - userAniData.StartTime.Get() + 1;

	//// �ִϸ��̼� ������ ����ִ� �༮���� ���� offset�̶�� �ϴ� T
	//// 
	//// ����
	//size_t aniFrameDataSize = userAniData.AniFrameData.size();
	//for (size_t aniFrameDataIndex = 0; aniFrameDataIndex < aniFrameDataSize; ++aniFrameDataIndex)
	//{
	//	FbxExBoneFrame& aniFrameData = userAniData.AniFrameData.at(aniFrameDataIndex);
	//	// ���������.
	//	if (0 == aniFrameData.BoneMatData.size())
	//	{
	//		aniFrameData.BoneMatData.resize(fbxTime);
	//		Bone& curBone = _Fbx->AllBones[aniFrameDataIndex];
	//		aniFrameData.BoneIndex = curBone.Index;
	//		aniFrameData.BoneParentIndex = curBone.ParentIndex;
	//		if (-1 != curBone.ParentIndex)
	//		{
	//			FbxExBoneFrame& parentAniFrameData = userAniData.AniFrameData.at(curBone.ParentIndex);
	//			for (fbxsdk::FbxLongLong start = 0; start < fbxTime; ++start)
	//			{
	//				aniFrameData.BoneMatData[start].Time = parentAniFrameData.BoneMatData[start].Time;
	//				aniFrameData.BoneMatData[start].LocalAnimation = float4x4ToFbxAMatrix(curBone.BonePos.Local);
	//				aniFrameData.BoneMatData[start].GlobalAnimation = parentAniFrameData.BoneMatData[start].GlobalAnimation * aniFrameData.BoneMatData[start].LocalAnimation;
	//				aniFrameData.BoneMatData[start].FrameMat = FbxMatTofloat4x4(aniFrameData.BoneMatData[start].GlobalAnimation);
	//				aniFrameData.BoneMatData[start].S = FbxVecTofloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetS());
	//				aniFrameData.BoneMatData[start].Q = FbxQuaternionTofloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetQ());
	//				aniFrameData.BoneMatData[start].T = FbxVecToTransform(aniFrameData.BoneMatData[start].GlobalAnimation.GetT());
	//			}
	//		}
	//		else
	//		{
	//			for (fbxsdk::FbxLongLong start = 0; start < fbxTime; ++start)
	//			{
	//				aniFrameData.BoneMatData[start].Time = 0;
	//				aniFrameData.BoneMatData[start].LocalAnimation = float4x4ToFbxAMatrix(curBone.BonePos.Local);
	//				aniFrameData.BoneMatData[start].GlobalAnimation = aniFrameData.BoneMatData[start].LocalAnimation;
	//				aniFrameData.BoneMatData[start].FrameMat = FbxMatTofloat4x4(aniFrameData.BoneMatData[start].GlobalAnimation);
	//				aniFrameData.BoneMatData[start].S = FbxVecTofloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetS());
	//				aniFrameData.BoneMatData[start].Q = FbxQuaternionTofloat4(aniFrameData.BoneMatData[start].GlobalAnimation.GetQ());
	//				aniFrameData.BoneMatData[start].T = FbxVecToTransform(aniFrameData.BoneMatData[start].GlobalAnimation.GetT());
	//			}
	//		}
	//	}
	//}
}

void GameEngineFBXAnimation::Initialize()
{
	FBXInit(GetPath());
	CheckAnimation();
}

bool GameEngineFBXAnimation::CheckAnimation()
{
	std::string_view Path = GetPath();

	fbxsdk::FbxArray<FbxString*> AniNameArray;
	Scene->FillAnimStackNameArray(AniNameArray);

	if (0 == AniNameArray.Size())
	{
		return false;
	}

	AnimationDatas.resize(AniNameArray.Size());

	for (unsigned int i = 0; i < AnimationDatas.size(); i++)
	{
		AnimationDatas[i].AniName = GameEngineString::UTF8ToAnsi(AniNameArray[i]->Buffer());

		FbxTakeInfo* TakeInfo = Scene->GetTakeInfo(AnimationDatas[i].AniName.c_str());
		AnimationDatas[i].StartTime = TakeInfo->mLocalTimeSpan.GetStart();
		AnimationDatas[i].EndTime = TakeInfo->mLocalTimeSpan.GetStop();
		AnimationDatas[i].TimeMode = Scene->GetGlobalSettings().GetTimeMode();
		AnimationDatas[i].TimeStartCount = AnimationDatas[i].StartTime.GetFrameCount(AnimationDatas[i].TimeMode);

		if (0 >= AnimationDatas[i].TimeStartCount)
		{
			AnimationDatas[i].TimeStartCount *= (FbxLongLong)-1;
		}

		AnimationDatas[i].TimeEndCount = AnimationDatas[i].EndTime.GetFrameCount(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FrameCount = AnimationDatas[i].TimeEndCount - AnimationDatas[i].TimeStartCount;

		AnimationDatas[i].FbxModeCount = (long long)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FbxModeRate = (double)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
	}

	for (int i = 0; i < AniNameArray.Size(); i++)
	{
		delete AniNameArray[i];
	}

	return true;
}