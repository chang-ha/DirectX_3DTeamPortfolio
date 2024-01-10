#pragma once

enum class Enum_MonsterType
{
	None,
	LothricKn = 1280,
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


	std::string GetTypeName();

	std::string GetEventPath();

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	template<typename EnumType>
	void MeshOnOffSwitch(EnumType _MeshIndex)
	{
		MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0]->OnOffSwitch();
	}

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;

private:
	static std::map<std::string, Enum_MonsterType> MonsterTypes;


};

