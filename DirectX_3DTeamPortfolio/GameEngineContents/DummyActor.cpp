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
	FbxRenderer = CreateComponent<GameEngineFBXRenderer>();
	FbxRenderer->SetMesh("Sphere");
	FbxRenderer->SetMaterial("FBXStaticColor");
	FbxRenderer->Transform.SetLocalScale(float4(100,100,100));

	BodyCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Dummy);
	BodyCollision->SetCollisionType(ColType::SPHERE3D);

	ControlInput.SetPointer(this);

	CameraPivot = CreateComponent<GameEngineObject>();

	Transform.SetLocalPosition(float4(0, 50, 0));
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

float4 DummyActor::CalMouseAxis()
{
	float4 Axis = ContentsMouseInput::GetMouseMovePos();

	Yaxis -= Axis.Y * RotSensitive;
	Xaxis += Axis.Y * RotSensitive;
	
	Xaxis = ContentsMath::ClampDeg(Xaxis);
	Yaxis = std::clamp<float>(Yaxis, 0.0f, 360.0f);
	return float4(Xaxis, Yaxis);
}

constexpr float DumpTrace = 20.0f;

void DummyActor::PivotUpdate(float _Delta)
{
	float4 Axis = CalMouseAxis();

	float4 Result = float4::FORWARD * Axis.EulerDegToQuaternion().QuaternionToMatrix();

	float4 Pivot = Result * Camera_Dist;
		GetLevel()->GetMainCamera()->SetCameraTargetPivot(Pivot);
}