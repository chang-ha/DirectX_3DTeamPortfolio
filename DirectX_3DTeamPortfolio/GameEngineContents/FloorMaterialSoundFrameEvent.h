#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class FloorMaterialSoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	FloorMaterialSoundFrameEvent();
	~FloorMaterialSoundFrameEvent();

	// delete Function
	FloorMaterialSoundFrameEvent(const FloorMaterialSoundFrameEvent& _Other) = delete;
	FloorMaterialSoundFrameEvent(FloorMaterialSoundFrameEvent&& _Other) noexcept = delete;
	FloorMaterialSoundFrameEvent& operator=(const FloorMaterialSoundFrameEvent& _Other) = delete;
	FloorMaterialSoundFrameEvent& operator=(FloorMaterialSoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<FloorMaterialSoundFrameEvent> CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName);

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