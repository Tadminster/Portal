#include "stdafx.h"
#include "Portal.h"

Portal::Portal()
{
	BluePortal = Actor::Create();
	BluePortal->LoadFile(" ");
	OrangePortal = Actor::Create();
	OrangePortal->LoadFile(" ");
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







	BluePortal->Update();
	OrangePortal->Update();
}

void Portal::LateUpdate()
{
}

void Portal::Render()
{
	BluePortal->Render();
	OrangePortal->Render();
}

void Portal::Portaling()
{
}
