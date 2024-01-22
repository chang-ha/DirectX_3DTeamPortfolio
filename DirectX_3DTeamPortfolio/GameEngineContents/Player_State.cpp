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

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					PlayerState.ChangeState(PlayerState::Run);
					return;
				}

				if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Left");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}


				if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Right");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Forward");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}


				if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Behind");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}

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
				if (GameEngineInput::IsPress('R', this))
				{
					FBXRenderer->ChangeAnimation("Portion_Drink_01");
					_Parent->ChangeState(PlayerState::Portion_01);
					return;
				}

				if (GameEngineInput::IsPress(VK_LBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Attack_01);
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
				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					PlayerState.ChangeState(PlayerState::Run);
					return; 
				}

				if (true == GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Forward");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Behind");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Left");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					FBXRenderer->ChangeAnimation("Slow_Walk_Right");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
				/*if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('A', this))
				{
					Transform.AddLocalPosition({ float4::UP * Speed });
					return; 
				}*/

				if (true == GameEngineInput::IsPress('W', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					Transform.AddLocalPosition({ float4::UP * Speed });
				
				}

				if (true == GameEngineInput::IsPress('S', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, -100, 0.0f });
					Transform.AddLocalPosition({ float4::DOWN * Speed });
				
				}

				if (true == GameEngineInput::IsPress('A', this))
				{
					//Capsule->MoveForce({ -100, 0.0f, 0.0f, 0.0f });
					Transform.AddLocalPosition({ float4::LEFT * Speed });
				
				}

				if (true == GameEngineInput::IsPress('D', this))
				{
					//Capsule->MoveForce({ 100, 0.0f, 0.0f, 0.0f });
					Transform.AddLocalPosition({ float4::RIGHT * Speed });
					
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
				if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
			
				if (FBXRenderer->GetCurAnimationFrame() >= 35)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsPress('A', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Left");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('D', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Right");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('W', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Forward");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('S', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Behind");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}



				
			};

		PlayerState.CreateState(PlayerState::Move_Stop, NewPara);
	}


	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{

			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				//FBXRenderer->ChangeAnimation("Idle");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}


				if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}


				if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}

				if (GameEngineInput::IsPress('W', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Forward");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('A', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Left");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('S', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Behind");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('D', this))
				{
					FBXRenderer->ChangeAnimation("Walk_Right");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}

				if (GameEngineInput::IsUp('A', this))
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('D', this))
				{		
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('W', this))
				{	
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('S', this))
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Slow_Walk, NewPara);
	}

	{
		CreateStateParameter NewPara;





		NewPara.Start = [=](class GameEngineState* _Parent)
		{
			FBXRenderer->ChangeAnimation("Run");
		};


	    NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{


			
			if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
			{
				Transform.AddLocalPosition({ 0.0f,0.0f,0.0f });
			}

			if (GameEngineInput::IsUp('W', this) )
			{
				FBXRenderer->ChangeAnimation("Forward_Stop");
				PlayerState.ChangeState(PlayerState::Move_Stop);
				return; 
			}

			if (GameEngineInput::IsUp(VK_SHIFT, this))
			{
				FBXRenderer->ChangeAnimation("Forward_Stop");
				PlayerState.ChangeState(PlayerState::Move);
				return;
			}

		};

	    PlayerState.CreateState(PlayerState::Run, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Run");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					Transform.AddLocalPosition({ 0.0f,0.0f,0.0f });
				}

				if (GameEngineInput::IsUp('W', this))
				{
					FBXRenderer->ChangeAnimation("Forward_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}

				if (GameEngineInput::IsUp(VK_SHIFT, this))
				{
					FBXRenderer->ChangeAnimation("Forward_Stop");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}

		};

		PlayerState.CreateState(PlayerState::Run, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Attack_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{
				if (FBXRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true; 
					}
				}	

				if (FBXRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && FBXRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && FBXRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Attack_02);
					return; 
				}
		};

		PlayerState.CreateState(PlayerState::Attack_01, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Attack_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (FBXRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && FBXRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && FBXRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Attack_03);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Attack_02, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Attack_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (FBXRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && FBXRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}


				else if (Attack_Check == true && FBXRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Attack_04);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Attack_03, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Attack_04");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (FBXRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						FBXRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}

				if (Attack_Check == false && FBXRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && FBXRenderer->GetCurAnimationFrame() > 30)
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Attack_01);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Attack_04, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Portion_Drink_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Portion_02);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Portion_01, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Portion_Drink_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Portion_03);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Portion_02, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				FBXRenderer->ChangeAnimation("Portion_Drink_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (FBXRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Portion_03, NewPara);
	}



	PlayerState.ChangeState(PlayerState::Idle);



}