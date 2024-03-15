#include "PreCompile.h"
#include "Player.h"
#include "BaseActor.h"
#include "BoneSocketCollision.h"
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
				Sword.ResetRecord();
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
				
			
				//Capsule->SetWorldRotation({ 0.0f,Capsule->GetDir(),0.0f });
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
					


				if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X ==true && Stamina > 0)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Forward);
					return;
				}
				else if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Behind);
					return;
				}
				else if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Left);
					return;
				}
				else if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					PlayerStates.ChangeState(PlayerState::Roll_Right);
					return;
				}

				else if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this) && Rotation_Check_X == true && Stamina > 0)
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
				else if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}
				else if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Rotation_Check_X == true && Rock_On_Check == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Attack_01);
					return;
				}

				else if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Back_Step);
					return;

				}

				else if (true == GameEngineInput::IsPress('W', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					//Capsule->MoveForce({ float4::FORWARD * Speed},Capsule->GetDir());
					//Capsule->SetWorldRotation({ 0.0f,180.0f,0.0f });
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					//MainRenderer->ChangeAnimation("Walk_Forward");
					//Capsule->MoveForce({ float4::BACKWARD * Speed }, Capsule->GetDir());
					//Capsule->SetWorldRotation({ 0.0f,180.0f,0.0f });
				}
				else if (true == GameEngineInput::IsPress('A', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					//Capsule->MoveForce({ float4::LEFT * Speed }, Capsule->GetDir());
					//Capsule->SetWorldRotation({ 0.0f,180.0f,0.0f });
				}
				else if (true == GameEngineInput::IsPress('D', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					//Capsule->MoveForce({ float4::RIGHT * Speed }, Capsule->GetDir());
					//Capsule->SetWorldRotation({ 0.0f,180.0f,0.0f });
				}
			
				else if (true == GameEngineInput::IsPress('W', this)&& Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Forward");
					//Capsule->MoveForce({ float4::FORWARD * Speed } , degree_X);
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rock_On_Check ==true)
				{				
					//MainRenderer->ChangeAnimation("Walk_Forward");
					//Capsule->MoveForce({ float4::BACKWARD * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('A', this) && Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Left");
					//Capsule->MoveForce({ float4::LEFT * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('D', this) && Rock_On_Check == true)
				{
					MainRenderer->ChangeAnimation("Walk_Right");
					//Capsule->MoveForce({ float4::RIGHT * Speed }, degree_X);
				}
				

				else if (GameEngineInput::IsPress(VK_CONTROL, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Parrying);
					return;
				}

				else if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check_X == true && Stamina > 0)
				{
					Rotation_Check_X = false;
					_Parent->ChangeState(PlayerState::Back_Step);
					return;
				}



				if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('A', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					Capsule->MoveForce({ float4{-1.0f, 0.0f,1.0f,} * Speed }, Capsule->GetDir());
				}
				else if (true == GameEngineInput::IsPress('W', this) && true == GameEngineInput::IsPress('D', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					Capsule->MoveForce({ float4{1.0f, 0.0f,1.0f,} *Speed }, Capsule->GetDir());
				}
				else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('A', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					Capsule->MoveForce({ float4{-1.0f, 0.0f,-1.0f,} *Speed }, Capsule->GetDir());
				}
				else if (true == GameEngineInput::IsPress('S', this) && true == GameEngineInput::IsPress('D', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					Capsule->MoveForce({ float4{1.0f, 0.0f,-1.0f,} *Speed }, Capsule->GetDir());
				}


				else if (true == GameEngineInput::IsPress('W', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					
					Capsule->MoveForce({ float4::FORWARD * Speed }, Capsule->GetDir());
					
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					
					Capsule->MoveForce({ float4::BACKWARD * Speed }, Capsule->GetDir());
					
					}
				else if (true == GameEngineInput::IsPress('A', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
				
					Capsule->MoveForce({ float4::LEFT * Speed }, Capsule->GetDir());
				
					}
				else if (true == GameEngineInput::IsPress('D', this) && Rotation_Check_X == true && Rock_On_Check == false)
				{
					
					Capsule->MoveForce({ float4::RIGHT * Speed }, Capsule->GetDir());
				
				}

				else if (true == GameEngineInput::IsPress('W', this) && Rock_On_Check == true)
				{
					Capsule->MoveForce({ float4::FORWARD * Speed }, degree_X);
				}

				else if (true == GameEngineInput::IsPress('S', this) && Rock_On_Check == true)
				{		
					Capsule->MoveForce({ float4::BACKWARD * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('A', this) && Rock_On_Check == true)
				{		
					Capsule->MoveForce({ float4::LEFT * Speed }, degree_X);
				}
				else if (true == GameEngineInput::IsPress('D', this) && Rock_On_Check == true)
				{	
					Capsule->MoveForce({ float4::RIGHT * Speed }, degree_X);
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
				if (GameEngineInput::IsPress(VK_CONTROL, this) && Rotation_Check_X == true && Stamina > 0)
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
				//Capsule->SetWorldRotation({ 0.0f,Capsule->GetDir()});


				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
				}

				if (GameEngineInput::IsPress(VK_CONTROL, this) && Stamina > 0)
				{
					_Parent->ChangeState(PlayerState::Parrying);
					return;
				}

				if (GameEngineInput::IsPress(VK_RBUTTON, this) && Stamina > 0)
				{
					_Parent->ChangeState(PlayerState::Shield_Idle);
					return;
				}

				if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Stamina > 0)
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
			StateValue = PlayerState::StaminaCheck;
		};


	NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{
			// 임시 지정 값 
			Stamina -= _DeltaTime * 10;

			if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this))
			{
				Capsule->MoveForce({ float4::FORWARD * Speed * 1.5 });
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
			Sword.ResetRecord();
			MainRenderer->ChangeAnimation("Attack_01");
			StateValue = PlayerState::StaminaCheck;
			Stamina -= 20;
		};


	NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
		{
			if (MainRenderer->GetCurAnimationFrame() >= 13)
			{
				if (MainRenderer->GetCurAnimationFrame() <= 16)
				{
					Attack_Col->On();
				}
			}
			if  (MainRenderer->GetCurAnimationFrame() > 16)
			{
				Attack_Col->Off();
			}



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
					Attack_Col->Off();
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20 && Stamina > 0)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_02);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						Attack_Col->Off();
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
				Sword.ResetRecord();
				MainRenderer->ChangeAnimation("Attack_02");
				StateValue = PlayerState::StaminaCheck;
				Stamina -= 20;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (MainRenderer->GetCurAnimationFrame() >= 14)
				{
					if (MainRenderer->GetCurAnimationFrame() <= 18)
					{
						Attack_Col->On();
					}

				}
				if (MainRenderer->GetCurAnimationFrame() > 18)
				{
					Attack_Col->Off();
				}


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
					Attack_Col->Off();
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20 && Stamina > 0)
				{

					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_03);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						Attack_Col->Off();
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
				Sword.ResetRecord();
				MainRenderer->ChangeAnimation("Attack_03");
				StateValue = PlayerState::StaminaCheck;
				Stamina -= 20;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (MainRenderer->GetCurAnimationFrame() >= 13)
				{
					if (MainRenderer->GetCurAnimationFrame() <= 15)
					{
						Attack_Col->On();
					}

				}
				if (MainRenderer->GetCurAnimationFrame() > 15)
				{
					Attack_Col->Off();
				}

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
					Attack_Col->Off();
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}


				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 20 && Stamina > 0)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_04);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						Attack_Col->Off();
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
				Sword.ResetRecord();
				MainRenderer->ChangeAnimation("Attack_04");
				StateValue = PlayerState::StaminaCheck;
				Stamina -= 15;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (MainRenderer->GetCurAnimationFrame() >= 16)
				{
					if (MainRenderer->GetCurAnimationFrame() <= 19)
					{
						Attack_Col->On();
					}

				}

				if (MainRenderer->GetCurAnimationFrame() > 19)
				{ 
					Attack_Col->Off();
				}
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
					Attack_Col->Off();
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				else if (Attack_Check == true && MainRenderer->GetCurAnimationFrame() > 30 && Stamina > 0)
				{
					Attack_Check = false;
					PlayerStates.ChangeState(PlayerState::Attack_01);
					return;
				}

				if (MainRenderer->GetCurAnimationFrame() > 20)
				{
					if (true == GameEngineInput::IsPress('W', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('S', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Behind");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('A', this))
					{
						Attack_Col->Off();
						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;
					}

					if (true == GameEngineInput::IsPress('D', this))
					{
						Attack_Col->Off();
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
				Weapon_Actor->Getweapon()->Off(); 
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
					Weapon_Actor->Getweapon()->On();
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
				StateValue = PlayerState::StaminaCheck;

			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
			
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });

					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed }, degree_X);
					}
				}

				else 
				{
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed });
					}
				}

				if (MainRenderer->GetCurAnimationFrame() < 15)
				{
					Body_Col->Off(); 
				}
				else if (MainRenderer->GetCurAnimationFrame() > 15)
				{
					Body_Col->On();
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
				StateValue = PlayerState::StaminaCheck;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				

			    if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::FORWARD * Speed }, degree_X);
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::FORWARD * Speed });
					}
				}


				if (MainRenderer->GetCurAnimationFrame() < 15)
				{
					Body_Col->Off();
				}
				else if (MainRenderer->GetCurAnimationFrame() > 15)
				{
					Body_Col->On();
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
				MainRenderer->ChangeAnimation("Roll_Right");
				StateValue = PlayerState::StaminaCheck;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (Rock_On_Check == true)
				{
			
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::LEFT * Speed  });
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::LEFT * Speed });
					}

					
				}

				if (MainRenderer->GetCurAnimationFrame() < 23)
				{
					Body_Col->Off();
				}
				else if (MainRenderer->GetCurAnimationFrame() > 15)
				{
					Body_Col->On();
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
				MainRenderer->ChangeAnimation("Roll_Left");
				StateValue = PlayerState::StaminaCheck;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::RIGHT * Speed  });
					}
				}

				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 20)
					{
						Capsule->MoveForce({ float4::RIGHT * Speed  });
					}
				}


				if (MainRenderer->GetCurAnimationFrame() < 23)
				{
					Body_Col->Off();
				}
				else if (MainRenderer->GetCurAnimationFrame() > 15)
				{
					Body_Col->On();
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
				StateValue = PlayerState::StaminaCheck;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{

				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });

					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed * float(1.2) });
					}
				}
				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 10)
					{
						Capsule->MoveForce({ float4::BACKWARD * Speed * float(1.2) });
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
				Shield_Col->On();
				MainRenderer->ChangeAnimation("Shield_Idle");
				StateValue = PlayerState::Shield_Idle;
				
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Shield_Col->Collision(Enum_CollisionOrder::MonsterAttack))
				{
					PlayerStates.ChangeState(PlayerState::Weak_Shield_block);
					return; 
				}
				
				

				if (true == GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					Shield_Col->Off(); 
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

				StateValue = PlayerState::Parrying;
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				

				if (MainRenderer->GetCurAnimationFrame() < 14)
				{
					Shield_Col->On();
				}
				if (MainRenderer->GetCurAnimationFrame() > 14)
				{
					Shield_Col->Off();
				}

				

				if (MainRenderer->IsCurAnimationEnd())
				{
					StateValue = PlayerState::Idle;
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








				if((degree_X > 0 && Actor_test->Transform.GetWorldRotationEuler().Y > 0) || (degree_X < 0 && Actor_test->Transform.GetWorldRotationEuler().Y < 0))
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
							Actor_test->Transform.AddLocalRotation({ 0.0f, 5.0f });
						}



						if (degree_X < Actor_test->Transform.GetWorldRotationEuler().Y)
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
							Actor_test->Transform.AddLocalRotation({ 0.0f,-5.0f });
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
				
				
				
				
				}
				else
				{
					Rock_On_Check = false;
					return;
				}
				




				if (Rotation_Check_X == true && Rotation_Check_Y == true && Rotation_Player_Check == true)
				{






					if (true == GameEngineInput::IsPress('W', this))
					{

						PlayerStates.ChangeState(PlayerState::Move);
						return;

					}

					else if (true == GameEngineInput::IsPress('S', this))
					{
						MainRenderer->ChangeAnimation("Walk_Forward");
						PlayerStates.ChangeState(PlayerState::Move);
						return;

					}

					else if (true == GameEngineInput::IsPress('A', this))
					{


						MainRenderer->ChangeAnimation("Walk_Left");
						PlayerStates.ChangeState(PlayerState::Move);
						return;


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
				MainRenderer->ChangeAnimation("Hit_Forward",true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}		

				Capsule->SetWorldRotation({ 0.0f,degree_X });

			};

		PlayerStates.CreateState(PlayerState::Forward_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_Behind", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				//Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Backward_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_right", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				//Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Right_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Hit_Left", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				//Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Left_Hit, NewPara);
	}






	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Forward", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Forward_Middle_Hit, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Behind", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Backward_Middle_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Right", true);
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Right_Middle_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Hit_Left", true);
				Capsule->SetWorldRotation({ 0.0f,degree_X });
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				Capsule->SetWorldRotation({ 0.0f,degree_X });
			};

		PlayerStates.CreateState(PlayerState::Left_Middle_Hit, NewPara);
	}



	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("String_Hit_Forward");
				Body_Col->Off(); 
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Body_Col->On(); 
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				
				

				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });

					if (MainRenderer->GetCurAnimationFrame() < 15)
					{
						Capsule->MoveForce({ 0.0f,0.0f,-600.0f }, degree_X);

					}
				}
				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 15)
					{
						Capsule->MoveForce({ 0.0f,0.0f,-600.0f }, Capsule->GetDir());
					}
				}




			};

		PlayerStates.CreateState(PlayerState::Forward_Big_Hit, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				// 애니메이션 터짐
				MainRenderer->ChangeAnimation("String_Hit_Behind");
				Body_Col->Off();
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Body_Col->On();
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				if (Rock_On_Check == true)
				{
					Capsule->SetWorldRotation({ 0.0f,degree_X });
					Actor_test->Transform.SetLocalRotation({ 0.0f,degree_X });

					if (MainRenderer->GetCurAnimationFrame() < 15)
					{
						Capsule->MoveForce({ 0.0f,0.0f,-600.0f }, degree_X);

					}
				}
				else
				{
					if (MainRenderer->GetCurAnimationFrame() < 15)
					{
						Capsule->MoveForce({ 0.0f,0.0f,600.0f }, Capsule->GetDir());
					}
				}

				
			};

		PlayerStates.CreateState(PlayerState::Backward_Big_Hit, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Up_Start");
				Capsule->GravityOff();

			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					if (GameEngineInput::IsPress('W', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Up_Left);
						return;
					}

					
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Start, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				StateValue = PlayerState::ladder_Up_Left;
				MainRenderer->ChangeAnimation("ladder_Up_Left");
				Capsule->GravityOff();
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
			
				Body_Col->CollisionEvent(Enum_CollisionOrder::LabberMiddle, Labber_Middle_Event);

				

				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					if (GameEngineInput::IsPress('W', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Up_Right);
						return;
					}

					if (GameEngineInput::IsPress('S', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Down_Right);
						return;
					}
					
				}
				


			};

		PlayerStates.CreateState(PlayerState::ladder_Up_Left, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				StateValue = PlayerState::ladder_Up_Right;
				MainRenderer->ChangeAnimation("ladder_Up_Right");
				Capsule->GravityOff();
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				Body_Col->CollisionEvent(Enum_CollisionOrder::LabberMiddle, Labber_Middle_Event);

				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					if (GameEngineInput::IsPress('W', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Up_Left);
						return;
					}	

					if (GameEngineInput::IsPress('S', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Down_Left);
						return;
					}


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
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					Capsule->GravityOn();
					Rabber_Collision_Check = false;
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
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					Capsule->GravityOn();
					Rabber_Collision_Check = false;;
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
				Capsule->GravityOff();
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

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
				if (Body_Col->Collision(Enum_CollisionOrder::LadderBot))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Stop_Left);
					return;
				}
				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);



					if (GameEngineInput::IsPress('W', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Up_Right);
						return;
					}
					if (GameEngineInput::IsPress('S', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Down_Right);
						return;
					}
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
				if (Body_Col->Collision(Enum_CollisionOrder::LadderBot))
				{
					PlayerStates.ChangeState(PlayerState::ladder_Down_Stop_Right);
					return;
				}

				


				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					if (GameEngineInput::IsPress('W', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Up_Left);
						return;
					}
					if (GameEngineInput::IsPress('S', this))
					{
						PlayerStates.ChangeState(PlayerState::ladder_Down_Left);
						return;
					}
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Right, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("ladder_Down_Stop_Left");
				//Capsule->MoveForce({ 0.0f,200.0f,0.0f }, Capsule->GetDir());
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					Capsule->GravityOn();
					Rabber_Collision_Check = false;
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
				//Capsule->MoveForce({ 0.0f,200.0f,0.0f }, Capsule->GetDir());
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z | Enum_Axies::Y);

					Capsule->GravityOn();
					Rabber_Collision_Check = false; 
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::ladder_Down_Stop_Right, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Death");			
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				
			};

		PlayerStates.CreateState(PlayerState::Death, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Weak_Shield_block",true);
				StateValue = PlayerState::Shield_Idle;

				Shield_Col->On(); 
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (Shield_Col->Collision(Enum_CollisionOrder::MonsterAttack))
				{
					PlayerStates.ChangeState(PlayerState::Weak_Shield_block);
					return;
				}


				if (MainRenderer->IsCurAnimationEnd())
				{
				
					
					PlayerStates.ChangeState(PlayerState::Shield_Idle);
					return;
				};
				
				if (GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					Shield_Col->Off();
					Body_Col->On(); 
					PlayerStates.ChangeState(PlayerState::Idle);
					return; 
				}


			};
		PlayerStates.CreateState(PlayerState::Weak_Shield_block, NewPara);
	}


	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Middle_Shield_block");
				StateValue = PlayerState::Shield_Idle;
				Shield_Col->On();
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{

					//Shield_Col->Off();
					PlayerStates.ChangeState(PlayerState::Shield_Idle);
					return;
				};

				if (GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					Shield_Col->Off();
					Body_Col->On();
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

			};
		PlayerStates.CreateState(PlayerState::Middle_Shield_block, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				Shield_Col->On();
				MainRenderer->ChangeAnimation("Big_Shield_block");
				StateValue = PlayerState::Shield_Idle;

			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Shield_Idle);
					return;
				};

				if (GameEngineInput::IsUp(VK_RBUTTON, this))
				{
					Body_Col->On();
					Shield_Col->Off();
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}

				
			};

		PlayerStates.CreateState(PlayerState::Big_Shield_block, NewPara);
	}

	{
		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				
				MainRenderer->ChangeAnimation("Parry_Attack");
			};


		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Parring_Attack, NewPara);
	}

	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				
				MainRenderer->ChangeAnimation("Attack_Block");

			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					Sword.ResetRecord();
					SetFlag(Enum_ActorFlag::Block_Shield, false);
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Attack_Block, NewPara);


	}


	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Sit_Down");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					if (GameEngineInput::IsDown('W',this))
					{
						PlayerStates.ChangeState(PlayerState::Stand_Up);
						return;
					}
				}
				
			};

		PlayerStates.CreateState(PlayerState::Sit_Down, NewPara);


	}

	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Stand_Up");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Stand_Up, NewPara);


	}

	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Stand_Up");
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::Stand_Up, NewPara);


	}

	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("Fail");
				testaaa = false;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (testaaa == true)
				{
					PlayerStates.ChangeState(PlayerState::landing);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::fail, NewPara);
	}

	{

		CreateStateParameter NewPara;

		NewPara.Start = [=](class GameEngineState* _Parent)
			{
				MainRenderer->ChangeAnimation("landing");
				testaaa = false;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				if (MainRenderer->IsCurAnimationEnd())
				{
					PlayerStates.ChangeState(PlayerState::Idle);
					return;
				}
			};

		PlayerStates.CreateState(PlayerState::landing, NewPara);
	}




	PlayerStates.ChangeState(PlayerState::Idle);



}

void Player::SoundFrameEvent()
{
	// walk 
	MainRenderer->SetFrameEvent("Walk_Forward", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});
	MainRenderer->SetFrameEvent("Walk_Forward", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Forward", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-armor-2.wav", BoneWorldPos(0), 0.1f);		
		});

	MainRenderer->SetFrameEvent("Walk_Behind", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});
	MainRenderer->SetFrameEvent("Walk_Behind", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Behind", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-armor-2.wav", BoneWorldPos(0), 0.1f);
		});

	MainRenderer->SetFrameEvent("Walk_Right", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});
	MainRenderer->SetFrameEvent("Walk_Right", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Right", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-armor-2.wav", BoneWorldPos(0), 0.1f);
		});


	MainRenderer->SetFrameEvent("Walk_Left", 7, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});
	MainRenderer->SetFrameEvent("Walk_Left", 18, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0));
		});

	MainRenderer->SetFrameEvent("Walk_Left", 15, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-armor-2.wav", BoneWorldPos(0), 0.1f);
		});

	// roll

	MainRenderer->SetFrameEvent("Roll_Behind", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-hauberk-rolling.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Roll_Right", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-hauberk-rolling.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Roll_Left", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-hauberk-rolling.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Roll_Forward", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-hauberk-rolling.wav", BoneWorldPos(0), 0.3f);
		});

	MainRenderer->SetFrameEvent("Back_Step", 0, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("body-hauberk-rolling.wav", BoneWorldPos(0), 0.3f);
		});


	// Attack

	MainRenderer->SetFrameEvent("Attack_02", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("swing-sword.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Attack_01", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("swing-sword2.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Attack_03", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("swing-sword-large.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Attack_04", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("swing-sword2.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Attack_05", 13, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("swing-sword-large.wav", BoneWorldPos(0), 0.3f);
		});

	// shield

	MainRenderer->SetFrameEvent("Shield_Idle", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("movement2.wav", BoneWorldPos(0), 0.3f);
		});
	MainRenderer->SetFrameEvent("Parrying", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("c000004950.wav", BoneWorldPos(0), 0.3f);
		});



	// moveStop


	MainRenderer->SetFrameEvent("Left_Stop", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0), 0.7f);
		});
	MainRenderer->SetFrameEvent("Behind_Stop", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0), 0.7f);
		});
	MainRenderer->SetFrameEvent("Right_Stop", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0), 0.7f);
		});
	MainRenderer->SetFrameEvent("Forward_Stop", 1, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("foot-stone-wa2.wav", BoneWorldPos(0), 0.7f);
		});


	// drink 
	MainRenderer->SetFrameEvent("Portion_Drink_01", 20, [&](GameContentsFBXRenderer* _Renderer)
		{
			GameEngineSound::Sound3DPlay("EST-drink.wav", BoneWorldPos(0), 1.0f);
		});

	
}

float4 Player::BoneWorldPos(int _BoneIndex)
{
	std::vector<float4x4>& BoneMats = MainRenderer->GetBoneSockets();
	float4x4 BoneMatrix = BoneMats.at(_BoneIndex);

	float4x4 BoneWMat = BoneMatrix * Transform.GetWorldMatrix();
	float4 S;
	float4 R;
	float4 P;
	BoneWMat.Decompose(S, R, P);

	return P;
}