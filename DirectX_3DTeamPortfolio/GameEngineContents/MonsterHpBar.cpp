#include "PreCompile.h"
#include "MonsterHpBar.h"

#include "BaseMonster.h"

MonsterHpBar::MonsterHpBar()
{
	GameEngineInput::AddInputObject(this);
}

MonsterHpBar::~MonsterHpBar()
{
}

#define ImageXScale 100.0f
#define BackBarYScale 12.0f
#define HpBarYScale 6.0f
#define DamagePos {-100.0f, 190.0f}

void MonsterHpBar::Start()
{
	if (nullptr == GameEngineSprite::Find("MonsterBar.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("Monster");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}

	BackBarRenderer = CreateComponent<GameEngineSpriteRenderer>();
	BackBarRenderer->SetSprite("MonsterBar.Png");
	BackBarRenderer->SetImageScale({ ImageXScale, BackBarYScale });
	BackBarRenderer->SetPivotType(PivotType::Left);
	BackBarRenderer->SetBillboardOn();

	DamageBarRenderer = CreateComponent<GameEngineSpriteRenderer>();
	DamageBarRenderer->SetSprite("MonsterDamageBar.Png");
	DamageBarRenderer->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	DamageBarRenderer->SetPivotType(PivotType::Left);
	DamageBarRenderer->SetBillboardOn();

	HpBarRenderer = CreateComponent<GameEngineSpriteRenderer>();
	HpBarRenderer->SetSprite("MonsterHp.Png");
	//Monster_HpBar->SetImageScale({ (MonsterCurHp / MosnterHp) });
	HpBarRenderer->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	HpBarRenderer->SetPivotType(PivotType::Left);
	HpBarRenderer->SetBillboardOn();

	MonsterPrevHp = MonsterCurHp;

	{
		DamageFontRenderer = CreateComponent<GameEngineSpriteRenderer>();
		DamageFontRenderer->SetText(GlobalValue::OptimusFont, "0", 15.0f, float4{ 1,0,0,1 }, FW1_LEFT);
		DamageFontRenderer->Transform.SetLocalPosition(DamagePos);
		DamageFontRenderer->SetBillboardOn();
		DamageFontRenderer->Off();
	}

	/*BaseActor* pActor;
	pActor->GetHp();*/
}

void MonsterHpBar::InitUIPosition(BaseMonster* _pOwner, const float4* _pHeadBonePos)
{
	if (nullptr == _pHeadBonePos || nullptr == _pOwner)
	{
		MsgBoxAssert("존재하지 않는 값이 들어왔습니다.");
		return;
	}

	pOwner = _pOwner;
	BonePosPointer = _pHeadBonePos;
}

void MonsterHpBar::Update(float _Delta)
{
	PositionUpdate();

	MonsterBarUpdate();
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		DamRan.SetSeed(time(nullptr));
		DamageRandom = (DamRan.RandomInt(20, 50));

		Damage = DamageRandom;

		MonsterPrevHp = MonsterCurHp;
		MonsterCurHp -= Damage;
	}

	if (GameEngineInput::IsDown('6', this))
	{
		ChangeState(MonsterHpActor::Appear);
	}
}

void MonsterHpBar::PositionUpdate()
{
	if (nullptr == pOwner)
	{
		MsgBoxAssert("오너를 지정해주지 않았습니다");
		return;
	}

	const float Height = 200.0f;
	const float4 MonsterWPos = pOwner->Transform.GetWorldPosition();
	float4 UIWPos = MonsterWPos;
	UIWPos.Y += Height;

	Transform.SetWorldPosition(UIWPos);
}

void MonsterHpBar::MonsterBarUpdate()
{
	if (MonsterCurHp <= 0.0f)
	{
		DamageBarRenderer->Transform.SetLocalPosition({
		HpBarRenderer->Transform.GetLocalPosition().X, HpBarRenderer->Transform.GetLocalPosition().Y });
		HpBarRenderer->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (MonsterCurHp > 0.0f)
	{
		DamageBarRenderer->Transform.SetLocalPosition({
		HpBarRenderer->Transform.GetLocalPosition().X, HpBarRenderer->Transform.GetLocalPosition().Y });
		HpBarRenderer->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	}
}

void MonsterHpBar::ChangeState(MonsterHpActor _State)
{
	if (_State != MHpActor)
	{
		switch (_State)
		{
		case MonsterHpActor::Off:
			OffStart();
			break;
		case MonsterHpActor::Appear:
			AppearStart();
			break;
		case MonsterHpActor::Add:
			AddStart();
			break;
		case MonsterHpActor::None:
		default:
			MsgBoxAssert("없는 상태로 MonsterHpBar의 상태를 바꾸려 했습니다.");
			break;
		}
	}

	MHpActor = _State;
}

void MonsterHpBar::StateUpdate(float _Delta)
{
	switch (MHpActor)
	{
	case MonsterHpActor::Off:
		return OffUpdate(_Delta);
	case MonsterHpActor::Appear:
		return AppearUpdate(_Delta);
	case MonsterHpActor::Add:
		return AddUpdate(_Delta);
	case MonsterHpActor::None:
	default:
		break;
	}
}

void MonsterHpBar::OffStart()
{
	DamageFontRenderer->Off();
}
void MonsterHpBar::OffUpdate(float _Delta)
{
	if (MonsterCurHp <= 0.0f)
	{
		return;
	}

	if (MonsterCurHp == MonsterPrevHp)
	{
		return;
	}

	ChangeState(MonsterHpActor::Appear);
}
void MonsterHpBar::AppearStart()
{
	DamageFontRenderer->On();

	DamRan.SetSeed(time(nullptr));
	DamageRandom = (DamRan.RandomInt(20, 50));
	Damage = DamageRandom;

	MonsterCurHp -= Damage;
	MonsterPrevHp = MonsterCurHp;

	SumDam = Damage;
	Dam = true;
}
void MonsterHpBar::AppearUpdate(float _Delta)
{
	DamageFontRenderer->SetText(GlobalValue::OptimusFont, std::to_string(Damage), 15.0f, float4{1,0,0,1}, FW1_LEFT);

	if (Dam == true)
	{
		if (MonsterCurHp != MonsterPrevHp)
		{
			ChangeState(MonsterHpActor::Add);
			return;
		}

		CurTime += _Delta;
		{
			if (CurTime >= LimitTime)
			{
				DamageCal();
				Dam = false;
				CurTime = 0;
				ChangeState(MonsterHpActor::Off);
				return;
			}
		}
	}
}
void MonsterHpBar::AddStart()
{
	SumDam += Damage;

	MonsterCurHp -= Damage;
	MonsterPrevHp = MonsterCurHp;
}
void MonsterHpBar::AddUpdate(float _Delta)
{
	DamageFontRenderer->SetText(GlobalValue::OptimusFont, std::to_string(SumDam), 15.0f, float4{ 1,0,0,1 }, FW1_LEFT);
	CurTime += _Delta;
	{
		if (CurTime >= LimitTime)
		{
			SumDam = 0;
			DamageCal();
			Dam = false;
			CurTime = 0;
			ChangeState(MonsterHpActor::Off);
			return;
		}
	}
}

void MonsterHpBar::DamageCal()
{
	if (MonsterCurHp <= 0.0f)
	{
		DamageBarRenderer->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (MonsterCurHp > 0.0f)
	{
		DamageBarRenderer->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
	}
}

void MonsterHpBar::Release()
{
	pOwner = nullptr;
	BonePosPointer = nullptr;
	BackBarRenderer = nullptr;
	HpBarRenderer = nullptr;
	DamageBarRenderer = nullptr;
	DamageFontRenderer = nullptr;
}