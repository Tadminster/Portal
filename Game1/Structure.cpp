#include "stdafx.h"
#include "Structure.h"

Structure::Structure(Material material, StructureSize size, StructureType type)
	: material(material), type(type)
{
	actor = Actor::Create();	// actor 객체 생성

	Vector3 tileSize;			// 타일 크기
	string path;				// texture 경로
	string file;				// texture 파일명

	// material 예외처리
	if (material < 1) material = Concrete;
	else if (material > 2) material = Metal;

	if (size < _1x1) size = _1x1;
	else if (size > _16x16) size = _16x16;

	if (material == Concrete)
	{
		// material에 따라 재질 설정
		actor->LoadFile("Concrete.xml");

		// size에 따라 texture 설정, 사이즈	설정
		path = "concrete/";
		switch (size)
		{
			case _1x1: file = "concrete_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case _2x1: file = "concrete_modular_2x1.png"; tileSize = Vector3(6, 1, 3); break;
			case _2x2: file = "concrete_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case _4x1: file = "concrete_modular_4x1.png"; tileSize = Vector3(12, 1, 3); break;
			case _4x2: file = "concrete_modular_4x2.png"; tileSize = Vector3(12, 1, 6); break;
			case _4x4: file = "concrete_modular_4x4.png"; tileSize = Vector3(12, 1, 12); break;
			case _8x1: file = "concrete_modular_8x1.png"; tileSize = Vector3(24, 1, 3); break;
			case _8x2: file = "concrete_modular_8x2.png"; tileSize = Vector3(24, 1, 6); break;
			case _8x4: file = "concrete_modular_8x4.png"; tileSize = Vector3(24, 1, 12); break;
			case _8x8: file = "concrete_modular_8x8.png"; tileSize = Vector3(24, 1, 24); break;
			case _16x1: file = "concrete_modular_16x1.png"; tileSize = Vector3(48, 1, 3); break;
			case _16x2: file = "concrete_modular_16x2.png"; tileSize = Vector3(48, 1, 6); break;
			case _16x4: file = "concrete_modular_16x4.png"; tileSize = Vector3(48, 1, 12); break;
			case _16x8: file = "concrete_modular_16x8.png"; tileSize = Vector3(48, 1, 24); break;
			case _16x16: file = "concrete_modular_16x16.png"; tileSize = Vector3(48, 1, 48); break;
		}
	}
	else if (material == Metal)
	{
		// material에 따라 재질 설정
		actor->LoadFile("Metal.xml");

		// size에 따라 texture 설정
		path = "metal/";
		switch (size)
		{
			case _1x1: file = "metal_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case _2x1: file = "metal_modular_2x1.png"; tileSize = Vector3(6, 1, 3); break;
			case _2x2: file = "metal_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case _4x1: file = "metal_modular_4x1.png"; tileSize = Vector3(12, 1, 3); break;
			case _4x2: file = "metal_modular_4x2.png"; tileSize = Vector3(12, 1, 6); break;
			case _4x4: file = "metal_modular_4x4.png"; tileSize = Vector3(12, 1, 9); break;
			case _8x1: file = "metal_modular_8x1.png"; tileSize = Vector3(24, 1, 3); break;
			case _8x2: file = "metal_modular_8x2.png"; tileSize = Vector3(24, 1, 6); break;
			case _8x4: file = "metal_modular_8x4.png"; tileSize = Vector3(24, 1, 12); break;
			case _8x8: file = "metal_modular_8x8.png"; tileSize = Vector3(24, 1, 24); break;
			case _16x1: file = "metal_modular_16x1.png"; tileSize = Vector3(48, 1, 3); break;
			case _16x2: file = "metal_modular_16x2.png"; tileSize = Vector3(48, 1, 6); break;
			case _16x4: file = "metal_modular_16x4.png"; tileSize = Vector3(48, 1, 12); break;
			case _16x8: file = "metal_modular_16x8.png"; tileSize = Vector3(48, 1, 24); break;
			case _16x16: file = "metal_modular_16x16.png"; tileSize = Vector3(48, 1, 48); break;
		}
	}
	
	// 텍스쳐 Load
	actor->Find("Mesh")->texture = RESOURCE->textures.Load(path + file);
	// scale 설정
	actor->Find("Mesh")->scale = tileSize;
}

Structure::~Structure()
{
	actor->Release();
}

void Structure::Init()
{
}

void Structure::Update()
{
	actor->Update();
}

void Structure::LateUpdate()
{
}

void Structure::Render()
{
	actor->Render();
}
