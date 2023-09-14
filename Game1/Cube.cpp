#include "stdafx.h"
#include "ObProto.h"
#include "Structure.h"
#include "ObjectManager.h"
#include "Cube.h"

Cube::Cube()
{
	actor = Actor::Create();
	actor->LoadFile("PortalCube.xml");
	
}

Cube::~Cube()
{
	actor->Release();
}

void Cube::Init()
{
}

void Cube::Update()
{
	if (OnGround) gravity = 0;
	else
	{
		// 땅에 닿아있지 않으면 중력 증가 (최대 200)
		gravity = clamp(gravity - 50.0f * DELTA, -200.0f, 200.0f);

		// 중력에 따라 플레이어 상하이동
		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	}

	actor->Update();
}

void Cube::LateUpdate()
{
	// 모든 지형지물과 충돌 체크
	for (auto& feature : OBJECT->GetStructures())
	{
		// 지형지물이 벽이면
		if (feature->type == Wall)
		{
			// 벽과 부딪치면 이전 위치로 이동
			if (actor->Find("Mesh")->Intersect(feature->GetActor()->Find("Mesh")))
			{
				actor->SetWorldPosX(lastPos.x);
				actor->SetWorldPosZ(lastPos.z);
				actor->Update();
			}
		}
	}

	for (auto& feature : OBJECT->GetStructures())
	{
		// 지형지물이 바닥이면
		if (feature->type == Floor)
		{
			// 지형지물의 Body와 플레이어의 Mesh가 충돌하면 땅에 닿아있는 것
			if (actor->Find("Mesh")->Intersect(feature->GetActor()->Find("Mesh")))
			{
				OnGround = true;
				break;
			}
			else OnGround = false;
		}
	}
}

void Cube::Render()
{
	actor->Render();
}
