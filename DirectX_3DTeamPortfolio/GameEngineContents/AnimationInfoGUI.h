#pragma once
#include "TreeWindow.h"


class EventTree
{
	friend class AnimationInfoGUI;

public:
	inline std::string GetName() const { return Name; }

protected:
	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _Delta) = 0;
	virtual void ChangeAnimation() {}
	virtual void ChangeActor() {}

	class AnimationInfoGUI* Parent = nullptr;

private:
	std::string Name;

};

class TotalEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:

private:
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

};

class SoundEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:

private:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;

private:
	std::vector<std::string> SoundFileList;
	std::vector<const char*> CSoundFileList;
	int SelectStartFrame = 0;
	int SelectSoundItem = 0;

};

class BoneSoundEventTree : public EventTree
{
	friend class AnimationInfoGUI;

public:

private:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _Delta) override;
	void ChangeActor() override;
	void ChangeAnimation() override;

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
		std::shared_ptr<ObjectType> NewTree = std::make_shared<ObjectType>();
		NewTree->Parent = this;
		NewTree->Name = _TabName;
		NewTree->Start();
		EventTrees.push_back(NewTree);
	}

	void AnimationChange();
	void DummyEditor();
	void DummyEditorReset();
	void DpEditorRefReset();
	void DpEditorAttachReset();

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
	float4 BoneRot;
	float4 BonePos;

	std::vector<std::shared_ptr<EventTree>> EventTrees;

	std::map<int, class DummyData> DummyPolyDatas;
	std::set<int> DummyPolyRefIndexCheck;
	std::vector<std::string> DummyPolyRefIndexs;
	std::vector<const char*> CDummyPolyRefIndexs;
	std::vector<std::string> DummyPolyAttachIndexs;
	std::vector<const char*> CDummyPolyAttachIndexs;
	const class DummyData* SelectDPData = nullptr;

	int Dummy_RefIndex = -1;
	int Dummy_ParentIndex = -1;
	float4 DummyS = float4::ZERO;	

};

