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
		//BluePortal->Find("OrangeCam")
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

void Portal::Portaling(Player* player) //포탈 이동
{
	//포탈과 접촉시 반대편 포탈로 이동
	if (player->GetActor()->Find("Body")->Intersect(BluePortal))
	{
		player->GetActor()->SetLocalPos(OrangePortal->GetWorldPos());
	}
	else if (player->GetActor()->Find("Body")->Intersect(OrangePortal))
	{
		player->GetActor()->SetLocalPos(BluePortal->GetWorldPos());
	}



}

void Portal::PortalInstall(Feature* wall) //포탈 설치
{
	Ray Up;
	Up = Utility::MouseToRay();
	Vector3 Hit;
	
	//좌클릭 블루포탈 생성
	if (INPUT->KeyDown(VK_LEFT))
	{
		if (wall->GetActor()->Find("Mesh")->Intersect(Up, Hit))
		{
			BluePortal->SetLocalPos(Hit);
		}
	}

	//우클릭 오렌지포탈 생성
	if (INPUT->KeyDown(VK_RIGHT))
	{
		if (wall->GetActor()->Find("Mesh")->Intersect(Up, Hit))
		{
			OrangePortal->SetLocalPos(Hit);
		}
	}
}
