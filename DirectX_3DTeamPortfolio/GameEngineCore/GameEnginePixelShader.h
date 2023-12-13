#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// Ό³Έν :
class GameEnginePixelShader : public GameEngineResources<GameEnginePixelShader> , public GameEngineShader
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEnginePixelShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEnginePixelShader> Load(std::string_view _Path, std::string_view _Name, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);

};

