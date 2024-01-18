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

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << EndFrame;
		_File << TurnSpeed;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> EndFrame;
		_File >> TurnSpeed;
	}

	inline int GetEndFrame() const
	{
		return EndFrame;
	}


	void PlayEvent() override;
	int UpdateEvent(float _Delta) override;

	void Init();


protected:

private:
	static const Enum_FrameEventType Type = Enum_FrameEventType::TurnSpeed;

	int EndFrame = -1;
	float TurnSpeed = 0.0f;

	class BaseMonster* pParentActor = nullptr;

};