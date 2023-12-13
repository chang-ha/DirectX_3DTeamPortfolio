#pragma once
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineSampler : public GameEngineResources<GameEngineSampler>
{
public:
	// constrcuter destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete Function
	GameEngineSampler(const GameEngineSampler& _Other) = delete;
	GameEngineSampler(GameEngineSampler&& _Other) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineSampler> Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineSampler> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	//D3D11_FILTER Filter;
	//D3D11_TEXTURE_ADDRESS_MODE AddressU;

	static std::shared_ptr<GameEngineSampler> Create(D3D11_FILTER _Filter, D3D11_TEXTURE_ADDRESS_MODE _Address)
	{
		if (false == OptionSamplers.contains(_Filter))
		{
			OptionSamplers[_Filter];
		}

		std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>& Add = OptionSamplers[_Filter];

		if (true == Add.contains(_Address))
		{
			return Add[_Address];
		}

		D3D11_SAMPLER_DESC Desc = {};
		Desc.Filter = _Filter;
		Desc.AddressU = _Address;
		Desc.AddressV = _Address;
		Desc.AddressW = _Address;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> NewSampler = std::make_shared<GameEngineSampler>();
		NewSampler->ResCreate(Desc);
		Add[_Address] = NewSampler;
		return NewSampler;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
	void CSSetting(UINT _Slot);

protected:
	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

private:
	static std::map<D3D11_FILTER, std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>> OptionSamplers;

	D3D11_SAMPLER_DESC Desc = {};
	ID3D11SamplerState* State = nullptr;

};

