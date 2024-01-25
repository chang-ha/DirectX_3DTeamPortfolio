#include "PreCompile.h"
#include "Player.h"
#include "BaseActor.h"
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
				MainRenderer->ChangeAnimation("Idle");
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
					MainRenderer->ChangeAnimation("Slow_Walk_Left");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}


				if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Right");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Forward");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}


				if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Behind");
					_Parent->ChangeState(PlayerState::Slow_Walk);
					return;
				}

				

				if (GameEngineInput::IsPress('A', this))
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}


				if (GameEngineInput::IsPress('D', this))
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}

				if (GameEngineInput::IsPress('W', this))
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}

				if (GameEngineInput::IsPress('S', this))
				{
					MainRenderer->ChangeAnimation("Walk_Behind");
					_Parent->ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress(VK_SPACE, this))
				{
					_Parent->ChangeState(PlayerState::Back_Step);
					return;
				}

				if (GameEngineInput::IsPress('R', this))
				{
					MainRenderer->ChangeAnimation("Portion_Drink_01");
					_Parent->ChangeState(PlayerState::Portion_01);
					return;
				}

				if (GameEngineInput::IsPress(VK_LBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
				if (GameEngineInput::IsPress(VK_RBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Shield_Idle);
					return;
				}
				if (GameEngineInput::IsPress(VK_CONTROL, this))
				{
					_Parent->ChangeState(PlayerState::Parrying);
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
				//if()

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SPACE, this))
				{
					PlayerState.ChangeState(PlayerState::Roll_Forward);
					return;
				}
				if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress(VK_SPACE, this))
				{
					PlayerState.ChangeState(PlayerState::Roll_Behind);
					return;
				}
				if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress(VK_SPACE, this))
				{
					PlayerState.ChangeState(PlayerState::Roll_Left);
					return;
				}
				if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress(VK_SPACE, this))
				{
					PlayerState.ChangeState(PlayerState::Roll_Right);
					return;
				}

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					PlayerState.ChangeState(PlayerState::Run);
					return; 
				}

				if (GameEngineInput::IsPress(VK_RBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Shield_Idle);
					return;
				}
				if (true == GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Forward");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Behind");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Left");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					MainRenderer->ChangeAnimation("Slow_Walk_Right");
					PlayerState.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				if (true == GameEngineInput::IsPress(VK_LBUTTON, this))
				{
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
				if (true == GameEngineInput::IsPress(VK_SPACE, this))
				{
					_Parent->ChangeState(PlayerState::Back_Step);
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
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::FORWARD * Speed });
				
				}

				if (true == GameEngineInput::IsPress('S', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, -100, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::BACKWARD * Speed });
				
				}

				if (true == GameEngineInput::IsPress('A', this))
				{
					//Capsule->MoveForce({ -100, 0.0f, 0.0f, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::LEFT * Speed });
				
				}

				if (true == GameEngineInput::IsPress('D', this))
				{
					//Capsule->MoveForce({ 100, 0.0f, 0.0f, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::RIGHT * Speed });
					
				}
				if (GameEngineInput::IsPress(VK_CONTROL, this))
				{
					_Parent->ChangeState(PlayerState::Parrying);
					return;
				}

				if (true == GameEngineInput::IsPress(VK_SPACE, this))
				{
					_Parent->ChangeState(PlayerState::Back_Step);
					return;
				}
				if (GameEngineInput::IsUp('A', this))
				{
					MainRenderer->ChangeAnimation("Left_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('D', this))
				{
					MainRenderer->ChangeAnimation("Right_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('W', this))
				{
					MainRenderer->ChangeAnimation("Forward_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}
				else if (GameEngineInput::IsUp('S', this))
				{
					MainRenderer->ChangeAnimation("Behind_Stop");
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
			
				if (MainRenderer->GetCurAnimationFrame() >= 35)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsPress('A', this))
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('D', this))
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('W', this))
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('S', this))
				{
					MainRenderer->ChangeAnimation("Walk_Behind");
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
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}


				if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}


				if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this))
				{
					//Capsule->MoveForce({ 0.0f, 0.0f, 100, 0.0f });
					GetFBXRenderer()->Transform.AddLocalPosition({ float4::UP * Speed });
					return;
				}

				if (GameEngineInput::IsPress('W', this))
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('A', this))
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('S', this))
				{
					MainRenderer->ChangeAnimation("Walk_Behind");
					PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('D', this))
				{
					MainRenderer->ChangeAnimation("Walk_Right");
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
				MainRenderer->ChangeAnimation("Run");
		};


	    NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{


			
			if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
			{
				GetFBXRenderer()->Transform.AddLocalPosition({ 0.0f,0.0f,0.0f });
			}

			if (GameEngineInput::IsUp('W', this) )
			{
				MainRenderer->ChangeAnimation("Forward_Stop");
				PlayerState.ChangeState(PlayerState::Move_Stop);
				return; 
			}

			if (GameEngineInput::IsUp(VK_SHIFT, this))
			{
				MainRenderer->ChangeAnimation("Forward_Stop");
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
				MainRenderer->ChangeAnimation("Run");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					GetFBXRenderer()->Transform.AddLocalPosition({ 0.0f,0.0f,0.0f });
				}

				if (GameEngineInput::IsUp('W', this))
				{
					MainRenderer->ChangeAnimation("Forward_Stop");
					PlayerState.ChangeState(PlayerState::Move_Stop);
					return;
				}

				if (GameEngineInput::IsUp(VK_SHIFT, this))
				{
					MainRenderer->ChangeAnimation("Forward_Stop");
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
				MainRenderer->ChangeAnimation("Attack_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{
				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true; 
					}
				}	

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
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
				MainRenderer->ChangeAnimation("Attack_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
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
				MainRenderer->ChangeAnimation("Attack_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}
				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}


				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
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
				MainRenderer->ChangeAnimation("Attack_04");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerState.ChangeState(PlayerState::Move);
						return;
					}

				}

				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 30)
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
				MainRenderer->ChangeAnimation("Portion_Drink_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
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
				MainRenderer->ChangeAnimation("Portion_Drink_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
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
				MainRenderer->ChangeAnimation("Portion_Drink_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Portion_03, NewPara);
	}

	

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Portion_Drink_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
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
				MainRenderer->ChangeAnimation("Portion_Drink_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
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
				MainRenderer->ChangeAnimation("Portion_Drink_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Portion_03, NewPara);
	}
	
	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Behind");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
			
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Roll_Behind, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Forward");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Roll_Forward, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Roll_Left, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Roll_Right, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Back_Step");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerState.CreateState(PlayerState::Back_Step, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Shield_Idle");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('W', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('A', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('S', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('D', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Move);
					return;
				}




				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
				{		
					PlayerState.ChangeState(PlayerState::Shield_Idle);
					return;
				}

				else if (true == GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Shield_Idle, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Shield_Move");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('W', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Move);
					return;
				}

				 if (true == GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					 MainRenderer->ChangeAnimation("Walk_Forward");
				    PlayerState.ChangeState(PlayerState::Move);
					return;
				}
				if (true == GameEngineInput::IsUp('W', this))
				{
					PlayerState.ChangeState(PlayerState::Shield_Idle);
					return;
				}

			};

		PlayerState.CreateState(PlayerState::Shield_Move, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Parrying");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				//if(GameEngineInput::)
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerState.ChangeState(PlayerState::Idle);
					return; 
				}
			};

		PlayerState.CreateState(PlayerState::Parrying, NewPara);
	}

	PlayerState.ChangeState(PlayerState::Idle);



}