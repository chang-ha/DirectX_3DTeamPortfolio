#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class SoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	SoundFrameEvent();
	~SoundFrameEvent();

	// delete Function
	SoundFrameEvent(const SoundFrameEvent& _Other) = delete;
	SoundFrameEvent(SoundFrameEvent&& _Other) noexcept = delete;
	SoundFrameEvent& operator=(const SoundFrameEvent& _Other) = delete;
	SoundFrameEvent& operator=(SoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<SoundFrameEvent> CreateEventObject(int _Frame, std::string_view _FileName);

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << SoundName;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> SoundName;
	}

	inline std::string_view GetSoundName() const
	{
		return SoundName;
	}


	int PlayEvent() override;


protected:

private:
	static const Enum_FrameEventType Type = Enum_FrameEventType::Sound;
	std::string SoundName;

};

