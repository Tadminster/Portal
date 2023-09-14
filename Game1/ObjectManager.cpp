#include <list>			// Doubly Linked List

#include "stdafx.h"
#include "Structure.h"
#include "ObjectManager.h"

void ObjectManager::Init()
{
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	for (auto& it : structures)
		it->Update();
}

void ObjectManager::LateUpdate()
{
}

void ObjectManager::Render()
{
	for (auto& it : structures)
		it->Render();
}

void ObjectManager::RenderHierarchy()
{
	for (auto& it : structures)
		it->GetActor()->RenderHierarchy();
}

void ObjectManager::AddFeature(Structure* feature, Vector3 position, float rotationY)
{
	// Set position
	feature->GetActor()->SetWorldPos(position);

	// type�� ���̸�
	if (feature->type == Wall)
	{
		// y�� ȸ��
		feature->GetActor()->rotation.y = rotationY * ToRadian;

		// x�� 90�� ȸ��
		feature->GetActor()->rotation.x = 90 * ToRadian;
		
		// ���� �⺻ ���� ����
		int tempPosY = feature->GetActor()->Find("Mesh")->scale.x;
		feature->GetActor()->Find("Mesh")->SetLocalPosZ(-tempPosY);
	}
	else if (feature->type == Floor)
	{
		feature->GetActor()->rotation.x = 180 * ToRadian;
	}
	else if (feature->type == Ceiling)
	{
		//feature->GetActor()->rotation.x = 0 * ToRadian;
	}

	structures.push_back(feature);
}
