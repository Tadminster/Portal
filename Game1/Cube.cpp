#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "ObjectManager.h"
#include "Cube.h"

Cube::Cube()
{
	actor = Actor::Create();
	actor->LoadFile("PortalCube.xml");
	
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
	if (OnGround) gravity = 0;
	else
	{
		// ���� ������� ������ �߷� ���� (�ִ� 200)
		gravity = clamp(gravity - 50.0f * DELTA, -200.0f, 200.0f);

		// �߷¿� ���� �÷��̾� �����̵�
		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
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
