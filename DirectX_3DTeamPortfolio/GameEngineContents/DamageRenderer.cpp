#include "PreCompile.h"
#include "DamageRenderer.h"

#include <time.h>

DamageRenderer::DamageRenderer()
{
}

DamageRenderer::~DamageRenderer()
{
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < Vec->size(); i++)
		{
			(*Vec)[i]->Death();
			(*Vec)[i] = nullptr;
		}

		delete (Vec);
		Start = DamageRenderList.erase(Start);
	}
}

void DamageRenderer::Start()
{
	if (nullptr == GameEngineSprite::Find("Number_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("Number");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& PFiles : Files)
		{
			GameEngineTexture::Load(PFiles.GetStringPath());
			GameEngineSprite::CreateSingle(PFiles.GetFileName());
		}
	}
}

void DamageRenderer::Update(float _Delta)
{
	if (DamageRenderList.size() <= 0)
	{
		Death();
	}
	
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End; Start++)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < (*Start)->size(); i++)
		{
			(*Vec)[i]->Transform.AddLocalPosition({ 0, 50.0f * _Delta });
		}
	}

	CurTime += _Delta;
	if (Disappear <= CurTime)
	{
		DeleteDamage();
		CurTime = 0.0f;
	}
}

void DamageRenderer::PushDamage(GameEngineObject* _Object, size_t _Damage)
{
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vect = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	
	DamRan.SetSeed(time(nullptr));
	float a = DamageRandom;
	again:;

	int b = rand() % 20 + 1;
	DamageRandom = static_cast<float>(DamRan.RandomInt(b + 70, b + 80));
	if (DamageRandom == a)
	{
		goto again;
	}
	Damage = DamageRandom;

	// 몬스터에게 데미지 주기 위한
	//_Object->GetParentObject()->GetDynamic_Cast_This<class Monster>()->Hit(Damage);

	int NumArr[4] = { 0, };
	int Digit;

	for (Digit = 0; Damage > 0; Digit++)
	{
		NumArr[Digit] = static_cast<unsigned long long>(Damage) % 10;
		Damage /= 10;
	}
	
	Vect->reserve(Digit);


	for (int i = Digit; i > 0; i--)
	{
		std::string TextureName = "Number_" + std::to_string(NumArr[i - 1]) + ".Png";

		NewNumberRender = CreateComponent<GameEngineSpriteRenderer>(/*Order지정*/);
		NewNumberRender->SetSprite(TextureName);
		NewNumberRender->Transform.SetWorldPosition({ (_Object->Transform.GetWorldPosition().X + (i - 1) * 32.0f),
			_Object->Transform.GetWorldPosition().Y + 100.0f });
		Vect->push_back(NewNumberRender);
	}

	DamageRenderList.push_back(Vect);
}

void DamageRenderer::DeleteDamage()
{
	if (DamageRenderList.size() <= 0)
	{
		return;
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		{
			for (int i = 0; i < (*Start)->size(); i++)
			{
				(*Vec)[i]->Death();
				(*Vec)[i] = nullptr;
			}

			delete (Vec);
			Start = DamageRenderList.erase(Start);

			continue;
		}

		Start++;
	}
}

void DamageRenderer::Release()
{
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < Vec->size(); i++)
		{
			(*Vec)[i]->Death();
			(*Vec)[i] = nullptr;
		}

		delete (Vec);
		Start = DamageRenderList.erase(Start);
	}
}

void DamageRenderer::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}