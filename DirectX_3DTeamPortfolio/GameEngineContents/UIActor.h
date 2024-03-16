#pragma once

// Ό³Έν :
class UIActor : public GameEngineActor
{
public:
	// constructer destructer
	UIActor();
	~UIActor();

	// delete Function
	UIActor(const UIActor& _Other) = delete;
	UIActor(UIActor&& _Other) noexcept = delete;
	UIActor& operator = (const UIActor& _Other) = delete;
	UIActor& operator = (UIActor&& _Other) noexcept = delete;

	virtual void Reset()
	{
		Off();
	}

protected:

private:

};

