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

	//양쪽 포탈이 활성시 Close 이미지 투명화
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

	//포탈 초기화
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
	//포탈 Close 이미지 애니매이션
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

void Portal::Portaling() //포탈 이동
{

	//포탈과 접촉시 반대편 포탈로 이동
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

void Portal::PortalInstall() //포탈 설치
{
	Ray Up;
	Up = Utility::MouseToRay();
	Vector3 Hit;
	
	//좌클릭 블루포탈 생성
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
	
	//우클릭 오렌지포탈 생성
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
