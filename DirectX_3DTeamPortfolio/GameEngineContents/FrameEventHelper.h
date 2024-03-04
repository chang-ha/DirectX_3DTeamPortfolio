#pragma once
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class FrameEventObject;
class FrameEventHelper : public GameEngineResources<FrameEventHelper>
{
public:
	// constrcuter destructer
	FrameEventHelper();
	~FrameEventHelper();

	// delete Function
	FrameEventHelper(const FrameEventHelper& _Other) = delete;
	FrameEventHelper(FrameEventHelper&& _Other) noexcept = delete;
	FrameEventHelper& operator=(const FrameEventHelper& _Other) = delete;
	FrameEventHelper& operator=(FrameEventHelper&& _Other) noexcept = delete;

	static inline std::string_view GetExtName() { return ExtName; }

	static std::string GetConvertFileName(std::string_view _AnimationName);

	static std::shared_ptr<FrameEventHelper> Load(class GameContentsFBXAnimationInfo* _AnimationInfo);

	static std::shared_ptr<FrameEventHelper> Load(std::string_view _Path)
	{
		GameEngineFile File(_Path.data());
		return Load(_Path, File.GetFileName());
	}

	static std::shared_ptr<FrameEventHelper> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<FrameEventHelper> Helper = CreateRes(_Name);
		Helper->Path = _Path;
		return Helper;
	}

	std::unique_ptr<FrameEventManager> Initialze(GameContentsFBXAnimationInfo* _AnimationInfo);

	void SaveFile();

	int GetEventSize();

	bool SetEvent(std::shared_ptr<FrameEventObject> _EventObject);
	void PopEvent(const std::shared_ptr<FrameEventObject>& _Event);


	template<typename _EventType>
	std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(_EventType _Type)
	{
		return GetEventGroup(static_cast<int>(_Type));
	}

	inline int GetFrameCount() const { return FrameCount; }
	inline std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& GetAllEvents() { return Events; }
	inline std::list<std::shared_ptr<FrameEventObject>>& GetEventGroup(int _Type);

protected:

private:
	static std::string ExtName;

	std::string Path;
	std::string AnimationName;

	int FrameCount = 0;

	std::map<int, std::list<std::shared_ptr<FrameEventObject>>> Events;

};