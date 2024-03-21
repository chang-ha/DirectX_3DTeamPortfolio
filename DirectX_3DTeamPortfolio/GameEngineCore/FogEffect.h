#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct FogInfo 
{
	float4x4 CameraViewInverseMatrix;
	float4 FogColor = { 0.02f, 0.01f, 0.01f, 1.0f }; // ���ϴ� ������ ����
	float FogMinHeight = -2800.0f; // ���װ� ���۵Ǵ� �Ÿ�
	float FogMaxHeight = -2400.0f; // ���װ� ������Ʈ�� ������ ������ �Ÿ� 
	float NoiseScale = 0.1f; // ������ �ؽ�ó ��ǥ�� ������
	float NoiseOffset = 0.0f; // ������ �ؽ�ó ��ǥ �ִϸ��̼��� ���� ������
	float NoiseIntensity = 0.5f; // ������ ��ⷹ�̼��� ����
	float WorldScale = 100.0f;
	float Def1 = 0.0f;
	float Def3 = 0.0f;
};


// ���� :
class FogEffect : public Effect
{
	friend class FogGUI;

public:
	static FogInfo* MainFogInfo;
	static float FogTimeScale;

	// constrcuter destructer
	FogEffect();
	~FogEffect();



	// delete Function
	FogEffect(const FogEffect& _Other) = delete;
	FogEffect(FogEffect&& _Other) noexcept = delete;
	FogEffect& operator=(const FogEffect& _Other) = delete;
	FogEffect& operator=(FogEffect&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineCamera> _Camera);

	static void Load();
	

	void Update(float _DeltaTime, std::shared_ptr<GameEngineCamera> _Camera) override; 

	
protected:


private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	FogInfo FogInfoValue;

};

