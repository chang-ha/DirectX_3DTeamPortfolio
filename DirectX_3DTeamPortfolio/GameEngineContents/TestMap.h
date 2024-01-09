#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class TestMap : public GameEngineActor
{
public:
	// constrcuter destructer
	TestMap();
	~TestMap();

	// delete Function
	TestMap(const TestMap& _Other) = delete;
	TestMap(TestMap&& _Other) noexcept = delete;
	TestMap& operator=(const TestMap& _Other) = delete;
	TestMap& operator=(TestMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	// std::shared_ptr<GameEngineFBXMesh> MapMesh;

	// �ʵ�����
	//std::vector<class MapData> MapDatas;
	//std::vector<GameEngineTransform> Transdate;

};

