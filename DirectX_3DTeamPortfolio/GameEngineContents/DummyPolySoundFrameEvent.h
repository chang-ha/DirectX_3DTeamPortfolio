#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class DummyPolySoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	DummyPolySoundFrameEvent();
	~DummyPolySoundFrameEvent();

	// delete Function
	DummyPolySoundFrameEvent(const DummyPolySoundFrameEvent& _Other) = delete;
	DummyPolySoundFrameEvent(DummyPolySoundFrameEvent&& _Other) noexcept = delete;
	DummyPolySoundFrameEvent& operator=(const DummyPolySoundFrameEvent& _Other) = delete;
	DummyPolySoundFrameEvent& operator=(DummyPolySoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<DummyPolySoundFrameEvent> CreateEventObject(int _Frame, std::string_view _SoundName, int _RefID, int _AttachBoneIndex);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << SoundName;
		_File << RefID;
		_File << AttachBoneIndex;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> SoundName;
		_File >> RefID;
		_File >> AttachBoneIndex;
	}

	int PlayEvent() override;
	void Init();

protected:

private:
	int RefID = FE_NOINDEX;
	int AttachBoneIndex = FE_NOINDEX;

	class GameContentsFBXRenderer* FbxRenderer = nullptr;

	std::string SoundName;
	float4 DPT = float4::ZERO; // DummyPoly Transition
	float4x4* pBoneMatrix = nullptr;
	bool* DummySoundSwitch = nullptr;
};