#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct FogInfo 
{
	float4x4 CameraViewInverseMatrix;
	float4 FogColor = { 0.5f, 0.6f, 0.7f, 1.0f }; // 원하는 포그의 색상
	float FogMinHeight = 0.0f; // 포그가 시작되는 거리
	float FogMaxHeight = 100.0f; // 포그가 오브젝트를 완전히 가리는 거리 
	float Def1 =0.0f;
	float Def2 = 0.0f;
};


// 설명 :
class FogEffect : public Effect
{
	friend class FogGUI;

public:
	static FogInfo* MainFogInfo;

	// constrcuter destructer
	FogEffect();
	~FogEffect();



	// delete Function
	FogEffect(const FogEffect& _Other) = delete;
	FogEffect(FogEffect&& _Other) noexcept = delete;
	FogEffect& operator=(const FogEffect& _Other) = delete;
	FogEffect& operator=(FogEffect&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineCamera> _Camera);
	

	void Update(float _DeltaTime, std::shared_ptr<GameEngineCamera> _Camera) override; 

	
protected:


private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	FogInfo FogInfoValue;

};

