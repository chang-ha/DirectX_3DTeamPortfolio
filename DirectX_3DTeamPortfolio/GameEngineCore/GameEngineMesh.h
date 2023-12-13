#pragma once
#include "GameEngineResources.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// 레스터라이저 전에 범위를 잡을때 사용하는 버텍스와 인덱스버퍼를 관리하는 클래스입니다.

// 설명 : 
class GameEngineMesh : public GameEngineResources<GameEngineMesh>
{
public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	void InputAssembler1();
	void InputAssembler2();

	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name, std::string_view _VtxName, std::string_view _IdxName)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResources::CreateRes(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if (nullptr == Res->VertexBufferPtr
			|| nullptr == Res->IndexBufferPtr)
		{
			MsgBoxAssert("매쉬를 만드는데 실패했습니다.");
		}

		return Res;
	}

	static std::shared_ptr<GameEngineMesh> Create(std::shared_ptr<GameEngineVertexBuffer> _Vtx, std::shared_ptr<GameEngineIndexBuffer> _Idx)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResources::CreateRes();
		Res->VertexBufferPtr = _Vtx;
		Res->IndexBufferPtr = _Idx;

		if (nullptr == Res->VertexBufferPtr
			|| nullptr == Res->IndexBufferPtr)
		{
			MsgBoxAssert("매쉬를 만드는데 실패했습니다.");
		}

		return Res;
	}


	std::shared_ptr<class GameEngineVertexBuffer> GetVertexBuffer()
	{
		return VertexBufferPtr;
	}

	void SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY _TOPOLOGY)
	{
		TOPOLOGY = _TOPOLOGY;
	}


	void IndexedDraw();
	void InstancingDraw(int _DrawCount);

protected:

private:
	// has a
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
};

