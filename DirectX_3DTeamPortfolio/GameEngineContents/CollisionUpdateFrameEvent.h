#pragma once
#include "FrameEventObject.h"

// Ό³Έν :
class CollisionUpdateFrameEvent : public FrameEventObject
{
public:
	// constrcuter destructer
	CollisionUpdateFrameEvent();
	~CollisionUpdateFrameEvent();

	// delete Function
	CollisionUpdateFrameEvent(const CollisionUpdateFrameEvent& _Other) = delete;
	CollisionUpdateFrameEvent(CollisionUpdateFrameEvent&& _Other) noexcept = delete;
	CollisionUpdateFrameEvent& operator=(const CollisionUpdateFrameEvent& _Other) = delete;
	CollisionUpdateFrameEvent& operator=(CollisionUpdateFrameEvent&& _Other) noexcept = delete;

	static std::shared_ptr<CollisionUpdateFrameEvent> CreateEventObject(int _SFrame, int _EFrame, std::shared_ptr<class BoneSocketCollision> Collision);
	std::shared_ptr<FrameEventObject> CreatePlayingEvent() override;

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << EndFrame;
		_File << ColNumber;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> EndFrame;
		_File >> ColNumber;
	}

	inline int GetEndFrame() const
	{
		return EndFrame;
	}

	inline int GetTypeNumber() const
	{
		return ColNumber;
	}


	std::shared_ptr<FrameEventObject> PlayEvent() override;
	int UpdateEvent(float _Delta) override;
	void Reset() override;

	void Init();


protected:

private:
	static const Enum_FrameEventType Type = Enum_FrameEventType::CollisionUpdate;

	int EndFrame = -1;
	int ColNumber = -1;

	class BoneSocketCollision* pCollision = nullptr;

};

