#pragma once
#include "UIAlert.h"

// ���� :
class UIAlert_BoneLit : public UIAlert
{
public:
	// constrcuter destructer
	UIAlert_BoneLit();
	~UIAlert_BoneLit();

	// delete Function
	UIAlert_BoneLit(const UIAlert_BoneLit& _Other) = delete;
	UIAlert_BoneLit(UIAlert_BoneLit&& _Other) noexcept = delete;
	UIAlert_BoneLit& operator=(const UIAlert_BoneLit& _Other) = delete;
	UIAlert_BoneLit& operator=(UIAlert_BoneLit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:


};

