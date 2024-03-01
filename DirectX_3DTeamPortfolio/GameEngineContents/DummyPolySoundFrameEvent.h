#pragma once

// Ό³Έν :
class DummyPolySoundFrameEvent
{
public:
	// constrcuter destructer
	DummyPolySoundFrameEvent();
	~DummyPolySoundFrameEvent();

	// delete Function
	DummyPolySoundFrameEvent(const DummyPolySoundFrameEvent& _Other) = delete;
	DummyPolySoundFrameEvent(DummyPolySoundFrameEvent&& _Other) noexcept = delete;
	DummyPolySoundFrameEvent& operator=(const DummyPolySoundFrameEvent& _Other) = delete;
	DummyPolySoundFrameEvent& operator=(DummyPolySoundFrameEvent&& _Other) noexcept = delete;

protected:

private:


};

