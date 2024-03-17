#pragma once
#include "GameEngineActor.h"

struct LightData
{
    // �׸��� �׸�����.
    float4x4 LightViewMatrix;
    float4x4 LightViewInverseMatrix;
    float4x4 LightProjectionMatrix;
    float4x4 LightProjectionInverseMatrix;
    float4x4 LightViewProjectionMatrix;
    float4x4 CameraViewInverseMatrix;
    float4 LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float4 AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
    float ShadowTargetSizeX;
    float ShadowTargetSizeY;
    float LightNear;
    float LightFar;
    float DifLightPower = 1.0f;
    float SpcLightPower = 2.0f;
    float AmbLightPower = 1.0f;
    float SpcPow = 15.0f;
    int LightType = 0;
    float PointLightRange = 800.0f;
    float LightPower = 1.0f;
    float ForceLightPower = 0.5f; //GI�ؽ��Ŀ� ���� ����Ʈ 
    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.003f;
    float quadraticAttenuation = 0.00003f;
    float Def1;
};

// ���� ���� 64�� �̻��� �ƴϰ���.
struct LightDatas
{
	int LightCount = 0;
	LightData AllLight[64];
};

enum class Enum_LightType
{
    Directional,
    Point,
    //Spot
};

// ���� :
class GameEngineLight : public GameEngineActor
{
    friend class GameEngineCamera;
public:
	// constrcuter destructer
	GameEngineLight();
	~GameEngineLight();

	// delete Function
	GameEngineLight(const GameEngineLight& _Other) = delete;
	GameEngineLight(GameEngineLight&& _Other) noexcept = delete;
	GameEngineLight& operator=(const GameEngineLight& _Other) = delete;
	GameEngineLight& operator=(GameEngineLight&& _Other) noexcept = delete;

	void LightUpdate(class GameEngineCamera* _Camera, float _DeltaTime);

	const LightData& GetLightData()
	{
		return LightDataValue;
	}

    void SetLightData(const LightData& _LightData)
    {
        LightDataValue = _LightData;
    }

    std::shared_ptr<class GameEngineRenderTarget> GetShadowTarget()
    {
        return ShadowTarget;
    }

    void ShadowTargetSetting();

    void SetShadowRange(float4 _Range)
    {
        ShadowRange = _Range;
    }

    inline void SetLightType(Enum_LightType _Type)
    {
        LightDataValue.LightType = static_cast<int>(_Type);
    }

    void CreateShadowMap(float4 _Size = float4{16384.f, 16384.f,0.0f});

    bool IsShadow()
    {
        if (ShadowTarget == nullptr or ShadowTargetStatic == nullptr)
        {
            if (static_cast<Enum_LightType>(LightDataValue.LightType) == Enum_LightType::Directional)
            {
                CreateShadowMap();
                return true;
            }
            return false;
        }
        else
        {
            return true;
        }
    }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	LightData LightDataValue;
    // �׸����� �������� ����Ҽ� �ִ�.
    float4 ShadowRange = { 32768, 32768 };
    std::shared_ptr<class GameEngineRenderTarget> ShadowTarget = nullptr;
    std::shared_ptr<class GameEngineRenderTarget> ShadowTargetStatic = nullptr;
};

