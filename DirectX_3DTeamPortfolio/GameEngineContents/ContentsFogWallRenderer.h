#pragma once
#include <GameEngineCore\GameEngineRenderer.h>


struct FogWallInfo
{
    float frameTime = 0.0f;
    float scrollSpeeds1 = -1.3f;
    float scrollSpeeds2 = -2.1f;
    float scrollSpeeds3 = -2.5f;
    float scales1 = 1.0f;
    float scales2 = 2.0f;
    float scales3 = 3.0f;
    float padding = 0.0f;

    float4 distortion1 = { 0.1f,0.2f,0.0f,0.0f };
    float4 distortion2 = { 0.1f,0.3f,0.0f,0.0f };
    float4 distortion3 = { 0.1f,0.1f,0.0f,0.0f };

    float distortionScale = 0.8f;
    float distortionBias = 0.5f;
    float perturbscale = 1.0f;
    float AlphaScale = 2.0f;
};


// Ό³Έν :
class ContentsFogWallRenderer : public GameEngineRenderer
{
    friend class FireGUI;
public:
    static ContentsFogWallRenderer* MainFogWall;
	// constrcuter destructer
	ContentsFogWallRenderer();
	~ContentsFogWallRenderer();

	// delete Function
	ContentsFogWallRenderer(const ContentsFogWallRenderer& _Other) = delete;
	ContentsFogWallRenderer(ContentsFogWallRenderer&& _Other) noexcept = delete;
	ContentsFogWallRenderer& operator=(const ContentsFogWallRenderer& _Other) = delete;
	ContentsFogWallRenderer& operator=(ContentsFogWallRenderer&& _Other) noexcept = delete;


protected:
    void Start() override;
    void Update(float _Delta) override;

private:
    FogWallInfo FogWallInfoValue;
    float TimeScale = 0.1f;
};

