#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class BoneSoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	BoneSoundFrameEvent();
	~BoneSoundFrameEvent();

	// delete Function
	BoneSoundFrameEvent(const BoneSoundFrameEvent& _Other) = delete;
	BoneSoundFrameEvent(BoneSoundFrameEvent&& _Other) noexcept = delete;
	BoneSoundFrameEvent& operator=(const BoneSoundFrameEvent& _Other) = delete;
	BoneSoundFrameEvent& operator=(BoneSoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<BoneSoundFrameEvent> CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName);

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << SoundName;
		_File << BoneIndex;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> SoundName;
		_File >> BoneIndex;
	}

	inline std::string_view GetSoundName() const
	{
		return SoundName;
	}


	void PlayEvent() override;


protected:

private:
	int BoneIndex = -1;
	std::string SoundName;

};

