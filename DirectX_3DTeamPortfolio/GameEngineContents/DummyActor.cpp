#include "PreCompile.h"
#include "DummyActor.h"

#include "ContentsMouseInput.h"
#include "ContentsMath.h"


constexpr float MinDist = 50.0f;
constexpr float MaxDist = 500.0f;

DummyActor::DummyActor() 
{
	GameEngineInput::AddInputObject(this);
}

DummyActor::~DummyActor() 
{
}


void DummyActor::On()
{
	GameEngineObjectBase::On();
}

void DummyActor::Off()
{
	GameEngineObjectBase::Off();

	if (true == IsCameraTargetting())
	{
		DettachCamera();
	}
}

void DummyActor::Start()
{
	BodyCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Dummy);
	BodyCollision->SetCollisionType(ColType::SPHERE3D);
	BodyCollision->Transform.SetWorldScale(float4(100.0f, 100.0f, 100.0f));

	ControlInput.SetPointer(this);

	CameraPivot = CreateComponent<GameEngineObject>();

	//Transform.SetLocalPosition(float4(0, 30.0f * 0.5f, 0));
}

void DummyActor::Update(float _Delta)
{
	MoveUpdate(_Delta);

	if (true == IsCameraTargetting())
	{
		PivotUpdate(_Delta);
	}
}

void DummyActor::Release()
{
	FbxRenderer = nullptr;
	BodyCollision = nullptr;
	CameraPivot = nullptr;

	BaseActor::Release();
}

void DummyActor::LevelEnd(class GameEngineLevel* _PrevLevel)
{
	DettachCamera();
}


void DummyActor::MoveUpdate(float _Delta)
{
	float4 DirVector = ControlInput.GetInputVector();
	Transform.AddLocalPosition(DirVector * Speed * _Delta);
}

void DummyActor::AttachCamera()
{
	GetLevel()->GetMainCamera()->CameraTargetSetting(Transform, float4::ZERO);
	SetCameraDist(MinDist);
}

void DummyActor::DettachCamera()
{
	GetLevel()->GetMainCamera()->CameraTargetReset();
}

bool DummyActor::IsCameraTargetting()
{
	bool bTargetThis = GetLevel()->GetMainCamera()->IsCameraTargetting(&Transform);
	if (true == bTargetThis)
	{
		return true;
	}

	return false;
}



void DummyActor::SetCameraDist(float _fDist)
{
	Camera_Dist = std::clamp(Camera_Dist, MinDist, MaxDist);
}

constexpr float RotSensitive = 1.0f;
constexpr float RotationMin = -70.0f;
constexpr float RotationMax = 70.0f;

void DummyActor::CalMouseAxis()
{
	ScreenMousePos = GameEngineCore::MainWindow.GetMousePos();
	MoveDir = ScreenMousePrevPos - ScreenMousePos;
	MouseDir = MoveDir.NormalizeReturn();
	ScreenMousePrevPos = ScreenMousePos;
}

constexpr float DumpTrace = 20.0f;

void DummyActor::PivotUpdate(float _Delta)
{
	CalMouseAxis();
	MouseDir *= _Delta * 360.0f;

	GetLevel()->GetMainCamera()->Transform.AddLocalRotation(float4(-MouseDir.Y, -MouseDir.X));
}