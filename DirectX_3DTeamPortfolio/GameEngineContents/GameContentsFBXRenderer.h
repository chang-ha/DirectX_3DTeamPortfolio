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
	GameContentsFBXRenderer* ParentRenderer = nullptr;
	// SetFBX 본을 가지고 있는 매쉬
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// 애니메이션을 가지고 있는 FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	// 애니메이션을 가지고 있는 FBX에서 알고 있는 애니메이션 정보
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
	bool IsEnd = false;
	bool RootMotion = false;
	float RootMotion_StartDir = 0.f;

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

	void SetFBXMesh(std::string_view _Name, std::string_view _Material);
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

	inline bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
	}

	inline int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	std::shared_ptr<GameEngineFBXMesh> GetFBXMesh(std::string_view _Name);

	inline std::shared_ptr<GameEngineFBXMesh>& GetFBXMesh() { return FBXMesh; }
	inline std::shared_ptr<GameContentsFBXAnimationInfo>&  GetCurAnimation() { return CurAnimation; }
	inline std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& GetRenderUnits() { return RenderUnits; } 
	inline std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& GetAnimationInfos() { return Animations; }
	inline std::vector<float4x4>& GetBoneMatrixs() { return AnimationBoneMatrixs; }
	inline std::vector<float4x4>& GetBoneSockets() { return AnimationBoneNotOffset; }

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

