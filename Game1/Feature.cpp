#include "stdafx.h"
#include "Feature.h"

Feature::Feature(int type, int size)
{
	actor = Actor::Create();	// actor 객체 생성

	Vector3 tileSize;			// 타일 크기
	string path;				// texture 경로
	string file;				// texture 파일명

	// type 예외처리
	if (type < 1) type = 1;
	else if (type > 2) type = 2;

	if (type == 1)
	{
		// type에 따라 재질 설정
		actor->LoadFile("Concrete.xml");

		// size 예외처리
		if (size < 1) size = 1;
		else if (size > 5) size = 5;

		// size에 따라 texture 설정, 사이즈	설정
		path = "concrete/";
		switch (size)
		{
			case 1: file = "concrete_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case 2: file = "concrete_modular_2x1.png"; tileSize = Vector3(6, 1, 6); break;
			case 3: file = "concrete_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case 4: file = "concrete_modular_4x1.png"; tileSize = Vector3(12, 1, 12); break;
			case 5: file = "concrete_modular_4x4.png"; tileSize = Vector3(12, 1, 12); break;
		}
	}
	else if (type == 2)
	{
		// type에 따라 재질 설정
		actor->LoadFile("Metal.xml");

		// size 예외처리
		if (size < 1) size = 1;
		else if (size > 3) size = 3;

		// size에 따라 texture 설정
		path = "metal/";
		switch (size)
		{
			case 1: file = "metal_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case 2: file = "metal_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case 3: file = "metal_modular_4x4.png"; tileSize = Vector3(12, 1, 12); break;
		}
	}
	
	// 텍스쳐 Load
	actor->Find("Mesh")->texture = RESOURCE->textures.Load(path + file);
	// scale 설정
	actor->Find("Mesh")->scale = tileSize;
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
