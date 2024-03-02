#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class CenterBodySoundFrameEvent : public FrameEventObject
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	CenterBodySoundFrameEvent();
	~CenterBodySoundFrameEvent();

	// delete Function
	CenterBodySoundFrameEvent(const CenterBodySoundFrameEvent& _Other) = delete;
	CenterBodySoundFrameEvent(CenterBodySoundFrameEvent&& _Other) noexcept = delete;
	CenterBodySoundFrameEvent& operator=(const CenterBodySoundFrameEvent& _Other) = delete;
	CenterBodySoundFrameEvent& operator=(CenterBodySoundFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<CenterBodySoundFrameEvent> CreateEventObject(int _Frame, int _RefID, int _AttachBoneIndex);

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << RefID;
		_File << AttachBoneIndex;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> RefID;
		_File >> AttachBoneIndex;
	}

	void PlayEvent() override;
	void Init();

protected:

private:
	int RefID = FE_NOINDEX;
	int AttachBoneIndex = FE_NOINDEX;

	class GameContentsFBXRenderer* FbxRenderer = nullptr;
	class BaseActor* pActor = nullptr;

	float4 DPT = float4::ZERO; // DummyPoly Transition
	float4x4* pBoneMatrix = nullptr;


};