#pragma once
#include "GameEngineFBX.h"
#include "GameEngineResources.h"


class FbxExBoneFrameData : public GameEngineSerializObject 
{
public:
	float4 S; // 크
	float4 Q; // 자
	float4 T; // 이
	double Time;
	float4x4 FrameMat;

	fbxsdk::FbxAMatrix GlobalAnimation;
	fbxsdk::FbxAMatrix LocalAnimation;

	FbxExBoneFrameData() {

	}

	void Write(GameEngineSerializer& _File) override
	{
		_File << S;
		_File << Q;
		_File << T;
		_File << Time;
		_File << FrameMat;
		_File << GlobalAnimation;
		_File << LocalAnimation;
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> S;
		_File >> Q;
		_File >> T;
		_File >> Time;
		_File >> FrameMat;
		_File >> GlobalAnimation;
		_File >> LocalAnimation;
	}

};

class FbxExBoneFrame : public GameEngineSerializObject
{
public:
	int BoneIndex;
	int BoneParentIndex;

	// 60프레임짜리 애니메이션 60
	std::vector<FbxExBoneFrameData> BoneMatData;

	FbxExBoneFrame() {

	}

	void Write(GameEngineSerializer& _File) override
	{
		_File << BoneIndex;
		_File << BoneParentIndex;
		_File << BoneMatData;
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> BoneIndex;
		_File >> BoneParentIndex;
		_File >> BoneMatData;
	}
};

// Take 001이라는 애니메이션이 있는데.
class FbxExAniData : public GameEngineSerializObject
{
public:
	std::string				AniName;
	fbxsdk::FbxTime			StartTime; // 설정된 애니메이션 시간
	fbxsdk::FbxTime			EndTime; // 
	fbxsdk::FbxLongLong		TimeStartCount;
	fbxsdk::FbxLongLong		TimeEndCount; // 1414
	fbxsdk::FbxLongLong		FrameCount;
	fbxsdk::FbxTime::EMode	TimeMode;
	__int64					FbxModeCount;
	double					FbxModeRate;

	// 0~100
	// 본이 68개
	std::vector<FbxExBoneFrame> AniFrameData;

	void Write(GameEngineSerializer& _File) override
	{
		_File << AniName;
		_File << StartTime;
		_File << EndTime;
		_File << TimeStartCount;
		_File << TimeEndCount;
		_File << FrameCount;
		_File << TimeMode;
		_File << FbxModeCount;
		_File << FbxModeRate;
		_File << AniFrameData;
	}

	void Read(GameEngineSerializer& _File) override
	{
		_File >> AniName;
		_File >> StartTime;
		_File >> EndTime;
		_File >> TimeStartCount;
		_File >> TimeEndCount;
		_File >> FrameCount;
		_File >> TimeMode;
		_File >> FbxModeCount;
		_File >> FbxModeRate;
		_File >> AniFrameData;
	}


public:
	float FrameTime(int _Frame)
	{
		fbxsdk::FbxTime tTime = {};
		tTime.SetFrame(_Frame, TimeMode);

		return (float)tTime.GetSecondDouble();
	}

public:
	__int64 FrameModeRateInt()
	{
		return static_cast<__int64>(fbxsdk::FbxGetFrameRate(TimeMode));
	}
	double FrameModeRateDouble()
	{
		return fbxsdk::FbxGetFrameRate(TimeMode);
	}

	float FrameModeRateFloat()
	{
		return static_cast<float>(fbxsdk::FbxGetFrameRate(TimeMode));
	}


public:
	FbxExAniData() : AniName(""), StartTime(0), EndTime(0), TimeStartCount(0), TimeEndCount(0), FrameCount(0), FbxModeCount(0), FbxModeRate(0.0), TimeMode()
	{}
	~FbxExAniData() {}
};

// 설명 :
class GameEngineFBXAnimation : public GameEngineFBX, public GameEngineResources<GameEngineFBXAnimation>
{
public:
	// constrcuter destructer
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();

	// delete Function
	GameEngineFBXAnimation(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _Other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation& operator=(GameEngineFBXAnimation&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFBXAnimation> Load(std::string_view _Path)
	{
		GameEnginePath FilePath(_Path);
		return Load(_Path, FilePath.GetFileName());
	}

	static std::shared_ptr<GameEngineFBXAnimation> Load(std::string_view& _Path, std::string_view _Name);


	void AnimationMatrixLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, const std::string_view& _Name, int _AnimationIndex);

	FbxExAniData* GetAnimationData(int _Index)
	{
		if (AnimationDatas.size() <= _Index)
		{
			MsgBoxAssert("애니메이션 데이터 범위를 넘어섰습니다");
		}

		return &AnimationDatas[_Index];
	}


protected:

private:
	std::vector<FbxExAniData> AnimationDatas;

	void Initialize();
	bool CheckAnimation();

	void ProcessAnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index);
	void ProcessAnimationCheckState(std::shared_ptr <GameEngineFBXMesh> _Fbx, int userAniDataIndex);
	bool AnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* _Node, int AnimationIndex);
	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode* pNode);
};

