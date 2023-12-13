#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineComputeUnit.h"

struct ParticleUpdateInfo
{
	// 파티클이 최대 몇개까지 눈에 보일거냐?
	int ParticleMaxCount = 100;
	// 파티클이 월드 기준으로 스폰되냐
	// 1이면 자기 위치를 가지는걸로 봅니다
	int IsWorldSpawn = 1;
	// 원형만 지원
	// 파티클이 만들어지는 범위
	float SpawnRange = 100.0f;
	float MinSpeed = 100.0f;
	float MaxSpeed = 100.0f;
	float MaxLife = 100.0f;
	float Temp0;
	float Temp1;
	float4 ObjectWorldPos; // 액터나 랜더러의 월드 포지션
	float4 StartScale = float4::ONE * 100.0f; // 액터나 랜더러의 월드 포지션
	float4 EndScale = float4::ONE * 100.0f; // 액터나 랜더러의 월드 포지션
};

struct ParticleShareData
{
	// 현재 몇개나 살아있냐?
	unsigned int iAliveCount;
	unsigned int iPadding0;
	unsigned int iPadding1;
	unsigned int iPadding2;
};

struct ParticleInfoData
{
    float4 RelativePos;
    float4 Dir;
    float MaxTime;
    float CurTime;
    float Speed;
    float iActive;
};


// 설명 :
class GameEngineParticleRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineParticleRenderer();
	~GameEngineParticleRenderer();

	// delete Function
	GameEngineParticleRenderer(const GameEngineParticleRenderer& _Other) = delete;
	GameEngineParticleRenderer(GameEngineParticleRenderer&& _Other) noexcept = delete;
	GameEngineParticleRenderer& operator=(const GameEngineParticleRenderer& _Other) = delete;
	GameEngineParticleRenderer& operator=(GameEngineParticleRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	ParticleUpdateInfo ParticleUpdateInfoValue;
	GameEngineComputeUnit UpdateUnit;
	std::shared_ptr<GameEngineStructuredBuffer> ParticleShareBuffer;
	float Frequency = 5.0f;
};

