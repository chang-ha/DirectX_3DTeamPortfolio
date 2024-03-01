#pragma once
#include <GameEngineCore\GameEngineRenderer.h>

struct FireInfo 
{
    float frameTime = 0.0f;
    float scrollSpeeds1 = 1.3f;
    float scrollSpeeds2 = 2.1f;
    float scrollSpeeds3 = 2.3f;
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
    float def2 = 0.0f;
};


// Ό³Έν :
class ContentsFireRenderer : public GameEngineRenderer
{
    friend class FireGUI;
public:

    static ContentsFireRenderer* MainFire;

	// constrcuter destructer
	ContentsFireRenderer();
	~ContentsFireRenderer();

	// delete Function
	ContentsFireRenderer(const ContentsFireRenderer& _Other) = delete;
	ContentsFireRenderer(ContentsFireRenderer&& _Other) noexcept = delete;
	ContentsFireRenderer& operator=(const ContentsFireRenderer& _Other) = delete;
	ContentsFireRenderer& operator=(ContentsFireRenderer&& _Other) noexcept = delete;
    static void Load();

protected:


	void Start() override;
    void Update(float _Delta) override;


private:

    FireInfo FireInfoValue;
    float TimeScale = 1.0f;
};

