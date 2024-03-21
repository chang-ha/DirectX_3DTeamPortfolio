#pragma once
#include "BaseActor.h"
class CameraCapsule : public BaseActor
{
public:
	CameraCapsule();
	~CameraCapsule();

	// delete Function
	CameraCapsule(const CameraCapsule& _Other) = delete;
	CameraCapsule(CameraCapsule&& _Other) noexcept = delete;
	CameraCapsule& operator=(const CameraCapsule& _Other) = delete;
	CameraCapsule& operator=(CameraCapsule&& _Other) noexcept = delete;
	std::shared_ptr<class GameEnginePhysXBox> Capsule_02;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;

private:
	//std::shared_ptr<class GameEnginePhysXCapsule> Capsule_02;

	std::shared_ptr<class GameEnginePhysXBox> Capsule_01;

};

