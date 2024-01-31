#pragma once
#include "BaseActor.h"

#include "ContentsControlInput.h"


// Ό³Έν :
class DummyActor : public BaseActor
{
public:
	// constrcuter destructer
	DummyActor();
	~DummyActor();

	// delete Function
	DummyActor(const DummyActor& _Other) = delete;
	DummyActor(DummyActor&& _Other) noexcept = delete;
	DummyActor& operator=(const DummyActor& _Other) = delete;
	DummyActor& operator=(DummyActor&& _Other) noexcept = delete;

	float* GetSpeedPointer() { return &Speed; }

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;


	void MoveUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineFBXRenderer> FbxRenderer;
	std::shared_ptr<GameEngineCollision> BodyCollision;
	class ContentsControlInput ControlInput;

	float Speed = 10.0f;

};

