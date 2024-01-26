#pragma once

class TestObject : public GameEngineActor
{
public:
	// constructer destructer
	TestObject();
	~TestObject();

	// delete function
	TestObject(const TestObject& _Ohter) = delete;
	TestObject(TestObject&& _Ohter) noexcept = delete;
	TestObject& operator=(const TestObject& _Other) = delete;
	TestObject& operator=(TestObject&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<class GameEnginePhysXTriMesh> TriMesh;
};

