#include "stdafx.h"
#include "Feature.h"

Feature::Feature(Material material, int size, StructureType type)
	: material(material), type(type)
{
	actor = Actor::Create();	// actor ��ü ����

	Vector3 tileSize;			// Ÿ�� ũ��
	string path;				// texture ���
	string file;				// texture ���ϸ�

	// material ����ó��
	if (material < 1) material = Concrete;
	else if (material > 2) material = Metal;

	if (material == Concrete)
	{
		// material�� ���� ���� ����
		actor->LoadFile("Concrete.xml");

		// size ����ó��
		if (size < 1) size = 1;
		else if (size > 7) size = 7;

		// size�� ���� texture ����, ������	����
		path = "concrete/";
		switch (size)
		{
			case 1: file = "concrete_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case 2: file = "concrete_modular_2x1.png"; tileSize = Vector3(6, 1, 6); break;
			case 3: file = "concrete_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case 4: file = "concrete_modular_4x1.png"; tileSize = Vector3(12, 1, 12); break;
			case 5: file = "concrete_modular_4x4.png"; tileSize = Vector3(12, 1, 12); break;
			case 6: file = "concrete_modular_8x8.png"; tileSize = Vector3(24, 1, 24); break;
			case 7: file = "concrete_modular_16x16.png"; tileSize = Vector3(48, 1, 48); break;
		}
	}
	else if (material == Metal)
	{
		// material�� ���� ���� ����
		actor->LoadFile("Metal.xml");

		// size ����ó��
		if (size < 1) size = 1;
		else if (size > 5) size = 5;

		// size�� ���� texture ����
		path = "metal/";
		switch (size)
		{
			case 1: file = "metal_modular_1x1.png"; tileSize = Vector3(3, 1, 3); break;
			case 2: file = "metal_modular_2x2.png"; tileSize = Vector3(6, 1, 6); break;
			case 3: file = "metal_modular_4x4.png"; tileSize = Vector3(12, 1, 12); break;
			case 4: file = "metal_modular_8x8.png"; tileSize = Vector3(24, 1, 24); break;
			case 5: file = "metal_modular_16x16.png"; tileSize = Vector3(48, 1, 48); break;
		}
	}
	
	// �ؽ��� Load
	actor->Find("Mesh")->texture = RESOURCE->textures.Load(path + file);
	// scale ����
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
