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

	void CopyEvent(const std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& _Events);
	void SetEvent(std::shared_ptr<FrameEventObject> _EventObject);
	void PopEvent(const std::shared_ptr<FrameEventObject>& _Event);
	void PushEvent(FrameEventObject* _Object);
	void PlayEvents(int _CurFrame);
	void UpdateEvent(float _Delta);
	void EventReset();
	void EventRelease();

	inline void SetHelper(class FrameEventHelper* _pHelper) { pHelper = _pHelper; }
	inline class FrameEventHelper* GetHelper() const { return pHelper; }
	inline void SetAnimationInfo(class GameContentsFBXAnimationInfo* _AnimationInfo) { AnimationInfo = _AnimationInfo; }
	inline class GameContentsFBXAnimationInfo* GetAnimationInfo() { return AnimationInfo; }
	inline const std::multimap<int, std::shared_ptr<FrameEventObject>>& GetEventInfo() { return EventInfos; }

protected:
	static std::unique_ptr<FrameEventManager> CreateEventManager();

private:
	class GameContentsFBXAnimationInfo* AnimationInfo = nullptr;
	class FrameEventHelper* pHelper = nullptr;

	std::multimap<int, std::shared_ptr<FrameEventObject>> EventInfos;
	std::list<FrameEventObject*> PlayingEvents;

};