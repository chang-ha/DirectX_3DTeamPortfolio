#pragma once

static constexpr int EMPTY_ID = 9999;

enum class Enum_ActorType
{
	None,
	LothricKn = 1280,
	Boss_Vordt = 2240,
	Player = 0010
};

// 상태 Enum 
// 이론상 30개까지 bool값 지원
enum class Enum_ActorFlag
{
	None = 0,
	Wake,
	Death,
	Parrying,
	Guarding,
	Hit,
	GuardSuccess,
	Block_Shield,
	Guard_Break,
	Break_Posture,
	TwoHand,
	FrontStab,
	BackStab,
};

// 실제 상태 비트값
// 아직까진 FrameEvent가 없습니다. 필요하면 만들겠습니다.
// FrameEvent가 생성되면 함부로 순서를 변경해선 안됩니다. 
// 파일 바이너리가 이상해질 수 있어요.
enum class Enum_ActorFlagBit
{
	None = 0,
	Wake = (1 << 0),
	Death = (1 << 1),
	Parrying = (1 << 2),
	Guarding = (1 << 3),
	Hit = (1 << 10),
	Block_Shield = (1 << 12), // 방패에 막힘
	Gaurd_Break = (1 <<  13), // 가드 브레이크
	Break_Posture = (1 << 14), // 패링 당함  << 마땅한 명칭이 없음
	TwoHand = (1 << 15), 
	FrontStab = (1 << 16), // 앞잡
	BackStab = (1 << 17), // 뒤잡
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

class StatusStruct
{
public:
	inline void SetHp(int _Value) { Hp = _Value; }
	inline int GetHp() const { return Hp; }
	inline void AddHp(int _Value) { Hp += _Value; }
	inline bool IsDeath() const { return (Hp <= 0); }

	inline void SetAtt(int _Value) { Att = _Value; }
	inline int GetAtt() const { return Att; }

	inline void SetSouls(int _Value) { Souls = _Value; }
	inline int GetSouls() const { return Souls; }

	inline void SetPoise(int _Value) { Poise = _Value; }
	inline void AddPoise(int _Value) { Poise += _Value; }
	inline int GetPoise() const { return Poise; }

private:
	int Hp = 0; // 체력
	int Att = 0; // 공격력
	int Souls = 0; // 소울량
	int Poise = 0; // 강인도

};

// XZ평면 방향 정의
// 순서 : Z축으로 시계방향
enum class Enum_DirectionXZ_Quat
{
	F = 0, // float4::FORWARD
	R,
	B,
	L,
	Center, // None 취급
};

class HitParameter
{
public:
	HitParameter() {}
	~HitParameter() 
	{
		pAttacker = nullptr;
	}

	HitParameter(class BaseActor* _pAttacker, int _Stiffness = 0, Enum_DirectionXZ_Quat _eDir = Enum_DirectionXZ_Quat::Center)
		:pAttacker(_pAttacker), iStiffness(_Stiffness), eDir(_eDir)
	{

	}

public:
	class BaseActor* pAttacker = nullptr; // 공격상대
	Enum_DirectionXZ_Quat eDir = Enum_DirectionXZ_Quat::Center; // 맞는 DIR
	int iStiffness = 0; // 경직도

};

class HitStruct
{
public:
	inline void SetHitDir(Enum_DirectionXZ_Quat _eDir) { eHitDir = _eDir; }
	inline Enum_DirectionXZ_Quat GetHitDir() const { return eHitDir; }
	static Enum_DirectionXZ_Quat ReturnDirectionToVector(const float4& _V);

	inline bool IsHit() const { return bHit; }
	inline void SetHit(bool _bValue) { bHit = _bValue; }
	inline bool IsGuardSuccesss() const { return bGuardSuccesss; }
	inline void SetGuardSuccesss(bool _bValue) { bGuardSuccesss = _bValue; }
	inline bool IsInvincible() const { return bInvincible; }
	inline void SetInvincible(bool _bValue) { bInvincible = _bValue; }

private:
	Enum_DirectionXZ_Quat eHitDir = Enum_DirectionXZ_Quat::Center; // 임시 멤버변수입니다.
	bool bHit = false;
	bool bGuardSuccesss = false; // 가드 성공
	bool bInvincible = false; // 무적

};

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
	inline void SetID(Enum_ActorType _Type) { ActorID = static_cast<int>(_Type); }
	inline int GetID() const { return ActorID; }
	std::string GetIDName() const;

	// Transform Function
	void AddWDirection(float _Degree);
	void SetWDirection(float _Degree);
	float GetWDirection() const;
	void SetWPosition(const float4& _wPos);

	// Flag
	bool IsFlag(Enum_ActorFlag _Flag) const;
	void SetFlag(Enum_ActorFlag _Flag, bool _Value);
	void AddFlag(Enum_ActorFlag _Flag);
	void SubFlag(Enum_ActorFlag _Flag);
	void DebugFlag();

	// Getter
	inline std::shared_ptr<GameContentsFBXRenderer>& GetFBXRenderer() { return MainRenderer; }
	inline std::map<int, std::shared_ptr<BoneSocketCollision>>& GetCollisions() { return SocketCollisions; }
	std::shared_ptr<BoneSocketCollision> GetSocketCollision(int _Index);
	inline int* GetFlagPointer() { return &Flags; }
	inline class GameEnginePhysXCapsule* GetPhysxCapsulePointer() { return Capsule.get(); }
	inline int GetHp() const { return Stat.GetHp(); }
	inline int GetAtt() const { return Stat.GetAtt(); }
	inline int GetPoise() const { return Stat.GetPoise(); }

	// CollisionEvent
	virtual bool GetHit(const HitParameter& _Para = HitParameter()) { return false; }
	virtual bool GetHitToShield(const HitParameter& _Para = HitParameter()) { return false; }

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

	// BoneIndex
	void AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum);
	int GetBoneIndex(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToType(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToIndex(int _Index);

	// SocketCollision
	template<typename OrderType>
	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(OrderType _Order, Enum_BoneType _Type, std::string_view ColName = "")
	{
		int SocketIndex = GetBoneIndex(_Type);
		return CreateSocketCollision(static_cast<int>(_Order), SocketIndex, ColName);
	}

	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(int _Order, int _SocketIndex, std::string_view _ColName = "");

	std::shared_ptr<BoneSocketCollision> FindSocketCollision(Enum_BoneType _Type); 
	void OnSocketCollision(Enum_BoneType _Type);
	void OffSocketCollision(Enum_BoneType _Type);

	// Debug
	void DrawRange(float _Range, const float4& _Color = float4::RED) const;

	// 나중에 지움 
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
	void CameraRotation(float _Delta);

private:
	int FindFlag(Enum_ActorFlag _Status) const;

protected:
	static constexpr float W_SCALE = 100.0f; // 모두의 스케일

	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions; // 소켓 콜리전

	GameEngineState MainState;
	StatusStruct Stat; // 플레이어와 몬스터가 공용으로 사용하는 기본스텟 구조체
	HitStruct Hit; // 플레이어와 몬스터가 공용으로 사용하는 히트 로직 구조체

	
private:
	static std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> FlagIndex;
	std::unordered_map<Enum_BoneType, int> BoneIndex;

	int ActorID = EMPTY_ID;
	int Flags = 0;
	
// Targeting
public:
	inline void SetTargeting(GameEngineActor* _Target)
	{
		Target = _Target;
	}

	inline bool IsTargeting() const
	{
		return (nullptr != Target);
	}

	inline float GetTargetAngle() const
	{
		return TargetAngle;
	}

	inline Enum_RotDir GetRotDir_e() const
	{
		return RotDir;
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

