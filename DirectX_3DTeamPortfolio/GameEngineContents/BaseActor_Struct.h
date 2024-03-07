#pragma once

enum class Enum_DS3MaterialSound
{
	E1001 = 1001,
	E1020 = 1020,
	E1301 = 1301,
	E2001 = 2001,
	E3001 = 3001,
	E3020 = 3020,
	E4001 = 4001,
	E4101 = 4101,
	E5000 = 5000,
	E5001 = 5001,
	E5500 = 5500,
	E6000 = 6000,
	E6005 = 6005,
	E6501 = 6501,
	E8000 = 8000,
	E8001 = 8001,
	E8500 = 8500,
};

class MaterialSoundStruct
{
	friend class BaseActor;
	// constrcuter destructer
	MaterialSoundStruct() {}
	~MaterialSoundStruct() {}

	// delete Function
	MaterialSoundStruct(const MaterialSoundStruct& _Other) = delete;
	MaterialSoundStruct(MaterialSoundStruct&& _Other) noexcept = delete;
	MaterialSoundStruct& operator=(const MaterialSoundStruct& _Other) = delete;
	MaterialSoundStruct& operator=(MaterialSoundStruct&& _Other) noexcept = delete;

	class SoundStruct
	{
	public:
		SoundStruct(){}
		~SoundStruct() {}

		std::string_view GetSound()
		{
			if (true == SoundRes.empty())
			{
				MsgBoxAssert("자료에 아무런 리소스도 담겨있지 않습니다.");
				return nullptr;
			}

			int MaxCount = static_cast<int>(SoundRes.size());
			if (CurIndex >= MaxCount)
			{
				CurIndex = 0;
			}

			return SoundRes.at(CurIndex);
		}

		void PushData(std::string_view _Soundname)
		{
			SoundRes.push_back(_Soundname.data());
		}

	private:
		std::vector<std::string> SoundRes;
		int CurIndex = 0;

	};

public:
	void PushMaterialSoundRes(int _Key, std::string_view _IDName, std::string_view _SoundName);
	bool IsKeyContain(int _Key);
	std::string_view GetSound(int _Key);
	std::vector<int> GetKeys();

private:
	std::map<int, SoundStruct> MaterialSounds; // 재질에 따른 발소리 리소스

};