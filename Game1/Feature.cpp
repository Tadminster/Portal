#include "stdafx.h"
#include "Feature.h"

Feature::Feature(int tileSize, int type)
{
	actor = Actor::Create();

	if (type == 0)
		actor->LoadFile("Concrete.xml");
	else if (type == 1)
		actor->LoadFile("Metal.xml");

	actor->Find("BodyMesh")->scale = Vector3(tileSize, tileSize, tileSize);
}

Feature::~Feature()
{
	actor->Release();
}

void Feature::Init()
{
}

void Feature::Update()
{
	actor->Update();
}

void Feature::LateUpdate()
{
}

void Feature::Render()
{
	actor->Render();
}
