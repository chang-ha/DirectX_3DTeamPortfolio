#pragma once
#include "BaseActor.h"

// Collision, BoneIndex
enum class Enum_BoneType
{
	None,
	B_01_LeftHand = 1,
	B_01_RightHand = 21,
	B_01_Spine = 31,
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

class BaseMonster : public BaseActor
{
protected:
	enum class Enum_TargetAngle
	{
		Front,
		Side,
		Back,
		None,
	};

	enum class Enum_TargetDist
	{
		Close,
		Melee,
		Medium,
		Long,
		None,
	};


public:
	// constrcuter destructer
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	// State
	// �ܺο��� ĳ���͸� ����� �������̽�
	// ���� ����
	virtual void WakeUp() {}
	void GravityOn();
	void GravityOff();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}


	// BoneIndex
	// BoneIndex�� EnumŸ������ ���� �����ϱ����� �����߽��ϴ�.
	// ������ ������� �ʴ´ٸ� �����ڽ��ϴ�. 
	// ������� ������ �ݴ븦 �������ּ���
	// ��ǥ : ����(), �ݴ�() << 2���� �ݴ��� ��� �ٷ� �����ڽ��ϴ�. 
	void AddBoneIndex(Enum_BoneType _BoneType, int _BoneNum);
	int GetBoneIndex(Enum_BoneType _BoneType);
	float4x4& GetBoneMatrixToType(Enum_BoneType _BoneType);

	// Socket Collision
	std::shared_ptr<BoneSocketCollision> CreateBoneCollision(Enum_CollisionOrder _Order, Enum_BoneType _Type, std::string_view ColName = "")
	{
		int SocketIndex = GetBoneIndex(_Type);
		return CreateSocketCollision(_Order, SocketIndex, {}, ColName);
	}

	std::shared_ptr<BoneSocketCollision> FindSocketCollision(Enum_BoneType _Type);
	void OnSocketCollisionInt(Enum_BoneType _Type);
	void OffSocketCollisionInt(Enum_BoneType _Type);

	// Mesh
	template<typename EnumType>
	void MeshOnOffSwitch(EnumType _MeshIndex)
	{
		MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0]->OnOffSwitch();
	}

	template<typename EnumType>
	void MeshOn(EnumType _MeshIndex)
	{
		MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0]->On();
	}

	template<typename EnumType>
	void MeshOff(EnumType _MeshIndex)
	{
		MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0]->Off();
	}

	template<typename EnumType>
	void SetMeshVisibility(EnumType _MeshIndex, bool bValue)
	{
		GameEngineRenderUnit* Unit = MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0].get();
		bValue ? Unit->On() : Unit->Off();
	}

	bool CheckAnimationName(std::string _AnimationName);


	// �ڽĿ��� �Լ� �������ؼ� ����� ��
	virtual Enum_TargetAngle GetTargetAngle_e() const
	{
		MsgBoxAssert("�����Ǹ� ���� �ʰ� ����� �� ���� �Լ��Դϴ�.");
		return Enum_TargetAngle::None;
	}

	// Ÿ�� ���� ����
	Enum_TargetAngle GetTargetAngle_e(float _fFrontAngle, float _fSideAngle) const
	{
		if (false == IsTargeting())
		{
			MsgBoxAssert("Ÿ���� �������� �ʴµ� ������ �������� �߽��ϴ�.");
			return Enum_TargetAngle::None;
		}

		const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

		bool RotValidation = (AbsTargetAngle >= 0.0f && AbsTargetAngle <= 180.0f);
		if (RotValidation)
		{
			bool bFrontAngle = AbsTargetAngle < _fFrontAngle;
			if (bFrontAngle)
			{
				return Enum_TargetAngle::Front;
			}

			bool bSideAngle = AbsTargetAngle < _fSideAngle;
			if (bSideAngle)
			{
				return Enum_TargetAngle::Side;
			}

			return Enum_TargetAngle::Back;
		}

		MsgBoxAssert("������ Ȯ�����ּ���.");
		return Enum_TargetAngle::None;
	}

	// �ڽĿ��� �Լ� �������ؼ� ����� ��
	virtual Enum_TargetDist GetTargetDistance_e() const
	{
		MsgBoxAssert("�����Ǹ� ���� �ʰ� ����� �� ���� �Լ��Դϴ�.");
		return Enum_TargetDist::None;
	}

	// �ڽĿ��� �Լ� �������ؼ� ����� ��
	virtual float ConvertDistance_eTof(Enum_TargetDist _eTDist) const;

	// Ÿ�� �Ÿ� ����
	Enum_TargetDist GetTargetDistance_e(float _fCloseRange, float _fmeleeRange, float _fMediumRange) const
	{
		if (false == IsTargeting())
		{
			MsgBoxAssert("Ÿ���� �������� �ʴµ� ������ �������� �߽��ϴ�.");
			return Enum_TargetDist::None;
		}

		const float AbsTargetDist = std::fabs(BaseActor::GetTargetDistance());

		bool bClose = AbsTargetDist < W_SCALE * _fCloseRange;
		if (bClose)
		{
			return Enum_TargetDist::Close;
		}

		bool bMelee = AbsTargetDist < W_SCALE * _fmeleeRange;
		if (bMelee)
		{
			return Enum_TargetDist::Melee;
		}

		bool bMedium = AbsTargetDist < W_SCALE * _fMediumRange;
		if (bMedium)
		{
			return Enum_TargetDist::Medium;
		}

		return Enum_TargetDist::Long;
	}
	
	// Ÿ���� Ư�� ������ ���������� true
	bool IsTargetInRange(Enum_TargetDist _eTDist);

	// Enum_TargetDist Ÿ���� �Ÿ� ��
	// _eCompareDist���� �ȿ� _eTDist �� ��������� ���� ��ȯ
	bool TargetRangeCmp(Enum_TargetDist _eTDist, Enum_TargetDist _eCompareDist) const;

	// 3D Sound �δ�
	void LoadRes3DSound(std::string_view _LoadCheck) const;

	// �浹 �� ��ȣ�ۿ� ó��
	bool GetHit(const HitParameter& _Para = HitParameter()) override;
	bool GetHitToShield(const HitParameter& _Para = HitParameter()) override;
	virtual int HitFormula(int _Att) { return _Att; }
	virtual int GuardHitFormula(int _Att) { return _Att; }

private:
	std::unordered_map<Enum_BoneType, int> BoneIndex;
	std::shared_ptr<class MonsterHpBar> MonsterUI;

};

