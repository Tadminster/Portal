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

	// �÷��̾� ���� (����� ��尡 �ƴҶ���)
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


		// ���� ������ JUMP -> IDLE
		if (OnGround)
		{
			state = PlayerState::IDLE;		
		}
	}
	else if (state == PlayerState::FIRE)
	{
	}

	// ���� ��������� �߷� 0
	if (OnGround) gravity = 0;
	else
	{
		// ���� ������� ������ �߷� ���� (�ִ� 200)
		gravity = clamp( gravity - 50.0f * DELTA,-200.0f,200.0f);
		
		// �߷¿� ���� �÷��̾� �����̵�
		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	}

	if (bounceSpeed > 0)
	{
		actor->MoveWorldPos(bounceDir * bounceSpeed * DELTA);
		bounceSpeed = clamp(bounceSpeed - 20.0f * DELTA, 0.0f, 400.0f);
		if (OnGround) bounceSpeed = 0;
	}

	actor->Update();
	


	//�÷��̾� x�� ���� ���� -90�� ~ 90��

	float rotationX = actor->Find("Player2")->rotation.x;
	rotationX = max(-90.0f * ToRadian, min(90.0f * ToRadian, rotationX));
	actor->Find("Player2")->rotation.x = rotationX;

	//��Ż�ǰ� �÷��̾� ��ġ�� �����̼� ����ȭ
	
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
	// ��� ���������� �浹 üũ
	for (auto& it : OBJECT->GetStructures())
	{
		// ���������� ���̸�
		if (it->type == Wall)
		{
			// ���� �ε�ġ�� ���� ��ġ�� �̵�
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
		// ���������� �ٴ��̸�
		if (it->type == Floor)
		{
			// ���������� Body�� �÷��̾��� Mesh�� �浹�ϸ� ���� ����ִ� ��
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
		// jump �� �̵�
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
		// FIRE �� �̵�
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
