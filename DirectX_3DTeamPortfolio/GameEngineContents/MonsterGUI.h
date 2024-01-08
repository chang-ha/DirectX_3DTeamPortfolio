#pragma once

class FrameEventTab
{
	friend class MonsterGUI;

protected:
	virtual void Init() {}
	virtual void Update(GameEngineLevel* _Level, float _Delta) = 0;

	class MonsterGUI* Parent = nullptr;

private:
	std::string Name;

};

class SoundFrameEventTab : public FrameEventTab
{
public:
	void Init() override;
	void Update(GameEngineLevel* _Level, float _Delta) override;

private:
	std::vector<std::string> SoundFileList;
	std::vector<const char*> CSoundFileList;
	int SelectItem = 0;

};

// TestLevel_Monster에서만 쓰이는 GUI입니다.
class MonsterGUI : public GameEngineGUIWindow
{
	friend class TestLevel_Monster;
	friend class SoundFrameEventTab;


private:
	void Start() override;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	void Release();


	void ShowLothricKnCount(class GameEngineLevel* _Level);
	void TransformEdit();
	void CopyObjectName();
	void CopyAnimationName();
	void ShowObjectNameList();
	void RenderUnitSwitch();

	template<typename TabType>
	void CreateEventTab(std::string_view _TabName)
	{
		std::shared_ptr<TabType> Tab = std::make_shared<TabType>();
		Tab->Init();
		Tab->Name = _TabName;
		Tab->Parent = this;
	}

private:
	class TestLevel_Monster* CurLevel = nullptr;
	class CommonMonster* SelectActor = nullptr;



	std::vector<std::string> ActorNames;
	std::vector<const char*> CObjectNames;
	std::vector<std::string> AnimationNames; // Store Value
	std::vector<const char*> CAnimationNames; // Use 'AnimationNames' Pointer
	std::shared_ptr<GameContentsFBXAnimationInfo> CurAnimationInfo;

	std::vector<std::shared_ptr<FrameEventTab>> FrameEventTabs;


	float Size = 0.0f;
	float4 Rot = float4::ZERO;
	float4 Pos = float4::ZERO;

	int SelectEventType = 0;
	int SelectActorIndex = -1;
	int SelectAnimationIndex = -1;
	int SelectFrame = 0;

};

