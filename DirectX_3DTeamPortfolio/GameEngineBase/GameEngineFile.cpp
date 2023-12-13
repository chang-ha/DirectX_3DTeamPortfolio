#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include <filesystem>

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

GameEngineFile::GameEngineFile(const std::string& _path)
	: GameEnginePath(_path)
{

}


void GameEngineFile::Open(FileOpenType _OpenType, FileDataType _DataType)
{

	// C시절부터 내려오는 할아버지 함수를 사용할 겁니다.
	// 바뀐적이 없어요.

	std::string Path = GameEngineFile::GetStringPath();

	std::string Mode = "";

	switch (_OpenType)
	{
	case FileOpenType::Write:
		Mode += "w";
		break;
	case FileOpenType::Read:
		Mode += "r";
		break;
	default:
		break;
	}

	switch (_DataType)
	{
	case FileDataType::Binary:
		Mode += "b";
		break;
	case FileDataType::Text:
		Mode += "t";
		break;
	default:
		break;
	}

	// "rb" 읽겠다 바이너리로
	// "rt" 읽겠다 Text로
	
	// "wb" 읽겠다 바이너리로
	// "wt" 읽겠다 Text로

	fopen_s(&FilePtr, Path.c_str(), Mode.c_str());

	OpenType = _OpenType;
	DataType = _DataType;


	if (false == IsExits() && OpenType == FileOpenType::Read)
	{
		MsgBoxAssert("존재하지 않는 파일을 열어서 읽으려고 해습니다.");
	}
}

void GameEngineFile::DataAllRead(class GameEngineSerializer& _Data)
{
	_Data.BufferResize(GetFileSize<size_t>());
	Read(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

void GameEngineFile::Read(void* _Data, size_t _Size)
{
	//void* _Buffer, 읽어드린 데이터를 쓸 버퍼의 위치
	//size_t _BufferSize, // 버퍼의 크기
	//size_t _ElementSize, // 읽을 양 50
	//size_t _ElementCount, // 읽을 횟수 2
	//FILE* _Stream 


	if (nullptr == FilePtr)
	{
		MsgBoxAssert("열리지 않은 파일을 읽으려고 했습니다. Open을 먼저 실행해주세요.");
	}

	if (OpenType != FileOpenType::Read)
	{
		MsgBoxAssert("읽기 모드로 열리지 않은 파일입니다.");
	}

	fread_s(_Data, _Size, _Size, 1, FilePtr);
}

uintmax_t GameEngineFile::GetFileSize()
{
	// c 함수를 사용했는데 
	return std::filesystem::file_size(Path);
}

void GameEngineFile::Write(class GameEngineSerializer& _Data)
{
	Write(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

// 파일에서 데이터를 쓴다.
void GameEngineFile::Write(void* _Data, size_t _Size)
{
	if (nullptr == FilePtr)
	{
		MsgBoxAssert("열리지 않은 파일을 읽으려고 했습니다. Open을 먼저 실행해주세요.");
	}

	if (OpenType != FileOpenType::Write)
	{
		MsgBoxAssert("쓰기 모드로 열리지 않은 파일입니다.");
	}

	fwrite(_Data, _Size, 1, FilePtr);

}