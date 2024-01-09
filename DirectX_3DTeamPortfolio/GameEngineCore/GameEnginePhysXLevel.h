#pragma once

class GameEnginePhysXLevel
{
public:
	// constructer destructer
	GameEnginePhysXLevel();
	~GameEnginePhysXLevel();

	// delete function
	GameEnginePhysXLevel(const GameEnginePhysXLevel& _Ohter) = delete;
	GameEnginePhysXLevel(GameEnginePhysXLevel&& _Ohter) noexcept = delete;
	GameEnginePhysXLevel& operator=(const GameEnginePhysXLevel& _Other) = delete;
	GameEnginePhysXLevel& operator=(GameEnginePhysXLevel&& _Other) noexcept = delete;

	inline physx::PxScene* GetScene()
	{
		return Scene;
	}

	inline physx::PxControllerManager* GetControllerManager()
	{
		return ControllerManager;
	}

protected:
	void PhysXLevelInit();
	void RunSimulation(float _Delta);

	physx::PxScene* Scene = nullptr;
	physx::PxControllerManager* ControllerManager = nullptr;
private:

};

