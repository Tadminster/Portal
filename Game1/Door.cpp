#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Cube.h"
#include "Door.h"

Door::Door()
{
	actor = Actor::Create();
	actor->LoadFile("Door.xml");
}

Door::~Door()
{
	actor->Release();
}

void Door::Init()
{
}

void Door::Update()
{
	actor->Update();
	
}

void Door::LateUpdate()
{
	if (isOpen)
	{
		actor->Find("DoorMesh")->visible = false;
	}
	else
	{
		actor->Find("DoorMesh")->visible = true;
		if (actor->Find("DoorMesh")->Intersect(PLAYER->GetActor()->Find("WallCol")))
		{
			PLAYER->GetActor()->SetWorldPosX(PLAYER->GetlastPos().x);
			PLAYER->GetActor()->SetWorldPosZ(PLAYER->GetlastPos().z);
			PLAYER->GetActor()->Update();
		}
	}
	
}

void Door::Render()
{
	actor->Render();
}
