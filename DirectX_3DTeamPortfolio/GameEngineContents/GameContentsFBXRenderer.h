#pragma once
#include <GameEngineCore/GameEngineRenderer.h>
#include "FrameEventManager.h"

#define ONE_FRAME_DTIME 0.033333f

enum class Enum_RootMotionMode
{
	StartDir,
	RealTimeDir,
};

class RootMotionData
{
	friend class GameContentsFBXAnimationInfo;
	friend class GameContentsFBXRenderer;

	bool RootMotion = false;
	float RootMotion_StartDir = 0.f;
	float MoveFrameTime = 0.f;
	Enum_RootMotionMode RootMotionMode = Enum_RootMotionMode::StartDir;
	bool IsRotation = true;

	float MoveRatio_X = 1.f;
	float MoveRatio_Y = 1.f;
	float MoveRatio_Z = 1.f;
};

class FbxExAniData;
class FrameEventHelper;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameContentsFBXRenderer;
class GameContentsFBXAnimationInfo : public std::enable_shared_from_this<GameContentsFBXAnimationInfo>
{
public:
	GameContentsFBXRenderer* ParentRenderer = nullptr;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	// 애니메이션을 가지고 있는 FBX에서 알고 있는 애니메이션 정보
	FbxExAniData* FBXAnimationData = nullptr;

	std::unique_ptr<class FrameEventManager> FrameEventInfo;

	float PlayTime = 0.0f;
	float CurFrameTime = 0.0f;
	float Inter = 0.1f;
	float BlendIn = 0.2f;

	std::vector<unsigned int> Frames;
	std::vector<float4> RootMotionFrames;
	UINT CurFrame = 0;
	UINT Start = -1;
	UINT End = -1;

	bool bOnceStart = true;
	bool bOnceEnd = true;
	bool Loop = true;
	bool IsStart = false;
	bool IsEnd = false;
	bool EventCheck = true;

	// RootMotion
	RootMotionData mRootMotionData;

	inline bool IsRootMotion()
	{
		return mRootMotionData.RootMotion;
	}

	inline void RootMotionOn()
	{
		mRootMotionData.RootMotion = true;
	}

	void RootMotionOff();

	void SwitchRootMotion();

	inline bool IsRootMotionRot()
	{
		return mRootMotionData.IsRotation;
	}

	inline void RootMotionRotOn()
	{
		mRootMotionData.IsRotation = true;
	}

	inline void RootMotionRotOff()
	{
		mRootMotionData.IsRotation = false;
	}

	inline void SwitchRootMotionRot()
	{
		mRootMotionData.IsRotation = !mRootMotionData.IsRotation;
	}

	inline void SetStartDir(float _Dir)
	{
		mRootMotionData.RootMotion_StartDir = _Dir;
	}

	void RootMotionUpdate(float _Delta);
	void SetBlendTime(float _Value);

	void Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);
	void Release();

	std::multimap<int, std::function<void(GameContentsFBXRenderer*)>> FrameEventFunction;
	std::function<void(UINT _FrameIndex)> FrameChangeFunction;
	std::function<void()> AnimationChangeFunction;
	std::function<void(GameContentsFBXRenderer*)> EndEvent;

	void EventCall(UINT _Frame);

	std::string_view GetAnimationName() const;

	class FrameEventManager* GetEventManager() const { return FrameEventInfo.get(); };

public:
	GameContentsFBXAnimationInfo()
		: Start(0)
		, End(0)
		, bOnceStart(false)
		, bOnceEnd(false)
	{
	}

	~GameContentsFBXAnimationInfo()
	{
		Release();
	}
};

class MultiBlendAnimationInfo
{
	friend class GameContentsFBXRenderer;

public:
	MultiBlendAnimationInfo() {}
	~MultiBlendAnimationInfo() {}

private:
	void SetInfo(const std::shared_ptr<GameContentsFBXAnimationInfo>& _AnimationInfo);
	void Reset();
	void Done();
	void Update(float _DeltaTime);

	inline bool IsUpdate() const { return !IsEnd; }
	inline std::string_view GetAnmationName() const { return AnimationName; }

private:
	GameContentsFBXRenderer* ParentRenderer = nullptr;
	FbxExAniData* FBXAnimationData = nullptr;

	float CurFrameTime = 0.0f;
	float PlayTime = 0.0f;
	float Inter = 0.0f;

	UINT CurFrame = 0;
	UINT End = 0;

	bool IsEnd = false;

	std::string AnimationName;

};

struct BlendData
{
public:
	float4 S;
	float4 R;
	float4 T;
};

// 설명 : 
class GameContentsFBXRenderer : public GameEngineRenderer
{
	friend GameContentsFBXAnimationInfo;
	friend MultiBlendAnimationInfo;

public:
	// constrcuter destructer
	GameContentsFBXRenderer();
	~GameContentsFBXRenderer();
	
	// delete Function
	GameContentsFBXRenderer(const GameContentsFBXRenderer& _Other) = delete;
	GameContentsFBXRenderer(GameContentsFBXRenderer&& _Other) noexcept = delete;
	GameContentsFBXRenderer& operator=(const GameContentsFBXRenderer& _Other) = delete;
	GameContentsFBXRenderer& operator=(GameContentsFBXRenderer&& _Other) noexcept = delete;


	void Update(float _DeltaTime) override;
	void Release() override;

	void SetFBXMesh(std::string_view _Name, std::string_view _Material, RenderPath _DefaultRenderPath = RenderPath::None);
	void SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex);

	void SetMapFBXMesh(std::string_view _Name, std::string_view _Material);

	// 보류
	void TestSetBigFBXMesh(std::string_view _Name, std::string_view _Material);

	std::shared_ptr<GameEngineRenderUnit> SetMapFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex);

	//                                                                  RenderUnitInfoIndex
	std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex);

	std::shared_ptr<GameContentsFBXAnimationInfo> FindAnimation(const std::string_view _AnimationName);

	void CreateFBXAnimation(const std::string_view _AnimationName, const std::string_view _AnimationFBX, const AnimationCreateParams& _Param = AnimationCreateParams(), int _Index = 0);
	void ChangeAnimation(const std::string_view _AnimationName, bool _Force = false);

	inline void SwitchPause()
	{
		Pause = !Pause;
	}

	inline bool IsFrameChange() const
	{
		return bFrameChange;
	}

	inline bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
	}

	inline int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	void ChangeCurFrame(UINT _Value)
	{
		if (CurAnimation->End < _Value)
		{
			MsgBoxAssert("넣은 인자 값이 현재 애니메이션의 엔드 프레임보다 큰 수입니다.");
			return;
		}
		CurAnimation->CurFrame = _Value;
	}

	std::shared_ptr<GameEngineFBXMesh> GetFBXMesh(std::string_view _Name);

	inline std::shared_ptr<GameEngineFBXMesh>& GetFBXMesh() { return FBXMesh; }
	inline const std::shared_ptr<GameContentsFBXAnimationInfo>&  GetCurAnimation() const { return CurAnimation; }
	inline std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& GetRenderUnits() { return RenderUnits; } 
	inline std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& GetAnimationInfos() { return Animations; }
	inline std::vector<float4x4>& GetBoneMatrixs() { return AnimationBoneMatrixs; }
	inline std::vector<float4x4>& GetBoneSockets() { return AnimationBoneNotOffset; }
	inline const std::vector<AnimationBoneData>& GetBoneDatas() { return AnimationBoneDatas; }
	

	void BlendReset();
	void SetBlendTime(std::string_view _AnimationName, float _fBlendTime);
	void SetBlendTime(std::string_view _AnimationName, int _iBlendFrame);
	void AddNotBlendBoneIndex(int _Index);
	void SetMultiBlend(std::string_view _AnimationName);

	// Root Motion
	
	AnimationBoneData GetBoneData(std::string_view _Name);

	AnimationBoneData GetBoneData(int _Index)
	{

		AnimationBoneData Data = AnimationBoneDatas[_Index];

		Data.Pos *= Transform.GetConstTransformDataRef().WorldMatrix;

		float4 NewRot = Data.RotQuaternion.QuaternionMulQuaternion(Transform.GetConstTransformDataRef().WorldQuaternion);
		Data.RotQuaternion = NewRot;


		return Data;
	}


	void SetRootMotionComponent(GameEnginePhysXComponent* _RootMotionComponent)
	{
		// TriMesh는 구현 안했습니다. 필요시 우창하에게 문의
		RootMotionComponent = _RootMotionComponent;
	}

	void SetRootMotion(std::string_view _AniName, std::string_view _FileName = "", Enum_RootMotionMode _Mode = Enum_RootMotionMode::StartDir, bool _RootMotion = true);
	void SetRootMotionMode(std::string_view _AniName, Enum_RootMotionMode _Mode);
	void SetRootMotionMoveRatio(std::string_view _AniName, float _Ratio_X = -1, float _Ratio_Z = -1, float _Ratio_Y = -1);
	void SetAllRootMotionMoveRatio(float _Ratio_X = -1, float _Ratio_Z = -1, float _Ratio_Y = -1);

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameContentsFBXRenderer*)> _Function);
	void SetAnimationChangeEvent(std::string_view _AnimationName, std::function<void()> _Function);

	void SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(int _FrameIndex)> _Function);
	void SetFrameChangeFunctionAll(std::function<void(int _FrameIndex)> _Function);

	void ChangeCurAnimationSpeed(float _Inter)
	{
		CurAnimation->Inter = _Inter;
	}

protected:
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> RenderUnits;

private:
	bool Pause = false;
	bool bFrameChange = false;
	float MultiBlendRatio = 0.0f;

	std::set<int> NotBlendBoneIndexs;

	AnimationBoneData Prev_BoneDate = {};
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>> Animations;
	std::shared_ptr<GameContentsFBXAnimationInfo> CurAnimation;
	std::unique_ptr<MultiBlendAnimationInfo> MultiBlendAnimation;

	std::vector<float4x4> AnimationBoneMatrixs;
	std::vector<float4x4> AnimationBoneNotOffset;
	std::vector<AnimationBoneData> BlendBoneData;
	std::vector<AnimationBoneData> MultiBlendBoneData;
	std::vector<AnimationBoneData> AnimationBoneDatas;

	// Root Motion
	GameEnginePhysXComponent* RootMotionComponent = nullptr;
};

