#pragma once
#include "TreeWindow.h"

class DummyPolyStruct
{
public:
	enum eDPFlag
	{
		None = 0,
		Tree = (1 << 0),
		Max,
	};

public:
	void Init(class BaseActor* _pActor, int _Flag);
	void AutoLoadDummyPolyRefID();
	void AutoLoadDummyPolyAttachBoneIndex();
	void ComboDummyPolyAttachBoneIndex();

	bool IsFlag(eDPFlag _BitFlag);
	bool IsFlag(int _BitFlag);
	void OutUsingImguiScope();

	void DpLoaderAllReset();
	void DpLoaderRefReset();
	void DpLoaderAttachReset();

	inline const class DummyData* GetDummyDataPointer() const { return SelectDPData; }

private:

private:
	std::string IDName;
	int Flag = 0;

	std::map<int, class DummyData> DummyPolyDatas;
	std::set<int> DummyPolyRefIndexCheck;
	std::vector<std::string> DummyPolyRefIndexs;
	std::vector<const char*> CDummyPolyRefIndexs;
	std::vector<std::string> DummyPolyAttachIndexs;
	std::vector<const char*> CDummyPolyAttachIndexs;
	const class DummyData* SelectDPData = nullptr;

	int Dummy_RefIndex = -1;
	int Dummy_ParentIndex = -1;

};

class EventTree
{
	friend class AnimationInfoGUI;

public:
	void SetParent(class AnimationInfoGUI* pParent)
	{
		Parent = pParent;
	}

	inline std::string GetName() const { return Name; }

protected:
	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _Delta) = 0;
	virtual void ChangeAnimation() {}
	virtual void ChangeActor() {}

	class BaseActor* GetSelectActor() const;
	class GameContentsFBXAnimationInfo* GetSelectAnimation() const;

protected:
	class AnimationInfoGUI* Parent = nullptr;

private:
	std::string Name;

};

class TotalEventTree : public EventTree
{
	friend class AnimationInfoGUI;

private:
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

};

class SoundEventTree : public EventTree
{
public:
	void ChangeActor() override;

protected:
	void LoadSoundList();

	std::vector<std::string> SoundFileList;
	std::vector<const char*> CSoundFileList;
	int SoundIndex = 0;

};

class BoneSoundEventTree : public EventTree
{
public:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;
	void ChangeActor() override;
	void ChangeAnimation() override;

private:
	void LoadSoundList();

private:
	std::vector<std::string> BoneNames;
	std::vector<const char*> CBoneNames;
	int BoneIndex = 0;

	std::vector<std::string> SoundFileList;
	std::vector<const char*> CSoundFileList;
	int SelectStartFrame = 0;
	int SoundIndex = 0;

};

class CenterBodySoundEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;
	void ChangeActor() override {}

private:
	int SelectStartFrame = 0;

};

class DPSoundEventTree : public SoundEventTree
{
	friend class AnimationInfoGUI;

public:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;
	void ChangeActor() override;

private:
	DummyPolyStruct DpLoader;

	int SelectStartFrame = 0;

};

class CollisionEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:

private:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;
	void ChangeActor() override;

private:
	std::vector<std::string> ColNames;
	std::vector<const char*> CColNames;

};


class TurnSpeedEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:

private:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

private:
	int TurnSpeedValue = 0;

};

// Ό³Έν :
class AnimationInfoGUI : public TreeObject
{
	friend class EventTree;
	friend class SoundEventTree;
	friend class BoneSoundEventTree;
	friend class TotalEventTree;
	friend class CollisionEventTree;
	friend class TurnSpeedEventTree;

public:
	// constrcuter destructer
	AnimationInfoGUI();
	~AnimationInfoGUI();

	// delete Function
	AnimationInfoGUI(const AnimationInfoGUI& _Other) = delete;
	AnimationInfoGUI(AnimationInfoGUI&& _Other) noexcept = delete;
	AnimationInfoGUI& operator=(const AnimationInfoGUI& _Other) = delete;
	AnimationInfoGUI& operator=(AnimationInfoGUI&& _Other) noexcept = delete;

	void ShowActorList(class GameEngineLevel* _Level);
	void ActorChange();
	void TransformEditor();
	void AnimationList(class GameEngineLevel* _Level, float _DeltaTime);
	void BoneEditor();
	void EventEditor(class GameEngineLevel* _Level, float _DeltaTime);

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

	template<typename ObjectType>
	void CreateEventTree(std::string_view _TabName)
	{
		std::shared_ptr<EventTree> NewTree = std::make_shared<ObjectType>();
		NewTree->Name = _TabName;
		NewTree->SetParent(this);
		NewTree->Start();
		EventTrees.push_back(NewTree);
	}

	void AnimationChange();
	void DummyEditor();
	void DummyEditorReset();

	void BoneCollisionEditor();

private:
	class BaseActor* SelectActor = nullptr;

	std::vector<std::string> ActorNames;
	std::vector<const char*> CObjectNames;

	float Size = 0.0f;
	float4 Rot = float4::ZERO;
	float4 Pos = float4::ZERO;

	std::vector<std::string> AnimationNames; // Store Value
	std::vector<const char*> CAnimationNames; // Use 'AnimationNames' Pointer
	int AnimationIndex = 0;

	std::shared_ptr<GameContentsFBXAnimationInfo> SelectAnimation;

	std::vector<std::string> BoneNames;
	std::vector<const char*> CBoneNames;
	float4 BoneS;
	float4 BoneRot = float4::ZERONULL;
	float4 BonePos;

	std::vector<std::shared_ptr<EventTree>> EventTrees;

	DummyPolyStruct DpLoader;

	float4 DummyS = float4::ZERO;	

};