#include "PreCompile.h"
#include "GameEngineParticleRenderer.h"
#include "GameEngineStructuredBuffer.h"

GameEngineParticleRenderer::GameEngineParticleRenderer()
{
}

GameEngineParticleRenderer::~GameEngineParticleRenderer()
{

}

void GameEngineParticleRenderer::Start()
{
	GameEngineRenderer::Start();

	UpdateUnit.GroupX = 128;

	std::vector<ParticleInfoData> Data;

	Data.resize(ParticleUpdateInfoValue.ParticleMaxCount);

	for (size_t i = 0; i < ParticleUpdateInfoValue.ParticleMaxCount; i++)
	{
		Data[i].CurTime = 0.0f;
		Data[i].MaxTime = 1.0f;
		Data[i].Dir = float4::ZERO;
		Data[i].RelativePos = float4::ZERO;
		Data[i].Speed = 100.0f;
		Data[i].iActive = 0;
	}

	UpdateUnit.SetComputeShader("ParticleUpdate_CS");

	UpdateUnit.ShaderResHelper.SetTexture("EngineNoise", "noise_03.jpg");
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	UpdateUnit.ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);


	ParticleUpdateInfoValue.SpawnRange = 500.0f;

	// 윈도우에 있는 함수입니다.
	// InterlockedAnd
	// 파티클정보에 대한 버퍼는 각 파티클 랜더러마다 가지고 있어야 한다고 봐서
	// New로 만들어집니다.
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> ParitcleInfoBuffers =
		UpdateUnit.ShaderResHelper.SetStructedNew("ParticleinfoBuffer", StructuredBufferType::UAV_INC, Data);
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> ParticleShareBuffers =
		UpdateUnit.ShaderResHelper.SetStructedNew("ParticleShareBuffer", StructuredBufferType::UAV_INC, nullptr, sizeof(ParticleShareData), 1);

	// 랜더 유니트가 알아서 랜더링을 하는겁니다
	GameEngineRenderer::SetMesh("PointMesh");
	GameEngineRenderer::SetMaterial("ParticleRender");

	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);

	Unit->SetRenderMode(RenderMode::Instancing);
	Unit->SetInstancingCount(ParticleUpdateInfoValue.ParticleMaxCount);
	Unit->ShaderResHelper.SetConstantBufferLink("ParticleUpdateInfo", ParticleUpdateInfoValue);
	Unit->ShaderResHelper.SetStructedBufferChange("ParticleInfoRenderBuffer", ParitcleInfoBuffers.front());
	ParticleShareBuffer = ParticleShareBuffers.front();

}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	GameEngineRenderer::Update(_DeltaTime);

	TransformData Data = Transform.GetConstTransformDataRef();

	RenderBaseInfoValue;


	float fAliveTime = 1.f / Frequency;

	// 우린 RenderBaseValue에서 이미 계산하고 있으므로 필요가 없다. 누적시간
	// m_fAccTime += _DeltaTime;

	ParticleUpdateInfoValue.ObjectWorldPos = Transform.GetWorldPosition();

	// 누적시간이 파티클 생성 시간을 넘어서면
	if (fAliveTime < RenderBaseInfoValue.AccDeltaTime)
	{
		float f = (RenderBaseInfoValue.AccDeltaTime / fAliveTime);
		UINT iAliveCount = (UINT)f;
		RenderBaseInfoValue.AccDeltaTime = f - floorf(f);

		ParticleShareData share = { 10, };
		ParticleShareBuffer->SetData(&share, 1);
	}
	else
	{
		ParticleShareData share = {};
		ParticleShareBuffer->SetData(&share, 1);
	}


	UpdateUnit.GroupX = 128;

	// 수백의 파티클 데이터를 컴퓨트쉐이더로 계산하고
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::Render(_Camera, _Delta);
}