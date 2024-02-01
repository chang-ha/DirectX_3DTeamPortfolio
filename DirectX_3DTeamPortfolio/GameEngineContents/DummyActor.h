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

	void On() override;
	void Off() override;

	float* GetSpeedPointer() { return &Speed; }

	void AttachCamera();
	void DettachCamera();

protected:

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _PrevLevel) override;


	void MoveUpdate(float _Delta);

	bool IsCameraTargetting();
	void SetCameraDist(float _fDist);
	float4 CalMouseAxis();
	void PivotUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineFBXRenderer> FbxRenderer;
	std::shared_ptr<GameEngineCollision> BodyCollision;
	std::shared_ptr<GameEngineObject> CameraPivot;
	class ContentsControlInput ControlInput;

	float Speed = 10.0f;

	float4 TargetRotation;
	float Camera_Dist = 200.0f;
	float4 Camera_Axis = float4::ZERO;
	float Xaxis = 0.0f;
	float Yaxis = 0.0f;

};

