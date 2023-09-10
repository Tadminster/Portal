#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"
#include "Feature.h"
#include "Portal.h"


Portal::Portal()
{
	BluePortal = Actor::Create();
	BluePortal->LoadFile("PortalBlue.xml");
	OrangePortal = Actor::Create();
	OrangePortal->LoadFile("PortalOrange.xml");

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

	BluePortal->Update();
	OrangePortal->Update();
}

void Portal::LateUpdate(Player* player, Feature* wall)
{
	PortalInstall(wall);

	if (ActivateP[BlueP] == true and ActivateP[OrangeP] == true)
	{
		Portaling(player);
	}
	


}

void Portal::Render()
{
	BluePortal->Render();
	OrangePortal->Render();
}

void Portal::Portaling(Player* player) //��Ż �̵�
{

	//��Ż�� ���˽� �ݴ��� ��Ż�� �̵�
	if (player->GetActor()->Find("Body")->Intersect(BluePortal))
	{
		player->GetActor()->SetLocalPos(OrangePortal->GetWorldPos());
	}
	else if (player->GetActor()->Find("Body")->Intersect(OrangePortal))
	{
		player->GetActor()->SetLocalPos(BluePortal->GetWorldPos());
	}



}

void Portal::PortalInstall(Feature* wall) //��Ż ��ġ
{
	Ray Up;
	Up = Utility::MouseToRay();
	Vector3 Hit;
	
	//��Ŭ�� �����Ż ����
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		
		if (wall->GetActor()->Find("Mesh")->Intersect(Up, Hit))
		{
			BluePortal->SetLocalPos(Hit);
			ActivateP[BlueP] = true;
			
		}
	}

	//��Ŭ�� ��������Ż ����
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		if (wall->GetActor()->Find("Mesh")->Intersect(Up, Hit))
		{
			OrangePortal->SetLocalPos(Hit);
			ActivateP[OrangeP] = true;
			
		}
	}

	
}
