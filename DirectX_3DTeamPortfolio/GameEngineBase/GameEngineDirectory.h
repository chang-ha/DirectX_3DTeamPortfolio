#pragma once
#include "GameEngineFile.h"

// Ό³Έν :
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(std::string_view _path);
	~GameEngineDirectory();

	// delete Function
	//GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	//GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	//GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	//GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	std::vector<class GameEngineFile> GetAllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

	std::vector<GameEngineDirectory> GetAllDirectory();

protected:
	void RecursiveAllDirectory(std::string _Path, std::vector<class GameEngineDirectory>& _Return);

	void RecursiveAllFile(const std::string& _Path, bool _Recursive, std::vector<class GameEngineFile>& Files, const std::vector<std::string>& _Ext);

private:

};

