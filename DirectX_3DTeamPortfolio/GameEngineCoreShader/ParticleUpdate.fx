#include "ParticleHeader.fx"

[numthreads(128, 1, 1)]
void ParticleUpdate_CS(uint3 _id : SV_DispatchThreadID)
{
    
    if ((uint) ParticleMaxCount <= _id.x)
    {
        return;
    }
    
    // 현재 비활성화인 파티클이므로 그 파티클을 깨울지 말지를 결정해야 한다.
    if (0 == ParticleInfoBuffer[_id.x].iActive)
    {

        
        // 크다면 자기 자신이 깨어나야하는 녀석인지를 확인한다.
        while (0 < ParticleShareBuffer[0].iAliveCount)
        {
            int iOriginValue = ParticleShareBuffer[0].iAliveCount;
            int iExchange = iOriginValue - 1;
            
            // 지원해 줍니다.
            InterlockedCompareExchange(ParticleShareBuffer[0].iAliveCount, iOriginValue, iExchange, iExchange);
            
            // 동기화된 값이 변경되지 않았다면
            if (iOriginValue == iExchange)
            {
                ParticleInfoBuffer[_id.x].iActive = 1;
                break;
            }
        }
        
        
        // 이녀석은 활성화 됩니다.
        if (0 != ParticleInfoBuffer[_id.x].iActive)
        {
            float4 RandomVector = RandomFloat4(_id.x, ParticleMaxCount);
            
            float Random = RandomVector.x * 3.141592f * 2.0f;

            // 랜덤한 xy위치를 뽑고
            ParticleInfoBuffer[_id.x].RelativePos.xy = float2(cos(Random), sin(Random)) * RandomVector.y * SpawnRange;
            ParticleInfoBuffer[_id.x].RelativePos.z = 0.0f;
            
            ParticleInfoBuffer[_id.x].Dir.xy = normalize(ParticleInfoBuffer[_id.x].RelativePos.xy);

            if (0 != IsWorldSpawn)
            {
                ParticleInfoBuffer[_id.x].RelativePos += ObjectWorldPos;
            }
            
            // 랜덤한 속력
            ParticleInfoBuffer[_id.x].Speed = RandomVector.z * (MaxSpeed - MinSpeed) + MinSpeed;
            
            ParticleInfoBuffer[_id.x].CurTime = 0.0f;
            ParticleInfoBuffer[_id.x].MaxTime = MaxLife;
        }
    }
    // 움직이는 일해야합니다
    else
    {
        ParticleInfoBuffer[_id.x].CurTime += DeltaTime;

        if (ParticleInfoBuffer[_id.x].MaxTime < ParticleInfoBuffer[_id.x].CurTime)
        {
            // 다시 죽는겁니다.
            ParticleInfoBuffer[_id.x].iActive = 0;
        }
        else
        {
            ParticleInfoBuffer[_id.x].RelativePos += ParticleInfoBuffer[_id.x].Dir * ParticleInfoBuffer[_id.x].Speed * DeltaTime;
        }
    }
    
    
    // 업데이트 완료
}

