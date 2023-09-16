#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"
#include "Structure.h"
#include "Cube.h"
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

	//포탈 ui 이미지
	if (activateP[BlueP] == true and activateP[OrangeP] == true)
	{
		ui->texture = RESOURCE->textures.Load("potalUi/PotalUiAll.png");
	}
	else if (activateP[BlueP] == true)
	{
		ui->texture = RESOURCE->textures.Load("potalUi/PotalUiBlue.png");
	}
	else if (activateP[OrangeP] == true)
	{
		ui->texture = RESOURCE->textures.Load("potalUi/PotalUiOrange.png");
	}
	else if (activateP[BlueP] == false and activateP[OrangeP] == false)
	{
		ui->texture = RESOURCE->textures.Load("potalUi/PotalUiNon.png");
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

	if (!GM->debugMode) ui->Render();
}

void Portal::Portaling() //포탈 이동
{

		//포탈과 접촉시 반대편 포탈로 이동
		//블루 -> 오렌지
		if (PLAYER->GetActor()->Find("PortalActor")->Intersect(bluePortal->Find("collider")))
		{ 
			PLAYER->SetState(PlayerState::JUMP);
			if (orangePortal->rotation.x == 90 * ToRadian)
			{
				PLAYER->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
					+ orangePortal->Find("PortalOrange")->GetForward()* -6);
				PLAYER->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
				PLAYER->PortalJump();								
			}
			else if(orangePortal->rotation.x == -90 * ToRadian)
			{
				PLAYER->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
					+ orangePortal->Find("PortalOrange")->GetForward() * -7);
				PLAYER->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
								
			}
			else
			{
				PLAYER->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
					+ orangePortal->Find("PortalOrange")->GetForward() * -5);
				PLAYER->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
				PLAYER->SetBounceDir(-orangePortal->Find("PortalOrange")->GetForward());
				PLAYER->PortalBounce();
			}
		}
		//오렌지 -> 블루
		else if (PLAYER->GetActor()->Find("PortalActor")->Intersect(orangePortal->Find("collider")))
		{
			PLAYER->SetState(PlayerState::JUMP);
			if (bluePortal->rotation.x == 90 * ToRadian)
			{
				PLAYER->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
					+ bluePortal->Find("PortalBlue")->GetForward() *-6);
				PLAYER->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
				PLAYER->PortalJump();

			}
			else if (bluePortal->rotation.x == -90 * ToRadian)
			{
				PLAYER->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
					+ bluePortal->Find("PortalBlue")->GetForward() * -7);
				PLAYER->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
				
			}
			else
			{
				PLAYER->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
					+ bluePortal->Find("PortalBlue")->GetForward() * -5);
				PLAYER->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
				PLAYER->SetBounceDir(-bluePortal->Find("PortalBlue")->GetForward());
				PLAYER->PortalBounce();
			}
		}
		

}

void Portal::PortalingCube(Cube* cube)//큐브 포탈이동
{
	//포탈과 접촉시 반대편 포탈로 이동
	//블루 -> 오렌지
	if (cube->GetActor()->Find("Mesh")->Intersect(bluePortal->Find("collider")))
	{
		HandFree(cube);
		if (orangePortal->rotation.x == 90 * ToRadian)
		{
			cube->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
				+ Vector3(0, 6, 0));
			cube->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
			cube->PortalJump();			
		}
		else if (orangePortal->rotation.x == -90 * ToRadian)
		{
			cube->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
				+ orangePortal->Find("PortalOrange")->GetForward() * -7);
			cube->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
		}
		else
		{
			cube->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
				+ orangePortal->Find("PortalOrange")->GetForward() * -5);
			cube->GetActor()->rotation.y += orangePortal->rotation.y - bluePortal->rotation.y + 180 * ToRadian;
			cube->SetBounceDir(-orangePortal->Find("PortalOrange")->GetForward());
			cube->PortalBounce();			
		}
	}
	//오렌지 -> 블루
	else if (cube->GetActor()->Find("Mesh")->Intersect(orangePortal->Find("collider")))
	{
		HandFree(cube);
		if (bluePortal->rotation.x == 90 * ToRadian)
		{
			cube->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
				+ Vector3(0, 6, 0));
			cube->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
			cube->PortalJump();			
		}
		else if (bluePortal->rotation.x == -90 * ToRadian)
		{
			cube->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
				+ bluePortal->Find("PortalBlue")->GetForward() * -7);
			cube->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
		}
		else
		{
			cube->GetActor()->SetWorldPos(bluePortal->Find("PortalBlue")->GetWorldPos()
				+ bluePortal->Find("PortalBlue")->GetForward() * -5);
			cube->GetActor()->rotation.y += bluePortal->rotation.y - orangePortal->rotation.y + 180 * ToRadian;
			cube->SetBounceDir(-bluePortal->Find("PortalBlue")->GetForward());
			cube->PortalBounce();			
		}
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
		for (auto& feature : OBJECT->GetStructures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit))
			{
				if (feature->type == StructureType::Wall)
				{
					bluePortal->visible = true;
					bluePortal->rotation = feature->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
					bluePortal->SetLocalPos(Hit );
					bluePortal->Find("PortalBlue")->SetLocalPosZ(
						bluePortal->Find("PortalBlue")->GetLocalPos().z - 0.01f);
					activateP[BlueP] = true;
				}
				if (feature->type == StructureType::Ceiling
					|| feature->type == StructureType::Floor)
				{
					bluePortal->visible = true;
					bluePortal->rotation = feature->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
					bluePortal->rotation.y = PLAYER->GetActor()->rotation.y;
					bluePortal->SetLocalPos(Hit);
					bluePortal->Find("PortalBlue")->SetLocalPosZ(
						bluePortal->Find("PortalBlue")->GetLocalPos().z - 0.01f);
					activateP[BlueP] = true;
				}			
			}
		}
	}
	
	//우클릭 오렌지포탈 생성
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		for (auto& feature : OBJECT->GetStructures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit))
			{
				if (feature->type == StructureType::Wall)
				{
					orangePortal->visible = true;
					orangePortal->rotation = feature->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
					orangePortal->SetLocalPos(Hit );
					orangePortal->Find("PortalOrange")->SetLocalPosZ(
						orangePortal->Find("PortalOrange")->GetLocalPos().z - 0.01f);
					activateP[OrangeP] = true;
				}
				if (feature->type == StructureType::Ceiling
					|| feature->type == StructureType::Floor)
				{
					orangePortal->visible = true;
					orangePortal->rotation = feature->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
					orangePortal->rotation.y = PLAYER->GetActor()->rotation.y;
					orangePortal->SetLocalPos(Hit);
					orangePortal->Find("PortalOrange")->SetLocalPosZ(
						orangePortal->Find("PortalOrange")->GetLocalPos().z - 0.01f);
					activateP[OrangeP] = true;
				}
			}
		}
	}
}

void Portal::HandFree(Cube* cube)
{
	PLAYER->isCatch = false;
	cube->SetisCatched(false);
}
