#include "PreCompile.h"
#include "GameEngineMesh.h"


GameEngineMesh::GameEngineMesh() 
{
}

GameEngineMesh::~GameEngineMesh() 
{
}

void GameEngineMesh::InputAssembler1()
{
	if (nullptr == VertexBufferPtr)
	{
		MsgBoxAssert("매쉬가 세팅되어 있지 않습니다.");
		return;
	}

	VertexBufferPtr->Setting();

	GameEngineCore::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}

void GameEngineMesh::InputAssembler2()
{
	if (nullptr == IndexBufferPtr)
	{
		MsgBoxAssert("매쉬가 세팅되어 있지 않습니다.");
		return;
	}

	IndexBufferPtr->Setting();
}

void GameEngineMesh::IndexedDraw()
{
	GameEngineCore::GetContext()->DrawIndexed(IndexBufferPtr->GetIndexCount(), 0, 0);
}

void GameEngineMesh::InstancingDraw(int _DrawCount)
{
	if (0 >= _DrawCount)
	{
		return;
	}

	GameEngineCore::GetContext()->DrawIndexedInstanced(IndexBufferPtr->GetIndexCount(), _DrawCount, 0, 0, 0);
}