#include "PreCompile.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include <fstream>
#include "GameEngineString.h"
//#include <stdio.h>
//#include <io.h>

std::string GameEnginePath::GetFileName(std::string_view _Path)
{
	std::filesystem::path ReturnPath = _Path.data();
	return ReturnPath.filename().string();
}

bool GameEnginePath::IsFileExist(std::string_view _Path)
{
	GameEnginePath NewPath = _Path;

	std::string Ext = GameEngineString::ToUpperReturn(NewPath.GetExtension());

	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	std::ifstream infile(wPath);

	return infile.good();
}

GameEnginePath::GameEnginePath() 
{
	SetCurrentPath();
}

GameEnginePath::GameEnginePath(std::string_view _path)
	: Path(_path)
{

}

GameEnginePath::~GameEnginePath() 
{
}

std::string GameEnginePath::GetExtension()
{
	return Path.extension().string();
}

std::string GameEnginePath::GetFolderPath()
{
	if (true == Path.has_filename())
	{
		std::filesystem::path Folder = Path.parent_path();
		return Folder.string();
	}

	return Path.string();
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}

void GameEnginePath::ChangeExtension(std::string_view _NewExtension)
{
	Path.replace_extension(_NewExtension);
}

void GameEnginePath::SetCurrentPath() 
{
	Path = std::filesystem::current_path();
}


void GameEnginePath::MoveParent() 
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToExistsChild(std::string_view _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else 
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("루트 경로까지 샅샅히 뒤졌지만" + std::string(_ChildPath) + "파일이나 폴더를 하위로 가지고 있는 경로를 찾지 못했습니다");
		}
	}


}

bool GameEnginePath::IsExits()
{
	return std::filesystem::exists(Path);
}

void GameEnginePath::MoveChild(std::string_view _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다." + CheckPath.string());
	}

	Path = CheckPath;
	// Path.append(_ChildPath);
}

std::string GameEnginePath::PlusFilePath(std::string_view _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다." + CheckPath.string());
	}

	return CheckPath.string();
}

void GameEnginePath::AppendPath(std::string_view _ChildPath)
{
	Path.append(_ChildPath);
}

bool GameEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

std::string GameEnginePath::GetParentString(const std::string& _ChildPath)
{
	int CountBeforeBackSlash = 0;

	while (true)
	{
		if ('\\' == _ChildPath[CountBeforeBackSlash])
		{
			break;
		}

		++CountBeforeBackSlash;
	}

	std::string ChildPath = "";
	ChildPath.reserve(CountBeforeBackSlash);

	for (size_t i = 0; i < CountBeforeBackSlash; i++)
	{
		ChildPath.push_back(_ChildPath[i]);
	}

	return ChildPath;
}