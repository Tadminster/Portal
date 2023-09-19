#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Cube.h"

Cube::Cube()
{
	actor = Actor::Create();
	actor->LoadFile("PortalCube.xml");
	actor->SetWorldPos(Vector3(100, 10, -30));
}

Cube::~Cube()
{
	actor->Release();
}

void Cube::Init()
{
}

void Cube::Update()
{
	lastPos = actor->GetWorldPos();

	Catch();


	if (isCatched == true)
	{
		actor->MoveWorldPos(PLAYER->GetActor()->Find("BodyCam")->GetWorldPos() + PLAYER->GetActor()->Find("BodyCam")->GetForward() * 10 - lastPos);
		//actor->SetWorldPos(PLAYER->GetActor()->Find("BodyCam")->GetWorldPos() +PLAYER->GetActor()->Find("BodyCam")->GetForward()*10);
		actor->rotation =PLAYER->GetActor()->rotation;
	}
	else
	{
		if (OnGround)
		{		
			gravity = 0;		
		}
		else
		{
			
			// ���� ������� ������ �߷� ���� (�ִ� 200)
			gravity = clamp(gravity - 50.0f * DELTA, -200.0f, 200.0f);
			if (!(PLAYER->GetState() == PlayerState::SPAWN))
			{
				// �߷¿� ����  �����̵�
				actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

			}
			
		}
	}
	
	if (bounceSpeed > 0)
	{
		actor->MoveWorldPos(bounceDir * bounceSpeed * DELTA);
		bounceSpeed = clamp(bounceSpeed - 20.0f * DELTA, 0.0f, 400.0f);
		if (OnGround) bounceSpeed = 0;
	}

	actor->Update();
}

void Cube::LateUpdate()
{
	// ��� ���������� �浹 üũ
	for (auto& feature : OBJECT->GetStructures())
	{
		// ���������� ���̸�
		if (feature->type == Wall)
		{
			// ���� �ε�ġ�� ���� ��ġ�� �̵�
			if (actor->Find("Mesh")->Intersect(feature->GetActor()->Find("Mesh")))
			{
				actor->SetWorldPosX(lastPos.x);
				actor->SetWorldPosZ(lastPos.z);
				actor->Update();
			}
		}
	}

	for (auto& feature : OBJECT->GetStructures())
	{
		// ���������� �ٴ��̸�
		if (feature->type == Floor)
		{
			// ���������� Body�� �÷��̾��� Mesh�� �浹�ϸ� ���� ����ִ� ��
			if (actor->Find("Mesh")->Intersect(feature->GetActor()->Find("Mesh")))
			{
				actor->SetWorldPosY(lastPos.y);
				actor->Update();
				
				
				
				OnGround = true;
				break;
			}
			else OnGround = false;
		}
	}
}

void Cube::Render()
{
	actor->Render();
}

void Cube::Catch()
{
	Ray Up;
	Up = Utility::MouseToRay();
	Up.direction.Normalize();
	Up.direction *=5;

	Vector3 Hit;

	// E������ ť�� ���
	if (INPUT->KeyDown('E') and actor->Find("Mesh")->Intersect(Up, Hit) and
		PLAYER->GetActor()->Find("CatchRange")->Intersect(actor->Find("Mesh")))
	{
		
		if (PLAYER->isCatch == false)
		{
			PLAYER->isCatch = true;
			isCatched = true;
			actor->SetWorldPos(PLAYER->GetActor()->Find("BodyCam")->GetWorldPos() + PLAYER->GetActor()->Find("BodyCam")->GetForward() * 10);
		}
		else if(PLAYER->isCatch == true)
		{
			PLAYER->isCatch = false;
			isCatched = false;
		}
	}
}
