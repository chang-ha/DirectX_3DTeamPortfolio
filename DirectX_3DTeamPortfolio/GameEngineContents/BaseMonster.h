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
	// 외부에서 캐릭터를 깨우는 인터페이스
	// 상태 정의
	virtual void WakeUp() {}
	void GravityOn();
	void GravityOff();

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

	template<typename EnumType>
	void SetMeshVisibility(EnumType _MeshIndex, bool bValue)
	{
		GameEngineRenderUnit* Unit = MainRenderer->GetRenderUnits().at(static_cast<int>(_MeshIndex))[0].get();
		bValue ? Unit->On() : Unit->Off();
	}

	bool CheckAnimationName(std::string _AnimationName);


	// 자식에서 함수 재정의해서 사용할 것
	virtual Enum_TargetAngle GetTargetAngle_e() const
	{
		MsgBoxAssert("재정의를 하지 않고 사용할 수 없는 함수입니다.");
		return Enum_TargetAngle::None;
	}

	// 타겟 범윈 정의
	Enum_TargetAngle GetTargetAngle_e(float _fFrontAngle, float _fSideAngle) const
	{
		if (false == IsTargeting())
		{
			MsgBoxAssert("타겟이 존재하지 않는데 변수를 가져오려 했습니다.");
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

		MsgBoxAssert("각도를 확인해주세요.");
		return Enum_TargetAngle::None;
	}

	// 자식에서 함수 재정의해서 사용할 것
	virtual Enum_TargetDist GetTargetDistance_e() const
	{
		MsgBoxAssert("재정의를 하지 않고 사용할 수 없는 함수입니다.");
		return Enum_TargetDist::None;
	}

	// 자식에서 함수 재정의해서 사용할 것
	virtual float ConvertDistance_eTof(Enum_TargetDist _eTDist) const;

	// 타겟 거리 정의
	Enum_TargetDist GetTargetDistance_e(float _fCloseRange, float _fmeleeRange, float _fMediumRange) const
	{
		if (false == IsTargeting())
		{
			MsgBoxAssert("타겟이 존재하지 않는데 변수를 가져오려 했습니다.");
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
	
	// 타겟이 특정 범위에 들어와있으면 true
	bool IsTargetInRange(Enum_TargetDist _eTDist);

	// Enum_TargetDist 타입의 거리 비교
	// _eCompareDist범위 안에 _eTDist 가 들어있으면 참을 반환
	bool TargetRangeCmp(Enum_TargetDist _eTDist, Enum_TargetDist _eCompareDist) const;

	// 3D Sound 로더
	void LoadRes3DSound(std::string_view _LoadCheck) const;

	// 충돌 후 상호작용 처리
	bool GetHit(const HitParameter& _Para = HitParameter()) override;
	bool GetHitToShield(const HitParameter& _Para = HitParameter()) override;
	virtual int HitFormula(int _Att) { return _Att; }
	virtual int GuardHitFormula(int _Att) { return _Att; }

private:
	

};

