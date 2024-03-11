#pragma once
#include "BaseMonster.h"

#include "ContentsControlInput.h"
#include "ContentsMouseInput.h"

// 설명 :
class DummyActor : public BaseMonster
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

		float PointDist = 70.0f;
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
	void ProjectileUpdate(float _Delta);

	// Camera Method
	inline bool IsCameraTargetting()
	{
		return CameraControler.IsUpdate();
	}

	void CameraControlUpdate(float _Delta);

	// Mode
	void ModeInputUpdate();

	// Test Collision
	void Stab();

private:
	std::shared_ptr<GameEngineRenderer> MainRenderer;
	std::shared_ptr<GameEngineCollision> DummyCollision;
	std::shared_ptr<GameEngineCollision> BodyCollision;
	std::shared_ptr<GameEngineCollision> ShieldCollision;
	std::shared_ptr<GameEngineCollision> StabCollision;
	std::vector<std::shared_ptr<class DummyProjectile>> Projectiles;

	ContentsControlInput ControlInput;
	CameraControl CameraControler;

	float MoveSpeed = 500.0f;
	float StateTime = 0.0f;

};