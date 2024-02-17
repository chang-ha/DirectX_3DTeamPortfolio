#pragma once
#include "BaseActor.h"

#include "ContentsControlInput.h"
#include "ContentsMouseInput.h"

// 설명 :
class DummyActor : public BaseActor
{
private:
	class CameraControl : public GameEngineObjectBase
	{
	public:
		void On() override;
		void Off() override;

		void Init(GameEngineActor* _pParent);
		void Release();

		void ControlUpdate(float _Delta);

		inline const float4& GetQuaternion() const { return QutRotation; }

	private:
		void InputUpdate(float _Delta);
		void FollowUpdate();
		void HeightUpdate() const;

	public:
		ContentsMouseInput MouseInput;
		GameEngineActor* pParent = nullptr;
		GameEngineTransform* pCameraTransfrom = nullptr;

		float PointDist = 50.0f;
		float4 OriginPos = float4::ZERO; // 전환 전의 원래 위치
		float4 QutRotation = float4::ZERONULL;

		std::shared_ptr<GameEngineObject> ColObject;
		std::shared_ptr<GameEngineRenderer> PointObject;
		std::shared_ptr<GameEngineRenderer> PosRenderer;

	};

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

	inline float* GetSpeedPointer() { return &MoveSpeed; }

	void AttachCamera();
	void DettachCamera();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelEnd(class GameEngineLevel* _PrevLevel) override;

	// Move
	void MoveUpdate(float _Delta);

	// Camera Method
	inline bool IsCameraTargetting()
	{
		return CameraControler.IsUpdate();
	}

	void CameraControlUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineRenderer> MainRenderer;
	std::shared_ptr<GameEngineCollision> BodyCollision;
	ContentsControlInput ControlInput;
	CameraControl CameraControler;

	float MoveSpeed = 500.0f;

};