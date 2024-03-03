#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class SwitchFlagFrameEvent : public FrameEventObject
{
public:
	// constrcuter destructer
	SwitchFlagFrameEvent();
	~SwitchFlagFrameEvent();

	// delete Function
	SwitchFlagFrameEvent(const SwitchFlagFrameEvent& _Other) = delete;
	SwitchFlagFrameEvent(SwitchFlagFrameEvent&& _Other) noexcept = delete;
	SwitchFlagFrameEvent& operator=(const SwitchFlagFrameEvent& _Other) = delete;
	SwitchFlagFrameEvent& operator=(SwitchFlagFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<SwitchFlagFrameEvent> CreateEventObject(int _SFrame, int _EFrame, int _iFlag, bool _OnValue);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << EndFrame;
		_File << iFlag;
		_File << bOnValue;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> EndFrame;
		_File >> iFlag;
		_File >> bOnValue;
	}

	inline int GetEndFrame() const
	{
		return EndFrame;
	}

	std::shared_ptr<FrameEventObject> PlayEvent() override;
	int UpdateEvent(float _Delta) override;
	void Reset() override;

	void Init();


protected:

private:
	int EndFrame = -1;
	int iFlag = -1;
	bool bOnValue = true;

	int* pFlags = nullptr;


};

