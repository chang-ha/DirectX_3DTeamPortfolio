#pragma once
#include <GameEngineCore/GameEngineActor.h>

 
class Object_FogWall : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_FogWall();
	~Object_FogWall();

	// delete Function
	Object_FogWall(const Object_FogWall& _Other) = delete;
	Object_FogWall(Object_FogWall&& _Other) noexcept = delete;
	Object_FogWall& operator=(const Object_FogWall& _Other) = delete;
	Object_FogWall& operator=(Object_FogWall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;


private:

	std::shared_ptr< class ContentsFogWallRenderer> FogWallRenderer;
};

