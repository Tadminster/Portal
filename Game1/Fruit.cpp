#include "stdafx.h"
#include "Fruit.h"

Fruit* Fruit::Create(string name)
{
	Fruit* temp = new Fruit();
	temp->LoadFile("bullet.xml");
	temp->type = ObType::Actor;
	return temp;
}

Fruit::Fruit()
{
}

Fruit::~Fruit()
{
}

void Fruit::Update()
{
	if (not isFire) return;
	MoveWorldPos(dir * power * DELTA);
	MoveWorldPos(Vector3(0,-1,0) * gravity * DELTA);
	gravity += 3 * DELTA;

	if (not Find("Body")->visible)
	{
		Find("L_Body")->MoveWorldPos(
			Find("L_Body")->GetUp() * boomPower * DELTA);
		Find("R_Body")->MoveWorldPos(
			Find("R_Body")->GetUp() * boomPower * DELTA);
		boomPower -= DELTA;
		if (boomPower < 0.0f) boomPower = 0.0f;
	}


	Actor::Update();

	if (GetWorldPos().y < -5)
	{
		isFire = false;
	}

}

void Fruit::Render()
{
	if (not isFire)  
		return ;

	Actor::Render();
}

bool Fruit::Fire(Vector3 pos, Vector3 dir, float power)
{
	if (isFire)  return false;

	SetWorldPos(pos);
	this->dir = dir;
	this->power = power;
	isFire = true;
	gravity = 0.0f;
	Find("Body")->visible = true;
	Find("L_Body")->visible = false;
	Find("R_Body")->visible = false;
	Find("L_Body")->SetLocalPos(Vector3());
	Find("R_Body")->SetLocalPos(Vector3());
	return true;
}

void Fruit::Boom()
{
	if (not Find("Body")->visible) return;

	Find("Body")->visible = false;
	Find("L_Body")->visible = true;
	Find("R_Body")->visible = true;
	boomPower = 2.0f;
	power = 0.0f;
	gravity *= 0.5f;
	
	rotation.z = 90.0f * ToRadian -atan2f(INPUT->movePosition.y, INPUT->movePosition.x);
}
