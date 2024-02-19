#pragma once

// Ό³Έν :
class DummyProjectile : public GameEngineActor
{
	enum class eState
	{
		Ready,
		Active,
		None,
	};

public:
	// constrcuter destructer
	DummyProjectile();
	~DummyProjectile();

	// delete Function
	DummyProjectile(const DummyProjectile& _Other) = delete;
	DummyProjectile(DummyProjectile&& _Other) noexcept = delete;
	DummyProjectile& operator=(const DummyProjectile& _Other) = delete;
	DummyProjectile& operator=(DummyProjectile&& _Other) noexcept = delete;

	void Init(class DummyActor* _pParent)
	{
		pParent = _pParent;
	}

	void Fire();
	inline bool IsReady() const { return bReady; }

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void AttackCollision();

private:
	std::shared_ptr<GameEngineRenderer> AttackRenderer;
	std::shared_ptr<GameEngineCollision> AttackCol;

	GameEngineState MainState;

	class DummyActor* pParent = nullptr;

	float4 DirVector = float4::ZERO;
	static constexpr int Att = 5;

	bool bReady = false;

};

