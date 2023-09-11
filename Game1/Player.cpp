#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player.xml");

	moveSpeed = 10.0f;
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
	}
	else if (state == PlayerState::FIRE)
	{
		actor->MoveWorldPos(dir * moveSpeed * 0.7f * DELTA);
	}

	// 중력가속도 (최대 200)
	//if (actor->Find("Body")->Intersect())
	//{
	//	gravity = min(200.0f, gravity - 30.0f * DELTA);
	//}

	// 중력
	actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

	actor->Update();
}

void Player::LateUpdate()
{
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
			this->Jump();
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
			actor->rotation.y -= DELTA;
			//dir = -actor->GetRight();
		}
		else if (INPUT->KeyPress('D'))
		{
			actor->rotation.y += DELTA;
			//dir = actor->GetRight();
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



}
