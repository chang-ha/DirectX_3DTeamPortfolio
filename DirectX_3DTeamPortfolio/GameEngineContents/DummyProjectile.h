#pragma once

// Ό³Έν :
class DummyProjectile : public GameEngineActor
{
public:
	// constrcuter destructer
	DummyProjectile();
	~DummyProjectile();

	// delete Function
	DummyProjectile(const DummyProjectile& _Other) = delete;
	DummyProjectile(DummyProjectile&& _Other) noexcept = delete;
	DummyProjectile& operator=(const DummyProjectile& _Other) = delete;
	DummyProjectile& operator=(DummyProjectile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void AttackCollision();

private:
	std::shared_ptr<GameEngineRenderer> AttackRenderer;
	std::shared_ptr<GameEngineCollision> AttackCol;

};

