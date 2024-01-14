#pragma once
#include "SoundFrameEvent.h"
#include <GameEngineCore/GameEngineResources.h>


// Ό³Έν :
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

	static std::shared_ptr<FrameEventHelper> CreateTempRes(std::string_view _TempPath, int _FrameCount)
	{
		std::shared_ptr<FrameEventHelper> Helper = Load(_TempPath);
		Helper->EventInfo.resize(_FrameCount);
		Helper->FrameCount = _FrameCount;
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

	void Initialze(int _Frame);
	void SaveFile();

	void PlayEvents(int _Frame);
	void EventReset() {}

	int GetEventSize();

	void CreateSoundEvent(int _StartFrame, std::string_view _SoundName);
	void SetEvent(std::shared_ptr<FrameEventObject> _EventObject);
	void PopEvent(const std::shared_ptr<FrameEventObject>& _Event);

	std::vector<std::list<FrameEventObject*>>& GetEventInfo() { return EventInfo; }
	std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& GetAllEvents() { return Events; }
	std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(Enum_FrameEventType _Type);
	std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(int _Type);

protected:
	void PushEventData();

private:
	static std::string ExtName;

	std::string Path;
	std::string AnimationName;

	int FrameCount = 0;

	std::vector<std::list<FrameEventObject*>> EventInfo;
	std::list<FrameEventObject*> PlayingEvents;
	std::map<int, std::list<std::shared_ptr<FrameEventObject>>> Events;

};