#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Object_Torchlight : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Torchlight();
	~Object_Torchlight();

	// delete Function
	Object_Torchlight(const Object_Torchlight& _Other) = delete;
	Object_Torchlight(Object_Torchlight&& _Other) noexcept = delete;
	Object_Torchlight& operator=(const Object_Torchlight& _Other) = delete;
	Object_Torchlight& operator=(Object_Torchlight&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<class ContentsLight> Light;
	std::shared_ptr<ContentsFireRenderer> FireRender;

	float LightPowerTime = 0.0f;
	unsigned int NoiseXOffset = 0;
	std::shared_ptr<GameEngineTexture> NoiseTexture;
};

