#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineThread.h"

enum class ThreadJobType
{
	UserJob = -2,
	Destroy = -1,
};

// Ό³Έν :
class GameEngineThreadJobQueue
{
	class Job
	{
	public:
		std::function<void()> Job;
	};

public:
	// constrcuter destructer
	GameEngineThreadJobQueue();
	~GameEngineThreadJobQueue();

	// delete Function
	GameEngineThreadJobQueue(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue(GameEngineThreadJobQueue&& _Other) noexcept = delete;
	GameEngineThreadJobQueue& operator=(const GameEngineThreadJobQueue& _Other) = delete;
	GameEngineThreadJobQueue& operator=(GameEngineThreadJobQueue&& _Other) noexcept = delete;

	void Initialize(const std::string_view& _ThreadName, int _ThreadCount = 0);

	void Work(std::function<void()> _Function);

	void End();

protected:

private:
	HANDLE IOCPHandle = nullptr;
	int ThreadCount = -1;

	static std::atomic_int RunThreadCount;
	std::atomic_bool IsRun = true;
	std::vector<std::shared_ptr<GameEngineThread>> AllThread;

	static void ThreadPoolFunction(GameEngineThreadJobQueue* _Queue, HANDLE _IOCPHandle);

	// static void ThreadPoolFunction()
};