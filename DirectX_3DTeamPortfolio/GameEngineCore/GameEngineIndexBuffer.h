#pragma once
#include "GameEngineDirectBuffer.h"

// 설명 :
class GameEngineIndexBuffer : 
	public GameEngineResources<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete Function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineIndexBuffer> Create(std::string_view _Name, const std::vector<unsigned int>& _Data)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], _Data.size());
		return Res;
	}

	static std::shared_ptr<GameEngineIndexBuffer> Create(const std::vector<unsigned int>& _Data)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResources::CreateRes();
		Res->ResCreate(&_Data[0], _Data.size());
		return Res;
	}

	void Setting();

	inline int GetIndexCount() 
	{
		return IndexCount;
	}

protected:

private:
	//                                점1개의 크기가 얼마? 점 개수가 몇개냐.,
	void ResCreate(const void* _Data, size_t _IndexCount);

	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	UINT IndexSize = 4;
	UINT IndexCount = 0;
	UINT Offset = 0;
};

