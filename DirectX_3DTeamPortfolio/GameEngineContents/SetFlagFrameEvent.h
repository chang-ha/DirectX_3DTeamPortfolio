#pragma once

// Ό³Έν :
class SetFlagFrameEvent
{
public:
	// constrcuter destructer
	SetFlagFrameEvent();
	~SetFlagFrameEvent();

	// delete Function
	SetFlagFrameEvent(const SetFlagFrameEvent& _Other) = delete;
	SetFlagFrameEvent(SetFlagFrameEvent&& _Other) noexcept = delete;
	SetFlagFrameEvent& operator=(const SetFlagFrameEvent& _Other) = delete;
	SetFlagFrameEvent& operator=(SetFlagFrameEvent&& _Other) noexcept = delete;

protected:

private:


};

