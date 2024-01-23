#pragma once

static constexpr int EMPTY_ID = 9999;

enum class Enum_MonsterType
{
	None,
	LothricKn = 1280,
};

// 상태 Enum 
// 최대 30개까지 bool값 지원
// 만든 목적은 에디터에서 몬스터의 Flag 수치를 변경하기 위해 만들었습니다.
enum class Enum_ActorStatus
{
	None = 0,
	HitValue,
	GaurdingValue,
	JumpPossible,
	ParryPossible,
	DeathValue,
};

// 실제 상태 비트값
enum class Enum_ActorFlag
{
	None = 0,
	HitValue = (1 << 0),
	GaurdingValue = (1 << 3),
	DeathValue = (1 << 4),
	JumpPossible = (1 << 29),
	ParryPossible = (1 << 30),
};

// Collision, BoneIndex
enum class Enum_BoneType
{
	None,
	B_01_LeftHand = 1,
	B_01_RightHand = 21,
};

namespace std
{
	template<>
	class hash<Enum_BoneType>
	{
	public:
		int operator()(Enum_BoneType _Type) const
		{
			return static_cast<int>(_Type);
		}
	};
}

namespace std
{
	template<>
	class hash<Enum_ActorStatus>
	{
	public:
		int operator()(Enum_ActorStatus _Type) const
		{
			return static_cast<int>(_Type);
		}
	};
}




// 설명 :
class BoneSocketCollision;
class BaseActor : public GameEngineActor
{
	friend class ContentsActorInitial;

public:
	// constrcuter destructer
	BaseActor();
	~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	// Path
	static std::string GetEventPath(int _ID);
	static bool LoadEvent(int _ID);

	// ID
	inline void SetID(Enum_MonsterType _Type) { ActorID = static_cast<int>(_Type); }
	inline int GetID() const { return ActorID; }


	void AddWDirection(float _Degree);
	void SetWDirection(float _Degree);
	float GetWDirection() const;

	// Getter
	inline std::shared_ptr<GameContentsFBXRenderer>& GetFBXRenderer() { return MainRenderer; }
	inline std::map<int, std::shared_ptr<BoneSocketCollision>>& GetCollisions() { return SocketCollisions; }
	std::shared_ptr<BoneSocketCollision> GetSocketCollision(int _Index);
	inline int* GetFlagPointer() { return &Flags; }

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


	// Flag
	bool GetFlag(Enum_ActorStatus _Flag) const;
	void SetFlag(Enum_ActorStatus _Flag, bool _Value);
	void AddFlag(Enum_ActorStatus _Flag);
	void SubFlag(Enum_ActorStatus _Flag);
	void DebugFlag();

	// BoneIndex
	void AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum);
	int GetBoneIndex(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToType(Enum_BoneType _BoneType);

	// SocketCollision
	template<typename OrderType>
	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(OrderType _Order, Enum_BoneType _Type, std::string ColName = "")
	{
		return CreateSocketCollision(static_cast<int>(_Order), _Type, ColName);
	}

	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(int _Order, Enum_BoneType _Type, std::string _ColName = "");

	std::shared_ptr<BoneSocketCollision> FindSocketCollision(Enum_BoneType _Type);

private:
	int FindFlag(Enum_ActorStatus _Status) const;

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;

	GameEngineState MainState;

	int Flags = 0;

private:
	static std::unordered_map<Enum_ActorStatus, Enum_ActorFlag> FlagIndex;
	std::unordered_map<Enum_BoneType, int> BoneIndex;

	int ActorID = EMPTY_ID;

};

