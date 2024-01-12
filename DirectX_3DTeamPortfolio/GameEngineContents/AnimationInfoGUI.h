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

	class AnimationInfoGUI* Parent = nullptr;

private:
	std::string Name;

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

// Ό³Έν :
class AnimationInfoGUI : public TreeObject
{
	friend class SoundEventTree;

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
	void TransformEditor();
	void AnimationList();
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

private:
	class CommonMonster* SelectActor = nullptr;

	std::vector<std::string> ActorNames;
	std::vector<const char*> CObjectNames;

	float Size = 0.0f;
	float4 Rot = float4::ZERO;
	float4 Pos = float4::ZERO;

	std::vector<std::string> AnimationNames; // Store Value
	std::vector<const char*> CAnimationNames; // Use 'AnimationNames' Pointer
	std::shared_ptr<GameContentsFBXAnimationInfo> SelectAnimation;

	std::vector<std::shared_ptr<EventTree>> EventTrees;

};

