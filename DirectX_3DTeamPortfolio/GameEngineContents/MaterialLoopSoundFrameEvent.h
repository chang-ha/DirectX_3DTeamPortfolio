#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class MaterialLoopSoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	MaterialLoopSoundFrameEvent();
	~MaterialLoopSoundFrameEvent();

	// delete Function
	MaterialLoopSoundFrameEvent(const MaterialLoopSoundFrameEvent& _Other) = delete;
	MaterialLoopSoundFrameEvent(MaterialLoopSoundFrameEvent&& _Other) noexcept = delete;
	MaterialLoopSoundFrameEvent& operator=(const MaterialLoopSoundFrameEvent& _Other) = delete;
	MaterialLoopSoundFrameEvent& operator=(MaterialLoopSoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<MaterialLoopSoundFrameEvent> CreateEventObject(int _Frame, int _SoundIndex);
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