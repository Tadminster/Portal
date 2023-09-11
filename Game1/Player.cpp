#include "stdafx.h"
#include "ObProto.h"
#include "Feature.h"
#include "ObjectManager.h"
#include "Player.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player.xml");
	actor->SetWorldPosY(5);

	moveSpeed = 15.0f;
}

Player::~Player()
{
	actor->Release();
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
		actor->MoveWorldPos(dir * moveSpeed * 0.7f * DELTA);
	}

	// 땅에 닿아있으면 중력 0
	if (OnGround) gravity = 0;
	else
	{
		// 땅에 닿아있지 않으면 중력 증가 (최대 200)
		gravity = min(200.0f, gravity - 50.0f * DELTA);
		// 중력에 따라 플레이어 상하이동
		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	}

	actor->Update();
}

void Player::LateUpdate()
{
	// 모든 지형지물과 충돌 체크
	for (auto& feature : OBJECT->GetFeatures())
	{
		// 지형지물이 벽이면
		if (feature->type == Wall)
		{
			// 벽과 부딪치면 이전 위치로 이동
			if (actor->Find("Body")->Intersect(feature->GetActor()->Find("Mesh")))
			{
				actor->SetWorldPos(lastPos);
			}
		}
	}

	for (auto& feature : OBJECT->GetFeatures())
	{
		// 지형지물이 바닥이면
		if (feature->type == Floor)
		{
			// 지형지물의 Body와 플레이어의 Mesh가 충돌하면 땅에 닿아있는 것
			if (actor->Find("Body")->Intersect(feature->GetActor()->Find("Mesh")))
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
			dir = actor->GetForward();
			state = PlayerState::RUN;
		}
		else if (INPUT->KeyPress('S'))
		{
			dir = -actor->GetForward();
			state = PlayerState::RUN;
		}

		if (INPUT->KeyPress('A'))
		{
			dir = -actor->GetRight();
			state = PlayerState::RUN;
		}
		else if (INPUT->KeyPress('D'))
		{
			dir = actor->GetRight();
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

		// run -> idle
		if (!(INPUT->KeyPress('A') || INPUT->KeyPress('D')))
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
