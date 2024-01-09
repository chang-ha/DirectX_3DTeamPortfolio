#include "PreCompile.h"
#include "GameEngineThreadJobQueue.h"
#include "GameEngineDebug.h"

std::atomic_int GameEngineThreadJobQueue::RunThreadCount = 0;

GameEngineThreadJobQueue::GameEngineThreadJobQueue() 
{
}

GameEngineThreadJobQueue::~GameEngineThreadJobQueue() 
{
	End();
}

void GameEngineThreadJobQueue::ThreadPoolFunction(GameEngineThreadJobQueue* _Queue, HANDLE _IOCPHandle)
{
	// 4바이트 정수
	DWORD Byte; // 날아온 패킷의 크기

	// 8바이트 정수
	ULONG_PTR Ptr; // 전달해주고 싶은 포인터키

	// 서버할때 
	LPOVERLAPPED OverLapped = nullptr; // 현재까지 얼마나 받았는지 

	while (_Queue->IsRun)
	{
		// 일이 보내질때까지 이 함수를 리턴하지 않겠다.
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &Ptr, &OverLapped, INFINITE);

		ThreadJobType Value = static_cast<ThreadJobType>(Byte);

		switch (Value)
		{
		case ThreadJobType::UserJob:
		{
			if (0 != Ptr)
			{
				Job* J = reinterpret_cast<Job*>(Ptr);
				if (nullptr != J->Job)
				{
					J->Job();
				}
				delete J;
			}

			break;
		}
		case ThreadJobType::Destroy:
			_Queue->RunThreadCount -= 1;
			return;
		default:
			// 양수로 왔다는건데. => 서버통신.
			break;
		}
	}

}

void GameEngineThreadJobQueue::Initialize(const std::string_view& _ThreadName, int _ThreadCount/* = 0*/)
{
	ThreadCount = _ThreadCount;

	if (0 == _ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount = Info.dwNumberOfProcessors;
	}

	// 최초에 IOCP를 만드는 사용법의 함수입니다.
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	// 값이 차는 사용법은 통신이나 파일입출력 관련으로 사용할때 이다.

	// IOCP를 만들고 관리해야할 쓰레드의 개수를 알려줬다.

	if (nullptr == IOCPHandle)
	{
		MsgBoxAssert("IOCP 핸들 생성에 실패했습니다.");
	}

	RunThreadCount = ThreadCount;

	AllThread.resize(ThreadCount);

	for (int i = 0; i < static_cast<int>(AllThread.size()); i++)
	{
		AllThread[i] = std::make_shared<GameEngineThread>();
		// std::function<void()>
		AllThread[i]->Start(std::string(std::to_string(i) + _ThreadName.data()), std::bind(ThreadPoolFunction, this, IOCPHandle));
	}
}


void GameEngineThreadJobQueue::Work(std::function<void()> _Function)
{
	Job* NewJob = new Job();
	NewJob->Job = _Function;

	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadJobType::UserJob), reinterpret_cast<__int64>(NewJob), nullptr);
}

void GameEngineThreadJobQueue::End()
{
	IsRun = false;

	while (RunThreadCount)
	{
		PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadJobType::Destroy), 0, nullptr);
	}
}
