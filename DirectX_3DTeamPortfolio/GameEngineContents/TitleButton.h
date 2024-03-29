#pragma once

class TitleButton : public GameEngineActor
{
	enum class ButtonType
	{
		Start,
		Exit,
		Done,
	};

public:
	// constructer destructer
	TitleButton();
	~TitleButton();

	// delete Function
	TitleButton(const TitleButton& _Other) = delete;
	TitleButton(TitleButton&& _Other) noexcept = delete;
	TitleButton& operator = (const TitleButton& _Other) = delete;
	TitleButton& operator = (TitleButton&& _Other) noexcept = delete;

	void SetButtonFunction(std::function<void()> _Func) { Event = _Func; }

	void ButtonTrigger();

	void CreateButton(int _Value);
	void ChangeButtonText(int _Value, const std::string& _Name);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

private:
	std::vector<std::shared_ptr<GameEngineUIRenderer>> Buttons;
	float FontScale = 0.0f;

	std::function<void()> Event;

};

