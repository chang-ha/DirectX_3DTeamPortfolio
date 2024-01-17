#pragma once
#include <GameEngineCore/GameEngineRenderer.h>



class FbxExAniData;
class FrameEventHelper;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameContentsFBXRenderer;
class GameContentsFBXAnimationInfo : public std::enable_shared_from_this<GameContentsFBXAnimationInfo>
{
public:
	GameContentsFBXRenderer* ParentRenderer;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	// 애니메이션을 가지고 있는 FBX에서 알고 있는 애니메이션 정보
	FbxExAniData* FBXAnimationData;

	FrameEventHelper* EventHelper = nullptr;

	// 재생시간
	float PlayTime = 0.0f;
	// 현재까지 생한 시간
	float CurFrameTime = 0.0f;
	// 프레임 간격타임
	float Inter = 0.1f;

	std::vector<unsigned int> Frames;
	std::vector<float4> RootMotionFrames;
	UINT CurFrame = 0;
	UINT Start = -1;
	UINT End = -1;

	bool bOnceStart = true;
	bool bOnceEnd = true;
	bool IsStart = true;
	bool Loop = true;
	bool RootMotion = false;

	// 과제로 내준것인데.
	float BlendIn = 0.2f;


	void Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

	inline void RootMotionOn()
	{
		RootMotion = true;
	}

	inline void RootMotionOff()
	{
		RootMotion = false;
	}

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

// 설명 : 
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

	// Sprite랜더러는 부담이 되지가 않아서 
	void SetFBXMesh(std::string_view _Name, std::string_view _Material);
	void SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex);

	void SetMapFBXMesh(std::string_view _Name, std::string_view _Material);

	// 보류
	void TestSetBigFBXMesh(std::string_view _Name, std::string_view _Material);

	std::shared_ptr<GameEngineRenderUnit> SetMapFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex);

	//                                                                  RenderUnitInfoIndex
	std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex);

	std::shared_ptr<GameContentsFBXAnimationInfo> FindAnimation(const std::string_view _AnimationName);

	void CreateFBXAnimation(const std::string_view _AnimationName, const std::string_view _AnimationFBX, const AnimationCreateParams& _Param, int _Index = 0);

	void ChangeAnimation(const std::string_view _AnimationName, bool _Force = false);

	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& GetAnimationInfos();

	inline void SwitchPause()
	{
		Pause = !Pause;
	}

	std::shared_ptr<GameEngineFBXMesh> GetFBXMesh(std::string_view _Name);

	inline std::shared_ptr<GameEngineFBXMesh>& GetFBXMesh() { return FBXMesh; }
	inline std::shared_ptr<GameContentsFBXAnimationInfo>& GetCurAnimation() { return CurAnimation; }
	inline std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& GetRenderUnits() { return RenderUnits; } 

	void BlendReset();

	// Root Motion

	void SetRootMotionComponent(GameEnginePhysXComponent* _RootMotionComponent)
	{
		// TriMesh는 아직 구현 안했습니다. 필요시 우창하에게 문의
		RootMotionComponent = _RootMotionComponent;
	}

	void SetRootMotion(std::string_view _AniName, std::string_view _FileName = "", bool _RootMotion = true);

protected:
	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> RenderUnits;

private:
	bool Pause = false;
	bool IsBlend = false;
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>> Animations;
	std::shared_ptr<GameContentsFBXAnimationInfo> CurAnimation;

	std::vector<float4x4> AnimationBoneMatrixs;
	std::vector<float4x4> AnimationBoneNotOffset;
	std::vector<float4x4> BlendBoneMatrixs;
	std::vector<AnimationBoneData> AnimationBoneDatas;

	// Root Motion
	GameEnginePhysXComponent* RootMotionComponent = nullptr;
};

