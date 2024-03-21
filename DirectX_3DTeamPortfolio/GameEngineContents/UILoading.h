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

	void MadesCreateSetName();
	void ExplainKey();

private:
	std::shared_ptr<GameEngineUIRenderer> BackDarkRenderer;
	std::shared_ptr<GameEngineUIRenderer> UICommentRenderer;

	std::shared_ptr<GameEngineUIRenderer> AKLogo;
	std::shared_ptr<GameEngineUIRenderer> TeamName;
	std::shared_ptr<GameEngineUIRenderer> ProductionAndField;
	std::shared_ptr<GameEngineUIRenderer> Mades;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> TeamMember;

	float4 ExplainStartPos = 0.0f;
	std::shared_ptr<GameEngineUIRenderer> ExplainText;

	std::shared_ptr<GameEngineUIRenderer> Explain;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> ExplainMember;
	std::shared_ptr<GameEngineUIRenderer> Explain_2;
};

