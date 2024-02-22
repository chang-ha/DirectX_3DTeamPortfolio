#pragma once

static constexpr int EMPTY_ID = 9999;

enum class Enum_ActorType
{
	None,
	LothricKn = 1280,
	Boss_Vordt = 2240,
	Player = 0010
};

// ���� Enum 
// �̷л� 31������ bool�� ����
enum class Enum_ActorFlag
{
	None = 0,
	Wake,
	Death,
	ParryPossible,
	JumpPossible,
	Hit,
	GaurdSuccess,
	Block_Shield,
	Gaurd_Break,
	Break_Down,
	FrontStab,
	BackStab,
};

// ���� ���� ��Ʈ��
// �������� FrameEvent�� �����ϴ�. �ʿ��ϸ� ����ڽ��ϴ�.
// FrameEvent�� �����Ǹ� �Ժη� ������ �����ؼ� �ȵ˴ϴ�. 
// ���� ���̳ʸ��� �̻����� �� �־��.
enum class Enum_ActorFlagBit
{
	None = 0,
	Wake = (1 << 0),
	Death = (1 << 1),
	ParryPossible = (1 << 2),
	JumpPossible = (1 << 3),
	Hit = (1 << 10),
	GaurdSuccess = (1 << 11), // ���� ����
	Block_Shield = (1 << 12), // ���п� ����
	Gaurd_Break = (1 <<  13), // ���� �극��ũ
	Break_Down = (1 << 14), // �и� ����  << ������ ��Ī�� ����
	FrontStab = (1 << 15), // ����
	BackStab = (1 << 16), // ����
};

// Collision, BoneIndex
enum class Enum_BoneType
{
	None,
	B_01_LeftHand = 1,
	B_01_RightHand = 21,
	B_01_Spine = 31,
};

enum Enum_RotDir
{
	Not_Rot = 0,
	Left = -1,
	Right = 1,
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
	class hash<Enum_ActorFlag>
	{
	public:
		int operator()(Enum_ActorFlag _Type) const
		{
			return static_cast<int>(_Type);
		}
	};
}

class ActorStatus
{
	friend class BaseActor;

public:
	inline void SetHp(int _Value) { Hp = _Value; }
	inline int GetHp() const { return Hp; }
	inline void AddHp(int _Value) { Hp += _Value; }

	inline void SetAtt(int _Value) { Att = _Value; }
	inline int GetAtt() const { return Att; }

	inline void SetDef(int _Value) { Def = _Value; }
	inline int GetDef() const { return Def; }

private:
	int Hp = 0;
	int Att = 0;
	int Def = 0;

};

// XZ��� ���� ����
// ���� : Z������ �ð����
enum class Enum_DirectionXZ_Quat
{
	F = 0, // float4::FORWARD
	R,
	B,
	L,
	Center, // None ���
};

class HitParameter
{
public:
	HitParameter() {}
	~HitParameter() 
	{
		pHitter = nullptr;
	}

	HitParameter(GameEngineActor* _pHitter, Enum_DirectionXZ_Quat _eDir)
		:pHitter(_pHitter), eDir(_eDir)
	{

	}

public:
	GameEngineActor* pHitter = nullptr;
	Enum_DirectionXZ_Quat eDir = Enum_DirectionXZ_Quat::Center;

};

class HitStruct
{
public:
	inline void SetHitDir(Enum_DirectionXZ_Quat _eDir) { eHitDir = _eDir; }
	inline Enum_DirectionXZ_Quat GetHitDir() const { return eHitDir; }
	static Enum_DirectionXZ_Quat ReturnDirectionToVector(const float4& _V);

	inline bool IsHit() const { return bHit; }
	inline void SetHit(bool _bValue) { bHit = _bValue; }

private:
	Enum_DirectionXZ_Quat eHitDir = Enum_DirectionXZ_Quat::Center; // �ӽ� ��������Դϴ�.
	bool bHit = false;

};

// ���� :
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
	inline void SetID(Enum_ActorType _Type) { ActorID = static_cast<int>(_Type); }
	inline int GetID() const { return ActorID; }
	std::string GetIDName() const;

	void AddWDirection(float _Degree);
	void SetWDirection(float _Degree);
	float GetWDirection() const;
	void SetWPosition(const float4& _wPos);

	// Interaction To Character
	void GetHit(int _AddHp, HitParameter _Para = HitParameter());    // �������°� ��� �ƹ����Գ� �� �۸��߽��ϴ�. �Լ��� �ٲټŵ� �˴ϴ�

	// Getter
	inline std::shared_ptr<GameContentsFBXRenderer>& GetFBXRenderer() { return MainRenderer; }
	inline std::map<int, std::shared_ptr<BoneSocketCollision>>& GetCollisions() { return SocketCollisions; }
	std::shared_ptr<BoneSocketCollision> GetSocketCollision(int _Index);
	inline int* GetFlagPointer() { return &Flags; }
	inline class GameEnginePhysXCapsule* GetPhysxCapsulePointer() { return Capsule.get(); }
	inline int GetHp() const { return Stat.GetHp(); }

	// Debug
	inline int GetCurStateInt() const
	{
		int StateNum = MainState.GetCurState();
		return StateNum;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	
	// Flag
	bool IsFlag(Enum_ActorFlag _Flag) const;
	void SetFlag(Enum_ActorFlag _Flag, bool _Value);
	void AddFlag(Enum_ActorFlag _Flag);
	void SubFlag(Enum_ActorFlag _Flag);
	void DebugFlag();

	// BoneIndex
	void AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum);
	int GetBoneIndex(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToType(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToIndex(int _Index);

	// SocketCollision
	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, Enum_BoneType _Type, std::string ColName = "")
	{
		int SocketIndex = GetBoneIndex(_Type);
		return CreateSocketCollision(_Order, SocketIndex, ColName);
	}

	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex, std::string _ColName = "");

	std::shared_ptr<BoneSocketCollision> FindSocketCollision(Enum_BoneType _Type); 

	// Debug
	void DrawRange(float _Range, const float4& _Color = float4::RED) const;

	// ���߿� ���� 
	
	std::shared_ptr<GameEngineActor> Actor_test;
	std::shared_ptr<GameEngineActor> Actor_test_02;
	std::shared_ptr<GameContentsFBXRenderer> test_Render;
	float4 CameraPos = {};
	float Mouse_Ro_X = 0.0f;
	float Mouse_Ro_Y = 0.0f;
	float4 PrevPos = {};
	float Camera_Pos_Y = 0.0f;
	float Camera_Pos_X = 0.0f;
	float Time = 0.0f;

private:
	int FindFlag(Enum_ActorFlag _Status) const;

protected:
	static constexpr float W_SCALE = 100.0f; // ����� ������

	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions; // ���� �ݸ���

	GameEngineState MainState;
	ActorStatus Stat; // �÷��̾�� ���Ͱ� �������� ����ϴ� �⺻���� ����ü
	HitStruct Hit; // �÷��̾�� ���Ͱ� �������� ����ϴ� ��Ʈ ���� ����ü

	int Flags = 0;
	
private:
	static std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> FlagIndex;
	std::unordered_map<Enum_BoneType, int> BoneIndex;

	int ActorID = EMPTY_ID;
	
// Targeting
public:
	inline void SetTargeting(GameEngineActor* _Target)
	{
		Target = _Target;
	}

	inline bool IsTargeting() const
	{
		if (nullptr != Target)
		{
			return true;
		}

		return false;
	}

	inline float GetTargetAngle() const
	{
		return TargetAngle;
	}

	inline Enum_RotDir GetRotDir_e() const
	{
		return RotDir;
	}
	
	float4 GetTargetPos()
	{
		return Target->Transform.GetWorldPosition();
	}
	float GetRotDir_f()
	{
		return static_cast<float>(RotDir);
	}

	inline void SetRotSpeed(float _RotSpeed)
	{
		RotSpeed = _RotSpeed;
	}

	inline float GetRotSpeed()
	{
		return RotSpeed;
	}

	inline GameEngineActor* GetTargetPointer()
	{
		return Target;
	}

	inline float GetRotMinAngle()
	{
		return RotMinAngle;
	}

	float GetTargetDistance() const;
	float4 GetTargetDirection() const;

private:
	float TargetAngle = 0.f;
	GameEngineActor* Target = nullptr;

	
	float RotSpeed = 0.f;
	const float RotMinAngle = 5.f;
	Enum_RotDir RotDir = Enum_RotDir::Not_Rot;

	void CalcuTargetAngle();

};

