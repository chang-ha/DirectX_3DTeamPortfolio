#pragma once
#include <GameEngineBase/GameEngineSerializer.h>

#define EVENT_ERROR -1
#define EVENT_DONE 0
#define EVENT_PLAY 1


enum Enum_FrameEventType
{
	None,
	Sound,
	CollisionUpdate = 11,
	Transfrom = 21,

};


// Ό³Έν :
class FrameEventObject : public GameEngineSerializObject
{
public:
	// constrcuter destructer
	FrameEventObject();
	~FrameEventObject();

	// delete Function
	FrameEventObject(const FrameEventObject& _Other) = delete;
	FrameEventObject(FrameEventObject&& _Other) noexcept = delete;
	FrameEventObject& operator=(const FrameEventObject& _Other) = delete;
	FrameEventObject& operator=(FrameEventObject&& _Other) noexcept = delete;

	virtual void PlayEvent() = 0;
	virtual int UpdateEvent(float _Delta) { return EVENT_DONE; }

	void Write(class GameEngineSerializer& _File) override
	{
		_File << static_cast<int>(EventID);
		_File << StartFrame;
	}
	void Read(class GameEngineSerializer& _File) override
	{
		_File >> StartFrame;
	}

	inline int GetFrame() const
	{
		return StartFrame;
	}

	inline int GetEventID() const
	{
		return EventID;
	}

	std::string GetTypeString() const;

	inline void SetParent(FrameEventHelper* _Parent) { ParentHelper = _Parent; }

protected:
	inline void SetEventID(int _ID) { EventID = _ID; }
	int GetCurFrame();

protected:
	class FrameEventHelper* ParentHelper = nullptr;

	int EventID = 0;
	int StartFrame = 0;

};