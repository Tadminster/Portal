#include <list>			// Doubly Linked List

#include "stdafx.h"
#include "Feature.h"
#include "ObjectManager.h"

void ObjectManager::Init()
{
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	for (auto& feature : features)
		feature->Update();
}

void ObjectManager::LateUpdate()
{
}

void ObjectManager::Render()
{
	for (auto& feature : features)
		feature->Render();
}

void ObjectManager::RenderHierarchy()
{
	for (auto& feature : features)
		feature->GetActor()->RenderHierarchy();
}

void ObjectManager::AddFeature(Feature* feature, Vector3 position, bool defalutAngle)
{
	// Set position
	feature->GetActor()->SetWorldPos(position);

	// type�� ���̸�
	if (feature->type == Wall)
	{
		// �⺻�ޱ��� �ƴϸ� y�� 90�� ȸ��
		if (!defalutAngle) feature->GetActor()->rotation.y = 90 * ToRadian;

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

	features.push_back(feature);
}
