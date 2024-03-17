#include "PreCompile.h"
#include "AddSouls.h"

AddSouls::AddSouls()
{
}

AddSouls::~AddSouls()
{
}

#define SoulsPos {390.0f, -180.0f}

void AddSouls::Start()
{
	WindowScale = GameEngineCore::MainWindow.GetScale().Half();

	SoulsBack = CreateComponent<GameEngineUIRenderer>();
	SoulsBack->AutoSpriteSizeOn();
	SoulsBack->Transform.SetLocalPosition({ WindowScale.X - 90.0f, -WindowScale.Y + 90.0f });
	SoulsBack->SetSprite("SoulsBack.Png");

	// ������ �ҿ�
	AddSoul = CreateComponent<GameEngineUIRenderer>();
	AddSoul->SetText(GlobalValue::OptimusFont, std::to_string(SoulAdd), 14.0f, float4{1,0,0,1}, FW1_RIGHT);
	AddSoul->Transform.SetLocalPosition({ WindowScale.X - 30.0f , -WindowScale.Y + 130.0f });
	AddSoul->Off();

	// ������ �ҿ�
	SumSouls = CreateComponent<GameEngineUIRenderer>();
	SumSouls->SetText(GlobalValue::OptimusFont, std::to_string(Souls), 14.0f, float4{ 1,1,1,1 }, FW1_RIGHT);
	SumSouls->Transform.SetLocalPosition({ WindowScale.X - 30.0f ,  -WindowScale.Y + 100.0f});

	GameEngineInput::AddInputObject(this);
}

void AddSouls::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1', this))
	{
		AddSouls::ChangeState(SoulsActor::Appear);
	}

	StateUpdate(_Delta);
	// ��Ʈ �ǽð��ݿ�
	FontUpdate();
}

void AddSouls::FontUpdate()
{
	AddSoul->SetText(GlobalValue::OptimusFont, "+" + std::to_string(SoulAdd), FontSize, float4{ 1,0,0,1 }, FW1_RIGHT);
}

void AddSouls::ChangeState(SoulsActor _State)
{
	if (_State != SoulState)
	{
		switch (_State)
		{
		case SoulsActor::Appear:
			AppearStart();
			break;
		case SoulsActor::Add:
			AddStart();
			break;
		case SoulsActor::Sum:
			SumStart();
			break;
		case SoulsActor::None:
			break;
		}
	}

	SoulState = _State;
}

void AddSouls::StateUpdate(float _Delta)
{
	switch (SoulState)
	{
	case SoulsActor::Appear:
		return AppearUpdate(_Delta);
	case SoulsActor::Add:
		return AddUpdate(_Delta);
	case SoulsActor::Sum:
		return SumUpdate(_Delta);
	case SoulsActor::None:
		break;
	}
}

// ��Ÿ���� ũ�Ⱑ Ŀ���� ��
void AddSouls::AppearStart()
{
	AddSoul->On();
	AddSoul->Transform.SetLocalPosition({ WindowScale.X - 30.0f , -WindowScale.Y + 125.0f });
	
	SoulAdd += 100;
	AddSoul->SetText(GlobalValue::OptimusFont,"+"+std::to_string(SoulAdd), FontSize, float4{1,0,0,1}, FW1_RIGHT);
	FontTime = 0.0f;
}

void AddSouls::AppearUpdate(float _Delta)
{
	FontTime += _Delta;
	FontSize += 10 * _Delta;

	if (FontTime >= FontSizeTime)
	{
		AddSouls::ChangeState(SoulsActor::Add);
		return;
	}
}

// ũ�Ⱑ �پ��� ���� �������� ��
void AddSouls::AddStart()
{
	FontTime = 0.0f;
}

void AddSouls::AddUpdate(float _Delta)
{
	FontTime += _Delta;
	FontSize -= 10 * _Delta;

	AddSoul->Transform.AddLocalPosition({ 0.0f, -50.0f * _Delta });

	if (FontTime >= FontSizeTime)
	{
		AddSouls::ChangeState(SoulsActor::Sum);
		AddSoul->Off();
	}
}

// ������ �ҿ��� �������� ��
void AddSouls::SumStart()
{
	Souls += SoulAdd;
	SumSouls->SetText(GlobalValue::OptimusFont, std::to_string(Souls), 14.0f, float4{ 1,1,1,1 }, FW1_RIGHT);
}

void AddSouls::SumUpdate(float _Delta)
{

}


void AddSouls::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}