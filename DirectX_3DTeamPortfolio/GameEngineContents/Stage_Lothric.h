#pragma once
#include "ContentLevel.h"

#define BEGIN_BOSS_BGM_VOLUME 0.15f

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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	// 멤버변수 이름은 각자가 알아서 정하기
	std::shared_ptr<class Boss_Vordt> Boss_Object;
	std::shared_ptr<class ContentsLight> Light;
	std::shared_ptr<class Player> Player_Object;
	std::shared_ptr<class WorldMap> Map_Lothric;

	std::vector<std::shared_ptr<class BaseMonster>> AllMonster;
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

	std::shared_ptr<class Object_BossDoor> BossDoor;
	std::shared_ptr<class Object_CastleDoor> CastleDoor;
	std::shared_ptr<class Object_Ladder1> Ladder1;
	std::shared_ptr<class Object_Ladder2> Ladder2;
	std::shared_ptr<class Object_Ladder3> Ladder3;
	std::shared_ptr<class Object_Ladder4> Ladder4;
	std::shared_ptr<class Object_Ladder5> Ladder5;
	std::shared_ptr<class Object_Ladder6> Ladder6;
	std::shared_ptr<class Object_Desk> Desk;

	std::shared_ptr<class Object_FogWall> FogWall = nullptr;

	std::shared_ptr<class MainUIActor> MainUI;

	float BossBGMVolume = BEGIN_BOSS_BGM_VOLUME;
	GameEngineSoundPlayer BossBGM;

	void SetAllMonster();
	void AllMonsterOn();
	void AllMonsterOff();

	void SetAllEvCol();
	void EvColUpdate();

	void Area0_On();
	void Area1_On();
	void Area2_On();
	void Area3_On();
	void Area4_On();
	void Area5_On();
	void Area6_On();

	void CreateObject();
	void BossBGMUpdate(float _Delta);

private:
	// Level State
	enum class Enum_LevelState
	{
		LevelStart, // 리소스 로딩 << 멀티쓰레드 로딩
		LoadingDone, // 리소스 로딩 종료, Fade Out
		PlayStart, // 
		PlayerDeath,
		Loading, // Reset
		BossStage,
		End,
	};

	GameEngineState LevelState;

	// State_Start 
	void Start_LevelStart(GameEngineState* _Parent);
	void Start_LoadingDone(GameEngineState* _Parent);
	void Start_PlayStart(GameEngineState* _Parent);
	void Start_PlayerDeath(GameEngineState* _Parent);
	void Start_Loading(GameEngineState* _Parent);
	void Start_BossStage(GameEngineState* _Parent);
	void Start_End(GameEngineState* _Parent);

	void Update_LevelStart(float _Delta, GameEngineState* _Parent);
	void Update_LoadingDone(float _Delta, GameEngineState* _Parent);
	void Update_PlayStart(float _Delta, GameEngineState* _Parent);
	void Update_PlayerDeath(float _Delta, GameEngineState* _Parent);
	void Update_Loading(float _Delta, GameEngineState* _Parent);
	void Update_BossStage(float _Delta, GameEngineState* _Parent);
	void Update_End(float _Delta, GameEngineState* _Parent);


	void End_LevelStart(GameEngineState* _Parent);
	void End_LoadingDone(GameEngineState* _Parent);
	void End_PlayStart(GameEngineState* _Parent);
	void End_PlayerDeath(GameEngineState* _Parent);
	void End_Loading(GameEngineState* _Parent);
	void End_BossStage(GameEngineState* _Parent);
	void End_End(GameEngineState* _Parent);

	static bool ResLoadingDone;

};

