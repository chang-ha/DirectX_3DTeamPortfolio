#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"
#include "GameEngineRenderTarget.h"
#include <unordered_set>
#include "GameEngineMesh.h"
#include "FogEffect.h"
#include "BlurPostEffect.h"

// std::shared_ptr<class GameEngineRenderTarget> GameEngineCamera::AllRenderTarget = nullptr;

float GameEngineCamera::FreeRotSpeed = 360.0f;
float GameEngineCamera::FreeSpeed = 100.0f;
float GameEngineCamera::DynamicShadowDistance = 0.013f;

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

	CameraBaseInfoValue.SizeX = GameEngineCore::MainWindow.GetScale().X;
	CameraBaseInfoValue.SizeY = GameEngineCore::MainWindow.GetScale().Y;
	CameraBaseInfoValue.DynamicShadowDistance = 0.013f;

	GameEngineLevel* Level = GetLevel();



	if (nullptr == Level)
	{
		MsgBoxAssert("Level�� nullptr�Դϴ�");
		return;
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	if (nullptr == AllRenderTarget)
	{
		// �̳༮�� ���� ���۵� �����ϴ�.
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


	//�ں��Ʈ ��ŧ���� 
	HBAO.Init(GameEngineCore::GetDevice());

	
	
	{
		DeferredLightTarget = GameEngineRenderTarget::Create();
		// ��� ����
		// DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// ��ǻ�� �÷�
		// DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// ���ݻ籤 dif
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// ���ݻ籤 spc
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// ȯ�汤 amb
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// �� ����
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// �׸���
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		// PBR
		DeferredLightTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		//Texture2D DifColorTex : register(t0);
		//Texture2D PositionTex : register(t1);
		//Texture2D NormalTex : register(t2);
		//SamplerState POINTWRAP : register(s0);

		DeferredLightTarget->CreateEffect<BlurPostEffect>();


		//DeferredTarget = GameEngineRenderTarget::Create();
		//// ��� ����
		//DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		//// ��ǻ�� �÷�
		//DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		//// ���ݻ籤 dif
		//DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		//// ���ݻ籤 spc
		//DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		//// ȯ�汤 amb
		//DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);



		DeferredLightRenderUnit.SetMesh("FullRect");
		DeferredLightRenderUnit.SetMaterial("ContentsDeferredLightRender");
		// DeferredRenderUnit.ShaderResHelper.SetTexture("DifColorTex", AllRenderTarget->GetTexture(1));
		DeferredLightRenderUnit.ShaderResHelper.SetTexture("PositionTex", AllRenderTarget->GetTexture(2));
		DeferredLightRenderUnit.ShaderResHelper.SetTexture("NormalTex", AllRenderTarget->GetTexture(3));
		//DeferredLightRenderUnit.ShaderResHelper.SetTexture("DiffuseTexture", AllRenderTarget->GetTexture(1));
		DeferredLightRenderUnit.ShaderResHelper.SetTexture("MaterialTexture", AllRenderTarget->GetTexture(5));
		DeferredLightRenderUnit.ShaderResHelper.SetTexture("SpecularTex", AllRenderTarget->GetTexture(4));
		DeferredLightRenderUnit.ShaderResHelper.SetConstantBufferLink("CameraBaseInfo", CameraBaseInfoValue);

		DeferredLightRenderUnit.ShaderResHelper.SetSampler("POINTWRAP", "POINT");
		DeferredLightRenderUnit.ShaderResHelper.SetSampler("LinearClamp", "LINEAR");
		//DeferredLightRenderUnit.ShaderResHelper.SetSampler("CompareSampler", "CompareSampler");

		


		DeferredTarget = GameEngineRenderTarget::Create();
		// ��������
		DeferredTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
		DeferredTarget->AddNewTexture(AllRenderTarget->GetTexture(2), float4::ZERONULL);
		DeferredTarget->SetDepthTexture(AllRenderTarget->GetDepthTexture());

		DeferredMergeUnit.SetMesh("FullRect");
		DeferredMergeUnit.SetMaterial("ContentsDeferredMergeRender");
		
		DeferredMergeUnit.ShaderResHelper.SetTexture("DifColorTex", AllRenderTarget->GetTexture(1));
		DeferredMergeUnit.ShaderResHelper.SetTexture("DifLightTex", DeferredLightTarget->GetTexture(0));
		DeferredMergeUnit.ShaderResHelper.SetTexture("SpcLightTex", DeferredLightTarget->GetTexture(1));
		//DeferredMergeUnit.ShaderResHelper.SetTexture("AmbLightTex", DeferredLightTarget->GetTexture(2));
		DeferredMergeUnit.ShaderResHelper.SetTexture("ShadowTex", DeferredLightTarget->GetTexture(3));
		DeferredMergeUnit.ShaderResHelper.SetTexture("SpecularTex", AllRenderTarget->GetTexture(4));
		DeferredMergeUnit.ShaderResHelper.SetTexture("HBAOTex", HBAO.HBAOTarget->GetTexture());
		DeferredMergeUnit.ShaderResHelper.SetTexture("PointDifLightTex", DeferredLightTarget->GetTexture(4));
		DeferredMergeUnit.ShaderResHelper.SetTexture("PointSpcLightTex", DeferredLightTarget->GetTexture(5));
		//DeferredMergeUnit.ShaderResHelper.SetTexture("PBRTex", DeferredLightTarget->GetTexture(5));
		DeferredMergeUnit.ShaderResHelper.SetSampler("POINTClamp", "POINT");
		DeferredMergeUnit.ShaderResHelper.SetSampler("LinearClamp", "LINEAR");
		
	}

	ShadowRenderUnit.SetMesh("Box");
	ShadowRenderUnit.SetMaterial("Shadow");
	ShadowRenderUnit.ShaderResHelper.SetConstantBufferLink("ShadowAniInfo", ShadowAniInfoValue);

	IsFreeCameraValue = false;
}

void GameEngineCamera::Update(float _Delta)
{
	CameraBaseInfoValue.DynamicShadowDistance = DynamicShadowDistance;

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

	if (GameEngineInput::IsDown('-', this))
	{
		FreeSpeed *= 0.1f;
		FreeSpeed = std::clamp(FreeSpeed, 1.0f, 1000.0f);
		std::string OutputStr = std::string("Camera Speed : ") + std::to_string(FreeSpeed) + "\n";
		OutputDebugStringA(OutputStr.c_str());
	}
	if (GameEngineInput::IsDown('=', this))
	{
		FreeSpeed *= 10.0f;
		FreeSpeed = std::clamp(FreeSpeed, 1.0f, 1000.0f);
		std::string OutputStr = std::string("Camera Speed : ") + std::to_string(FreeSpeed) + "\n";
		OutputDebugStringA(OutputStr.c_str());
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
		const float FreeRotPower = FreeRotSpeed * _Delta;
		float4 Dir = ScreenMouseDirNormal;
		Dir *= FreeRotPower;
		Transform.AddWorldRotation({ -Dir.Y, -Dir.X});
	}

}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level�� nullptr�Դϴ�");
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
	if (true == Units.empty())
	{
		return;
	}

	AllRenderTarget->Clear();
	DeferredTarget->Clear();
	AllRenderTarget->Setting();

	for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : Renderers)
	{
		std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;
		for (std::shared_ptr<class GameEngineRenderer>& Renderer : RendererList)
		{

			if (Renderer->BillboardValue == true)
			{
				float4 CameraRotation = Transform.GetLocalRotationEuler();
				//Transform.GetLocalR();

				
				Renderer->BillboardUpdate(CameraRotation);

			}

			Renderer->Transform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

		}
	}

	// ����Ʈ ����Ʈ�� ������Ʈ

	ForwardTarget->EffectUpdate(_DeltaTime, std::static_pointer_cast<GameEngineCamera>(shared_from_this()));
	DeferredTarget->EffectUpdate(_DeltaTime, std::static_pointer_cast<GameEngineCamera>(shared_from_this()));

	

	AllRenderTarget->Setting();

	bool IsDeferredResult = false;
	// ���۵� ������ �׸��� ��������
	{
		// std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPath = Units[RenderPath::Deferred];

		for (std::pair<const RenderPath, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>& RenderPath : Units)
		{

			if (RenderPath.first != RenderPath::Forward)
			{
				IsDeferredResult = true;
			}
			if (RenderPath.first == RenderPath::Alpha)
			{
				continue;
			}

			for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPath.second)
			{

				std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

				for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
				{
					if (EPROJECTIONTYPE::Perspective != ProjectionType or InCamera(Unit->GetParentRenderer()->Transform, Unit->GetMesh()->GetMeshBaseInfo()) == true)
					{
						Unit->Render();
						Unit->InCameraValue = true;
					}
					else
					{
						Unit->InCameraValue = false;
					}
				}
			}
		}

		ForwardTarget->Copy(0, AllRenderTarget, 0);


		// ���۵� ������ ������.

		std::shared_ptr<GameEngineMaterial> ShadowAni = GameEngineMaterial::Find("ShadowAni");
		std::shared_ptr<GameEngineMaterial> ShadowStatic = GameEngineMaterial::Find("ShadowStatic");

		// ������ �� �׸��� ����� 
		std::list<std::shared_ptr<class GameEngineLight>>& Lights = GetLevel()->AllLight;

		// ����ƽ�� �� �� �� �� ����ϴ� �׸���
		if (StaticRenderInitValue == true and ShadowValue == true)
		{
			StaticRenderInitValue = false;
			for (std::shared_ptr<GameEngineLight> Light : Lights)
			{
				if (false == Light->IsShadow())
				{
					continue;
				}

				Light->ShadowTargetStatic->Clear();
				Light->ShadowTargetStatic->Setting();


				std::unordered_set<GameEngineRenderer*> TransformRenderer;
				for (std::pair<const RenderPath, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>& RenderPathvalue : Units)
				{

					for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPathvalue.second)
					{
						if (RenderPathvalue.first != RenderPath::Deferred)
						{
							continue;
						}
						else {
							IsDeferredResult = true;
						}

						std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

						for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
						{

							// �ø��Ǹ� ī�޶� ���̸� ó��x
							/*if (Unit->InCameraValue == false)
							{
								continue;
							}*/

							GameEngineRenderer* ParentRenderer = Unit->GetParentRenderer();

							if (nullptr == ParentRenderer)
							{
								MsgBoxAssert("�������� �������� �ʴ� ����Ƽ�� �ֽ��ϴ�");
								return;
							}

							//�����̴� ��ü��
							if (ParentRenderer->StaticValue == false)
							{
								continue;
							}

							if (false == ParentRenderer->RenderBaseInfoValue.IsShadow)
							{
								continue;
							}

							const LightData& Data = Light->GetLightData();
							if (false == TransformRenderer.contains(ParentRenderer))
							{
								ParentRenderer->Transform.CalculationViewAndProjection(Data.LightViewMatrix, Data.LightProjectionMatrix);
								TransformRenderer.insert(ParentRenderer);
							}


							ShadowAniInfoValue.IsShadowAnimation = ParentRenderer->RenderBaseInfoValue.IsAnimation;

							if (1 == ShadowAniInfoValue.IsShadowAnimation)
							{
								GameEngineStructedBufferSetter* Buffer = Unit->ShaderResHelper.GetStructedBufferSetter("ArrAniMationMatrix", ShaderType::Vertex);

								if (nullptr == Buffer)
								{
									MsgBoxAssert("�������� �ʴ� ��Ʈ��ó�� ���۸� �׸��� �������� �̿��Ϸ��� �߽��ϴ�.");
								}

								Buffer->Setting();
							}

							ShadowAniInfoValue.WorldViewProjectionMatrix = ParentRenderer->Transform.GetWorldViewProjectionMatrix();
							ShadowRenderUnit.SetMesh(Unit->GetMesh());
							ShadowRenderUnit.Render();

						}
					}
				}
			}
		}
		
		if (ShadowValue == true)
		{
			// ���̳��� �׸��� ����
			for (std::shared_ptr<GameEngineLight> Light : Lights)
			{
				// �׸��ڿ� Ÿ�� ����
				if (false == Light->IsShadow())
				{
					continue;
				}
				Light->ShadowTargetSetting();

				std::unordered_set<GameEngineRenderer*> TransformRenderer;


				for (std::pair<const RenderPath, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>& RenderPathvalue : Units)
				{
					if (RenderPathvalue.first != RenderPath::Deferred)
					{

						continue;
					}
					else {
						IsDeferredResult = true;
					}

					for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPathvalue.second)
					{


						std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

						for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
						{

							// �ø��Ǹ� ī�޶� ���̸� ó��x
							/*if (Unit->InCameraValue == false)
							{
								continue;
							}*/


							GameEngineRenderer* ParentRenderer = Unit->GetParentRenderer();

							if (nullptr == ParentRenderer)
							{
								MsgBoxAssert("�������� �������� �ʴ� ����Ƽ�� �ֽ��ϴ�");
								return;
							}
							if (Unit->IsUpdate() == false)
							{
								continue;
							}

							//�������� �ʴ� ��ü��
							if (ParentRenderer->StaticValue == true)
							{
								continue;
							}

							if (false == ParentRenderer->RenderBaseInfoValue.IsShadow)
							{
								continue;
							}

							const LightData& Data = Light->GetLightData();
							if (false == TransformRenderer.contains(ParentRenderer))
							{
								ParentRenderer->Transform.CalculationViewAndProjection(Data.LightViewMatrix, Data.LightProjectionMatrix);
								TransformRenderer.insert(ParentRenderer);
							}


							ShadowAniInfoValue.IsShadowAnimation = ParentRenderer->RenderBaseInfoValue.IsAnimation;

							if (1 == ShadowAniInfoValue.IsShadowAnimation)
							{
								GameEngineStructedBufferSetter* Buffer = Unit->ShaderResHelper.GetStructedBufferSetter("ArrAniMationMatrix", ShaderType::Vertex);

								if (nullptr == Buffer)
								{
									MsgBoxAssert("�������� �ʴ� ��Ʈ��ó�� ���۸� �׸��� �������� �̿��Ϸ��� �߽��ϴ�.");
								}

								Buffer->Setting();
							}

							ShadowAniInfoValue.WorldViewProjectionMatrix = ParentRenderer->Transform.GetWorldViewProjectionMatrix();
							ShadowRenderUnit.SetMesh(Unit->GetMesh());
							ShadowRenderUnit.Render();

						}
					}
				}

			}
		}

		



		if (true == IsDeferredResult)
		{
			AllRenderTarget->RenderTargetReset();


			if (ProjectionType == EPROJECTIONTYPE::Perspective)
			{
				HBAO.DrawHBAO(AllRenderTarget, Transform.GetConstTransformDataRef());
			}
			DeferredLightTarget->Clear();

			for (std::shared_ptr<GameEngineLight> Light : Lights)
			{
				if (Light->LightDataValue.LightType != static_cast<int>(Enum_LightType::Directional) and InCamera(Light->Transform, Light->LightDataValue.PointLightRange) == false)
				{
					continue;
				}

				if (true == Light->IsShadow())
				{
					DeferredLightRenderUnit.ShaderResHelper.SetTexture("ShadowTex", Light->GetShadowTarget()->GetDepthTexture());
					DeferredLightRenderUnit.ShaderResHelper.SetTexture("ShadowStaticTex", Light->ShadowTargetStatic->GetDepthTexture());
				}
				
				DeferredLightRenderUnit.ShaderResHelper.SetConstantBufferLink("OneLightData", Light->GetLightData());
				DeferredLightTarget->Setting();
				DeferredLightRenderUnit.Render();
			}

			DeferredLightTarget->PostEffect(_DeltaTime);

			DeferredLightTarget->RenderTargetReset();
			
			DeferredTarget->Setting();
			DeferredMergeUnit.Render();

			std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPathlist = Units[RenderPath::Alpha];

				for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : RenderPathlist)
				{

					std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

					for (std::shared_ptr<class GameEngineRenderUnit> Unit : UnitList)
					{
						Unit->Render();
					}
				}
			
		}
	}


	// ���۵�� �ϸ� �ȵǴµ�.
	//AllRenderTarget->Clear();
	//AllRenderTarget->Setting();


	// ���� ���۴� Ŭ�����ϸ� �ȵǰ�.


	// ������ �׷����� �ϴ� ����� ����
	// CameraTarget->Copy(0, AllRenderTarget, 0);
	// 
	// ���۵�� �׷��� ���� ����
	if (true == IsDeferredResult)
	{
		DeferredTarget->PostEffect(_DeltaTime);
		GetLevel()->LevelRenderTarget->Merge(0, DeferredTarget, 0);
	}

	// ������� �׷��� ���� ����
	ForwardTarget->PostEffect(_DeltaTime);
	GetLevel()->LevelRenderTarget->Merge(0, ForwardTarget, 0);
	

	//GetLevel()->LevelRenderTarget->PostEffect(_DeltaTime);
}

void GameEngineCamera::AllReleaseCheck()
{
	if (true == Renderers.empty())
	{
		return;
	}

	// ����ִ� �༮���� ���δ� ���Ͱ�����
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

	for (std::pair<const RenderPath, std::map<int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>>& Path : Units)
	{
		for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderUnit>>>& RenderPair : Path.second)
		{
			std::list<std::shared_ptr<class GameEngineRenderUnit>>& UnitList = RenderPair.second;

			std::list<std::shared_ptr<class GameEngineRenderUnit>>::iterator StartIter = UnitList.begin();
			std::list<std::shared_ptr<class GameEngineRenderUnit>>::iterator EndIter = UnitList.end();

			for (; StartIter != EndIter;)
			{
				const std::shared_ptr<GameEngineRenderUnit>& RenderUnit = (*StartIter);
				if (RenderUnit->GetParentRenderer()->IsDeath() || RenderUnit->IsDeath())
				{
					StartIter = UnitList.erase(StartIter);
					continue;
				}

				++StartIter;
			}
		}
	}
}

float4 GameEngineCamera::GetWorldMousePos2D()
{
	// ������ �ϴ� ������ ȭ��� ������ ������.
	// �׷��� �����ְ� �ƴ�.
	
	// ������
	// ���� => ����(ũ���̰���) => �� => �������� => ����Ʈ(��ũ����ǥ)

	float4x4 ViewPort;

	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();

	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);
	// ��ũ�� => ������������ �̵�
	MousePos *= ViewPort.InverseReturn();

	// �������� => ��� �̵�
	MousePos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();

	// �� => �����
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
		// �����ൿ ī�޶�� �ൿ
	}
	else if (nullptr != Target)
	{
		// ���� ����ٴϴ� �༮�� �ִٸ�
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

	CameraLightFrustum = CameraFrustum;
	CameraLightFrustum.Far = Far * 0.3f;

}


bool GameEngineCamera::InCamera(const GameEngineTransform& _Trans, MeshBaseInfo _MeshBaseInfo)
{
	
	UnitTransform.LocalPosition = _MeshBaseInfo.CenterPosition;
	UnitTransform.LocalScale = _MeshBaseInfo.BoundScaleBox;
	UnitTransform.LocalRotation = float4::ZERONULL;

	UnitTransform.LocalCalculation(_Trans.GetWorldMatrix());
	UnitTransform.WorldDecompos();

	// ������ 
	//ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	//ColData.OBB.Center = TransData.WorldPosition.Float3;

	DirectX::BoundingSphere AABB;
	AABB.Center = UnitTransform.WorldPosition.Float3;
	AABB.Radius = UnitTransform.WorldScale.ToABS().Size() / 2.0f;
		

	bool Result;

	Result = CameraFrustum.Intersects(AABB);

	
	//Result = true;

	return Result;
}

bool GameEngineCamera::InCamera(const GameEngineTransform& _Trans, float Scale)
{
	//UnitTransform.LocalPosition = _MeshBaseInfo.CenterPosition;
	//UnitTransform.LocalScale = _MeshBaseInfo.BoundScaleBox;
	//UnitTransform.LocalRotation = float4::ZERONULL;

	UnitTransform.LocalCalculation(_Trans.GetWorldMatrix());
	UnitTransform.WorldDecompos();

	// ������ 
	//ColData.OBB.Extents = TransData.WorldScale.ToABS().Half().Float3;
	//ColData.OBB.Center = TransData.WorldPosition.Float3;

	DirectX::BoundingSphere AABB;
	AABB.Center = UnitTransform.WorldPosition.Float3;
	AABB.Radius = Scale;


	bool Result;

	Result = CameraFrustum.Intersects(AABB);


	//Result = true;

	return Result;
}


float4 GameEngineCamera::GetScreenPos(GameEngineTransform& _TargetTransform)
{


	// ������� ���
	_TargetTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	const TransformData& TargetTransformData = _TargetTransform.GetConstTransformDataRef();

	// ��ũ�� ��ǥ ���

	float4x4 ViewPort;
	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);

	float4 Result;

	switch (ProjectionType)
	{
	case EPROJECTIONTYPE::Perspective:
	{
		float4 ScreenPos = TargetTransformData.WorldPosition;


		float4x4 VM = TargetTransformData.ViewMatrix;
		float4x4 PM = TargetTransformData.ProjectionMatrix;

		ScreenPos *= VM;
		ScreenPos *= PM;


		const float RHW = 1.0f / ScreenPos.W;

		float4 PosInScreenSpace = float4(ScreenPos.X * RHW, ScreenPos.Y * RHW, ScreenPos.Z * RHW, ScreenPos.W);
		const float NormalizedX = (PosInScreenSpace.X / 2.f) + 0.5f;
		const float NormalizedY = 1.f - (PosInScreenSpace.Y / 2.f) - 0.5f;

		float4 RayStartViewRectSpace;

		RayStartViewRectSpace.X = NormalizedX * Scale.X;
		RayStartViewRectSpace.Y = -NormalizedY * Scale.Y;

		Result = RayStartViewRectSpace;

		Result -= float4{ Scale.X / 2, -Scale.Y / 2 }; 
	}
		break;
	case EPROJECTIONTYPE::Orthographic:
	{
		float4 screenpos = TargetTransformData.WorldPosition;
		screenpos *= TargetTransformData.ViewMatrix;
		screenpos *= TargetTransformData.ProjectionMatrix;
		screenpos *= ViewPort;

		Result = screenpos;
	}
		break;
	default:
		break;
	}

	return Result;
}

void GameEngineCamera::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (false == IsFreeCameraValue)
	{
		IsFreeCameraValue = false;
		GameEngineInput::IsObjectAllInputOn();
		ProjectionType = PrevProjectionType;
		Transform.SetTransformData(OriginData);
	}
}