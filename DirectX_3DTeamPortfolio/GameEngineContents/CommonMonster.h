#pragma once

enum class Enum_MonsterType
{
	None,
	LothricKn,
};

// Ό³Έν :
class CommonMonster : public GameEngineActor
{
	friend class MonsterInitial;

public:
	// constrcuter destructer
	CommonMonster();
	~CommonMonster();

	// delete Function
	CommonMonster(const CommonMonster& _Other) = delete;
	CommonMonster(CommonMonster&& _Other) noexcept = delete;
	CommonMonster& operator=(const CommonMonster& _Other) = delete;
	CommonMonster& operator=(CommonMonster&& _Other) noexcept = delete;

	inline std::shared_ptr<GameContentsFBXRenderer> GetFBXRenderer() { return MainRenderer; }


	static Enum_MonsterType GetMonsterType(std::string_view _MonsterTypeName)
	{
		if (auto search = MonsterTypes.find(_MonsterTypeName.data()); search != MonsterTypes.end())
			return search->second;

		return Enum_MonsterType::None;
	}

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;

private:
	static std::map<std::string, Enum_MonsterType> MonsterTypes;


};

