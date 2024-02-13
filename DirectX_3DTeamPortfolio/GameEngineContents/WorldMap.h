#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class WorldMap : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMap();
	~WorldMap();

	// delete Function
	WorldMap(const WorldMap& _Other) = delete;
	WorldMap(WorldMap&& _Other) noexcept = delete;
	WorldMap& operator=(const WorldMap& _Other) = delete;
	WorldMap& operator=(WorldMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;

	std::shared_ptr<class GameEnginePhysXTriMesh> TriMesh;

	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer2;

	std::shared_ptr<class GameEnginePhysXTriMesh> TriMesh2;

	std::shared_ptr<GameContentsFBXRenderer> SkyRenderer;



	//// 맵데이터
	//std::shared_ptr<GameEngineFBXMesh> MapMesh;
	//std::vector<class MapData> MapDatas;
	//std::vector<GameEngineTransform> Transdate;

};

