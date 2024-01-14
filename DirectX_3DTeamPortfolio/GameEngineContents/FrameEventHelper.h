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
		Helper->Events.resize(_FrameCount);
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

	int GetEventCount();

	void CreateSoundEvent(int _StartFrame, std::string_view _SoundName);
	void PopEvent(const std::shared_ptr<SoundFrameEvent>& _Event);


	std::vector<std::list<FrameEventObject*>>& GetAllEvents() { return Events; }
	std::list<std::shared_ptr<SoundFrameEvent>>& GetSoundEvents() { return SoundEvents; }

protected:
	void PushEventData();

private:
	std::string Path;
	std::string AnimationName;
	static std::string ExtName;
	int FrameCount = 0;
	int EventCount = 0;
	std::vector<std::list<FrameEventObject*>> Events;
	std::list<FrameEventObject*> PlayingEvents;
	std::list<std::shared_ptr<SoundFrameEvent>> SoundEvents;


};