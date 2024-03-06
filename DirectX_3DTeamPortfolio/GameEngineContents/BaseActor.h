#pragma once
#include "DummyPolyCollision.h"
#include "BaseActor_Para.h"

static constexpr int EMPTY_ID = 9999;

enum class Enum_ActorType
{
	None,
	LothricKn = 1280,
	Boss_Vordt = 2240,
	Player = 0010
};

// ���� Enum 
// �̷л� 30������ bool�� ����
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

// ���� ���� ��Ʈ��
// �������� FrameEvent�� �����ϴ�. �ʿ��ϸ� ����ڽ��ϴ�.
// FrameEvent�� �����Ǹ� �Ժη� ������ �����ؼ� �ȵ˴ϴ�. 
// ���� ���̳ʸ��� �̻����� �� �־��.
enum class Enum_ActorFlagBit
{
	None = 0,
	Wake = (1 << 0),
	Death = (1 << 1),
	Parrying = (1 << 2),
	Guarding = (1 << 3),
	Hit = (1 << 10),
	HyperArmor = (1 << 11),
	Block_Shield = (1 << 12), // ���п� ����
	Guard_Break = (1 <<  13), // ���� �극��ũ
	Break_Posture = (1 << 14), // �и� ����  << ������ ��Ī�� ����
	TwoHand = (1 << 15), 
	FrontStab = (1 << 16), // ����
	BackStab = (1 << 17), // ����
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
	int Hp = 0; // ü��
	int Att = 0; // ���ݷ�
	int Souls = 0; // �ҿ﷮
	int Poise = 0; // ���ε�

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
	bool bGuardSuccesss = false; // ���� ����
	bool bInvincible = false; // ����

};

// ���� :
class BoneSocketCollision;
class BaseActor : public GameEngineActor
{
	friend class ContentsActorInitial;

public:
	// constrcuter destructer
	BaseActor();
	virtual ~BaseActor();

	// delete Function
	BaseActor(const BaseActor& _Other) = delete;
	BaseActor(BaseActor&& _Other) noexcept = delete;
	BaseActor& operator=(const BaseActor& _Other) = delete;
	BaseActor& operator=(BaseActor&& _Other) noexcept = delete;

	// ID
	// �ִϸ��̼� ������ �̺�Ʈ�� ����Ϸ��� �ʼ��� ���������ϴ� �ڽ��� ���� ID�Դϴ�.
	// ������� ������ Animation Editor ����� ����� �� �����ϴ�. 
	inline void SetID(Enum_ActorType _Type) { ActorID = static_cast<int>(_Type); }
	inline int GetID() const { return ActorID; }
	std::string GetIDName() const;

	// Transform Function
	// �������� ���õ� ����, �̵� �Լ��Դϴ�. 
	// BaseActor ������ ����� ���� ��������, �ܺο��� �ٲ��� ��Ȳ�� ���ܼ� ��������ϴ�.
	void AddWDirection(float _Degree);
	void SetWDirection(float _Degree);
	float GetWDirection() const;
	void SetWPosition(const float4& _wPos);

	// Flag
	// ������ �ൿ�� �������ַ��� Flag ��, ������ State ������ �ٲ��ִ� ���� ȿ������ �� ���Ƽ� �����߽��ϴ�.
	// ������ State�� ���õ� Flag Bit�� �ٲ� �� Flag�� �´� ���¸� �����ϴ°� ���� State�� �����ϴ� �ͺ��� �� ���ٰ� �����մϴ�. 
	bool IsFlag(Enum_ActorFlag _Flag) const;
	void SetFlag(Enum_ActorFlag _Flag, bool _Value);
	void AddFlag(Enum_ActorFlag _Flag);
	void SubFlag(Enum_ActorFlag _Flag);
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
	inline int GetPoise() const { return Stat.GetPoise(); }
	inline void SetHit(bool _Value) { Hit.SetHit(_Value); }
	inline int GetCenterDPIndex() const { return CenterBodyIndex; }

	// CollisionEvent 
	// ĳ���Ͱ� �浹�� ������ ��ġ�� �ٲ��ֱ����� ��ȣ�ۿ� �������̽��Դϴ�.
	// ����ڴ� GetHit�� ����ؼ� �������ֽø� �ǰ�, ������Ʈ�� �и��ϰ� ���� ĳ���ͺ���
	// ���� ����ϼŵ� �����մϴ�. �Ǵ� �� �������̽��� ������� �����ŵ� �˴ϴ�.
	virtual bool GetHit(const HitParameter& _Para = HitParameter()) { return false; }
	virtual bool GetHitToShield(const HitParameter& _Para = HitParameter()) { return false; }

	// Stab 
	// ������ �յ��� ������ ���մϴ�.
	// �����Լ��� �� ������ ĳ���͸��� �յ��� ������ �ٸ� ���ɼ��� �����ϴ�.
	// ���ø� ���ڸ� ����� �ҷο� ����Ʈ�� �������� ��ġ ���̷� ���� �ٸ� ���Դϴ�.
	// �׷��� �յ����� ���ϴ� ĳ���Ͱ� �����̳� ��ġ�� ���� �� �ְ� �����Լ��� �־��Ѵٰ� �����ؼ� �־����ϴ�. 
	virtual bool FrontStabCheck(const float4& _WPos, float _RotY) const {return false;} // ������ ���� ���ǹ�
	virtual bool BackStabCheck(const float4& _WPos, float _RotY) const { return false; } // ������ ���� ���ǹ�
	virtual float4 GetBackStabPosition() { return float4::ZERO; } // ���� ��ġ
	virtual float4 GetFrontStabPosition() { return float4::ZERO; } // ���� ��ġ

	// Floor Foot Sound
	std::string_view GetFloorMaterialName();

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

	std::shared_ptr<BoneSocketCollision> CreateSocketCollision(Enum_CollisionOrder _Order, int _SocketIndex,
		BSCol_TransitionParameter _Para = BSCol_TransitionParameter(), std::string_view _ColName = "");
	std::shared_ptr<class DummyPolyCollision> CreateDummyPolyCollision(Enum_CollisionOrder _Order, const SetDPMatrixParameter& _Para, std::string _ColName = "");

	void OnSocketCollision(int _BoneIndex);
	void OffSocketCollision(int _BoneIndex);

	void SetCenterBodyDPIndex(int _DPIndex);

	// Floor Foot Sound Initial
	// ���ڷ� ���� �̸��� �־��ֵ� ���� Ÿ���� ���� ���带 �־��ּ���
	//  ����) c128005501.wav, c128005501b.wav, c128005501c.wav, c128005501d.wav << �̷� �����̶��
	//	���� ���� �̸��� "c218005501.wav" �� ���ڷ� �־��ּ���.
	void SetFloorMaterialSoundRes(std::string_view _ResName); 

	// Debug
	void DrawRange(float _Range, const float4& _Color = float4::RED) const; // ĳ���� �� ������ Ȯ���ϱ����� ���Ǽ� ����� ����Դϴ�.

	
private:
	int FindFlag(Enum_ActorFlag _Status) const;

protected:
	static constexpr float W_SCALE = 100.0f; // ����� ������

	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::map<int, std::shared_ptr<BoneSocketCollision>> SocketCollisions; // ���� �ݸ���

	GameEngineState MainState;
	StatusStruct Stat; // �÷��̾�� ���Ͱ� �������� ����ϴ� �⺻���� ����ü
	HitStruct Hit; // �÷��̾�� ���Ͱ� �������� ����ϴ� ��Ʈ ���� ����ü

	int CenterBodyIndex = -1; // FrameEvent���� ����� DummyPoly Center Body�� ������ּ���
	
private:
	static std::unordered_map<Enum_ActorFlag, Enum_ActorFlagBit> FlagIndex; // �÷��׸� �����س��� ����ü�Դϴ�. �����Ϳ� ���� �����մϴ�.
	std::vector<std::string> FloorMaterialSoundRes; // ������ ���� �߼Ҹ� ���ҽ�

	int ActorID = EMPTY_ID;
	int Flags = 0;

	int FloorMaterialIndex = 0; // �߼Ҹ� ���� �ε���
	
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

