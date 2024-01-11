#pragma once

class GameEnginePhysXLevel
{
	friend class GameEnginePhysX;
	friend class GameEnginePhysXTriMesh;
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

	bool RayCast(const float4& _Pos, const float4& _DirVector, float _MaxDisTance);

protected:
	void PhysXLevelInit();
	void RunSimulation(float _Delta);

	physx::PxScene* Scene = nullptr;
	physx::PxControllerManager* ControllerManager = nullptr;
private:
	void Release();

	static std::list<void*> AllData;
};

