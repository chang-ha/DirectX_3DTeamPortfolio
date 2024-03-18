#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class TurnSpeedFrameEvent : public FrameEventObject
{
public:
	// constrcuter destructer
	TurnSpeedFrameEvent();
	~TurnSpeedFrameEvent();

	// delete Function
	TurnSpeedFrameEvent(const TurnSpeedFrameEvent& _Other) = delete;
	TurnSpeedFrameEvent(TurnSpeedFrameEvent&& _Other) noexcept = delete;
	TurnSpeedFrameEvent& operator=(const TurnSpeedFrameEvent& _Other) = delete;
	TurnSpeedFrameEvent& operator=(TurnSpeedFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<TurnSpeedFrameEvent> CreateEventObject(int _SFrame, int _EFrame, float _TurnSpeed);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << EndFrame;
		_File << TurnAngle;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> EndFrame;
		_File >> TurnAngle;
	}

	inline int GetEndFrame() const
	{
		return EndFrame;
	}


	int PlayEvent() override;
	int UpdateEvent(float _Delta) override;

	void Init();

protected:

private:
	int EndFrame = -1;
	float TurnAngle = 0.0f;
	float TurnSpeed = 0.0f;
	bool bFixSpeed = true;

	class BaseActor* pParentActor = nullptr;

};