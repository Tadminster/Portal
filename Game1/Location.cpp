#include "stdafx.h"
#include "Location.h"

Location::Location(Vector3 scale, Vector3 pos)
{
	location->LoadFile("Location");
	location->collider->scale = scale;
	location->SetWorldPos(Vector3(pos.x, pos.y + 1, pos.z));
}

Location::~Location()
{
	location->Release();
}

void Location::Init()
{
}

void Location::Update()
{
	location->Update();
}

void Location::LateUpdate()
{
}

void Location::Render()
{
	location->Render();
}
