#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Object_BaseLadder.h"

class Object_BaseLadder : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_BaseLadder();
	~Object_BaseLadder();

	// delete Function
	Object_BaseLadder(const Object_BaseLadder& _Other) = delete;
	Object_BaseLadder(Object_BaseLadder&& _Other) noexcept = delete;
	Object_BaseLadder& operator=(const Object_BaseLadder& _Other) = delete;
	Object_BaseLadder& operator=(Object_BaseLadder&& _Other) noexcept = delete;


	float4 GetRotation();
protected:
	void Start() override;
	void Update(float _Delta) override;
	float4 LadderRotation;

private:
	
	
};

