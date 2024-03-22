#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct FogInfo 
{
	float4x4 CameraViewInverseMatrix;
	float4 FogColor = { 0.204f, 0.184f, 0.131f, 1.0f }; // ���ϴ� ������ ����
	float FogMinHeight = -2600.0f; // ���װ� ���۵Ǵ� �Ÿ�
	float FogMaxHeight = -2000.0f; // ���װ� ������Ʈ�� ������ ������ �Ÿ� 
	float NoiseScale = 0.06f; // ������ �ؽ�ó ��ǥ�� ������
	float NoiseOffset = 0.0f; // ������ �ؽ�ó ��ǥ �ִϸ��̼��� ���� ������
	float NoiseIntensity = 1.0f; // ������ ��ⷹ�̼��� ����
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

