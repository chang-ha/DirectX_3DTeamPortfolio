#pragma once
#include "BaseActor.h"
class shield : public BaseActor
{
public:
	shield();
	~shield();

	// delete Function
	shield(const shield& _Other) = delete;
	shield(shield&& _Other) noexcept = delete;
	shield& operator=(const shield& _Other) = delete;
	shield& operator=(shield&& _Other) noexcept = delete;


protected:

	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;


private:
	std::shared_ptr<GameContentsFBXRenderer> Shield;
	std::shared_ptr<GameEngineCollision> Col;


};