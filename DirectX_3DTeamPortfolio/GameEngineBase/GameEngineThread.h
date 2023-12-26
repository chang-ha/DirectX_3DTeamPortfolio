#pragma once
#include <thread>
#include <string>
#include <functional>

// Ό³Έν :
class GameEngineThread
{
public:
	// constrcuter destructer
	GameEngineThread();
	~GameEngineThread();

	// delete Function
	GameEngineThread(const GameEngineThread& _Other) = delete;
	GameEngineThread(GameEngineThread&& _Other) noexcept = delete;
	GameEngineThread& operator=(const GameEngineThread& _Other) = delete;
	GameEngineThread& operator=(GameEngineThread&& _Other) noexcept = delete;

	void Start(std::string _Name, std::function<void()> _Function);
	void Join();

protected:

private:
	std::thread GameThread;
	std::function<void()> CallBackFunction;

	static void ThreadBaseFunction(GameEngineThread* Thread, std::string Name);
};

