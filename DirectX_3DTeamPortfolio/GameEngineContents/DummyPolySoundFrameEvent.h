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

	static std::shared_ptr<DummyPolySoundFrameEvent> CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName);

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << SoundName;
		_File << BoneIndex;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> SoundName;
		_File >> BoneIndex;
	}

	inline std::string_view GetSoundName() const
	{
		return SoundName;
	}

	void PlayEvent() override;
	void Init();

protected:

private:
	int BoneIndex = -1;
	std::string SoundName;

	float4x4 BoneMatrix;
	GameEngineActor* pActor = nullptr;

};