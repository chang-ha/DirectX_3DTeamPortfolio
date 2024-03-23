#include "PreCompile.h"
#include "UIAlertMaanger.h"

#include "UIAlert_BoneLit.h"
#include "UIAlert_Destroy.h"
#include "UIAlert_YouDie.h"

std::list<Enum_AlertType> UIAlertMaanger::CallMSG;
bool UIAlertMaanger::Alerting = false;


void UIAlertMaanger::CallAlert(Enum_AlertType _Type)
{
	CallMSG.push_back(_Type);
}

UIAlertMaanger::UIAlertMaanger() 
{
}

UIAlertMaanger::~UIAlertMaanger() 
{
}

void UIAlertMaanger::Update(float _Delta)
{
	DetectOffAlert();

	bool IsContain = (false == CallMSG.empty());
	if (true == IsContain && false == Alerting)
	{
		Enum_AlertType Type = CallMSG.front();
		CallMSG.pop_front();
		switch (Type)
		{
		case Enum_AlertType::YouDie:
			UIAlertPointer = GetLevel()->CreateActor<UIAlert_YouDie>(Enum_UpdateOrder::UI).get();
			break;
		case Enum_AlertType::Destroy:
			UIAlertPointer = GetLevel()->CreateActor<UIAlert_Destroy>(Enum_UpdateOrder::UI).get();
			break;
		case Enum_AlertType::BoneFire:
			UIAlertPointer = GetLevel()->CreateActor<UIAlert_BoneLit>(Enum_UpdateOrder::UI).get();
			break;
		default:
			break;
		}

		Alerting = true;
	}
}

void UIAlertMaanger::Release()
{
	UIAlertPointer = nullptr;
	CallMSG.clear();
}

void UIAlertMaanger::LevelEnd(GameEngineLevel* _NextLeve) 
{
	if (nullptr != UIAlertPointer)
	{
		UIAlertPointer->Death();
		UIAlertPointer = nullptr;
	}

	Alerting = false;
}

void UIAlertMaanger::DetectOffAlert()
{
	if (true == Alerting)
	{
		if (nullptr != UIAlertPointer)
		{
			bool AlertDone = (false == UIAlertPointer->IsUpdate());
			if (AlertDone)
			{
				UIAlertPointer->Death();
				UIAlertPointer = nullptr;
				Alerting = false;
			}
		}
	}
}