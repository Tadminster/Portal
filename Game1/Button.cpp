#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Cube.h"
#include "Button.h"

void Button::PlaybuttonUpSoundEffect()
{
	SOUND->Play(buttonUpSoundKey);
}

void Button::PlaybuttonDownSoundEffect()
{
	SOUND->Play(buttonDownSoundKey);
}

Button::Button()
{
	actor = Actor::Create();
	actor->LoadFile("Button.xml");

	buttonCount = 0;

	buttonUpSoundKey = "ButtonUpSound";
	SOUND->AddSound("ButtonUpSound.wav", buttonUpSoundKey);

	buttonDownSoundKey = "ButtonDownSound";
	SOUND->AddSound("ButtonDownSound.wav", buttonDownSoundKey);

	SOUND->SetVolume(buttonDownSoundKey, 0.3f);
	
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

		
		if (buttonCount == 0)
		{
			PlaybuttonDownSoundEffect();  // 사운드 재생
			buttonCount++;
		}
		
		count++;
		
		if (count >= 2) cube->GetActor()->SetWorldPosY(actor->GetWorldPos().y + 1);
			
	}
	else buttonCount = 0;

		

	//버튼 스위치 누르기
	if (actor->Find("ButtonSwitch")->Intersect(PLAYER->GetActor()->Find("PortalActor")) or
		actor->Find("ButtonCol")->Intersect(cube->GetActor()->Find("Mesh")))
	{
		
		switched = true;
		
	}
	else  switched = false;;
	

}
