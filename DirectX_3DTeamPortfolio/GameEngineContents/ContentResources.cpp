#include "PreCompile.h"
#include "ContentResources.h"

ContentResources::ContentResources()
{

}

ContentResources::~ContentResources()
{

}

void ContentResources::ContentResourcesInit()
{
	{
		{
			// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("GameEngineContentsShader");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineShader::AutoCompile(File);
			}
		}
	}

	{
		{
			// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Mesh");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

			for (size_t i = 0; i < Files.size(); i++)
			{
				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Files[i].GetStringPath());
			}
		}
	}

	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Mesh");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineFBXAnimation> Mesh = GameEngineFBXAnimation::Load(Files[i].GetStringPath());
		}
	}
}