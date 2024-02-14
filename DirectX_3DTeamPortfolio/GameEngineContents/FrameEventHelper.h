#pragma once
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class FrameEventObject;
class FrameEventHelper : public GameEngineResources<FrameEventHelper>
{
public:
	// constrcuter destructer
	FrameEventHelper();
	~FrameEventHelper();

	// delete Function
	FrameEventHelper(const FrameEventHelper& _Other) = delete;
	FrameEventHelper(FrameEventHelper&& _Other) noexcept = delete;
	FrameEventHelper& operator=(const FrameEventHelper& _Other) = delete;
	FrameEventHelper& operator=(FrameEventHelper&& _Other) noexcept = delete;

	static std::string_view GetExtName()
	{
		return ExtName;
	}

	static std::string GetConvertFileName(std::string_view _AnimationName);

	static std::shared_ptr<FrameEventHelper> CreateTempRes(std::string_view _TempPath, GameContentsFBXAnimationInfo* _AnimationInfo)
	{
		int FrameCnt = static_cast<int>(_AnimationInfo->FBXAnimationData->FrameCount + 1);

		std::shared_ptr<FrameEventHelper> Helper = Load(_TempPath);
		Helper->ParentInfo = _AnimationInfo;
		Helper->EventInfo.resize(FrameCnt);
		Helper->FrameCount = FrameCnt;
		return Helper;
	}

	static std::shared_ptr<FrameEventHelper> Load(std::string_view _Path)
	{
		GameEngineFile File(_Path.data());
		return Load(_Path, File.GetFileName());
	}

	static std::shared_ptr<FrameEventHelper> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<FrameEventHelper> Helper = CreateRes(_Name);
		Helper->Path = _Path;
		return Helper;
	}

	void Initialze(GameContentsFBXAnimationInfo* _AnimationInfo);
	void SaveFile();

	void PlayEvents(int _Frame);
	void PushPlayingEvent(FrameEventObject* _Object);
	void UpdateEvent(float _Delta);
	void EventReset();

	int GetEventSize();

	void SetEvent(std::shared_ptr<FrameEventObject> _EventObject);
	void PopEvent(const std::shared_ptr<FrameEventObject>& _Event);

	inline class GameContentsFBXAnimationInfo* GetAnimationInfo() { return ParentInfo; }
	inline std::vector<std::list<FrameEventObject*>>& GetEventInfo() { return EventInfo; }
	inline std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& GetAllEvents() { return Events; }

	template<typename _EventType>
	std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(_EventType _Type)
	{
		return GetEventGroup(static_cast<int>(_Type));
	}

	inline std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(int _Type);
	inline class GameContentsFBXAnimationInfo* GetParentInfo() { return ParentInfo; }

protected:
	void PushEventData();

private:
	static std::string ExtName;

	std::string Path;
	std::string AnimationName;

	int FrameCount = 0;

	class GameContentsFBXAnimationInfo* ParentInfo = nullptr;
	std::vector<std::list<FrameEventObject*>> EventInfo;
	std::list<FrameEventObject*> PlayingEvents;
	std::map<int, std::list<std::shared_ptr<FrameEventObject>>> Events;

};