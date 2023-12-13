#pragma once
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineRasterizer : public GameEngineResources<GameEngineRasterizer>
{
public:
	// constrcuter destructer
	GameEngineRasterizer();
	~GameEngineRasterizer();

	// delete Function
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRasterizer> Create(std::string_view _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineRasterizer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();

protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Desc);

private:
	D3D11_RASTERIZER_DESC Desc = {};
	ID3D11RasterizerState* State = nullptr;

};

