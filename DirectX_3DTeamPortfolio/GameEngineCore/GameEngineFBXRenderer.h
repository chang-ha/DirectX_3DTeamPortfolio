#pragma once
#include "GameEngineRenderer.h"

struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};

class AnimationCreateParams
{
public:
	float Inter = 0.0f;
	bool Loop = true;
};

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameEngineFBXRenderer;
class GameEngineFBXAnimationInfo : public std::enable_shared_from_this<GameEngineFBXAnimationInfo>
{
public:
	GameEngineFBXRenderer* ParentRenderer;
	// SetFBX ���� ������ �ִ� �Ž�
	std::shared_ptr<GameEngineFBXMesh> Mesh;
	// �ִϸ��̼��� ������ �ִ� FBX
	std::shared_ptr<GameEngineFBXAnimation> Aniamtion;
	// �ִϸ��̼��� ������ �ִ� FBX���� �˰� �ִ� �ִϸ��̼� ����
	FbxExAniData* FBXAnimationData;

	// ����ð�
	float PlayTime = 0.0f;
	// ������� ���� �ð�
	float CurFrameTime = 0.0f;
	// ������ ����Ÿ��
	float Inter = 0.1f;

	std::vector<unsigned int> Frames;
	UINT CurFrame = 0;
	UINT Start = -1;
	UINT End = -1;

	bool bOnceStart = true;
	bool bOnceEnd = true;
	bool Loop = true;

	// ������ ���ذ��ε�.
	float BlendIn = 0.2f;
	float BlendOut = 0.2f;

	void Init(std::shared_ptr<GameEngineFBXMesh> _Mesh, std::shared_ptr<GameEngineFBXAnimation> _Animation, const std::string_view& _Name, int _Index);
	void Reset();
	void Update(float _DeltaTime);

public:
	GameEngineFBXAnimationInfo()
		: Start(0)
		, End(0)
		, bOnceStart(false)
		, bOnceEnd(false)
	{
	}

	~GameEngineFBXAnimationInfo()
	{
	}
};


// ���� :
class GameEngineFBXRenderer : public GameEngineRenderer
{
	friend GameEngineFBXAnimationInfo;

public:
	// constrcuter destructer
	GameEngineFBXRenderer();
	~GameEngineFBXRenderer();

	// delete Function
	GameEngineFBXRenderer(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer(GameEngineFBXRenderer&& _Other) noexcept = delete;
	GameEngineFBXRenderer& operator=(const GameEngineFBXRenderer& _Other) = delete;
	GameEngineFBXRenderer& operator=(GameEngineFBXRenderer&& _Other) noexcept = delete;

	void Update(float _DeltaTime) override;

	// Sprite�������� �δ��� ������ �ʾƼ� 
	void SetFBXMesh(std::string_view _Name, std::string_view _Material);
	void SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex);
	//                                                                  RenderUnitInfoIndex
	std::shared_ptr<GameEngineRenderUnit> SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex);

	std::shared_ptr<GameEngineFBXAnimationInfo> FindAnimation(const std::string_view _AnimationName);

	void CreateFBXAnimation(const std::string_view _AnimationName, const std::string_view _AnimationFBX, const AnimationCreateParams& _Param, int _Index = 0);

	void ChangeAnimation(const std::string_view _AnimationName, bool _Force = false);

	std::map<std::string, std::shared_ptr<GameEngineFBXAnimationInfo>>& GetAnimationInfos();

	inline void SwitchPause()
	{
		Pause = !Pause;
	}

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>> RenderUnits;
protected:

private:
	bool Pause = false;
	std::shared_ptr<GameEngineFBXMesh> FBXMesh;
	std::map<std::string, std::shared_ptr<GameEngineFBXAnimationInfo>> Animations;
	std::shared_ptr<GameEngineFBXAnimationInfo> CurAnimation;

	std::vector<float4x4> AnimationBoneMatrixs;
	std::vector<float4x4> AnimationBoneNotOffset;
	std::vector<AnimationBoneData> AnimationBoneDatas;

};

