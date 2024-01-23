#pragma once

// Ό³Έν :
class FlagSwitchFrameEvent
{
public:
	// constrcuter destructer
	FlagSwitchFrameEvent();
	~FlagSwitchFrameEvent();

	// delete Function
	FlagSwitchFrameEvent(const FlagSwitchFrameEvent& _Other) = delete;
	FlagSwitchFrameEvent(FlagSwitchFrameEvent&& _Other) noexcept = delete;
	FlagSwitchFrameEvent& operator=(const FlagSwitchFrameEvent& _Other) = delete;
	FlagSwitchFrameEvent& operator=(FlagSwitchFrameEvent&& _Other) noexcept = delete;

protected:

private:


};

