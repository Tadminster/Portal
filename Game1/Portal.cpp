#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"
#include "Feature.h"
#include "ObjectManager.h"
#include "Portal.h"


Portal::Portal()
{
	bluePortal = Actor::Create();
	bluePortal->LoadFile("PortalBlue.xml");
	orangePortal = Actor::Create();
	orangePortal->LoadFile("PortalOrange.xml");

	ui = Actor::Create();
	ui->LoadFile("ui.xml");


	bluePortal->visible = false;
	orangePortal->visible = false;

	activateP[BlueP] = false;
	activateP[OrangeP] = false;

}

Portal::~Portal()
{
	bluePortal->Release();
	orangePortal->Release();
}

void Portal::Init()
{
}

void Portal::Update()
{

	ui->RenderHierarchy();

	//���� ��Ż�� Ȱ���� Close �̹��� ����ȭ
	if (activateP[BlueP] == true and activateP[OrangeP] == true)
	{
		bluePortal->Find("Close")->visible = false;
		orangePortal->Find("Close")->visible = false;
		
	}
	else
	{
		bluePortal->Find("Close")->visible = true;
		orangePortal->Find("Close")->visible = true;

	}

	//��Ż �ʱ�ȭ
	if (INPUT->KeyPress(VK_F5))
	{
		bluePortal->visible = false;
		orangePortal->visible = false;

		activateP[BlueP] = false;
		activateP[OrangeP] = false;
	}

	//cout << orangePortal->Find("PortalOrange")->GetForward().x <<"  "
	//<< orangePortal->Find("PortalOrange")->GetForward().y<< "  "
	//<< orangePortal->Find("PortalOrange")->GetForward().z << endl;
	//��Ż Close �̹��� �ִϸ��̼�
	//bluePortal->Find("Close")

	bluePortal->Update();
	orangePortal->Update();
	ui->Update();
}

void Portal::LateUpdate()
{
	PortalInstall();

	if (activateP[BlueP] == true and activateP[OrangeP] == true)
	{
		Portaling();
	}
}

void Portal::Render()
{
	bluePortal->Find("Close")->mesh->AnimationDown();
	orangePortal->Find("Close")->mesh->AnimationUp();
	bluePortal->Render();
	orangePortal->Render();
	ui->Render();
}

void Portal::Portaling() //��Ż �̵�
{

	//��Ż�� ���˽� �ݴ��� ��Ż�� �̵�
	if (PLAYER->GetActor()->Find("Body")->Intersect(bluePortal->Find("PortalBlue")))
	{
		PLAYER->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
			+ orangePortal->Find("PortalOrange")->GetForward() * -5);
		PLAYER->GetActor()->rotation.y += orangePortal->rotation.y  - bluePortal->rotation.y +180*ToRadian;
		
	}
	else if (PLAYER->GetActor()->Find("Body")->Intersect(orangePortal->Find("PortalOrange")))
	{
		PLAYER->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
			+ bluePortal->Find("PortalBlue")->GetForward() * -5);
		PLAYER->GetActor()->rotation.y += bluePortal->rotation.y  - orangePortal->rotation.y + 180 * ToRadian;
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
				
				bluePortal->visible = true;
				bluePortal->rotation = feature->GetActor()->rotation + Vector3(-90*ToRadian,0,0);
				bluePortal->SetLocalPos(Hit);
				bluePortal->Find("PortalBlue")->SetLocalPosZ(
					bluePortal->Find("PortalBlue")->GetLocalPos().z - 0.01f);
					activateP[BlueP] = true;
				
				
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
				
					orangePortal->visible = true;					
					orangePortal->rotation = feature->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
					orangePortal->SetLocalPos(Hit);
					orangePortal->Find("PortalOrange")->SetLocalPosZ(
						orangePortal->Find("PortalOrange")->GetLocalPos().z - 0.01f);
					activateP[OrangeP] = true;
				
				
			}
		}
	}
}
