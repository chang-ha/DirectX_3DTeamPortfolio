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
		_File << static_cast<int>(Type);
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

	inline Enum_FrameEventType GetType() const
	{
		return Type;
	}

	std::string GetTypeString() const;

	void SetParent(FrameEventHelper* _Parent) { ParentHelper = _Parent; }

protected:
	class FrameEventHelper* ParentHelper = nullptr;

	Enum_FrameEventType Type = Enum_FrameEventType::None;
	int StartFrame = 0;

};