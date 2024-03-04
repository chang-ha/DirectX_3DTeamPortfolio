#pragma once
#include <GameEngineBase/GameEngineSerializer.h>

#include "FrameEventHelper.h"

#define EVENT_ERROR -1
#define EVENT_DONE 0
#define EVENT_PLAY 1
#define FE_NOINDEX -1


enum class Enum_FrameEventType
{
	None,
	Sound = 1,
	BSound = 2,
	CenterBodySound = 3,
	DPSound = 4,
	CollisionUpdate = 11,
	SwitchFlag = 16,
	Transfrom = 21,
	TurnSpeed = 22,

};


// 설명 :
class FrameEventObject : public GameEngineSerializObject
{
	friend class FrameEventHelper;
public:
	// constrcuter destructer
	FrameEventObject();
	~FrameEventObject();

	// delete Function
	FrameEventObject(const FrameEventObject& _Other) = delete;
	FrameEventObject(FrameEventObject&& _Other) noexcept = delete;
	FrameEventObject& operator=(const FrameEventObject& _Other) = delete;
	FrameEventObject& operator=(FrameEventObject&& _Other) noexcept = delete;

	virtual std::shared_ptr<FrameEventObject> CreatePlayingEvent() { return nullptr; }

	virtual void PlayEvent() = 0;
	virtual int UpdateEvent(float _Delta) { return EVENT_DONE; }
	virtual void Reset() {}

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

	inline void SetParentManger(FrameEventManager* _pManager) { ParentManager = _pManager; }
	inline FrameEventManager* GetEventManger() const { return ParentManager; }

protected:
	template<typename EnumType>
	void SetEventID(EnumType _ID) 
	{ 
		SetEventID(static_cast<int>(_ID));
	}

	inline void SetEventID(int _ID) { EventID = _ID; }
	int GetCurFrame();

	GameContentsFBXRenderer* GetParentRenderer() const;
	
	template<typename ObjectType>
	std::shared_ptr<ObjectType> GetDynamicCastParentActor()
	{
		GameContentsFBXRenderer* FBXRenderer = GetParentRenderer();
		if (nullptr == FBXRenderer)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다.");
			return nullptr;
		}

		std::shared_ptr<ObjectType> DynamicObject = FBXRenderer->GetActor()->GetDynamic_Cast_This<ObjectType>();
		if (nullptr == DynamicObject)
		{
			MsgBoxAssert("다이나믹 캐스팅된 액터가 존재하지 않습니다.");
			return nullptr;
		}

		return DynamicObject;
	}

protected:
	class FrameEventManager* ParentManager = nullptr;

	int EventID = 0;
	int StartFrame = 0;

};