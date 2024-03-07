#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class SingleCenterSoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	SingleCenterSoundFrameEvent();
	~SingleCenterSoundFrameEvent();

	// delete Function
	SingleCenterSoundFrameEvent(const SingleCenterSoundFrameEvent& _Other) = delete;
	SingleCenterSoundFrameEvent(SingleCenterSoundFrameEvent&& _Other) noexcept = delete;
	SingleCenterSoundFrameEvent& operator=(const SingleCenterSoundFrameEvent& _Other) = delete;
	SingleCenterSoundFrameEvent& operator=(SingleCenterSoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<SingleCenterSoundFrameEvent> CreateEventObject(int _Frame);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
	}

	int PlayEvent() override;
	void Init();

protected:

private:
	class GameContentsFBXRenderer* FbxRenderer = nullptr;
	class BaseActor* pActor = nullptr;

	float4 DPT = float4::ZERO; // DummyPoly Transition
	float4x4* pBoneMatrix = nullptr;


};