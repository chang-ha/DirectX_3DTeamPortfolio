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
	// 4����Ʈ ����
	DWORD Byte; // ���ƿ� ��Ŷ�� ũ��

	// 8����Ʈ ����
	ULONG_PTR Ptr; // �������ְ� ���� ������Ű

	// �����Ҷ� 
	LPOVERLAPPED OverLapped = nullptr; // ������� �󸶳� �޾Ҵ��� 

	while (_Queue->IsRun)
	{
		// ���� ������������ �� �Լ��� �������� �ʰڴ�.
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
			// ����� �Դٴ°ǵ�. => �������.
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

	// ���ʿ� IOCP�� ����� ������ �Լ��Դϴ�.
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	// ���� ���� ������ ����̳� ��������� �������� ����Ҷ� �̴�.

	// IOCP�� ����� �����ؾ��� �������� ������ �˷����.

	if (nullptr == IOCPHandle)
	{
		MsgBoxAssert("IOCP �ڵ� ������ �����߽��ϴ�.");
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
