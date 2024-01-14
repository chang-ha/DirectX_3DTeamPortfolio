#pragma once
#include <GameEngineBase/GameEngineSerializer.h>

enum Enum_FrameEventType
{
	None,
	Sound,
	Collision,
	Transfrom,

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

	void Write(class GameEngineSerializer& _File) override
	{
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

	Enum_FrameEventType GetType() 
	{
		return Type;
	}

	std::string GetTypeString() const;

protected:
	Enum_FrameEventType Type = Enum_FrameEventType::None;
	int StartFrame = 0;

};