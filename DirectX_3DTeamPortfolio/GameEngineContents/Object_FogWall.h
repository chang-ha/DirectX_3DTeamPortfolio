#pragma once
 
class Object_FogWall : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_FogWall();
	~Object_FogWall();

	// delete Function
	Object_FogWall(const Object_FogWall& _Other) = delete;
	Object_FogWall(Object_FogWall&& _Other) noexcept = delete;
	Object_FogWall& operator=(const Object_FogWall& _Other) = delete;
	Object_FogWall& operator=(Object_FogWall&& _Other) noexcept = delete;

	void SetInFunction(std::function<void()> _InFunction)
	{
		InFunction = _InFunction;
	}

	void SetOutFunction(std::function<void()> _OutFunction)
	{
		OutFunction = _OutFunction;
	}

	void Start_InFunction()
	{
		if (nullptr == InFunction)
		{
			MsgBoxAssert("시작함수가 존재하지 않습니다.");
			return;
		}

		InFunction();
	}

	void Reset();
	void End();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<class ContentsFogWallRenderer> FogWallRenderer = nullptr;

	std::shared_ptr<GameEnginePhysXBox> WallCollision = nullptr;
	std::shared_ptr<GameEngineCollision> InDetectCollision = nullptr;
	std::shared_ptr<GameEngineCollision> OutDetectCollision = nullptr;

	std::function<void()> InFunction;
	std::function<void()> OutFunction;

	void Start_OutFunction()
	{
		if (nullptr == OutFunction)
		{
			MsgBoxAssert("시작함수가 존재하지 않습니다.");
			return;
		}

		OutFunction();
	}

	void OutDetect();

};

