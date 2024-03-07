#include "PreCompile.h"
#include "BaseActor_Struct.h"


void MaterialSoundStruct::PushMaterialSoundRes(int _Key, std::string_view _IDName, std::string_view _SoundName)
{
	std::string ResName = _SoundName.data();
	size_t Index = ResName.find_last_of('.');
	if (std::string::npos == Index)
	{
		MsgBoxAssert("이름을 등록하지 못했습니다. 확장자까지 넣어주세요");
		return;
	}

	std::string Identify = ResName.substr(0, Index);
	std::string IDName = _IDName.data();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources\\Sound");
	Dir.MoveChild(IDName);
	if (false == Dir.IsExits())
	{
		MsgBoxAssert(IDName + "경로를 찾지 못했습니다.");
		return;
	}

	SoundStruct NewStruct;

	bool FindCheck = false;
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".wav" });
	for (GameEngineFile& pFile : Files)
	{
		std::string FileName = pFile.GetFileName();
		if (std::string::npos != FileName.find(Identify))
		{
			FindCheck = true;
			NewStruct.PushData(FileName);
			continue;
		}

		if (true == FindCheck)
		{
			std::pair<int, SoundStruct> Pair = std::make_pair(_Key, NewStruct);
			MaterialSounds.insert(Pair);
			return;
		}
	}

	if (false == FindCheck)
	{
		MsgBoxAssert("자료를 찾지 못했습니다.");
		return;
	}
}

bool MaterialSoundStruct::IsKeyContain(int _Key)
{
	return MaterialSounds.contains(_Key);
}

std::string_view MaterialSoundStruct::GetSound(int _Key)
{
	if (false == IsKeyContain(_Key))
	{
		static std::string ReturnValue;
		return ReturnValue;
	}

	std::map<int, SoundStruct>::iterator FindIter = MaterialSounds.find(_Key);
	return FindIter->second.GetSound();
}

std::vector<int> MaterialSoundStruct::GetKeys()
{
	std::vector<int> Keys;
	if (MaterialSounds.empty())
	{
		return Keys;
	}

	Keys.reserve(MaterialSounds.size());

	for (const std::pair<int, SoundStruct> Pair : MaterialSounds)
	{
		Keys.push_back(Pair.first);
	}

	return Keys;
}