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

				/*float4 A = Actor_test->Transform.GetWorldPosition() - float4{ Actor_test_02->Transform.GetWorldPosition().X, Actor_test_02->Transform.GetWorldPosition().Y - 400.0f, Actor_test_02->Transform.GetWorldPosition().Z };

				A.Normalize();

				if (Camera_Pos_Y <= 0)
				{
					if (PrevPos.Y < Mouse_Ro_Y && abs(Actor_test_02->Transform.GetLocalPosition().Z) >= abs(500))
					{
						Actor_test_02->Transform.AddWorldPosition(A * _DeltaTime * 2000);
					}

					else if (PrevPos.Y > Mouse_Ro_Y && abs(Actor_test_02->Transform.GetLocalPosition().Z) <= abs(1000))
					{
						Actor_test_02->Transform.AddWorldPosition(-A * _DeltaTime * 2000);
					}
				}*/

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


				//Player_Pos.X = Camera_Pos_X;
			};

		NewPara.Stay = [=](float _DeltaTime, class GameEngineState* _Parent)
			{
				
				//if (Rotation_Check == false)
				//{
				//	if (Angle > 0)
				//	{
				//		Rotation_Check_Plus = true;
				//	}
				//	else if (Angle < 0)
				//	{
				//		Rotation_Check_Mus = true;
				//	}
				//}
				//	if (Rotation_Check_Plus == true)
				//	{
				//		Capsule->AddWorldRotation({ 0.0f,5.0f });


				//		if (Angle < 0)
				//		{
				//			
				//			Rotation_Check_Plus = false;
				//			Rotation_Check_Mus = false;
				//			Rotation_Check = true;
				//			
				//			_Parent->ChangeState(PlayerState::Move);
				//			
				//			return;
				//		}

				//	}

				//	
				//	if (Rotation_Check_Mus == true)
				//	{
				//		Capsule->AddWorldRotation({ 0.0f,-5.0f });


				//		if (Angle > 0)
				//		{
				//			
				//			Rotation_Check_Mus = false;
				//			Rotation_Check_Plus = false;
				//			Rotation_Check = true;
				//			
				//			_Parent->ChangeState(PlayerState::Move);
				//		
				//			return;
				//		}

				//	}	

				//if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check ==true)
				//{
				//	Rotation_Check = false;
				//	PlayerStates.ChangeState(PlayerState::Roll_Forward);
				//	return;
				//}
				//if (GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	PlayerStates.ChangeState(PlayerState::Roll_Behind);
				//	return;
				//}
				//if (GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	PlayerStates.ChangeState(PlayerState::Roll_Left);
				//	return;
				//}
				//if (GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	PlayerStates.ChangeState(PlayerState::Roll_Right);
				//	return;
				//}

				//if (GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress(VK_SHIFT, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	PlayerStates.ChangeState(PlayerState::Run);
				//	return; 
				//}

				//if (GameEngineInput::IsPress(VK_RBUTTON, this))
				//{
				//	Rotation_Check = false;
				//	_Parent->ChangeState(PlayerState::Shield_Idle);
				//	return;
				//}
				//if (true == GameEngineInput::IsPress('W', this) && GameEngineInput::IsPress('C', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Slow_Walk_Forward");
				//	PlayerStates.ChangeState(PlayerState::Slow_Walk);
				//	return;
				//}

				//if (true == GameEngineInput::IsPress('S', this) && GameEngineInput::IsPress('C', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Slow_Walk_Behind");
				//	PlayerStates.ChangeState(PlayerState::Slow_Walk);
				//	return;
				//}

				//if (true == GameEngineInput::IsPress('A', this) && GameEngineInput::IsPress('C', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Slow_Walk_Left");
				//	PlayerStates.ChangeState(PlayerState::Slow_Walk);
				//	return;
				//}

				//if (true == GameEngineInput::IsPress('D', this) && GameEngineInput::IsPress('C', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Slow_Walk_Right");
				//	PlayerStates.ChangeState(PlayerState::Slow_Walk);
				//	return;
				//}

				//if (true == GameEngineInput::IsPress(VK_LBUTTON, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	_Parent->ChangeState(PlayerState::Attack_01);
				//	return;
				//}
				//if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	_Parent->ChangeState(PlayerState::Back_Step);
				//	return;

				//}
			
			

				//if (true == GameEngineInput::IsPress('W', this) && Rotation_Check == true)
				//{
				//	
				//	/*Capsule->setw
				//	Player_Pos*/
				//	
				//}

				//if (true == GameEngineInput::IsPress('S', this) && Rotation_Check == true)
				//{
				//	
				//	//Capsule->MoveForce({ float4::BACKWARD * Speed }, Capsule->GetDir());
				//
				//}

				if (true == GameEngineInput::IsPress('A', this) )
				{
					float ads = GetTargetAngle();
					float4 asd = GetTargetDirection();

					
					Capsule->MoveForce({ float4::LEFT * Speed },ads);
				
				}

				if (true == GameEngineInput::IsPress('D', this) )
				{
					float ads = GetTargetAngle();

					//Capsule->SetWorldRotation({ 0.0f, ads,0.0f });
					Capsule->MoveForce({ float4::RIGHT * Speed }, ads);
					
				}
				//if (GameEngineInput::IsPress(VK_CONTROL, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	_Parent->ChangeState(PlayerState::Parrying);
				//	return;
				//}

				//if (true == GameEngineInput::IsPress(VK_SPACE, this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	_Parent->ChangeState(PlayerState::Back_Step);
				//	return;
				//}
				//if (GameEngineInput::IsUp('A', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Left_Stop");
				//	PlayerStates.ChangeState(PlayerState::Move_Stop);
				//	return;
				//}
				//else if (GameEngineInput::IsUp('D', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Right_Stop");
				//	PlayerStates.ChangeState(PlayerState::Move_Stop);
				//	return;
				//}
				//else if (GameEngineInput::IsUp('W', this) && Rotation_Check == true)
				//{
				//	//Camera_Pos_X = Player_Pos.X;
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Forward_Stop");
				//	PlayerStates.ChangeState(PlayerState::Move_Stop);
				//	return;
				//}
				//else if (GameEngineInput::IsUp('S', this) && Rotation_Check == true)
				//{
				//	Rotation_Check = false;
				//	MainRenderer->ChangeAnimation("Behind_Stop");
				//	PlayerStates.ChangeState(PlayerState::Move_Stop);
				//	return;
				//}

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

	PlayerStates.ChangeState(PlayerState::Idle);



}