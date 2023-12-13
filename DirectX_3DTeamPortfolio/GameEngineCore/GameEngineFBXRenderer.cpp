#include "PreCompile.h"
#include "GameEngineFBXRenderer.h"

GameEngineFBXRenderer::GameEngineFBXRenderer() 
{
}

GameEngineFBXRenderer::~GameEngineFBXRenderer() 
{
}

void GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�ε����� ���� FBX �Ž��� ����Ϸ��� �߽��ϴ�");
	}

	FindFBXMesh->Initialize();

	for (int UnitCount = 0; UnitCount < FindFBXMesh->GetRenderUnitCount(); UnitCount++)
	{
		SetFBXMesh(_Name, _Material, UnitCount);
	}

}

// ���� ����Ʈ�� �ϳ��� 
void GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex = 0)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);
	FindFBXMesh->Initialize();
	for (int SubSetCount = 0; SubSetCount < FindFBXMesh->GetSubSetCount(_RenderUnitInfoIndex); SubSetCount++)
	{
		SetFBXMesh(_Name, _Material, _RenderUnitInfoIndex, SubSetCount);
	}
}

std::shared_ptr<GameEngineRenderUnit> GameEngineFBXRenderer::SetFBXMesh(std::string_view _Name, std::string_view _Material, int _RenderUnitInfoIndex, int _SubSetIndex)
{
	std::shared_ptr<GameEngineFBXMesh> FindFBXMesh = GameEngineFBXMesh::Find(_Name);

	if (nullptr == FindFBXMesh)
	{
		MsgBoxAssert("�������� �ʴ� FBXMesh�� �����߽��ϴ�");
		return nullptr;
	}

	if (nullptr == FBXMesh && nullptr != FindFBXMesh)
	{
		FBXMesh = FindFBXMesh;
	}

	if (FBXMesh->GetPath() != FindFBXMesh->GetPath())
	{
		MsgBoxAssert("�̹� ������ �Ϸ�� FBXRenderer�� �ٸ� FBX mesh�� �����Ϸ��� �߽��ϴ�.");
		return nullptr;
	}

	FindFBXMesh->Initialize();

	// []
	// []
	// []
	// []
	// []
	// []
	// []
	// []
	// []
	// []
	// []

	// FBXmesh�� ���� ����Ʈ ����
	// 

	if (true == RenderUnits.empty())
	{
		RenderUnits.resize(FBXMesh->GetRenderUnitCount());
		for (int i = 0;  i < FBXMesh->GetRenderUnitCount();  i++)
		{
			int Count = FindFBXMesh->GetSubSetCount(i);
			RenderUnits[i].resize(Count);
		}
	}
	// _RenderUnitInfoIndex, int _SubSetIndex
	if (nullptr == RenderUnits[_RenderUnitInfoIndex][_SubSetIndex])
	{
		RenderUnits[_RenderUnitInfoIndex][_SubSetIndex] = CreateAndFindRenderUnit(-1);
	}

	std::shared_ptr<GameEngineRenderUnit> Unit = RenderUnits[_RenderUnitInfoIndex][_SubSetIndex];
	std::shared_ptr<GameEngineMesh> Mesh = FindFBXMesh->GetGameEngineMesh(_RenderUnitInfoIndex, _SubSetIndex);

	Unit->SetMesh(Mesh);
	Unit->SetMaterial(_Material);

	return Unit;
}