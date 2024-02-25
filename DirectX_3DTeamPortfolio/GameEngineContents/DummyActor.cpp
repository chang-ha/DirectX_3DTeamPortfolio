#include "PreCompile.h"
#include "DummyActor.h"

#include "ContentsMouseInput.h"
#include "ContentsDebug.h"

#include "DummyProjectile.h"

const float RenScale = 10.0f;

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

static constexpr int MAX_PROJECTILE = 10;

void DummyActor::Start()
{
	MainRenderer = CreateComponent<GameEngineRenderer>(Enum_RenderOrder::Monster);
	MainRenderer->SetMesh("Box");
	MainRenderer->SetMaterial("FBXStaticColor");
	MainRenderer->Transform.SetWorldScale(float4(RenScale, RenScale, RenScale));

	BodyCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Dummy);
	BodyCollision->SetCollisionType(ColType::SPHERE3D);
	BodyCollision->Transform.SetWorldScale(float4(1.0f, 1.0f, 1.0f));
	BodyCollision->Transform.SetLocalPosition(float4::ZERO);


	 Projectiles.resize(MAX_PROJECTILE);

	 for (int i = 0; i < MAX_PROJECTILE; i++)
	 {
		  std::shared_ptr<DummyProjectile> pActor = GetLevel()->CreateActor<DummyProjectile>(Enum_CollisionOrder::MonsterAttack);
		  pActor->Init(this);
		  Projectiles[i] = pActor;
	 }

	ControlInput.SetPointer(this);
	CameraControler.Init(this);

	Transform.SetLocalPosition(float4(0, 100.0f, 0));

	Off();
}

void DummyActor::Update(float _Delta)
{
	MoveUpdate(_Delta);
	CameraControlUpdate(_Delta);
	ProjectileUpdate(_Delta);
}

void DummyActor::Release()
{
	CameraControler.Release();
	MainRenderer = nullptr;
	BodyCollision = nullptr;

	Projectiles.clear();

	BaseActor::Release();
}

void DummyActor::LevelEnd(class GameEngineLevel* _PrevLevel)
{
	DettachCamera();
}

/////////
// Input for Move Logic
void DummyActor::MoveUpdate(float _Delta)
{
	float4 InputVector = ControlInput.GetInputVector();

	if (float4::ZERO != InputVector)
	{
		if (CameraControler.IsUpdate())
		{
			const float4 Rot = CameraControler.GetQuaternion();
			const float4 DirVector = InputVector.VectorRotationToDegYReturn(Rot.Y);
			const float4 MovePos = DirVector * MoveSpeed* _Delta;
			Transform.SetLocalRotation(float4(0.0f, Rot.Y));
			Transform.AddLocalPosition(MovePos);
		}
		else
		{
			const float4 MovePos = InputVector * MoveSpeed * _Delta;
			Transform.AddLocalPosition(MovePos);
		}
	}
}

static constexpr float FIRE_COOL_TIME = 0.1f;

void DummyActor::ProjectileUpdate(float _Delta)
{
	if (StateTime < FIRE_COOL_TIME)
	{
		StateTime += _Delta;
	}

	if (GameEngineInput::IsPress(VK_LBUTTON, this))
	{
		if (StateTime >= FIRE_COOL_TIME)
		{
			for (const std::shared_ptr<DummyProjectile>& pProjectile : Projectiles)
			{
				if (pProjectile->IsReady())
				{
					pProjectile->Fire();
					StateTime -= FIRE_COOL_TIME;
					break;
				}
			}
		}
	}
}

/////////
// CaemraMethod
void DummyActor::AttachCamera()
{
	CameraControler.On();
}

void DummyActor::DettachCamera()
{
	CameraControler.Off();
}

void DummyActor::CameraControlUpdate(float _Delta)
{
	if (false == CameraControler.IsUpdate())
	{
		return;
	}

	CameraControler.ControlUpdate(_Delta);
}




void DummyActor::CameraControl::Init(GameEngineActor* _pParent)
{
	if (nullptr == _pParent)
	{
		MsgBoxAssert("존재하지 않는 오브젝트입니다.");
		return;
	}

	pParent = _pParent;
	pCameraTransfrom = &_pParent->GetLevel()->GetMainCamera()->Transform;

	PointObject = _pParent->CreateComponent<GameEngineRenderer>(0);
	PointObject->SetMesh("Sphere");
	PointObject->SetMaterial("FBXStaticColor");
	PointObject->RenderBaseInfoValue.BaseColor = float4::UP;
	PointObject->Off();

	ColObject = _pParent->CreateChild<GameEngineObject>(static_cast<int>(Enum_UpdateOrder::Component));
	ColObject->SetParent(PointObject);

	PosRenderer = _pParent->CreateComponent<GameEngineRenderer>(0);
	PosRenderer->SetMesh("Sphere");
	PosRenderer->SetMaterial("FBXStaticColor");
	PosRenderer->RenderBaseInfoValue.BaseColor = float4::UP;
	PosRenderer->Off();

	HeightUpdate();

	Off();
}

void DummyActor::CameraControl::Release()
{
	Off();

	pParent = nullptr;
	pCameraTransfrom = nullptr;

	ColObject = nullptr;
	PointObject = nullptr;
	PosRenderer = nullptr;
}

void DummyActor::CameraControl::On()
{
	GameEngineObjectBase::On();

	FollowUpdate();

	// PointObject->On();
	// PosRenderer->On();

	MouseInput.Reset();
}

void DummyActor::CameraControl::Off()
{
	GameEngineObjectBase::Off();
	
	PointObject->Off();
	PosRenderer->Off();
}

constexpr float MinDist = 50.0f;
constexpr float MaxDist = 500.0f;

constexpr float ROTSPEED = 200.0f;
constexpr float RotSensitive = 0.2f;
constexpr float ROTATION_MIN = -70.0f;
constexpr float ROTATION_MAX = 70.0f;

constexpr float PIVOT_RATIO = 0.2f;

constexpr float DUMP_TRACE = 20.0f;

void DummyActor::CameraControl::InputUpdate(float _Delta)
{
	// Axis Update
	MouseInput.InputUpdate();

	if (nullptr == pParent)
	{
		MsgBoxAssert("부모 포인터가 널입니다.");
		return;
	}

	const float fHeight = 10.0f;
	const float ZoomSpeed = 20.0f;

	if (nullptr != ColObject)
	{
		if (GameEngineInput::IsDown('Q', pParent))
		{
			const float fHeight = 10.0f;
			pParent->Transform.AddLocalPosition(float4::UP * fHeight);
		}

		if (GameEngineInput::IsDown('E', pParent))
		{
			pParent->Transform.AddLocalPosition(float4::DOWN * fHeight);
		}
	}

	bool bPressCtrl = GameEngineInput::IsPress(VK_CONTROL, pParent);
	if (bPressCtrl && GameEngineInput::IsDown(VK_MBUTTON, pParent))
	{
		PointDist -= ZoomSpeed;
		PointDist = std::clamp(PointDist, 10.0f, 300.0f);
		HeightUpdate();
	}

	if (false == bPressCtrl && GameEngineInput::IsDown(VK_MBUTTON, pParent))
	{
		PointDist += ZoomSpeed;
		PointDist = std::clamp(PointDist, 10.0f, 300.0f);
		HeightUpdate();
	}

	if (GameEngineInput::IsPress(VK_RBUTTON, pParent))
	{
		const float YAxis = -MouseInput.GetScreenMovePos().X;
		const float XAxis = -MouseInput.GetScreenMovePos().Y;

		const float SensSpeed = ROTSPEED * RotSensitive * _Delta;

		QutRotation += float4(XAxis, YAxis) * SensSpeed;
		QutRotation.X = std::clamp(QutRotation.X, ROTATION_MIN, ROTATION_MAX);
		QutRotation.Y = ContentsMath::ClampDeg(QutRotation.Y);
	}
}

void DummyActor::CameraControl::FollowUpdate()
{
	if (nullptr == PointObject
		|| nullptr == pCameraTransfrom)
	{
		MsgBoxAssert("존재하지 않는 포인터에 접근하려했습니다.");
		return;
	}

	PointObject->Transform.SetWorldRotation(QutRotation);

	float4 WRot = ColObject->Transform.GetWorldRotationEuler();
	float4 WPos = ColObject->Transform.GetWorldPosition();

	pCameraTransfrom->SetWorldRotation(WRot);
	pCameraTransfrom->SetWorldPosition(WPos);
}

void DummyActor::CameraControl::HeightUpdate() const
{
	if (nullptr == ColObject
		|| nullptr == PosRenderer)
	{
		MsgBoxAssert("값이 존재하지 않습니다.");
		return;
	}

	const float4 WPointScale = PointObject->Transform.GetWorldScale();
	float4 Pos = float4::BACKWARD * PointDist;
	Pos /= WPointScale.X;
	ColObject->Transform.SetLocalPosition(Pos);
	PosRenderer->Transform.SetLocalPosition(Pos);
}

void DummyActor::CameraControl::ControlUpdate(float _Delta)
{
	if (false == IsUpdate())
	{
		return;
	}

	InputUpdate(_Delta);
	FollowUpdate();
}