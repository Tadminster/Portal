#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"
#include "Feature.h"
#include "ObjectManager.h"
#include "Portal.h"


Portal::Portal()
{
	BluePortal = Actor::Create();
	BluePortal->LoadFile("PortalBlue.xml");
	OrangePortal = Actor::Create();
	OrangePortal->LoadFile("PortalOrange.xml");

	BluePortal->visible = false;
	OrangePortal->visible = false;

	ActivateP[BlueP] = false;
	ActivateP[OrangeP] = false;

}

Portal::~Portal()
{
	BluePortal->Release();
	OrangePortal->Release();
}

void Portal::Init()
{
}

void Portal::Update()
{

	//���� ��Ż�� Ȱ���� Close �̹��� ����ȭ
	if (ActivateP[BlueP] == true and ActivateP[OrangeP] == true)
	{
		BluePortal->Find("Close")->visible = false;
		OrangePortal->Find("Close")->visible = false;

	}
	else
	{
		BluePortal->Find("Close")->visible = true;
		OrangePortal->Find("Close")->visible = true;
	}

	//��Ż �ʱ�ȭ
	if (INPUT->KeyPress(VK_F5))
	{
		BluePortal->visible = false;
		OrangePortal->visible = false;

		ActivateP[BlueP] = false;
		ActivateP[OrangeP] = false;
	}

	//��Ż Close �̹��� �ִϸ��̼�
	//BluePortal->Find("Close")

	BluePortal->Update();
	OrangePortal->Update();
}

void Portal::LateUpdate()
{
	PortalInstall();

	if (ActivateP[BlueP] == true and ActivateP[OrangeP] == true)
	{
		Portaling();
	}
}

void Portal::Render()
{
	BluePortal->Find("Close")->mesh->AnimationDown();
	OrangePortal->Find("Close")->mesh->AnimationUp();
	BluePortal->Render();
	OrangePortal->Render();
}

void Portal::Portaling() //��Ż �̵�
{

	//��Ż�� ���˽� �ݴ��� ��Ż�� �̵�
	if (PLAYER->GetActor()->Find("Body")->Intersect(BluePortal->Find("PortalBlue")))
	{
		PLAYER->GetActor()->SetLocalPos(OrangePortal->GetWorldPos() + Vector3(0,3,-3));
		PLAYER->GetActor()->rotation.y += OrangePortal->rotation.y + 180 * ToRadian;
	}
	else if (PLAYER->GetActor()->Find("Body")->Intersect(OrangePortal->Find("PortalOrange")))
	{
		PLAYER->GetActor()->SetLocalPos(BluePortal->GetWorldPos() + Vector3(0, 3, -3));
		PLAYER->GetActor()->rotation.y += BluePortal->rotation.y + 180 * ToRadian;
	}

}

void Portal::PortalInstall() //��Ż ��ġ
{
	Ray Up;
	Up = Utility::MouseToRay();
	Vector3 Hit;
	
	//��Ŭ�� �����Ż ����
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		for (auto& feature : OBJECT->GetFeatures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit))
			{
				BluePortal->visible = true;
				BluePortal->SetLocalPos(Hit + Vector3(0, 0, -0.01));
				ActivateP[BlueP] = true;
			}
		}
	}

	//��Ŭ�� ��������Ż ����
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		for (auto& feature : OBJECT->GetFeatures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit))
			{
				OrangePortal->visible = true;
				OrangePortal->SetLocalPos(Hit + Vector3(0,0,-0.01));
				ActivateP[OrangeP] = true;
			}
		}
	}
}
