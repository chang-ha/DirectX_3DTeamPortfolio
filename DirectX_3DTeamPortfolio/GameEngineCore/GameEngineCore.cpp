#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineGUI.h"

std::shared_ptr<GameEngineObject> GameEngineCore::CoreObject;
GameEngineTime GameEngineCore::MainTime;
GameEngineWindow GameEngineCore::MainWindow;
GameEngineDevice GameEngineCore::MainDevice;

std::shared_ptr<GameEngineLevel> GameEngineCore::CurLevel;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel;
std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::AllLevel;



GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

void GameEngineCore::Start() 
{
	GameEngineGUI::Start();
	CoreObject->Start();
}

void GameEngineCore::Update() 
{


	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->AllLevelEnd(NextLevel.get());
			CurLevel->AllReleaseCheck();
		}

		// NextLevel->OverCheck(CurLevel);

		NextLevel->AllLevelStart(CurLevel.get());

		CurLevel = NextLevel;

		NextLevel = nullptr;
		MainTime.Reset();
	}

	MainTime.Update();
	float DeltaTime = MainTime.GetDeltaTime();

	if (DeltaTime > 1.0f / 60.0f)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	GameEngineSound::Update();
	CoreObject->Update(DeltaTime);

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(DeltaTime);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->AddLiveTime(DeltaTime);
	CurLevel->AllUpdate(DeltaTime);

	//HDC DC;
	//{
	//	DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
	//	float4 WinScale = GameEngineCore::MainWindow.GetScale();
	//	Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	//}

	MainDevice.RenderStart();

	CurLevel->Render(DeltaTime);

	GameEngineGUI::GUIRender(CurLevel.get(), DeltaTime);

	MainDevice.RenderEnd();

	CurLevel->AllReleaseCheck();
}

void GameEngineCore::Release() 
{
	if (nullptr != CoreObject)
	{
		CoreObject->Release();
		CoreObject = nullptr;
	}
	CurLevel = nullptr;
	AllLevel.clear();
	Resources_Release();
	GameEngineGUI::Release();
	GameEngineSound::Release();
}

void GameEngineCore::EngineProcess(HINSTANCE _Inst, const std::string& _WindowName, float4 _Pos, float4 _Size)
{
	// 릭체크 해주고
	GameEngineDebug::LeakCheck();

	// 윈도우 만들고
	MainWindow.Open(_WindowName, _Inst);
	MainWindow.SetPosAndScale(_Pos, _Size);

	// 3D 디바이스를 그 윈도우를 기반으로 만든다.
	MainDevice.Initiallize(MainWindow);

	// 시간이나 타임
	GameEngineWindow::MessageLoop(_Inst, Start, Update, Release);
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level, std::string_view _Name)
{
	_Level->SetName(_Name);



	_Level->Start();
}