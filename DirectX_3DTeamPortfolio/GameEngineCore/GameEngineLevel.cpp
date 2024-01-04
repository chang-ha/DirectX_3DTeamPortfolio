#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineLight.h"
#include "GameEngineCollision.h"
#include "GameEngineCollisionGroup.h"
#include "GAMEENGINERENDERTARGET.H"

bool GameEngineLevel::IsDebug = true;

GameEngineLevel::GameEngineLevel() 
{
	// Main
	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(INT_MIN, ECAMERAORDER::Main);
		GameEngineInput::AddInputObject(NewCamera.get());

	}

	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(INT_MIN, ECAMERAORDER::UI);
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	LevelRenderTarget = GameEngineRenderTarget::Create();
	LevelRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
}

std::shared_ptr<GameEngineCamera> GameEngineLevel::CreateCamera(int _Order, int _CameraOrder)
{
	std::shared_ptr<GameEngineCamera> NewCamera = CreateActor<GameEngineCamera>(_Order);
	NewCamera->SetCameraOrder(_CameraOrder);
	return NewCamera;
}

GameEngineLevel::~GameEngineLevel() 
{
}

void GameEngineLevel::Start() 
{
}

void GameEngineLevel::PushLight(std::shared_ptr<GameEngineLight> _Light)
{
	AllLight.push_back(_Light);
}

void GameEngineLevel::AllUpdate(float _Delta)
{
	GameEngineDebug::GameEngineDebugCore::CurLevel = this;

	Update(_Delta);

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		float TimeScale = GameEngineCore::MainTime.GetTimeScale(_Pair.first);
		for (std::shared_ptr<GameEngineObject>& _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->AddLiveTime(_Delta * TimeScale);
			_Actor->AllUpdate(_Delta * TimeScale);
		}
	}

	int a = 0;
}

void GameEngineLevel::Render(float _Delta)
{
	LevelRenderTarget->Clear();

	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& CameraPair : Cameras)
	{
		if (nullptr == CameraPair.second)
		{
			continue;
		}

		if (false == CameraPair.second->IsUpdate())
		{
			continue;
		}

		std::shared_ptr<GameEngineCamera>& Camera = CameraPair.second;
		// 카메라 행렬 계산하고
		Camera->CameraUpdate(_Delta);

		// 빛한테 나눠주고
		LightDataObject.LightCount = 0;
		for (std::shared_ptr<GameEngineLight> Light : AllLight)
		{
			Light->LightUpdate(Camera.get(), _Delta);
			LightDataObject.AllLight[LightDataObject.LightCount] = Light->GetLightData();
			++LightDataObject.LightCount;
		}

		// 라이트 데이터는 미리 계산되어 있어야 한다.

		// 
		Camera->Render(_Delta);
	}

	// post process라는것을 보여줄것인데.

	// 뭔가 
	LevelRenderTarget->PostEffect(_Delta);

	GameEngineCore::GetBackBufferRenderTarget()->Copy(0, LevelRenderTarget, 0);

	if (true == IsDebug)
	{
		GameEngineCore::GetBackBufferRenderTarget()->Setting();

		GameEngineDebug::GameEngineDebugCore::DebugRender();
		// 몬가를 한다.
	}
}

void GameEngineLevel::Release()
{
	// MsgBoxAssert("치명적인 버그를 발견하셨군요 팀장님한테 연락하세요. 사수 거칠필요 없습니다. 연락 xxx 번호");
	MsgBoxAssert("레벨은 엔진 규칙상 삭제할수 없습니다.");
}

void GameEngineLevel::AllReleaseCheck()
{
	// 레벨은 지워질일이 없기 때문에 스스로의 release는 호출하지 않는다.
	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& Pair : Cameras)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}

	for (std::pair<const int, std::shared_ptr<class GameEngineCollisionGroup>>& Pair : Collisions)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}


	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineObject>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineObject>>::iterator End = Group.end();

		for (; Start != End;)
		{
			(*Start)->AllReleaseCheck();

			if (false == (*Start)->IsDeath())
			{
				++Start;
				continue;
			}

			Start = Group.erase(Start);
		}
	}
}

void GameEngineLevel::ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order, std::string_view _Name/* = ""*/)
{
	_Actor->SetName(_Name);
	_Actor->SetParent(this, _Order);
	_Actor->Start();
}

void GameEngineLevel::PushCollision(std::shared_ptr<class GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("존재하지 않는 콜리전을 사용하려고 했습니다.");
		return;
	}

	if (false == Collisions.contains(_Collision->GetOrder()))
	{
		Collisions[_Collision->GetOrder()] = std::make_shared<GameEngineCollisionGroup>();
	}

	Collisions[_Collision->GetOrder()]->PushCollision(_Collision);
}

