#pragma once

class TriggerActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TriggerActor();
	~TriggerActor();

	// delete Function
	TriggerActor(const TriggerActor& _Other) = delete;
	TriggerActor(TriggerActor&& _Other) noexcept = delete;
	TriggerActor& operator=(const TriggerActor& _Other) = delete;
	TriggerActor& operator=(TriggerActor&& _Other) noexcept = delete;

	void SetFunction(std::function<void()> _Func) { Event = _Func; }
	void SetWorldPosition(const float4& _Pos);
	void SetWorldScale(const float4& _Scale);

	void Trigger();

protected:
	void Start() override;
	void Release() override;

private:
	std::shared_ptr<GameEngineCollision> EventCollision;
	std::function<void()> Event;

};

