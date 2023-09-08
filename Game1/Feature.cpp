#include "stdafx.h"
#include "Feature.h"

Feature::Feature(int type)
{
	actor = Actor::Create();

	if (type == 0)
		actor->LoadFile("Concrete.xml");
	else if (type == 1)
		actor->LoadFile("Metal.xml");
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
