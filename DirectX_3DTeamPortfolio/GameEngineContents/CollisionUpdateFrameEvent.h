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

	void Write(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Write(_File);
		_File << EndFrame;
		_File << TypeNumber;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		FrameEventObject::Read(_File);
		_File >> EndFrame;
		_File >> TypeNumber;
	}

	inline int GetEndFrame() const
	{
		return EndFrame;
	}

	inline int GetTypeNumber() const
	{
		return TypeNumber;
	}


	void PlayEvent() override;


protected:

private:
	int EndFrame = -1;
	int TypeNumber = -1;

	BoneSocketCollision* pCollision;

};

