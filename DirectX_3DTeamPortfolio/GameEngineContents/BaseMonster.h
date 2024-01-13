#pragma once

enum class Enum_MonsterType
{
	None,
	LothricKn = 1280,
};


// Ό³Έν :
class BaseMonster : public GameEngineActor
{
private:
	enum Enum_MonsterFlag
	{
		None = 0,
		IsHit = (1 << 0),
		IsAbleJump = (1 << 1),
		IsGaurding = (1 << 2)
	};

	friend class MonsterInitial;

public:
	// constrcuter destructer
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;


	std::string GetTypeName();
	std::string GetEventPath();
	void EventLoad();

	inline std::shared_ptr<GameContentsFBXRenderer> GetFBXRenderer() { return MainRenderer; }

protected:
	void Start() override;
	void Update(float _Delta) override;
	
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	template<typename EnumType>
	void MeshOnOffSwitch(EnumType _MeshIndex)
	{
		MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0]->OnOffSwitch();
	}

	bool IsFlag(Enum_MonsterFlag _Flag) const;
	void SetFlag(Enum_MonsterFlag _Flag, bool _Value);
	void AddFlag(Enum_MonsterFlag _Flag);
	void SubFlag(Enum_MonsterFlag _Flag);

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<GameEngineCollision> RAttackCollision;

	GameEngineState MainState;

private:
	static std::map<std::string, Enum_MonsterType> MonsterTypes;

	int Flag = 0;

};

