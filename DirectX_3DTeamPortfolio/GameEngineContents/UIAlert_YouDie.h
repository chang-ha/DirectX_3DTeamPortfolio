#pragma once
#include "UIAlert.h"

// ���� :
class UIAlert_YouDie : public UIAlert
{
	enum class eState
	{
		Appear,
		Stay,
		Disappear,
	};

public:
	// constrcuter destructer
	UIAlert_YouDie();
	~UIAlert_YouDie();

	// delete Function
	UIAlert_YouDie(const UIAlert_YouDie& _Other) = delete;
	UIAlert_YouDie(UIAlert_YouDie&& _Other) noexcept = delete;
	UIAlert_YouDie& operator=(const UIAlert_YouDie& _Other) = delete;
	UIAlert_YouDie& operator=(UIAlert_YouDie&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void Start_Appear(GameEngineState* _Parent);

	void Update_Stay(float _Delta, GameEngineState* _Parent);


private:
	GameEngineState mState;

	float ScaleRatio = 0.0f;
	
};

