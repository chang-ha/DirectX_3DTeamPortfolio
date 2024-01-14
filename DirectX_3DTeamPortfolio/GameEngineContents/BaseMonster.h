#pragma once

enum class Enum_MonsterType
{
	None,
	LothricKn = 1280,
};

enum class Enum_BoneType
{
	None,
	B_01_LeftHand,
	B_01_RightHand,
};


// Ό³Έν :
class BoneSocketCollision;
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

	inline std::shared_ptr<GameContentsFBXRenderer>& GetFBXRenderer() { return MainRenderer; }

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

	bool IsOnFlag(Enum_MonsterFlag _Flag) const;
	void SetFlag(Enum_MonsterFlag _Flag, bool _Value);
	void AddFlag(Enum_MonsterFlag _Flag);
	void SubFlag(Enum_MonsterFlag _Flag);

	void SetBoneIndex(Enum_BoneType _BoneType, int _BoneNum);
	int GetBoneIndex(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToIndex(Enum_BoneType _BoneType);

	template<typename MonsterType>
	std::shared_ptr<BoneSocketCollision> FindAndCreateSocketCollision(Enum_BoneType _Index, MonsterType _Type)
	{
		int SocketIndex = GetBoneIndex(_Index);
		if (auto FindIter = Collisions.find(SocketIndex); FindIter != Collisions.end())
		{
			return FindIter->second;
		}

		std::shared_ptr<BoneSocketCollision> NewCol = CreateComponent<BoneSocketCollision>(_Type);
		NewCol->SetSocket(&GetBoneMatrixToIndex(_Index));
		Collisions.insert(std::make_pair(SocketIndex, NewCol));
		return NewCol;
	}

	void AllUpdateSocketCollision();

	void EventLoad();

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::map<int, std::shared_ptr<BoneSocketCollision>> Collisions;

	GameEngineState MainState;

	int Flags = 0;

private:
	static std::map<Enum_BoneType, int> BoneIndex;
	static std::map<std::string, Enum_MonsterType> MonsterTypes;


};