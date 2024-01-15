#include "PreCompile.h"
#include "Player.h"

void Player::Player_State()
{
	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{

			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Idle");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (GameEngineInput::IsPress('A', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Left");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}


				if (GameEngineInput::IsPress('D', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Right");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}

				if (GameEngineInput::IsPress('W', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Forward");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}


				if (GameEngineInput::IsPress('S', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Behind");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Idle, NewPara);
	}


	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				// MainSpriteRenderer->ChangeAnimation("Idle");
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (true == GameEngineInput::IsPress('W', this))
				{
					Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
				}

				if (true == GameEngineInput::IsPress('S', this))
				{
					Capsule->MoveForce({ 0.0f, 0.0f, -100, 0.0f });
				}

				if (true == GameEngineInput::IsPress('A', this))
				{
					Capsule->MoveForce({ -100, 0.0f, 0.0f, 0.0f });
				}

				if (true == GameEngineInput::IsPress('D', this))
				{
					Capsule->MoveForce({ 100, 0.0f, 0.0f, 0.0f });
				}


				if (GameEngineInput::IsUp('A', this))
				{
					FBXRenderer->ChangeAnimation("Left_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('D', this))
				{
					FBXRenderer->ChangeAnimation("Right_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('W', this))
				{
					FBXRenderer->ChangeAnimation("Forward_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('S', this))
				{
					FBXRenderer->ChangeAnimation("Behind_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Move, NewPara);
	}


	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{
				// MainSpriteRenderer->ChangeAnimation("Idle");
			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->IsCurAnimationEnd())
				{

					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}



			};

		PlayerState.CreateState(PlayerState::Move_Stop, NewPara);
	}










	PlayerState.ChangeState(PlayerState::Idle);



}