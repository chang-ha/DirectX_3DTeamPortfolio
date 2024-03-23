#pragma once
#include "UIAlert.h"

// Ό³Έν :
class UIAlert_Destroy : public UIAlert
{
	enum class eState
	{
		Appear,
		Stay,
		Disappear,
	};

public:
	// constrcuter destructer
	UIAlert_Destroy();
	~UIAlert_Destroy();

	// delete Function
	UIAlert_Destroy(const UIAlert_Destroy& _Other) = delete;
	UIAlert_Destroy(UIAlert_Destroy&& _Other) noexcept = delete;
	UIAlert_Destroy& operator=(const UIAlert_Destroy& _Other) = delete;
	UIAlert_Destroy& operator=(UIAlert_Destroy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;


	void Start_Appear(GameEngineState* _Parent);
	void Start_Stay(GameEngineState* _Parent);
	void Start_Disappear(GameEngineState* _Parent);

	void Update_Appear(float _Delta, GameEngineState* _Parent);
	void Update_Stay(float _Delta, GameEngineState* _Parent);
	void Update_Disappear(float _Delta, GameEngineState* _Parent);

private:
	GameEngineState mState;

	float4 ChangeScale = float4::ZERO;

};

