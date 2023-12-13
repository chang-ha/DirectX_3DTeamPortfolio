#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineShader.h"
#include "GameEngineStructuredBuffer.h"

class GameEngineShaderResources
{
public:
	std::string Name; // Transformdata <= 쉐이더에서 사용하는 리소스의 이름
	class GameEngineShader* ParentShader; // <= 날 사용하는 쉐이더
	int BindPoint = -1; // <= b0 t0 s0 ... s1 s2 s3, b1 b2 b3 몇번 상수버퍼냐

public:
	virtual void Setting() = 0;
	virtual void Reset() = 0;
};

// 이 쉐이더가 상수버퍼를 몇개 사용하냐
// 상수버퍼가 아니라.
// 상수버퍼를 이용하는 클래스
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;

	const void* CPUDataPtr = nullptr;
	int DataSize = -1;

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineSampler> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineStructedBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineStructuredBuffer> Res;

	const void* CPUDataPtr = nullptr;
	int DataSize = -1;
	int DataCount = -1;

	void Setting() override;
	void Reset() override;
};


// 설명 : 쉐이더 리소스 헬퍼는 2가지 역할을 합니다.
//       1. 특정 쉐이더가 어떤 리소스들을 가지고 있느냐를 조사를 해주는 역할을
//       2. 특정 랜더러가 어떤 리소스들을 세팅해야하는지에 대한 역할 <= 멀티맵으로 해야한다.

// 이걸 만들게된 이유는 <= 그런 복잡한 리소스의 구조를 이름으로 통합하기 위해서 
// SetConstBuffer(0, TransData);
// SetConstBuffer("TransformData", TransData);

class GameEngineShaderResHelper
{
public:
	// constrcuter destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	// 쉐이더의 컴파일된 코드 결과물
	void ShaderResCheck(std::string _FunctionName, class GameEngineShader* _Shader, ID3DBlob* _CompileCode);

	void ShaderResCopy(class GameEngineShader* _Shader);

	void AllShaderResourcesReset();
	void AllShaderResourcesSetting();

	bool IsConstantBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return ConstantBufferSetters.contains(UpperString);
	}

	bool IsStructedBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return StructedBufferSetters.contains(UpperString);
	}

	bool IsTexture(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return TextureSetters.contains(UpperString);
	}

	bool IsSampler(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return SamplerSetters.contains(UpperString);
	}

	// 여기에 값형만 들어갑니다.
	template<typename DataType>
	void SetConstantBufferLink(std::string_view _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, &_Data, sizeof(_Data));
	}

	void SetConstantBufferLink(std::string_view _Name, const void* _Data, int _Size);

	void SetTexture(std::string_view _Name, std::string_view _TextureName, bool _SamplerCheck = true);

	void SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture, bool _SamplerCheck = true);

	void SetSampler(std::string_view _Name, std::string_view _SamplerName);

	void SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler);

	void ResClear();

	// 자신만의 메모리를 만들기 위한 녀석
	template<typename DataType>
	std::list<std::shared_ptr<GameEngineStructuredBuffer>> SetStructedNew(std::string_view _Name, StructuredBufferType _Type, const std::vector<DataType>& _ArrData)
	{
		if (true == _ArrData.empty())
		{
			MsgBoxAssert(std::string(_Name) + "개수가 0개인 데이터를 스트럭처드 버퍼에 세팅하려고 했습니다.");
		}

		return SetStructedNew(_Name, _Type , &_ArrData[0], sizeof(DataType), static_cast<int>(_ArrData.size()));

	}

	std::list<std::shared_ptr<GameEngineStructuredBuffer>> SetStructedNew(std::string_view _Name, StructuredBufferType _Type,const void* _Data, int _Size, int _Count);

	template<typename DataType>
	void SetStructedBufferLink(std::string_view _Name, const std::vector<DataType>& _ArrData)
	{
		if (true == _ArrData.empty())
		{
			MsgBoxAssert(std::string(_Name) + "개수가 0개인 데이터를 스트럭처드 버퍼에 세팅하려고 했습니다.");
		}

		SetStructedBufferLink(_Name, &_ArrData[0], sizeof(DataType), static_cast<int>(_ArrData.size()));
	}

	void SetStructedBufferLink(std::string_view _Name, const void* _Data, int _Size, int _Count);

	void SetStructedBufferChange(std::string_view _Name, std::shared_ptr<GameEngineStructuredBuffer> _Buffer);

	std::shared_ptr<GameEngineStructuredBuffer> GetStructedBuffer(std::string_view _Name, ShaderType Type);

protected:

private:
	// std::shared_ptr로 만들고 
	// 그걸 기억을 해놔야하기 때문에.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
	std::multimap<std::string, GameEngineStructedBufferSetter> StructedBufferSetters;

};

