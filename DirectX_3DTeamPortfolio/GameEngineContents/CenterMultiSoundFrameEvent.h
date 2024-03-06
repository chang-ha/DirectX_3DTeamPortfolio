#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class CenterMultiSoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	CenterMultiSoundFrameEvent();
	~CenterMultiSoundFrameEvent();

	// delete Function
	CenterMultiSoundFrameEvent(const CenterMultiSoundFrameEvent& _Other) = delete;
	CenterMultiSoundFrameEvent(CenterMultiSoundFrameEvent&& _Other) noexcept = delete;
	CenterMultiSoundFrameEvent& operator=(const CenterMultiSoundFrameEvent& _Other) = delete;
	CenterMultiSoundFrameEvent& operator=(CenterMultiSoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<CenterMultiSoundFrameEvent> CreateEventObject(int _Frame);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << SoundIndex;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> SoundIndex;
	}

	int PlayEvent() override;
	void Init();

protected:

private:
	class GameContentsFBXRenderer* FbxRenderer = nullptr;
	class BaseActor* pActor = nullptr;
	int SoundIndex = -1;

	float4 DPT = float4::ZERO; // DummyPoly Transition
	float4x4* pBoneMatrix = nullptr;


};