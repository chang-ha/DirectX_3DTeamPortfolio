#pragma once
#include "ContentLevel.h"

#define BEGIN_BOSS_BGM_VOLUME 0.3f

// 설명 :
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

	void ResLoading();
	void ResetLoading();

	static bool ResLoadingDone;
	static bool ResetLoadingDone;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
private:
	// 멤버변수 이름은 각자가 알아서 정하기
	std::shared_ptr<class Boss_Vordt> Boss_Object;
	std::shared_ptr<class ContentsLight> Light;
	std::shared_ptr<class ContentsLight> BossDoorLight;
	std::shared_ptr<class Player> Player_Object;
	std::shared_ptr<class WorldMap> Map_Lothric;

	// 몬스터
	std::vector<std::shared_ptr<class BaseMonster>> AllMonster;
	// 이벤트충돌체
	std::vector<std::shared_ptr<class EventCol>> AllEvCol;

	//오브젝트
	std::vector<std::shared_ptr<class Object_bonfire>> VBonfire;
	std::vector<std::shared_ptr<class Object_Table>> VTable;
	std::vector<std::shared_ptr<class Object_Torchlight>> VTorchlight;
	std::vector<std::shared_ptr<class Object_Skeleton>> VSkeleton;
	std::vector<std::shared_ptr<class Object_Skeleton1>> VSkeleton1;
	std::vector<std::shared_ptr<class Object_HumanTree1>> VHumanTree1;
	std::vector<std::shared_ptr<class Object_HumanTree2>> VHumanTree2;
	std::vector<std::shared_ptr<class Object_HumanTree3>> VHumanTree3;
	std::vector<std::shared_ptr<class Object_HumanTree4>> VHumanTree4;
	std::vector<std::shared_ptr<class Object_HumanTree5>> VHumanTree5;
	std::vector<std::shared_ptr<class Object_CandleHuman>> VCandleHuman;
	std::vector<std::shared_ptr<class Object_CandleHuman2>> VCandleHuman2;
	std::vector<std::shared_ptr<class Object_Box>> VBox;
	std::vector<std::shared_ptr<class Object_OakBarrel>> VOakBarrel;
	std::vector<std::shared_ptr<class Object_Shelf>> VShelf;

	std::shared_ptr<class Object_BossDoor> BossDoor;
	std::shared_ptr<class Object_CastleDoor> CastleDoor;
	std::shared_ptr<class Object_Ladder1> Ladder1;
	std::shared_ptr<class Object_Ladder2> Ladder2;
	std::shared_ptr<class Object_Ladder3> Ladder3;
	std::shared_ptr<class Object_Ladder4> Ladder4;
	std::shared_ptr<class Object_Ladder5> Ladder5;
	std::shared_ptr<class Object_Ladder6> Ladder6;
	std::shared_ptr<class Object_Desk> Desk;

	std::shared_ptr<class Object_bonfire> BossRoom_bonfire = nullptr;
	std::shared_ptr<class Object_FogWall> FogWall = nullptr;

	std::shared_ptr<class MainUIActor> MainUI;
	std::shared_ptr<class GameEngineActor> BlackScreen;

	float BossBGMVolume = BEGIN_BOSS_BGM_VOLUME;
	GameEngineSoundPlayer BossBGM;
	void BossBGMStart();
	void BossBGMUpdate(float _Delta);
	void BossBGMEnd();

	void SetAllMonster();
	void AllMonsterOn();
	void AllMonsterOff();

	void SetAllEvCol();
	void AllEvColOn();

	void Area0_On();
	void Area1_On();
	void Area2_On();
	void Area3_On();
	void Area4_On();
	void Area5_On();
	void Area6_On();

	void CreateObject();

private:
	void StateInit();

	// Level State
	enum class Enum_LevelState
	{
		Play, // 
		PlayerDeath,
		BossDeath,
		StageClear,
	};

	GameEngineState LevelState;

	// PlayState_Start 
	void Start_Play(GameEngineState* _Parent);
	void Start_PlayerDeath(GameEngineState* _Parent);
	void Start_BossDeath(GameEngineState* _Parent);
	void Start_StageClear(GameEngineState* _Parent);

	// PlayState_Update
	void Update_Play(float _Delta, GameEngineState* _Parent);
	void Update_PlayerDeath(float _Delta, GameEngineState* _Parent);
	void Update_BossDeath(float _Delta, GameEngineState* _Parent);
	void Update_StageClear(float _Delta, GameEngineState* _Parent);

	void PlayUpdate(float _Delta);

	// PlayState_End
	void End_Play(GameEngineState* _Parent);
	void End_PlayerDeath(GameEngineState* _Parent);
	void End_BossDeath(GameEngineState* _Parent);
	void End_StageClear(GameEngineState* _Parent);

	// PlayerDeath State
	enum class Enum_PlayerDeathState
	{
		Ready,
		YouDie,
		FadeOut,
		Done,
	};

	GameEngineState PlayerDeathState;

	void Start_PlayerDeath_Ready(GameEngineState* _Parent);
	void Start_PlayerDeath_YouDie(GameEngineState* _Parent);
	void Start_PlayerDeath_FadeOut(GameEngineState* _Parent);

	void Update_PlayerDeath_Ready(float _Delta, GameEngineState* _Parent);
	void Update_PlayerDeath_YouDie(float _Delta, GameEngineState* _Parent);
	void Update_PlayerDeath_FadeOut(float _Delta, GameEngineState* _Parent);

	enum class Enum_BossDeathState
	{
		Ready,
		Alert,
		Done,
	};

	GameEngineState BossDeathState;
	bool IsAlert = false;

	void Start_BossDeath_Ready(GameEngineState* _Parent);
	void Start_BossDeath_Alert(GameEngineState* _Parent);

	void Update_BossDeath_Ready(float _Delta, GameEngineState* _Parent);
	void Update_BossDeath_Alert(float _Delta, GameEngineState* _Parent);

};

