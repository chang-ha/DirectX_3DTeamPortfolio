#include "PreCompile.h"
#include "GameEngineDebug.h"
#include <crtdbg.h>

void GameEngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameEngineDebug::GetWindowLastErrorPrint()
{
	// 윈도우 함수를 사용했는데 에러가 나거나 결과가 이상하다면
	// 이 함수를 사용하면
	// 그 에러의 실제 에러코드와 텍스트도 알수 있다.

	DWORD error = GetLastError();
	char* message = nullptr;

	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&message,
		0,
		nullptr);

	if (nullptr != message)
	{
		std::string Text = "Code : ";
		Text += std::to_string(error);
		Text += " Message : ";
		Text += message;

		MessageBoxA(nullptr, (Text).c_str(), "Error", MB_OK);
		// 운영체제가 준건 해제헤야 한다.
		// 서버면 더더더더더더욱
		// 실행중 발생하는 릭이 가장 위험하다.
		// 힙이 비대해지기 시작합니다.
		// 램을 초과하면서 터진다.
		LocalFree(message);
	}
}