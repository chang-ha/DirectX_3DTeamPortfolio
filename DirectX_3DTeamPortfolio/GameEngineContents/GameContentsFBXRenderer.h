#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

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
	// SetFBX ���� ������ �ִ� �Ž�
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// �ִϸ��̼��� ������ �ִ� FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	// �ִϸ��̼��� ������ �ִ� FBX���� �˰� �ִ� �ִϸ��̼� ����
	FbxExAniData* FBXAnimationData = nullptr;

	FrameEventHelper* EventHelper = nullptr;

	float PlayTime = 0.0f;
	float CurFrameTime = 0.0f;
	float Inter = 0.1f;

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

	float BlendIn = 0.2f;

	void Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

	std::function<void(UINT _FrameIndex)> FrameChangeFunction;

	std::map<int, std::function<void(GameContentsFBXRenderer*)>> FrameEventFunction;

	std::function<void(GameContentsFBXRenderer*)> EndEvent;

	void EventCall(UINT _Frame);

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
	}
};

struct BlendData
{
public:
	float4 S;
	float4 R;
	float4 T;
};

// ���� : 
class GameContentsFBXRenderer : public GameEngineRenderer
{
	friend GameContentsFBXAnimationInfo;
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

	void SetFBXMesh(std::string_view _Name, std::string_view _Material, RenderPath _DefaultRenderPath = RenderPath::None);
	void SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex);

	void SetMapFBXMesh(std::string_view _Name, std::string_view _Material);

	// ����
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
			MsgBoxAssert("���� ���� ���� ���� �ִϸ��̼��� ���� �����Ӻ��� ū ���Դϴ�.");
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
	void AddNotBlendBoneIndex(int _Index);

	// Root Motion
	AnimationBoneData Get_Prev_BoneDate()
	{
		return Prev_BoneDate; 
	}
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
		// TriMesh�� ���� ���߽��ϴ�. �ʿ�� ��â�Ͽ��� ����
		RootMotionComponent = _RootMotionComponent;
	}

	void SetRootMotion(std::string_view _AniName, std::string_view _FileName = "", Enum_RootMotionMode _Mode = Enum_RootMotionMode::StartDir, bool _RootMotion = true);
	void SetRootMotionMode(std::string_view _AniName, Enum_RootMotionMode _Mode);

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameContentsFBXRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameContentsFBXRenderer*)> _Function);

	void SetFrameChangeFunction(std::string_view _AnimationName, std::function<void(int _FrameIndex)> _Function);
	void SetFrameChangeFunctionAll(std::function<void(int _FrameIndex)> _Function);

protected:
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> RenderUnits;

private:
	bool Pause = false;
	bool bFrameChange = false;

	std::set<int> NotBlendBoneIndexs;

	AnimationBoneData Prev_BoneDate = {};
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>> Animations;
	std::shared_ptr<GameContentsFBXAnimationInfo> CurAnimation;

	std::vector<float4x4> AnimationBoneMatrixs;
	std::vector<float4x4> AnimationBoneNotOffset;
	std::vector<AnimationBoneData> BlendBoneData;
	std::vector<AnimationBoneData> AnimationBoneDatas;

	// Root Motion
	GameEnginePhysXComponent* RootMotionComponent = nullptr;
};

