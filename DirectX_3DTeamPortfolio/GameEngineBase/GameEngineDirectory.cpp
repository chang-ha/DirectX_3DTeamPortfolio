#include "PreCompile.h"
#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory() 
{
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

GameEngineDirectory::GameEngineDirectory(std::string_view _path) 
	: GameEnginePath(_path)
{
	if (false == IsDirectory())
	{
		MsgBoxAssert("디렉토리 경로가 아닙니다." + std::string(_path));
	}


}

// 자신의 디렉토리의 파일만 넣습니다.
// 
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string> _Ext, bool _Recursive)
{
	// std::string_view _Path, bool _Recursive, std::vector<class GameEngineFile>& Files, const std::vector<std::string>& _Ext

	std::vector<GameEngineFile> Files;

	RecursiveAllFile(Path.string(), _Recursive, Files, _Ext);

	return Files;
}

std::vector<class GameEngineDirectory> GameEngineDirectory::GetAllDirectory()
{
	std::vector<class GameEngineDirectory> Result;

	RecursiveAllDirectory(Path.string(), Result);

	return Result;
}

void GameEngineDirectory::RecursiveAllDirectory(std::string _Path, std::vector<class GameEngineDirectory>& _Result)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();

		if (true == Entry.is_directory())
		{
			GameEngineDirectory& Dir = _Result.emplace_back();
			Dir.Path = Path;

			RecursiveAllDirectory(Path.string(), _Result);
		}
	}


	return;
}

void GameEngineDirectory::RecursiveAllFile(const std::string& _Path, bool _Recursive, std::vector<class GameEngineFile>& _Files, const std::vector<std::string>& _Ext)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	std::vector<std::string> UpperFilter;
	UpperFilter.resize(_Ext.size());

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		UpperFilter.push_back(GameEngineString::ToUpperReturn(_Ext[i]));
	}

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			if (true == _Recursive)
			{
				std::string Path = Entry.path().string();
				RecursiveAllFile(Path, _Recursive, _Files, _Ext);
			}
			continue;
		}

		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = GameEngineString::ToUpperReturn(Ext.string());

		bool Check = false;

		for (size_t i = 0; i < UpperFilter.size(); i++)
		{
			if (UpperExt == UpperFilter[i])
			{
				Check = true;
				break;
			}
		}

		if (0 == UpperFilter.size())
		{
			Check = true;
		}

		if (false == Check)
		{
			continue;
		}


		_Files.push_back(GameEngineFile(Path.string()));

	}

}