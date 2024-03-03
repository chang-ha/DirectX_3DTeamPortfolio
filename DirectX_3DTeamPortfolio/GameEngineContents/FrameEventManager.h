#pragma once

// Ό³Έν :
class FrameEventObject;
class FrameEventManager
{
	friend class FrameEventHelper;

public:
	// constrcuter destructer
	FrameEventManager();
	~FrameEventManager();

	// delete Function
	FrameEventManager(const FrameEventManager& _Other) = delete;
	FrameEventManager(FrameEventManager&& _Other) noexcept = delete;
	FrameEventManager& operator=(const FrameEventManager& _Other) = delete;
	FrameEventManager& operator=(FrameEventManager&& _Other) noexcept = delete;

	class FrameEventHelper* GetHelper() const { return pHelper; }
	void SetHelper(class FrameEventHelper* _pHelper) { pHelper = _pHelper; }
	void SetAnimationInfo(class GameContentsFBXAnimationInfo* _AnimationInfo) { AnimationInfo = _AnimationInfo; }

	void SetEvent(std::shared_ptr<FrameEventObject> _EventObject);
	void PopEvent(const std::shared_ptr<FrameEventObject>& _Event);
	void PushEvent(std::shared_ptr<FrameEventObject> _Object);
	void PlayEvents(int _CurFrame);
	void UpdateEvent(float _Delta);
	void EventReset();

	inline class GameContentsFBXAnimationInfo* GetAnimationInfo() { return AnimationInfo; }

protected:
	static std::unique_ptr<FrameEventManager> CreateEventManager();

private:
	class GameContentsFBXAnimationInfo* AnimationInfo = nullptr;
	class FrameEventHelper* pHelper = nullptr;

	std::list<std::shared_ptr<FrameEventObject>> PlayingEvents;

};