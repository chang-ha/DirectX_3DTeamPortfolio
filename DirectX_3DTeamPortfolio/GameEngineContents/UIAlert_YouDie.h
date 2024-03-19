#pragma once
#include "UIAlert.h"

// Ό³Έν :
class UIAlert_YouDie : public UIAlert
{
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

private:


};

