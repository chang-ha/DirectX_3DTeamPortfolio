#include "Random.fx"

struct ParticleShareData
{
    uint iAliveCount;
    uint iPadding0;
    uint iPadding1;
    uint iPadding2;
};

struct ParticleInfoData
{
    // 현재위치
    float4 RelativePos;
    
    // 날아가는 방향
    float4 Dir;
    
    // 죽는시간
    float MaxTime;
    
    // 현재까지 경과한 시간
    float CurTime;
    
    // 이동할때의 스피드
    float Speed;
    
    // 나 죽었다 살았다.
    float iActive;
};

cbuffer ParticleUpdateInfo : register(b7)
{
	// 파티클이 최대 몇개까지 눈에 보일거냐?
    int ParticleMaxCount;
	// 파티클이 월드 기준으로 스폰되냐
	// 1이면 자기 위치를 가지는걸로 봅니다
    int IsWorldSpawn;
	// 원형만 지원
	// 파티클이 만들어지는 범위
    float SpawnRange;
    float MinSpeed;
    float MaxSpeed;
    float MaxLife;
    float Temp0;
    float Temp1;
    float4 ObjectWorldPos; // 액터나 랜더러의 월드 포지션
    float4 StartScale; // 액터나 랜더러의 월드 포지션
    float4 EndScale; // 액터나 랜더러의 월드 포지션
};

// UAV
// 그러면
RWStructuredBuffer<ParticleShareData> ParticleShareBuffer : register(u0);
// 아래 메모리는 100개 의 쓰레드에서 100개의 배열중 자기껄 알아서 압겹치게 쓸것이기 때문에 문제가 
// 문제가 없다.
RWStructuredBuffer<ParticleInfoData> ParticleInfoBuffer : register(u1);

// SRV
// 그러면
StructuredBuffer<ParticleShareData> ParticleShareRenderBuffer : register(t11);
// 아래 메모리는 100개 의 쓰레드에서 100개의 배열중 자기껄 알아서 압겹치게 쓸것이기 때문에 문제가 
// 문제가 없다.
StructuredBuffer<ParticleInfoData> ParticleInfoRenderBuffer : register(t12);
