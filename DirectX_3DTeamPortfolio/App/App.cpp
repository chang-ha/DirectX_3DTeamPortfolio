#include <GameEngineContents/PreCompile.h>

#pragma comment(lib, "GameEngineContents.lib")

#include <GameEngineContents/ContentsCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<ContentsCore>(hInstance);
}

