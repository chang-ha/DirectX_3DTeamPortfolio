#pragma once
#include "DummyPolyCollision.h"

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
	HyperArmor,
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
	HyperArmor = (1 << 11),
	Block_Shield = (1 << 12), // 방패에 막힘
	Guard_Break = (1 <<  13), // 가드 브레이크
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

	inline bool IsHit() const { return bHit; }
	inline void SetHit(bool _bValue) { bHit = _bValue; }
	inline bool IsGuardSuccesss() const { return bGuardSuccesss; }
	inline void SetGuardSuccesss(bool _bValue) { bGuardSuccesss = _bValue; }
	inline bool IsInvincible() const { return bInvincible; }
	inline void SetInvincible(bool _bValue) { bInvincible = _bValue; }

private:
	Enum_DirectionXZ_Quat eHitDir = Enum_DirectionXZ_Quat::Center;
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
	// 나중에 다른 소스파일로 분리할 예정입니다.
	static std::string GetEventPath(int _ID);
	static bool LoadEvent(int _ID);

	// ID
	// 애니메이션 프레임 이벤트를 사용하려면 필수로 등록해줘야하는 자신의 고유 ID입니다.
	// 등록하지 않으면 Animation Editor 기능을 사용할 수 없습니다. 
	inline void SetID(Enum_ActorType _Type) { ActorID = static_cast<int>(_Type); }
	inline int GetID() const { return ActorID; }
	std::string GetIDName() const;

	// Transform Function
	// 피직스와 관련된 방향, 이동 함수입니다. 
	// BaseActor 내에서 사용은 거의 없겠지만, 외부에서 바꿔줄 상황이 생겨서 만들었습니다.
	void AddWDirection(float _Degree);
	void SetWDirection(float _Degree);
	float GetWDirection() const;
	void SetWPosition(const float4& _wPos);

	// Flag
	// 상대방의 행동을 지정해주려면 Flag 즉, 상대방의 State 변수를 바꿔주는 것이 효율적일 것 같아서 구현했습니다.
	// 상대방의 State에 관련된 Flag Bit를 바꿔 그 Flag에 맞는 상태를 구현하는게 직접 State를 변경하는 것보다 더 낫다고 생각합니다. 
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
	inline void SetHit(bool _Value) { Hit.SetHit(_Value); }
	inline int GetCenterDPIndex() const { return CenterBodyIndex; }

	// CollisionEvent 
	// 캐릭터간 충돌시 상대방의 수치를 바꿔주기위한 상호작용 인터페이스입니다.
	// 사용자는 GetHit만 사용해서 정의해주시면 되고, 방패히트와 분리하고 싶은 캐릭터분은
	// 따로 사용하셔도 무방합니다. 또는 이 인터페이스를 사용하지 않으셔도 됩니다.
	virtual bool GetHit(const HitParameter& _Para = HitParameter()) { return false; }
	virtual bool GetHitToShield(const HitParameter& _Para = HitParameter()) { return false; }

	// Stab 
	// 상대방의 앞뒤잡 판정을 정합니다.
	// 가상함수로 둔 이유는 캐릭터마다 앞뒤잡 판정이 다를 가능성이 높습니다.
	// 예시를 들자면 볼드와 할로우 나이트를 비교했을때 덩치 차이로 판정 다를 것입니다.
	// 그래서 앞뒤잡을 당하는 캐릭터가 판정이나 위치를 정할 수 있게 가삼함수로 둬야한다고 생각해서 넣었습니다. 
	virtual bool FrontStabCheck(const float4& _WPos, float _RotY) const {return false;} // 상대방의 앞잡 조건문
	virtual bool BackStabCheck(const float4& _WPos, float _RotY) const { return false; } // 상대방의 뒤잡 조건문
	virtual float4 GetBackStabPosition() { return float4::ZERO; } // 뒤잡 위치
	virtual float4 GetFrontStabPosition() { return float4::ZERO; } // 앞잡 위치

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

	float4x4& GetBoneMatrixToIndex(int _Index);

	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex, std::string _ColName = "");
	std::shared_ptr<class DummyPolyCollision> CreateDummyPolyCollision(Enum_CollisionOrder _Order, const SetDPMatrixParameter& _Para, std::string _ColName = "");

	void OnSocketCollision(int _BoneIndex);
	void OffSocketCollision(int _BoneIndex);

	// Debug
	void DrawRange(float _Range, const float4& _Color = float4::RED) const; // 캐릭터 내 범위를 확인하기위한 편의성 디버깅 기능입니다.

	
private:
	int FindFlag(Enum_ActorFlag _Status) const;

protected:
	static constexpr float W_SCALE = 100.0f; // 모두의 스케일

	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions; // 소켓 콜리전
	std::vector<std::string> FloorMaterialSoundRes; // 재질에 따른 발소리 리소스

	GameEngineState MainState;
	StatusStruct Stat; // 플레이어와 몬스터가 공용으로 사용하는 기본스텟 구조체
	HitStruct Hit; // 플레이어와 몬스터가 공용으로 사용하는 히트 로직 구조체

	int CenterBodyIndex = 0; // FrameEvent에서 사용할 DummyPoly Center Body를 등록해주세요
	int FloorMaterialIndex = 0; // 
	
private:
	static std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> FlagIndex; // 플레그를 매핑해놓은 구조체입니다. 에디터와 연계 가능합니다.

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

