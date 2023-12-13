#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader() 
{
}

GameEngineShader::~GameEngineShader() 
{
}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow)
{
	ShaderTypeValue = _Type;


	switch (_Type)
	{
	case ShaderType::None:
	{
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
		break;
	}
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Geometry:
		Version = "gs";
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Compute:
		Version = "cs";
		break;
	case ShaderType::Max:
	default:
	{
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
		break;
	}
	}

	Version += "_";
	Version += std::to_string(_VersionHigh); // 5
	Version += "_";
	Version += std::to_string(_VersionLow); // 5

	// "vs_5_0"
}


void GameEngineShader::ShaderResCheck()
{
	ResHelper.ShaderResCheck(EntryName, this, BinaryCode);
}

// 부모가 자식클래스를 알고 있는 경우라 조금 선생님 타입
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineGeometryShader.h"
#include "GameEngineComputeShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	// 쉐이더 파일안에 나나 여러분들일것이다.
	// 쉐이더를 짜다보면 다양한 종류의 쉐이더가 있을수 있다를 거장하고.
	// 우리만의 네이밍 규칙을 기반으로
	// 어떤 쉐이더가 들어있는지 이해하고 파악된 쉐이더 함수들을 자동 쉐이더로 만들어주는 함수에요.

	// 규칙은 일단 기본적으로 _VS <= 버텍스 쉐이더 함수다를 명확하게 표현하는 함수다를 표현하는 이름이어야 한다.
	// 코딩 스텐다드 부터.

	// 이 파일의 경로로 
	_File.Open(FileOpenType::Read, FileDataType::Text);
	uintmax_t size = _File.GetFileSize();

	if (0 == size)
	{
		return false;
	}

	GameEngineSerializer Ser;
	_File.DataAllRead(Ser);

	std::string_view ShaderCode = Ser.GetStringView();

	// 파일을 다 읽어왔고
	// 내부에 어떤 쉐이더가 있는지 분석하기 시작할 것이다.
	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_VS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineVertexShader::Load(_File.GetStringPath(), EntryName);

			// ColorShader.fx 픽셀쉐이더가 있을수 있다.

		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_GS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineGeometryShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_PS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);
			GameEnginePixelShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_CS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineComputeShader::Load(_File.GetStringPath(), EntryName);

		}
	}



	return true;
}

