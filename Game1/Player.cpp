#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "ObjectManager.h"
#include "Player.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player.xml");
	actor->SetWorldPosY(5);

	moveSpeed = 20.0f;
	gun = Actor::Create();
	gun->LoadFile("Gun.xml");

	moveSpeed = 15.0f;
}

Player::~Player()
{
	actor->Release();
	gun->Release();
	
}

void Player::Init()
{
}

void Player::Update()
{

	lastPos = actor->GetWorldPos();

	// 플레이어 조작 (디버그 모드가 아닐때만)
	if (!GM->debugMode) Control();
	else dir = Vector3();

	if (state == PlayerState::IDLE)
	{
		
	}
	else if (state == PlayerState::RUN)
	{
		actor->MoveWorldPos(dir * moveSpeed * DELTA);
		
	}
	else if (state == PlayerState::JUMP)
	{
		actor->MoveWorldPos(dir * moveSpeed * DELTA);


		// 땅에 닿으면 JUMP -> IDLE
		if (OnGround)
		{
			state = PlayerState::IDLE;		
		}
	}
	else if (state == PlayerState::FIRE)
	{
	}

	// 땅에 닿아있으면 중력 0
	if (OnGround) gravity = 0;
	else
	{
		// 땅에 닿아있지 않으면 중력 증가 (최대 200)
		gravity = clamp( gravity - 50.0f * DELTA,-200.0f,200.0f);
		
		// 중력에 따라 플레이어 상하이동
		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	}

	if (bounceSpeed > 0)
	{
		actor->MoveWorldPos(bounceDir * bounceSpeed * DELTA);
		bounceSpeed = clamp(bounceSpeed - 20.0f * DELTA, 0.0f, 400.0f);
		if (OnGround) bounceSpeed = 0;
	}

	actor->Update();
	


	//플레이어 x축 범위 제한 -90도 ~ 90도

	float rotationX = actor->Find("Player2")->rotation.x;
	rotationX = max(-90.0f * ToRadian, min(90.0f * ToRadian, rotationX));
	actor->Find("Player2")->rotation.x = rotationX;

	//포탈건과 플레이어 위치와 로테이션 동기화
	
	actor->Find("LeftLeg")->rotation.x = actor->Find("Player2")->rotation.x;
	actor->Find("RightLeg")->rotation.x = -actor->Find("Player2")->rotation.x;

	gun->rotation.x = actor->Find("Player2")->rotation.x;
	gun->rotation.y = actor->rotation.y;

	
	


	gun->SetWorldPos(actor->Find("elbow")->GetWorldPos());
	gun->Update();
	gun->RenderHierarchy();
}

void Player::LateUpdate()
{
	// 모든 지형지물과 충돌 체크
	for (auto& it : OBJECT->GetStructures())
	{
		// 지형지물이 벽이면
		if (it->type == Wall)
		{
			// 벽과 부딪치면 이전 위치로 이동
			if (actor->Find("WallCol")->Intersect(it->GetActor()->Find("Mesh")))
			{
				actor->SetWorldPosX(lastPos.x);
				actor->SetWorldPosZ(lastPos.z);
				actor->Update();
			}
		}
	}

	for (auto& it : OBJECT->GetStructures())
	{
		// 지형지물이 바닥이면
		if (it->type == Floor)
		{
			// 지형지물의 Body와 플레이어의 Mesh가 충돌하면 땅에 닿아있는 것
			if (actor->Find("RightFoot")->Intersect(it->GetActor()->Find("Mesh")))
			{
				
				OnGround = true;

				break;
			}
			else OnGround = false;

		}
	}
	
}

void Player::Render()
{
	gun->Render();
	actor->Render();
}

void Player::Control()
{
	dir = Vector3();
	
	

	if (state == PlayerState::IDLE)
	{
		// IDLE -> RUN
		if (INPUT->KeyPress('W'))
		{
			dir += actor->GetForward();
			state = PlayerState::RUN;
		}
		if (INPUT->KeyPress('S'))
		{
			dir -= actor->GetForward();
			state = PlayerState::RUN;
		}

		if (INPUT->KeyPress('A'))
		{
			dir -= actor->GetRight();
			state = PlayerState::RUN;
		}
		if (INPUT->KeyPress('D'))
		{
			dir += actor->GetRight();
			state = PlayerState::RUN;
		}




		// IDLE -> JUMP
		if (INPUT->KeyDown(VK_SPACE))
		{
			Jump();
			state = PlayerState::JUMP;
		}

		// IDLE -> FIRE_BLUE_PORTAL
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			//this->FireBluePortal();
			//state = PlayerState::FIRE;
		}

		// IDLE -> FIRE_BLUE_PORTAL
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			//this->FireYellowPortal();
			//state = PlayerState::FIRE;
		}
	}
	else if (state == PlayerState::RUN)
	{
		// moving
		if (INPUT->KeyPress('W'))
		{
			dir += actor->GetForward();
		}
		if (INPUT->KeyPress('S'))
		{
			dir -= actor->GetForward();
		}

		if (INPUT->KeyPress('A'))
		{
			dir -= actor->GetRight();
		}
		 if (INPUT->KeyPress('D'))
		{
			dir += actor->GetRight();
		}

		// run -> idle
		if (!(INPUT->KeyPress('W') || INPUT->KeyPress('S') || INPUT->KeyPress('A') || INPUT->KeyPress('D')) )
		{
			state = PlayerState::IDLE;
		}

		// run -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			Jump();
			state = PlayerState::JUMP;
		}

		// RUN -> attack
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			//this->FireBluePortal();
			//state = PlayerState::FIRE;
		}

		// RUN -> FIRE_BLUE_PORTAL
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			//this->FireYellowPortal();
			//state = PlayerState::FIRE;
		}
	}
	else if (state == PlayerState::JUMP)
	{
		// jump 중 이동
		if (INPUT->KeyPress('W'))
		{
			dir += actor->GetForward();
		}
		else if (INPUT->KeyPress('S'))
		{
			dir -= actor->GetForward();
		}
		if (INPUT->KeyPress('A'))
		{
			dir -=	actor->GetRight();
		}
		else if (INPUT->KeyPress('D'))
		{
			dir += actor->GetRight();
		}

		// JUMP -> FIRE_BLUE_PORTAL
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			//this->FireBluePortal();
			//state = PlayerState::FIRE;
		}

		// RUN -> FIRE_YELLOW_PORTAL
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			//this->FireYellowPortal();
			//state = PlayerState::FIRE;
		}
	}
	else if (state == PlayerState::FIRE)
	{
		// FIRE 중 이동
		if (INPUT->KeyPress('W'))
		{
			dir = actor->GetForward();
		}
		else if (INPUT->KeyPress('S'))
		{
			dir = -actor->GetForward();
		}
		if (INPUT->KeyPress('A'))
		{
			dir = -actor->GetRight();
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = actor->GetRight();
		}
	}

}

void Player::FireBluePortal()
{
}

void Player::FireYellowPortal()
{
}

void Player::Jump()
{
	actor->SetWorldPos(actor->GetWorldPos() + Vector3(0, 0.1f, 0));
	OnGround = false;
	gravity = 25.0f;
}
