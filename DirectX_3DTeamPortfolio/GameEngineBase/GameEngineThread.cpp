#include "PreCompile.h"
#include "GameEngineThread.h"
#include "GameEngineString.h"

GameEngineThread::GameEngineThread() 
{
}

GameEngineThread::~GameEngineThread() 
{
	Join();
}

void GameEngineThread::Join()
{
	if (nullptr != CallBackFunction)
	{
		GameThread.join();
		CallBackFunction = nullptr;
	}
}

void GameEngineThread::ThreadBaseFunction(GameEngineThread* Thread, std::string Name)
{
	// 여기는 이미 쓰레드
	std::wstring String = GameEngineString::AnsiToUnicode(Name);
	SetThreadDescription(GetCurrentThread(), String.c_str());
	Thread->CallBackFunction();
}

void GameEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	CallBackFunction = _Function;
	GameThread = std::thread(ThreadBaseFunction, this, _Name);
}