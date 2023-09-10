#include "stdafx.h"
#include "GameManager.h"

void GameManager::Init()
{
}

void GameManager::Release()
{
}

void GameManager::Update()
{
	if (INPUT->KeyDown(VK_F1))
	{
		debugMode = !debugMode;
	}
}

void GameManager::LateUpdate()
{
}

void GameManager::Render()
{
}

void GameManager::ResizeScreen()
{
}
