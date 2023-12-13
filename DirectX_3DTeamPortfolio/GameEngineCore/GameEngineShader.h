#pragma once
#include "GameEngineShaderResHelper.h"

// 설명 :
class GameEngineShader
{
public:
	static bool AutoCompile(GameEngineFile& _File);

	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineShaderResHelper ResHelper;

	ShaderType GetShaderType() 
	{
		return ShaderTypeValue;
	}
	
protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
	std::string Version;

	// 쉐이더의 바이너리 코드에 대한 포인터
	// 쉐이더 코드를 관리하기 위한 컴파일 포인터이다.
	ID3DBlob* BinaryCode = nullptr;
	std::string EntryName = "";

	void ShaderResCheck();

private:
	ShaderType ShaderTypeValue = ShaderType::None;

};

