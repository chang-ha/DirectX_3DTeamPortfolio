#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class EventCol : public GameEngineActor
{
public:
	// constrcuter destructer
	EventCol();
	virtual ~EventCol();

	// delete Function
	EventCol(const EventCol& _Other) = delete;
	EventCol(EventCol&& _Other) noexcept = delete;
	EventCol& operator=(const EventCol& _Other) = delete;
	EventCol& operator=(EventCol&& _Other) noexcept = delete;

	void SetWorldPosition(const float4& _Pos);
	void SetWorldScale(const float4& _Scale);

	template<typename EnumType>
	bool Collision(EnumType _Order)
	{
		return Collision(static_cast<int>(_Order));
	}

	bool Collision(int _Order)
	{
		return Ev_Col->Collision(_Order);
	}

	std::function<void()> Event;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> Ev_Col;

};

