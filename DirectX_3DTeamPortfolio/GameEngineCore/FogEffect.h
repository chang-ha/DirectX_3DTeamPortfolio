#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct FogInfo 
{
	float4x4 CameraViewInverseMatrix;
	float4 FogColor = { 0.204f, 0.184f, 0.131f, 1.0f }; // 원하는 포그의 색상
	float FogMinHeight = -2600.0f; // 포그가 시작되는 거리
	float FogMaxHeight = -2000.0f; // 포그가 오브젝트를 완전히 가리는 거리 
	float NoiseScale = 0.06f; // 노이즈 텍스처 좌표의 스케일
	float NoiseOffset = 0.0f; // 노이즈 텍스처 좌표 애니메이션을 위한 오프셋
	float NoiseIntensity = 1.0f; // 노이즈 모듈레이션의 강도
	float WorldScale = 100.0f;
	float Def1 = 0.0f;
	float Def3 = 0.0f;
};


// 설명 :
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

