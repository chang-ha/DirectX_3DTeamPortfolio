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
				//Camera_Pos_X = Player_Pos.X;
				MainRenderer->ChangeAnimation("Idle");
				StateValue = PlayerState::Idle;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}
				


				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					PlayerStates.ChangeState(PlayerState::Run);
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
					//Player_Pos = Camera_Pos_X;
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

		PlayerStates.CreateState(PlayerState::Idle, NewPara);
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
				StateValue = PlayerState::Move;
				Rotation_Check_X = false;
				//Player_Pos.X = Camera_Pos_X;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				
				if (Rotation_Check_X == false)
				{
				if (Angle > 0)
					{
						Rotation_Check_X_Plus = true;
					}
					else if (Angle < 0)
					{
						Rotation_Check_X_Mus = true;
					}
				}
					if (Rotation_Check_X_Plus == true)
					{
						Capsule->AddWorldRotation({ 0.0f,10.0f });


						if (Angle < 0)
						{
							
							Rotation_Check_X_Plus = false;
							Rotation_Check_X_Mus = false;
							Rotation_Check_X = true;
							
							
						}

					}

					
					if (Rotation_Check_X_Mus == true)
					{
						Capsule->AddWorldRotation({ 0.0f,-10.0f });


						if (Angle > 0)
						{
							
							Rotation_Check_X_Mus = false;
							Rotation_Check_X_Plus = false;
							Rotation_Check_X = true;
							
							
						}

					}	
					

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X ==true)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Forward);
					return;
				}
				else if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Behind);
					return;
				}
				else if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Left);
					return;
				}
				else if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Right);
					return;
				}

				else if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Run);
					return; 
				}

				
				else if (true == GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Slow_Walk_Forward");
					PlayerStates.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				else if (true == GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Slow_Walk_Behind");
					PlayerStates.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				else if (true == GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Slow_Walk_Left");
					PlayerStates.ChangeState(PlayerState::Slow_Walk);
					return;
				}

				else if (true == GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Slow_Walk_Right");
					PlayerStates.ChangeState(PlayerState::Slow_Walk);
					return;
				}
		
				else if (GameEngineInput::IsPress(VK_RBUTTON, this))
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Shield_Idle);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Rotation_Check_X == true && Rock_On_Check == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}

				else if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Back_Step);
					return;

				}

				else if (true == GameEngineInput::IsPress('W', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					Capsule->MoveForce({ float4::FORWARD * Speed });
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					//MainRenderer->ChangeAnimation("Walk_Forward");
					Capsule->MoveForce({ float4::BACKWARD * Speed });
				}
				else if (true == GameEngineInput::IsPress('A', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					Capsule->MoveForce({ float4::LEFT * Speed });
				}
				else if (true == GameEngineInput::IsPress('D', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					Capsule->MoveForce({ float4::RIGHT * Speed });
				}
			
				else if (true == GameEngineInput::IsPress('W', this)&& Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					Capsule->MoveForce({ float4::FORWARD * Speed } , degree_X);
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rock_On_Check ==true)
				{				
					//MainRenderer->ChangeAnimation("Walk_Forward");
					Capsule->MoveForce({ float4::BACKWARD * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('A', this) && Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					Capsule->MoveForce({ float4::LEFT * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('D', this) && Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					Capsule->MoveForce({ float4::RIGHT * Speed }, degree_X);
				}
				

				else if (GameEngineInput::IsPress(VK_CONTROL, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Parrying);
					return;
				}

				else if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Back_Step);
					return;
				}
				if (GameEngineInput::IsUp('A', this) )
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Left_Stop");
					PlayerStates.ChangeState(PlayerState::Move_Stop);
					return;
				}
				if (GameEngineInput::IsUp('D', this) )
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Right_Stop");
					PlayerStates.ChangeState(PlayerState::Move_Stop);
					return;
				}
				if (GameEngineInput::IsUp('W', this) )
				{
					//Camera_Pos_X = Player_Pos.X;
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Forward_Stop");
					PlayerStates.ChangeState(PlayerState::Move_Stop);
					return;
				}
				if (GameEngineInput::IsUp('S', this))
				{
					Rotation_Check_X = false;
					MainRenderer->ChangeAnimation("Behind_Stop");
					PlayerStates.ChangeState(PlayerState::Move_Stop);
					return;
				}
				if (GameEngineInput::IsPress(VK_CONTROL, this) && Rotation_Check_X == true)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Parrying);
					return;
				}

				if (GameEngineInput::IsPress(VK_RBUTTON, this) && Rotation_Check_X == true )
				{
					_Parent->ChangeState(PlayerState::Shield_Idle);
					return;
				}
				


				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}

			};

		PlayerStates.CreateState(PlayerState::Move, NewPara);
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
				//Capsule->ResetMove(Enum_Axies::All);
				
				StateValue = PlayerState::Move_Stop;
				
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
					
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsPress('A', this))
				{
					
					MainRenderer->ChangeAnimation("Walk_Left");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('D', this))
				{
				
					MainRenderer->ChangeAnimation("Walk_Right");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('W', this))
				{
				
					MainRenderer->ChangeAnimation("Walk_Forward");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				else if (GameEngineInput::IsPress('S', this))
				{
				
					MainRenderer->ChangeAnimation("Walk_Behind");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}



				
			};

		PlayerStates.CreateState(PlayerState::Move_Stop, NewPara);
	}


	{
		CreateStateParameter NewPara;

		// 한번만 실행되는 겁니다.
		NewPara.Init = [=](class GameEngineState* _Parent)
			{

			};


		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				StateValue = PlayerState::Slow_Walk;
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
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('A', this))
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('S', this))
				{
					MainRenderer->ChangeAnimation("Walk_Behind");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				if (GameEngineInput::IsPress('D', this))
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}

				if (GameEngineInput::IsUp('A', this))
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('D', this))
				{		
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('W', this))
				{	
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
				else if (GameEngineInput::IsUp('S', this))
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerStates.CreateState(PlayerState::Slow_Walk, NewPara);
	}

	/*{
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
				PlayerStates.ChangeState(PlayerState::Move_Stop);
				return; 
			}

			if (GameEngineInput::IsUp(VK_SHIFT, this))
			{
				MainRenderer->ChangeAnimation("Forward_Stop");
				PlayerStates.ChangeState(PlayerState::Move);
				return;
			}

		};

	    PlayerStates.CreateState(PlayerState::Run, NewPara);
	}*/

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				Rotation_Check_X = true;
				MainRenderer->ChangeAnimation("Run");
				StateValue = PlayerState::Run;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{

				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
				{
					Capsule->MoveForce({ float4::FORWARD * Speed*1.5 });
				}

				if (GameEngineInput::IsUp('W', this))
				{
					MainRenderer->ChangeAnimation("Forward_Stop");
					PlayerStates.ChangeState(PlayerState::Move_Stop);
					return;
				}

				if (GameEngineInput::IsUp(VK_SHIFT, this))
				{
					MainRenderer->ChangeAnimation("Forward_Stop");
					PlayerStates.ChangeState(PlayerState::Move);
					return;
				}

		};

		PlayerStates.CreateState(PlayerState::Run, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Attack_01");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}


				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true; 
					}
				}	

				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_02);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

				}
				
		};

		PlayerStates.CreateState(PlayerState::Attack_01, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Attack_02");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}


				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_03);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

				}
				
			};

		PlayerStates.CreateState(PlayerState::Attack_02, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Attack_03");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}


				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}


				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_04);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

				}
				
			};

		PlayerStates.CreateState(PlayerState::Attack_03, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Attack_04");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}


				if (MainRenderer->GetCurAnimationFrame() < 30)
				{
					if (GameEngineInput::IsDown(VK_LBUTTON, this))
					{
						Attack_Check = true;
					}
				}

				if (Attack_Check == false && MainRenderer->IsCurAnimationEnd())
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 30)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_01);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

				}

				
			};

		PlayerStates.CreateState(PlayerState::Attack_04, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Portion_02);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Portion_01, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Portion_03);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Portion_02, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerStates.CreateState(PlayerState::Portion_03, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Portion_02);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Portion_01, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Portion_03);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Portion_02, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerStates.CreateState(PlayerState::Portion_03, NewPara);
	}
	
	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Behind");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
			
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					Capsule->MoveForce({ float4::BACKWARD * Speed * 1.2 }, degree_X);
				}

				else 
				{
					if (MainRenderer->GetCurAnimationFrame() < 25)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed * 1.2 });
					}
				}


				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Roll_Behind, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Forward");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				

			    if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::FORWARD * Speed * 1.2 });
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::FORWARD * Speed * 1.2 });
					}
				}
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}


			};






		PlayerStates.CreateState(PlayerState::Roll_Forward, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (Rock_On_Check == true)
				{
			
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::LEFT * Speed * 1.2 });
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::LEFT * Speed * 1.2 });
					}

					
				}
				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Roll_Left, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Roll_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::RIGHT * Speed * 1.2 });
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::RIGHT * Speed * 1.2 });
					}
				}

				if (MainRenderer->GetCurAnimationFrame() > 30)
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Roll_Right, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Back_Step");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });

					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed * 1.2 });
					}
				}
				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed * 1.2 });
					}
				}
				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Back_Step, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('A', this))
				{
					PlayerStates.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('S', this))
				{
					PlayerStates.ChangeState(PlayerState::Shield_Move);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this) && true == GameEngineInput::IsPress('D', this))
				{
					PlayerStates.ChangeState(PlayerState::Shield_Move);
					return;
				}




				else if (true == GameEngineInput::IsPress(VK_RBUTTON, this))
				{		
					PlayerStates.ChangeState(PlayerState::Shield_Idle);
					return;
				}

				else if (true == GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

			};

		PlayerStates.CreateState(PlayerState::Shield_Idle, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Shield_Move);
					return;
				}

				 if (true == GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					 MainRenderer->ChangeAnimation("Walk_Forward");
				    PlayerStates.ChangeState(PlayerState::Move);
					return;
				}
				if (true == GameEngineInput::IsUp('W', this))
				{
					PlayerStates.ChangeState(PlayerState::Shield_Idle);
					return;
				}

			};

		PlayerStates.CreateState(PlayerState::Shield_Move, NewPara);
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
					PlayerStates.ChangeState(PlayerState::Idle);
					return; 
				}
			};

		PlayerStates.CreateState(PlayerState::Parrying, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				StateValue = PlayerState::RockOn;
				Rotation_Check_X = false;
				Rotation_Check_X_Plus = false;
				Rotation_Check_X_Mus = false;

				Rotation_Check_Y = false;
				Rotation_Check_Y_Plus = false;
				Rotation_Check_Y_Mus = false;

				Rotation_Player_Check = false;
				Rotation_Player_Plus = false;
				Rotation_Player_Mus = false;

				Rock_On_Check = true; 
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				
				
				
			
				
				

				
				if (Rotation_Player_Check == false)
				{
					if (GetTargetAngle() > 0)
					{
						Rotation_Player_Plus = true;
					}

					else if (GetTargetAngle() < 0)
					{
						Rotation_Player_Mus = true;
					}
				}

				if (Rotation_Player_Plus == true)
				{
					Capsule->AddWorldRotation({ 0.0f,2.0f });

					if (GetTargetAngle() < 0)
					{
						Rotation_Player_Check = true;
						Rotation_Player_Mus = false;
						Rotation_Player_Plus = false;
					}

				}
				else if (Rotation_Player_Mus == true)
				{
					
					Capsule->AddWorldRotation({ 0.0f,-2.0f });

					if (GetTargetAngle() > 0)
					{
						Rotation_Player_Check = true;
						Rotation_Player_Mus = false;
						Rotation_Player_Plus = false;
					}
				}





				if (Rotation_Check_X == false)
				{
					if (degree_X > Actor_test->Transform.GetWorldRotationEuler().Y)
					{
						Rotation_Check_X_Plus = true;
					}
					else if (degree_X < Actor_test->Transform.GetWorldRotationEuler().Y)
					{
						Rotation_Check_X_Mus = true;
					}

				}

				if (Rotation_Check_X_Plus == true)
				{
					if (degree_X > Actor_test->Transform.GetWorldRotationEuler().Y)
					{
						Actor_test->Transform.AddLocalRotation({ 0.0f, 2.0f });
					}

					
				
					if (degree_X < Actor_test->Transform.GetWorldRotationEuler().Y )
					{

						Rotation_Check_X_Plus = false;
						Rotation_Check_X_Mus = false;
						Rotation_Check_X = true;
					}

				}
				else if (Rotation_Check_X_Mus == true)
				{

					if (degree_X < Actor_test->Transform.GetWorldRotationEuler().Y)
					{
						Actor_test->Transform.AddLocalRotation({ 0.0f,-2.0f });
					}
					
				
					if (degree_X > Actor_test->Transform.GetWorldRotationEuler().Y)
					{

						Rotation_Check_X_Mus = false;
						Rotation_Check_X_Plus = false;
						Rotation_Check_X = true;
									
					}

				}

				



				
				
				
				if (Rotation_Check_Y == false)
				{
					if (Actor_test->Transform.GetWorldRotationEuler().X == 0)
					{
						Rotation_Check_Y = true; 
					}


					if (Actor_test->Transform.GetWorldRotationEuler().X < 0)
					{
						Rotation_Check_Y_Plus = true;
					}
					else if (Actor_test->Transform.GetWorldRotationEuler().X > 0)
					{
						Rotation_Check_Y_Mus = true;
					}
				}


				if (Rotation_Check_Y_Plus == true)
				{
					Actor_test->Transform.AddLocalRotation({ 2.0f,0.0f });



					if (Actor_test->Transform.GetWorldRotationEuler().X >= 0)
					{

						Rotation_Check_Y_Plus = false;
						Rotation_Check_Y_Mus = false;
						Rotation_Check_Y = true;
					}

				}

				else if (Rotation_Check_Y_Mus == true)
				{

					Actor_test->Transform.AddLocalRotation({ -2.0f,0.0f });

					if (Actor_test->Transform.GetWorldRotationEuler().X <= 0)
					{
						Rotation_Check_Y_Mus = false;
						Rotation_Check_Y_Plus = false;
						Rotation_Check_Y = true;
						//_Parent->ChangeState(PlayerState::RockOn);				
					}

				}
				


			
				if (Rotation_Check_X == true && Rotation_Check_Y == true && Rotation_Player_Check == true)
				{

					


				

					if (true == GameEngineInput::IsPress('W', this))
					{

						PlayerStates.ChangeState(PlayerState::Move);
						return; 
						//Capsule->MoveForce({ float4::FORWARD * Speed }, GetTargetAngle());
					}

					else if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return; 
						//Capsule->MoveForce({ float4::BACKWARD * Speed }, GetTargetAngle());
					}

					else if (true == GameEngineInput::IsPress('A', this))
					{


						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
						//Capsule->MoveForce({ float4::LEFT * Speed }, GetTargetAngle());

					}

					else if (true == GameEngineInput::IsPress('D', this))
					{
						MainRenderer->ChangeAnimation("Walk_Right");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
						//Capsule->MoveForce({ float4::RIGHT * Speed });
					}
					

					else if (true == GameEngineInput::IsUp('W', this))
					{
						PlayerStates.ChangeState(PlayerState::Idle);
						return; 
					}
					else if (true == GameEngineInput::IsUp('S', this))
					{
						PlayerStates.ChangeState(PlayerState::Idle);
						return;
					}
					else if (true == GameEngineInput::IsUp('A', this))
					{
						PlayerStates.ChangeState(PlayerState::Idle);
						return;
					}
					else if (true == GameEngineInput::IsUp('D', this))
					{
						PlayerStates.ChangeState(PlayerState::Idle);
						return;
					}

					if (true == GameEngineInput::IsDown('Q', this))
					{
						PlayerStates.ChangeState(PlayerState::Idle);
						return;
					}

				}
			};

		PlayerStates.CreateState(PlayerState::RockOn, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_Forward");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}		
			};

		PlayerStates.CreateState(PlayerState::Forward_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_Behind");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Backward_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Right_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Left_Hit, NewPara);
	}






	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Forward");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Forward_Middle_Hit, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Behind");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Backward_Middle_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Right_Middle_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Left_Middle_Hit, NewPara);
	}



	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("String_Hit_Forward");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Forward_Big_Hit, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Start");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Up_Left);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Start, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Col->Collision(Enum_CollisionOrder::LadderTop))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Up_Stop_Left);
					return;
				}
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Up_Right);
					return;
				}
				


			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Left, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Col->Collision(Enum_CollisionOrder::LadderTop))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Up_Stop_Right);
					return;
				}




				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Up_Left);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Right, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Stop_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Stop_Left, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Stop_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Stop_Right, NewPara);
	}



	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Start");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Left);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Start, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Col->Collision(Enum_CollisionOrder::LadderBot))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Stop_Left);
					return;
				}
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Right);
					return;
				}



			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Left, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Col->Collision(Enum_CollisionOrder::LadderBot))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Stop_Right);
					return;
				}




				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Left);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Right, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Stop_Left");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Stop_Left, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Stop_Right");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Stop_Right, NewPara);
	}

	PlayerStates.ChangeState(PlayerState::Idle);



}