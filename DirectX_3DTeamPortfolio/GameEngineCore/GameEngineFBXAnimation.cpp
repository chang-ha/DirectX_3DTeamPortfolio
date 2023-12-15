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
		MsgBoxAssert("애니메이션 데이터가 존재하지 않는 매쉬로 애니메이션을 만들려고 했습니다");
		return;
	}

	if (0 != AnimationDatas[_AnimationIndex].AniFrameData.size())
	{
		// 행렬 계산까지 다 끝났다.
		// 이미 로드가 끝난 녀석이야.
		return;
	}

	// 본 개수만큼 애니메이션 행렬을 확장한다.
	AnimationDatas[_AnimationIndex].AniFrameData.resize(_Mesh->GetBoneCount());

	if (nullptr == _Mesh->RootNode)
	{
		// ???이게 
		// 나중에 해야할거 같다. 
		MsgBoxAssert("FBX 본매쉬가 로드가 안된 상태입니다.");
		// GameEngineFile File = _Mesh->GetPath();
	}

	ProcessAnimationLoad(_Mesh, _Mesh->RootNode, _AnimationIndex);
}

void GameEngineFBXAnimation::ProcessAnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index)
{
	// 뛴다
	//FbxExAniData& userAniData = AnimationDatas.at(userAniDataIndex);
	//fbxsdk::FbxLongLong fbxTime = userAniData.EndTime.Get() - userAniData.StartTime.Get() + 1;

	//// 애니메이션 정보가 비어있는 녀석등은 보통 offset이라고 하는 T
	//// 
	//// 몸통
	//size_t aniFrameDataSize = userAniData.AniFrameData.size();
	//for (size_t aniFrameDataIndex = 0; aniFrameDataIndex < aniFrameDataSize; ++aniFrameDataIndex)
	//{
	//	FbxExBoneFrame& aniFrameData = userAniData.AniFrameData.at(aniFrameDataIndex);
	//	// 비어있을때.
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