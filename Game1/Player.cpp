#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	actor = Actor::Create();
	//actor->LoadFile("Player.xml");
}

Player::~Player()
{
	actor->Release();
}

void Player::Init()
{
}

void Player::Update()
{
	actor->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	actor->Render();
}
