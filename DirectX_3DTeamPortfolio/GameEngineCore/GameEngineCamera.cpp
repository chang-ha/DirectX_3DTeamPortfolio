#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"
#include "GameEngineRenderTarget.h"


// std::shared_ptr<class GameEngineRenderTarget> GameEngineCamera::AllRenderTarget = nullptr;

float GameEngineCamera::FreeRotSpeed = 180.0f;
float GameEngineCamera::FreeSpeed = 200.0f;

GameEngineCamera::GameEngineCamera() 
{
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Start()
{
	GameEngineActor::Start();

	ZoomValue = 1.0f;

	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	if (nullptr == AllRenderTarget)
	{
		// 이녀석이 깊이 버퍼도 가집니다.
		AllRenderTarget = GameEngineRenderTarget::Create();
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		AllRenderTarget->CreateDepthTexture();
	}

	{
		ForwardTarget = GameEngineRenderTarget::Create();
		ForwardTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
	}


	//앰비언트 오큘르전 
	HBAO.Init(GameEngineCore::GetDevice());

	{
		DeferredTarget = GameEngineRenderTarget::Create();
		// 모두 종합
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// 디퓨즈 컬러
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// 난반사광 dif
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// 정반사광 spc
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// 환경광 amb
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

		//Texture2D DifColorTex : register(t0);
		//Texture2D PositionTex : register(t1);
		//Texture2D NormalTex : register(t2);
		//SamplerState POINTWRAP : register(s0);


		DeferredRenderUnit.SetMesh("FullRect");
		DeferredRenderUnit.SetMaterial("ContentsDeferredRender");
		DeferredRenderUnit.ShaderResHelper.SetTexture("DifColorTex", AllRenderTarget->GetTexture(1));
		DeferredRenderUnit.ShaderResHelper.SetTexture("PositionTex", AllRenderTarget->GetTexture(2));
		DeferredRenderUnit.ShaderResHelper.SetTexture("NormalTex", AllRenderTarget->GetTexture(3));
		DeferredRenderUnit.ShaderResHelper.SetTexture("SpecularTex", AllRenderTarget->GetTexture(4));
		DeferredRenderUnit.ShaderResHelper.SetTexture("HBAOTex", HBAO.HBAOTarget->GetTexture());
		DeferredRenderUnit.ShaderResHelper.SetSampler("POINTWRAP", "POINT");
		DeferredRenderUnit.ShaderResHelper.SetConstantBufferLink("LightDatas", GetLevel()->LightDataObject);
	}

	// 이건 최종 타겟일 뿐입니다.
	/*CameraTarget = GameEngineRenderTarget::Create();
	CameraTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);*/

	IsFreeCameraValue = false;
}

void GameEngineCamera::Update(float _Delta)
{
	GameEngineActor::Update(_Delta);

	ScreenMousePos = GameEngineCore::MainWindow.GetMousePos();

	ScreenMouseDir = ScreenMousePrevPos - ScreenMousePos;
	ScreenMouseDirNormal = ScreenMouseDir.NormalizeReturn();

	ScreenMousePrevPos = ScreenMousePos;

	if (false == IsFreeCameraValue)
	{
		return;
	}

	if (GameEngineInput::IsDown('O', this))
	{
		switch (ProjectionType)
		{
		case EPROJECTIONTYPE::Perspective:
			ProjectionType = EPROJECTIONTYPE::Orthographic;
			break;
		case EPROJECTIONTYPE::Orthographic:
			ProjectionType = EPROJECTIONTYPE::Perspective;
			break;
		default:
			break;
		}
	}

	float Speed = FreeSpeed;

	if (GameEngineInput::IsPress(VK_LSHIFT, this))
	{
		Speed *= 5.0f;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		Transform.AddWorldPosition(Transform.GetWorldLeftVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D', this))
	{
		Transform.AddWorldPosition(Transform.GetWorldRightVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W', this))
	{
		Transform.AddWorldPosition(Transform.GetWorldForwardVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S', this))
	{
		Transform.AddWorldPosition(Transform.GetWorldBackVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q', this))
	{
		Transform.AddWorldPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('E', this))
	{
		Transform.AddWorldPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		float4 Dir = ScreenMouseDirNormal;

		Transform.AddWorldRotation({ -Dir.Y, -Dir.X});
	}

}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	if (Level->Cameras[CameraOrder] == shared_from_this())
	{
		Level->Cameras[CameraOrder] = nullptr;
	}
	CameraOrder = _Order;
	Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}

void GameEngineCamera::Render(float _DeltaTime)
{
	// CameraUpdate(_DeltaTime);

	//  랜더러가 없으면 continue;
	if (true == Renderers.empty())
	{
		return;
	}

	// GameEngineCore::GetBackBufferRenderTarget()->Setting();

	AllRenderTarget->Clear();
	AllRenderTarget->Setting();

	for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : Renderers)
	{
		std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;

		if (true == ZSortMap.contains(RendererPair.first))
		{
			RendererList.sort([](std::shared_ptr<class GameEngineRenderer> _Left, std::shared_ptr<class GameEngineRenderer> _Right)
				{
					return _Left->Transform.GetWorldPosition().Z > _Right->Transform.GetWorldPosition().Z;
				});
		}

		if (true == YSortMap.contains(RendererPair.first))
		{
			RendererList.sort([](std::shared_ptr<class GameEngineRenderer> _Left, std::shared_ptr<class GameEngineRenderer> _Right)
				{
					return _Left->Transform.GetWorldPosition().Y > _Right->Transform.GetWorldPosition().Y;
				});
		}

		for (std::shared_ptr<class GameEngineRenderer> & Renderer : RendererList)
		{
			Renderer->Transform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
		}

		//for (std::shared_ptr<class GameEngineRenderer> & Renderer : RendererList)
		//{
		//	if (false == Renderer->IsUpdate())
		//	{
		//		continue;
		//	}

		//	Renderer->Transform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
		//	Renderer->Render(this, _DeltaTime);
		//}
	}

	// 포워드 그리고
	{
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPath = Units[RenderPath::Forward];
		for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPath)
		{
			std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

			for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
			{
				Unit->Render();
			}
		}

		ForwardTarget->Copy(0, AllRenderTarget, 0);
	}

	AllRenderTarget->Setting();
	// 디퍼드 그리고
	{
		std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPath = Units[RenderPath::Deferred];

		for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPath)
		{
			std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

			for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
			{
				Unit->Render();
			}
		}

		AllRenderTarget->RenderTargetReset();
		if (ProjectionType == EPROJECTIONTYPE::Perspective)
		{
			HBAO.DrawHBAO(AllRenderTarget, Transform.GetConstTransformDataRef());
		}
		auto LightData = GetLevel()->LightDataObject;

		DeferredRenderUnit.ShaderResHelper.SetConstantBufferLink("LightDatas", GetLevel()->LightDataObject);

		DeferredTarget->Clear();
		DeferredTarget->Setting();
		DeferredRenderUnit.Render();

	}


	// 디퍼드는 하면 안되는데.
	//AllRenderTarget->Clear();
	//AllRenderTarget->Setting();


	// 깊이 버퍼는 클리어하면 안되고.


	// 기존에 그려진걸 싹다 지우고 복사
	// CameraTarget->Copy(0, AllRenderTarget, 0);

	AllRenderTarget->PostEffect(_DeltaTime);

	// 포워드로 그려진 모든것 병합
	GetLevel()->LevelRenderTarget->Merge(0, ForwardTarget, 0);
	// 디퍼드로 그려진 모든것 병합
	GetLevel()->LevelRenderTarget->Merge(0, DeferredTarget, 0);
}

void GameEngineCamera::AllReleaseCheck()
{
	if (true == Renderers.empty())
	{
		return;
	}

	// 들고있는 녀석들은 전부다 액터겠지만
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& _Pair : Renderers)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineRenderer>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator End = Group.end();

		for (; Start != End;)
		{
			if (false == (*Start)->IsDeath())
			{
				(*Start)->AllReleaseCheck();
				++Start;
				continue;
			}

			Start = Group.erase(Start);
		}
	}
}

float4 GameEngineCamera::GetWorldMousePos2D()
{
	// 월드라고 하는 세상은 화면과 관련이 없었다.
	// 그런데 관련있게 됐다.
	
	// 나누기
	// 로컬 => 월드(크자이공부) => 뷰 => 프로젝션 => 뷰포트(스크린좌표)

	float4x4 ViewPort;

	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();

	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);
	// 스크린 => 프로젝션으로 이동
	MousePos *= ViewPort.InverseReturn();

	// 프로젝션 => 뷰로 이동
	MousePos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();

	// 뷰 => 월드로
	MousePos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();

	return MousePos;
}

void GameEngineCamera::CameraUpdate(float _DeltaTime)
{

	if (GameEngineInput::IsDown(VK_OEM_4, this))
	{
		IsFreeCameraValue = !IsFreeCameraValue;

		if (true == IsFreeCameraValue)
		{
			GameEngineInput::IsOnlyInputObject(this);
			PrevProjectionType = ProjectionType;
			ProjectionType = EPROJECTIONTYPE::Perspective;
			OriginData = Transform.GetConstTransformDataRef();
		}
		else
		{
			GameEngineInput::IsObjectAllInputOn();
			ProjectionType = PrevProjectionType;
			Transform.SetTransformData(OriginData);
		}
	}

	if (true == IsFreeCameraValue)
	{
		// 자율행동 카메라로 행동
	}
	else if (nullptr != Target)
	{
		// 내가 따라다니는 녀석이 있다면
		Transform.SetWorldPosition(Target->GetWorldPosition() + Pivot);
	}

	float4 Position = Transform.GetLocalPosition();
	float4 Forward = Transform.GetLocalForwardVector();
	float4 Up = Transform.GetLocalUpVector();

	Transform.LookToLH(Position, Forward, Up);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	WindowScale *= ZoomValue;

	float4 Qur = Transform.GetConstTransformDataRef().WorldQuaternion;

	switch (ProjectionType)
	{
	case EPROJECTIONTYPE::Perspective:
		Transform.PerspectiveFovLHDeg(FOV, WindowScale.X, WindowScale.Y, Near, Far);
		CameraFrustum.Far = Far;
		CameraFrustum.Near = Near;
		CameraFrustum.Origin = { Position.X, Position.Y, Position.Z };
		CameraFrustum.Orientation = { Qur.X, Qur.Y, Qur.Z, Qur.W };
		break;
	case EPROJECTIONTYPE::Orthographic:
		Transform.OrthographicLH(WindowScale.X, WindowScale.Y, Near, Far);
		CameraFrustum.Far = Far;
		CameraFrustum.Near = Near;
		CameraFrustum.Origin = { Position.X, Position.Y, Position.Z };
		CameraFrustum.Orientation = { Qur.X, Qur.Y, Qur.Z, Qur.W };
		break;
	default:
		break;
	}

}