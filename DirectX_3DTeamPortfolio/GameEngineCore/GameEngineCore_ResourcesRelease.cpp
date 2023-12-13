#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineFBXMesh.h"

void GameEngineCore::Resources_Release()
{
	GameEngineFBXMesh::AllResourcesRelease();
}
