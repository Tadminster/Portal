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

	//약쪽 포탈이 활성시 Close 이미지 투명화
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

	//포탈 초기화
	if (INPUT->KeyPress(VK_F5))
	{
		BluePortal->visible = false;
		OrangePortal->visible = false;

		ActivateP[BlueP] = false;
		ActivateP[OrangeP] = false;
	}

	//포탈 Close 이미지 애니매이션
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

void Portal::Portaling() //포탈 이동
{

	//포탈과 접촉시 반대편 포탈로 이동
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
				BluePortal->visible = true;
				BluePortal->SetLocalPos(Hit + Vector3(0, 0, -0.01));
				ActivateP[BlueP] = true;
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
				OrangePortal->visible = true;
				OrangePortal->SetLocalPos(Hit + Vector3(0,0,-0.01));
				ActivateP[OrangeP] = true;
			}
		}
	}
}
