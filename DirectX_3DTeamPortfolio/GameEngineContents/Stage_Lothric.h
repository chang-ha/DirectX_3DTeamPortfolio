#pragma once
#include "ContentLevel.h"

// ���� :
class Stage_Lothric : public ContentLevel
{
public:
	// constructer destructer
	Stage_Lothric();
	~Stage_Lothric();

	// delete function
	Stage_Lothric(const Stage_Lothric& _Ohter) = delete;
	Stage_Lothric(Stage_Lothric&& _Ohter) noexcept = delete;
	Stage_Lothric& operator=(const Stage_Lothric& _Other) = delete;
	Stage_Lothric& operator=(Stage_Lothric&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	// ������� �̸��� ���ڰ� �˾Ƽ� ���ϱ�
	std::shared_ptr<class Boss_Vordt> Boss_Object;
	std::shared_ptr<class ContentsLight> Light;
	std::shared_ptr<class Player> Player_Object;
	std::shared_ptr<class WorldMap> Map_Lothric;
};

