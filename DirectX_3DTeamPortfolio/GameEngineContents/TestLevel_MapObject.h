#pragma once
#include "ContentLevel.h"

class TestLevel_MapObject : public ContentLevel
{
public:
	// constructer destructer
	TestLevel_MapObject();
	~TestLevel_MapObject();

	// delete function
	TestLevel_MapObject(const TestLevel_MapObject& _Ohter) = delete;
	TestLevel_MapObject(TestLevel_MapObject&& _Ohter) noexcept = delete;
	TestLevel_MapObject& operator=(const TestLevel_MapObject& _Other) = delete;
	TestLevel_MapObject& operator=(TestLevel_MapObject&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
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


	void CreateObject();

};

