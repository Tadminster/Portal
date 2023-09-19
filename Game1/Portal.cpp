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

	bluePortalSoundKey = "BluePortalSound";
	SOUND->AddSound("BluePortalSound.wav", bluePortalSoundKey);

	orangePortalSoundKey = "OrangePortalSound";
	SOUND->AddSound("OrangePortalSound.wav", orangePortalSoundKey);

	portalEnterSoundKey = "PortalEnterSound";
	SOUND->AddSound("PortalEnterSound.wav", portalEnterSoundKey);

	SOUND->SetVolume(bluePortalSoundKey, 0.3f);
	SOUND->SetVolume(orangePortalSoundKey, 0.3f);
	SOUND->SetVolume(portalEnterSoundKey, 0.3f);
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

	//ui->RenderHierarchy();

	//양쪽 포탈이 활성화 되었을 때
	if (activateP[BlueP] == true and activateP[OrangeP] == true)
	{
		// Close 이미지 보이게
		bluePortal->Find("CloseB")->visible = true;
		orangePortal->Find("CloseO")->visible = true;

		// 이미지 움직이기
		bluePortal->Find("CloseB")->mesh->AnimationDown();
		orangePortal->Find("CloseO")->mesh->AnimationDown();
		
	}
	else
	{
		bluePortal->Find("CloseB")->visible = false;
		orangePortal->Find("CloseO")->visible = false;
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
			SOUND->Stop(portalEnterSoundKey);  
			SOUND->Play(portalEnterSoundKey);  

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
			SOUND->Stop(portalEnterSoundKey);
			SOUND->Play(portalEnterSoundKey);


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
	if (activateP[BlueP] == true and activateP[OrangeP] == true)
	{
		if (cube->GetActor()->Find("Mesh")->Intersect(bluePortal->Find("collider")))
		{
			HandFree(cube);
			if (orangePortal->rotation.x == 90 * ToRadian)
			{
				cube->GetActor()->SetWorldPos(orangePortal->Find("PortalOrange")->GetWorldPos()
					+ orangePortal->Find("PortalOrange")->GetForward() * -6);
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
					+ orangePortal->Find("PortalOrange")->GetForward() * -6);
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
	
}

void Portal::PortalInstall() //포탈 설치
{
	Ray Up;
	Up = Utility::MouseToRay();
	Vector3 Hit;
	Vector3 LastHitB = Vector3(0,0,0);
	Structure* saveFeatureB = nullptr;
	//좌클릭 블루포탈 생성
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		for (auto& feature : OBJECT->GetStructures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit) && feature->material == Concrete)
			{							
				if (LastHitB == Vector3(0, 0, 0))
				{
					LastHitB = Hit;
					saveFeatureB = feature;
				}

				if ((LastHitB - PLAYER->GetActor()->GetWorldPos()).Length() >=
					(Hit - PLAYER->GetActor()->GetWorldPos()).Length())
				{
					LastHitB = Hit;
					saveFeatureB = feature;
				}									
			}			
		}
		if (saveFeatureB!= nullptr )
		{
			SOUND->Stop(bluePortalSoundKey);  // 현재 재생 중인 사운드 중지
			SOUND->Play(bluePortalSoundKey);  // 사운드 재생
			//PlayBluePortalSoundEffect();
			if (saveFeatureB->type == StructureType::Wall)
			{
				bluePortal->visible = true;
				bluePortal->rotation = saveFeatureB->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
				bluePortal->SetWorldPos(LastHitB);
				/*bluePortal->Find("PortalBlue")->SetWorldPosZ(
					bluePortal->Find("PortalBlue")->GetLocalPos().z - 0.1f);*/
				activateP[BlueP] = true;
			}
			if (saveFeatureB->type == StructureType::Ceiling
				|| saveFeatureB->type == StructureType::Floor)
			{
				bluePortal->visible = true;
				bluePortal->rotation = saveFeatureB->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
				bluePortal->rotation.y = PLAYER->GetActor()->rotation.y;
				bluePortal->SetWorldPos(LastHitB);
				/*bluePortal->Find("PortalBlue")->SetWorldPosZ(
					abluePortal->Find("PortalBlue")->GetLocalPos().z - 0.1f);*/
				activateP[BlueP] = true;
			}

			bluePortal->Update();
			//spaceCheck(bluePortal, BlueP);
		}
		
	}
	
	Vector3 LastHitO = Vector3(0, 0, 0);
	Structure* saveFeatureO = nullptr;
	//우클릭 오렌지포탈 생성
	if (INPUT->KeyDown(VK_RBUTTON))
	{
		for (auto& feature : OBJECT->GetStructures())
		{
			if (feature->GetActor()->Find("Mesh")->Intersect(Up, Hit) && feature->material == Concrete)
			{
				if (LastHitO == Vector3(0, 0, 0))
				{
					LastHitO = Hit;
					saveFeatureO = feature;
				}

				if ((LastHitO - PLAYER->GetActor()->GetWorldPos()).Length() >=
					(Hit - PLAYER->GetActor()->GetWorldPos()).Length())
				{
					LastHitO = Hit;
					saveFeatureO = feature;
				}
				
			}
		}

		if (saveFeatureO!= nullptr)
		{
			SOUND->Stop(orangePortalSoundKey);  // 현재 재생 중인 사운드 중지
			SOUND->Play(orangePortalSoundKey);  // 사운드 재생

			if (saveFeatureO->type == StructureType::Wall)
			{
				orangePortal->visible = true;
				orangePortal->rotation = saveFeatureO->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
				orangePortal->SetWorldPos(LastHitO);
				/*orangePortal->Find("PortalOrange")->SetLocalPosZ(
					orangePortal->Find("PortalOrange")->GetLocalPos().z - 0.1f);*/
				activateP[OrangeP] = true;
			}
			if (saveFeatureO->type == StructureType::Ceiling
				|| saveFeatureO->type == StructureType::Floor)
			{
				orangePortal->visible = true;
				orangePortal->rotation = saveFeatureO->GetActor()->rotation + Vector3(-90 * ToRadian, 0, 0);
				orangePortal->rotation.y = PLAYER->GetActor()->rotation.y;
				orangePortal->SetWorldPos(LastHitO);
				/*orangePortal->Find("PortalOrange")->SetLocalPosZ(
					orangePortal->Find("PortalOrange")->GetLocalPos().z - 0.1f);*/
				activateP[OrangeP] = true;
			}

			orangePortal->Update();
			//spaceCheck(orangePortal, OrangeP);
		}
		
	}
}

void Portal::PlayBluePortalSoundEffect()
{
	SOUND->Play(bluePortalSoundKey);
}

void Portal::PlayOrangePortalSoundEffect()
{
	SOUND->Play(orangePortalSoundKey);
}

void Portal::PlayPortalEnterSoundEffect()
{
	SOUND->Play(portalEnterSoundKey);
}

void Portal::spaceCheck(Actor* portal, int portalNumber)
{
	bool edgeLT = false;
	bool edgeRT = false;
	bool edgeLB = false;
	bool edgeRB = false;

	// 네 모서리 콜라이더가 벽과 겹치는지 확인
	for (auto& it : OBJECT->GetStructures())
	{
		if (!edgeLT && portal->Find("collider_LT")->Intersect(it->GetActor()->Find("Mesh")))
		{
			edgeLT = true;
		}
		if (!edgeRT && portal->Find("collider_RT")->Intersect(it->GetActor()->Find("Mesh")))
		{
			edgeRT = true;
		}
		if (!edgeLB && portal->Find("collider_LB")->Intersect(it->GetActor()->Find("Mesh")))
		{
			edgeLB = true;
		}
		if (!edgeRB && portal->Find("collider_RB")->Intersect(it->GetActor()->Find("Mesh")))
		{
			edgeRB = true;
		}
	}
	cout << "LT: " << edgeLT << endl;
	cout << "RT: " << edgeRT << endl;
	cout << "LB: " << edgeLB << endl;
	cout << "RB: " << edgeRB << endl << endl;
	// 네 모서리가 벽과 겹치지 않았으면
	if (!edgeLT || !edgeRT || !edgeLB || !edgeRB)
	{
		portal->visible = false;
		activateP[portalNumber] = false;
	}
}


void Portal::HandFree(Cube* cube)
{
	PLAYER->isCatch = false;
	cube->SetisCatched(false);
}
