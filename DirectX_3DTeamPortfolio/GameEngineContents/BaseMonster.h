#pragma once
#include "BaseActor.h"

#include "ContentsDebug.h"

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
	virtual void WakeUp() {}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

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

	bool CheckAnimationName(std::string _AnimationName);


	// �ڽĿ��� �Լ� �������ؼ� ����� ��
	virtual Enum_TargetAngle GetTargetAngle_e() const
	{
		MsgBoxAssert("�����Ǹ� ���� �ʰ� ����� �� ���� �Լ��Դϴ�.");
		return Enum_TargetAngle::None;
	}

	// State
	Enum_TargetAngle GetTargetAngle_e(float _fFrontAngle, float _fSideAngle) const
	{
		if (false == IsTargeting())
		{
			MsgBoxAssert("Ÿ���� �������� �ʴµ� ������ �������� �߽��ϴ�.");
			return Enum_TargetAngle::None;
		}

		const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());

		bool RotValidation = (AbsTargetAngle >= 0.0f && AbsTargetAngle < 180.0f);
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
	
	bool IsTargetInRange(Enum_TargetDist _eTDist);

	void LoadRes3DSound(std::string_view _LoadCheck) const;

private:

};

