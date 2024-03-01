#pragma once
#include <GameEngineCore/GameEngineLight.h>




// Ό³Έν :
class ContentsLight : public GameEngineLight
{
public:
	// constrcuter destructer
	ContentsLight();
	~ContentsLight();

	// delete Function
	ContentsLight(const ContentsLight& _Other) = delete;
	ContentsLight(ContentsLight&& _Other) noexcept = delete;
	ContentsLight& operator=(const ContentsLight& _Other) = delete;
	ContentsLight& operator=(ContentsLight&& _Other) noexcept = delete;

	bool IsDebugValue = false;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

