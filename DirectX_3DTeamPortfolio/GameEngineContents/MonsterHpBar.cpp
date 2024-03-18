#include "PreCompile.h"
#include "MonsterHpBar.h"

#include "GaugeRenderer.h"

#include "BaseMonster.h"

// #define BAR_DEBUG
#ifdef BAR_DEBUG
#define DEBUGON true
#else
#define DEBUGON false
#endif



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

	BackBarRenderer = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI_BackBar);
	BackBarRenderer->SetSprite("MonsterBar.Png");
	BackBarRenderer->GetImageTransform().SetLocalScale({ ImageXScale, BackBarYScale });
	BackBarRenderer->SetBillboardOn();

	BackBarScale = ImageXScale;

	DamageBarRenderer = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI_BackGauge);
	DamageBarRenderer->SetSprite("MonsterDamageBar.Png");
	DamageBarRenderer->GetImageTransform().SetLocalScale({ ImageXScale, HpBarYScale });
	DamageBarRenderer->SetBillboardOn();

	HpBarRenderer = CreateComponent<GameEngineSpriteRenderer>(Enum_RenderOrder::UI_StatGauge);
	HpBarRenderer->SetSprite("MonsterHp.Png");
	HpBarRenderer->GetImageTransform().SetLocalScale({ ImageXScale, HpBarYScale });
	HpBarRenderer->SetBillboardOn();

	InitState();
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
	RenderHp = MaxHp = _pOwner->GetHp();

	if (bool Debug = DEBUGON)
	{
		MainState.ChangeState(eState::Awake);
	}
	else
	{
		MainState.ChangeState(eState::Off);
	}
}

void MonsterHpBar::Update(float _Delta)
{
	MainState.Update(_Delta);
	if (true == RenderValue)
	{
		PositionUpdate();
	}
}

void MonsterHpBar::PositionUpdate()
{
	if (nullptr == pOwner)
	{
		MsgBoxAssert("오너를 지정해주지 않았습니다");
		return;
	}

	const float4x4& ActorWMatrix = pOwner->GetFBXRenderer()->Transform.GetWorldMatrix();
	float4 BoneLocalPos = (*BonePosPointer);
	BoneLocalPos.W = 1.0f;
	const float4 BoneWPos = BoneLocalPos *ActorWMatrix;
	const float4 UIWPos = BoneWPos + float4(0.0f, HeightDist);

	Transform.SetWorldPosition(UIWPos);
}

void MonsterHpBar::Release()
{
	pOwner = nullptr;
	BonePosPointer = nullptr;
	BackBarRenderer = nullptr;
	HpBarRenderer = nullptr;
	DamageBarRenderer = nullptr;
}

void MonsterHpBar::InitState()
{
	// Bar State
	CreateStateParameter AwakeState;
	AwakeState.Start = std::bind(&MonsterHpBar::Start_Awake, this, std::placeholders::_1);

	CreateStateParameter IdleState;
	IdleState.Stay = std::bind(&MonsterHpBar::Update_Idle, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter OffState;
	OffState.Start = std::bind(&MonsterHpBar::Start_Off, this, std::placeholders::_1);
	OffState.Stay = std::bind(&MonsterHpBar::Update_Off, this, std::placeholders::_1, std::placeholders::_2);

	MainState.CreateState(eState::Awake, AwakeState);
	MainState.CreateState(eState::Idle, IdleState);
	MainState.CreateState(eState::Off, OffState);
}

static constexpr float MAX_OFF_TIME = 8.0f;
static constexpr float MAX_DAMAGE_RENDER_TIME = 0.8f;

// State_Start
void MonsterHpBar::Start_Awake(GameEngineState* _Parent)
{
	RendererOn();

	OffTime = MAX_OFF_TIME;
	DamageRenderTime = MAX_DAMAGE_RENDER_TIME;

	SetHPGauge();

	_Parent->ChangeState(eState::Idle);
}


void MonsterHpBar::Start_Off(GameEngineState* _Parent)
{
	RendererOff();

	DamgeRenderHp = RenderHp;
	SetDamageGauge();
}

// State Update
void MonsterHpBar::Update_Idle(float _Delta, GameEngineState* _Parent)
{
	const int CurHp = pOwner->GetHp();
	if (CurHp != RenderHp)
	{
		DamgeRenderHp = RenderHp;
		RenderHp = CurHp;

		OffTime = MAX_OFF_TIME;
		DamageRenderTime = MAX_DAMAGE_RENDER_TIME;

		SetHPGauge();
		SetDamageGauge();
	}

	OffTime -= _Delta;
	if (OffTime <= 0.0f)
	{
		if (!DEBUGON)
		{
			_Parent->ChangeState(eState::Off);
			return;
		}
	}

	DamageRenderTime -= _Delta;
	if (DamageRenderTime <= 0.0f)
	{
		DamgeRenderHp = RenderHp;
		SetDamageGauge();
	}
}

void MonsterHpBar::Update_Off(float _Delta, GameEngineState* _Parent)
{
	if (pOwner)
	{
		const int CurHp = pOwner->GetHp();
		if (CurHp != RenderHp)
		{
			RenderHp = CurHp;
			_Parent->ChangeState(eState::Awake);
			return;
		}
	}
}

// State_Func
void MonsterHpBar::RendererOn()
{
	RenderValue = true;
	BackBarRenderer->On();
	HpBarRenderer->On();
	DamageBarRenderer->On();
}

void MonsterHpBar::RendererOff()
{
	RenderValue = false;
	BackBarRenderer->Off();
	HpBarRenderer->Off();
	DamageBarRenderer->Off();
}

void MonsterHpBar::SetDamageGauge()
{
	if (DamageBarRenderer)
	{
		float GaugeRatio = static_cast<float>(DamgeRenderHp) / static_cast<float>(MaxHp);
		GaugeRatio = std::clamp(GaugeRatio, 0.0f, 1.0f);
		const float RenderScale = GaugeRatio * ImageXScale;
		DamageBarRenderer->GetImageTransform().SetLocalScale({ RenderScale , HpBarYScale });
	}
}

void MonsterHpBar::SetHPGauge()
{
	if (HpBarRenderer)
	{
		float GaugeRatio = static_cast<float>(RenderHp) / static_cast<float>(MaxHp);
		GaugeRatio = std::clamp(GaugeRatio, 0.0f,1.0f);
		const float RenderScale = GaugeRatio * ImageXScale;
		HpBarRenderer->GetImageTransform().SetLocalScale({ RenderScale , HpBarYScale });
	}
}