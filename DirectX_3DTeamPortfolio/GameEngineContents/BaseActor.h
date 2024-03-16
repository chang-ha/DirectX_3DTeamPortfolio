#pragma once
#include "DummyPolyCollision.h"
#include "BaseActor_Para.h"
#include "BaseActor_Struct.h"

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
	HyperArmor,
	Block_Shield,
	Guard_Break,
	Break_Posture,
	Groggy,
	FrontStab,
	BackStab,
	TwoHand,
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
	HyperArmor = (1 << 11),
	Block_Shield = (1 << 12), // 방패에 막힘
	Guard_Break = (1 <<  13), // 가드 브레이크
	Break_Posture = (1 << 14), // 패링 당함  << 마땅한 명칭이 없음
	Groggy = (1 << 15),
	FrontStab = (1 << 16), // 앞잡
	BackStab = (1 << 17), // 뒤잡
	TwoHand = (1 << 20), // 뒤잡
};

enum Enum_RotDir
{
	Not_Rot = 0,
	Left = -1,
	Right = 1,
};

enum Enum_Player_Hit
{
	weak,
	Middle,
	Strong,
};

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

	inline void SetStamina(float _Value) { Stamina = _Value; }
	inline void AddStamina(float _Value) { Stamina += _Value; }
	inline float GetStamina() const { return Stamina; }
	

private:
	int Hp = 0; // 체력
	int Att = 0; // 공격력
	int Souls = 0; // 소울량
	int Poise = 0; // 강인도
	float Stamina = 0.0f; // 지구력 
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
	bool bInvincible = false; // 무적s

};

enum class Enum_JumpTableFlag
{
	Default = 0,
	StopJumpTable = (1 << 0),
};

struct JumpTableInfo
{
	friend struct JumpTableManager;
	void SetJumpTableInfo(int _StartFrame, int _EndFrame, std::function<Enum_JumpTableFlag()> _JumpTable)
	{
		StartFrame = _StartFrame;
		EndFrame = _EndFrame;
		JumpTable = _JumpTable;
	}

	bool operator==(const JumpTableInfo& _Other) const
	{
		if (StartFrame != _Other.StartFrame)
		{
			return false;
		}

		if (EndFrame != _Other.EndFrame)
		{
			return false;
		}

		const void* _thisAddress = JumpTable.target<void*>();
		const void* _OtherAddress = _Other.JumpTable.target<void*>();

		if (_thisAddress != _OtherAddress)
		{
			return false;
		}

		return true;
	}

	bool operator!=(const JumpTableInfo& _Other) const
	{
		if (StartFrame == _Other.StartFrame)
		{
			return false;
		}

		if (EndFrame == _Other.EndFrame)
		{
			return false;
		}

		const void* _thisAddress = JumpTable.target<void*>();
		const void* _OtherAddress = _Other.JumpTable.target<void*>();

		if (_thisAddress == _OtherAddress)
		{
			return false;
		}

		return true;
	}

private:
	int StartFrame = -1;
	int EndFrame = -1;
	std::function<Enum_JumpTableFlag()> JumpTable;
};

struct JumpTableManager
{
	friend class BaseActor;

	void AddJumpTable(std::string_view _AnimationName, JumpTableInfo _JumpTableInfo);
	void AddJumpTable(std::string_view _AnimationName, int _StartFrame, int _EndFrame, std::function<Enum_JumpTableFlag()> _JumpTable);
	void ClearJumpTable()
	{
		IsClearJumpTable = true;
	}

private:
	class BaseActor* Owner = nullptr;
	bool IsClearJumpTable = false;
	std::list<JumpTableInfo> RunJumpTable;

	void Update();
	void Release();

	void PushJumpTable(JumpTableInfo _JumpTableInfo);
	void PopJumpTable(JumpTableInfo _JumpTableInfo);
};

// 설명 :
class BoneSocketCollision;
class BaseActor : public GameEngineActor
{
	friend class ContentsActorInitial;
	friend struct JumpTableManager;

public:
	// constrcuter destructer
	BaseActor();
	virtual ~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	void On() override
	{
		GameEngineActor::On();
		Capsule->On();
	}

	void Off() override
	{ 
		GameEngineActor::Off();
		Capsule->Off();
	}

	void OnOffSwitch() override
	{
		GameEngineActor::OnOffSwitch();
		IsUpdate() ? Capsule->On() : Capsule->Off();
	}

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

	void SetWorldPosition(const float4& _Pos);
	void SetWorldRotation(const float4& _Rot);

	// 로직 리셋
	virtual void Reset() {} 

	// Flag
	// 상대방의 행동을 지정해주려면 Flag 즉, 상대방의 State 변수를 바꿔주는 것이 효율적일 것 같아서 구현했습니다.
	// 상대방의 State에 관련된 Flag Bit를 바꿔 그 Flag에 맞는 상태를 구현하는게 직접 State를 변경하는 것보다 더 낫다고 생각합니다. 
	bool IsFlag(Enum_ActorFlag _Flag) const;
	void SetFlag(Enum_ActorFlag _Flag, bool _Value);
	void AddFlag(Enum_ActorFlag _Flag);
	void SubFlag(Enum_ActorFlag _Flag);
	void SetFlagNull() { Flags = 0; }
	void DebugFlag() const;

	// Getter
	inline std::shared_ptr<GameContentsFBXRenderer>& GetFBXRenderer() { return MainRenderer; }
	inline std::map<int, std::shared_ptr<BoneSocketCollision>>& GetCollisions() { return SocketCollisions; }
	int GetSocketIndex(const std::shared_ptr<class BoneSocketCollision>& _pCol);
	std::shared_ptr<BoneSocketCollision> GetSocketCollision(int _Index);
	inline int* GetFlagPointer() { return &Flags; }
	inline class GameEnginePhysXCapsule* GetPhysxCapsulePointer() { return Capsule.get(); }
	inline int GetHp() const { return Stat.GetHp(); }
	inline int GetAtt() const { return Stat.GetAtt(); }
	inline void Damage(int _Damage) { Stat.AddHp(-_Damage); }
	inline int GetPoise() const { return Stat.GetPoise(); }
	inline void SetHit(bool _Value) { Hit.SetHit(_Value); }
	inline int GetCenterDPIndex() const { return CenterBodyIndex; }
	std::string_view GetMaterialSoundName(int _Index) { return MaterialSound.GetSound(_Index); }
	std::vector<int> GetMaterialSoundKeys() { return MaterialSound.GetKeys(); }
	bool IsContainMaterialType(int _Key) { return MaterialSound.IsKeyContain(_Key); }


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

	void SetPause(bool _SwitchValue) { _SwitchValue ? MainRenderer->SetPause(true) : MainRenderer->SetPause(false); }

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

	float4x4& GetBoneMatrixToIndex(int _Index);

	template<typename EnumType>
	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, EnumType _eIndex,
		BSCol_TransitionParameter _Para = BSCol_TransitionParameter(), std::string_view _ColName = "")
	{
		return CreateSocketCollision(_Order, static_cast<int>(_eIndex), _Para, _ColName);
	}
	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex,
		BSCol_TransitionParameter _Para = BSCol_TransitionParameter(), std::string_view _ColName = "");

	std::shared_ptr<class DummyPolyCollision> CreateDummyPolyCollision(Enum_CollisionOrder _Order, const SetDPMatrixParameter& _Para, std::string _ColName = "");

	void OnAllCollision();
	void OffAllCollision();
	void OnSocketCollision(int _BoneIndex);
	void OffSocketCollision(int _BoneIndex);

	void SetCenterBodyDPIndex(int _DPIndex);

	// Floor Foot Sound Initial
	// 인자로 사운드 이름을 넣어주되 같은 타입의 재질 사운드를 넣어주세요
	//  예시) c128005501.wav, c128005501b.wav, c128005501c.wav, c128005501d.wav << 이런 형식이라면
	//	가장 낮은 이름인 "c218005501.wav" 을 인자로 넣어주세요.
	template<typename EnumType>
	void PushMaterialSound(EnumType _Key, std::string_view _SoundFileName)
	{
		PushMaterialSound(static_cast<int>(_Key), _SoundFileName);
	}
	void PushMaterialSound(int _Key, std::string_view _SoundFileName);

	// Debug
	void DrawRange(float _Range, const float4& _Color = float4::RED) const; // 캐릭터 내 범위를 확인하기위한 편의성 디버깅 기능입니다.

	
private:
	int FindFlag(Enum_ActorFlag _Status) const;

protected:
	static constexpr float W_SCALE = 100.0f; // 모두의 스케일
	static constexpr int MAX_POISE = 100; // 강직도 세팅

	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions; // 소켓 콜리전

	GameEngineState MainState;
	StatusStruct Stat; // 플레이어와 몬스터가 공용으로 사용하는 기본스텟 구조체
	HitStruct Hit; // 플레이어와 몬스터가 공용으로 사용하는 히트 로직 구조체

	int CenterBodyIndex = -1; // FrameEvent에서 사용할 DummyPoly Center Body를 등록해주세요
	
	float Reduce_Stamina = 0;

private:
	static std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> FlagIndex; // 플레그를 매핑해놓은 구조체입니다. 에디터와 연계 가능합니다.
	MaterialSoundStruct MaterialSound;

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
	inline Enum_Player_Hit Get_Hit_Type() const
	{
		return Hit_Type;
	}

	
	float4 GetTargetPos()
	{
		if (nullptr == Target)
		{
			MsgBoxAssert("타겟이 존재하지 않습니다.");
		}

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
	void RotToTarget(float _DeltaTime, float _fMinSpeed, float _fMaxSpeed, float DeclinePoint = 45.0f);

private:
	float TargetAngle = 0.f;
	GameEngineActor* Target = nullptr;

	
	float RotSpeed = 0.f;
	const float RotMinAngle = 5.f;
	Enum_RotDir RotDir = Enum_RotDir::Not_Rot;

	
	void CalcuTargetAngle();

protected:
	JumpTableManager mJumpTableManager;
	Enum_Player_Hit Hit_Type = Enum_Player_Hit::weak;
};

