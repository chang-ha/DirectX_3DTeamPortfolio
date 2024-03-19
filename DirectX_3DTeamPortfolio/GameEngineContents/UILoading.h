#pragma once

// Ό³Έν :
class UILoading : public GameEngineActor
{
public:
	// constrcuter destructer
	UILoading();
	~UILoading();

	// delete Function
	UILoading(const UILoading& _Other) = delete;
	UILoading(UILoading&& _Other) noexcept = delete;
	UILoading& operator=(const UILoading& _Other) = delete;
	UILoading& operator=(UILoading&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineUIRenderer> BackRenderer;

};

