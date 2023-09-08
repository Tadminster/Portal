#include "stdafx.h"
#include "Feature.h"

Feature::Feature()
{
	actor = Actor::Create();
	actor->LoadFile("Feature.xml");
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
