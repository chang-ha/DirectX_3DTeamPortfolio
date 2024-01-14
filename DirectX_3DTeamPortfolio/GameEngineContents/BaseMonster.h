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


// 설명 :
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

	/// <summary>
	/// 본 소켓 행렬로 자동으로 콜리전 Model행렬 업데이트를 수행하는 콜리전
	/// map 컨테이너에 있다면 ReturnType이 반환되며, 없으면 만들어서 반환됩니다.
	/// </summary>
	/// <typeparam name="MonsterType">콜리전 오더 타입</typeparam>
	/// <param name="_Order">콜리전 오더</param>
	/// <param name="_Index">본 해시 값</param>
	/// <returns>Collision 공유 포인터</returns>
	/// <list>야</list>
	template<typename OrderType>
	std::shared_ptr<BoneSocketCollision> FindAndCreateSocketCollision(OrderType _Order, Enum_BoneType _Index)
	{
		return FindAndCreateSocketCollision(static_cast<int>(_Order), _Index);
	}

	std::shared_ptr<BoneSocketCollision> FindAndCreateSocketCollision(int _Order, Enum_BoneType _Index);

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