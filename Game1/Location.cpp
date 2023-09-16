#include "stdafx.h"
#include "Location.h"

Location::Location(Vector3 scale, Vector3 pos)
{
	location = Actor::Create();
	location->LoadFile("Location.xml");
	location->scale = scale;
	location->SetWorldPos(Vector3(pos.x, pos.y + scale.y + 1, pos.z));
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

void Location::RenderHierarchy()
{
	location->RenderHierarchy();
}
