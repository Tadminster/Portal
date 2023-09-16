#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Cube.h"
#include "Button.h"

Button::Button()
{
	actor = Actor::Create();
	actor->LoadFile("Button.xml");
}

Button::~Button()
{
	actor->Release();
}

void Button::Init()
{
}

void Button::Update()
{

	actor->Update();
}

void Button::LateUpdate()
{
}

void Button::Render()
{
	actor->Render();
}

void Button::SwitchPress(Cube* cube)
{
	//버튼 위로 이동
	if (actor->Find("ButtonCol")->Intersect(cube->GetActor()->Find("Mesh")))
	{
		cube->GetActor()->SetWorldPosY(actor->GetWorldPos().y + 1);
	}

	//버튼 스위치 누르기
	if (actor->Find("ButtonSwitch")->Intersect(PLAYER->GetActor()->Find("PortalActor")) or
		actor->Find("ButtonCol")->Intersect(cube->GetActor()->Find("Mesh")))
	{
		switched = true;
	}
	else  switched = false;;

}
