#include "PreCompile.h"
#include "ContentLevel.h"
#include "FXAAEffect.h"

ContentLevel::ContentLevel()
{
	GameEngineInput::AddInputObject(this);
}

ContentLevel::~ContentLevel()
{

}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	//GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<FXAAEffect>();
	PhysXLevelInit();
}

void ContentLevel::Update(float _Delta)
{
	DebugInput();
	RunSimulation(_Delta);
	ChaseListener();
	
	// float4 Pos = GetMainCamera()->Transform.GetWorldPosition();
	// float4 Up = GetMainCamera()->Transform.GetWorldUpVector();
	// float4 Forward = GetMainCamera()->Transform.GetWorldForwardVector();
	// 
	// static float PosPlus = 100.0f;
	// PosPlus += 10.0f;
	// physx::PxVec3 PxPos = { Pos.X + PosPlus, Pos.Y, Pos.Z };
	// physx::PxVec3 PxUp = { 0, 1, 0};
	// physx::PxVec3 PxForward = { Forward.X, Forward.Y, Forward.Z };
	// physx::PxVec3 PxTraget = PxPos + PxForward * 50.0f;
	// Scene->getScenePvdClient()->updateCamera("NewCamera", PxPos, PxUp, PxTraget);


	//physx::PxVec3 camPos(PxPos);
	//physx::PxVec3 camDir = mCamera.getViewDir();
	//physx::PxVec3 camUp = PxVec3(0, 1, 0);
	//physx::PxVec3 camTarget = camPos + camDir * 50.0f;
	//PxPvdSceneClient* pvdClient = mSample->getActiveScene().getScenePvdClient();
	//if (pvdClient)
	//	pvdClient->updateCamera("SampleCamera", camPos, camUp, camTarget);
	//mSample->render();
	//renderer->render(mCamera.getViewMatrix(), mCamera.getProjMatrix());
	//mSample->getDebugRenderer()->queueForRenderLine();
	//mSample->getDebugRenderer()->queueForRenderPoint();

	//// modify entry(3,3) of the projection matrix according to 
	//// http://www.terathon.com/gdc07_lengyel.pdf
	//// this applies a small constant depth bias in NDC
	//SampleRenderer::RendererProjection proj = mCamera.getProjMatrix();
	//proj.getPxMat44()(3, 3) += 4.8e-3f;

	//renderer->render(mCamera.getViewMatrix(), proj);
}

void ContentLevel::Release()
{

}

void ContentLevel::ChaseListener()
{
	float4 Pos = GetMainCamera()->Transform.GetWorldPosition();
	float4 Rot = GetMainCamera()->Transform.GetWorldRotationEuler();

	// Y축만 고려 X,Z축은 필요시
	float4 ForWard = { 0.f, 0.f, 1.f, 1.f };
	ForWard.VectorRotationToDegY(Rot.Y);

	float4 Up = { 0.f, 1.f, 0.f, 1.f };

	GameEngineSound::SetListenerPos(Pos, ForWard, Up);
}

void ContentLevel::DebugInput()
{
	if (GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineLevel::IsDebug = !GameEngineLevel::IsDebug;
	}
}