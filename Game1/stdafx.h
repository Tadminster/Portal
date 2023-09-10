#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

#include "GameManager.h"

#define GM		GameManager::GetInstance()
#define PLAYER	GameManager::GetInstance()->player
#define OBJECT	GameManager::GetInstance()->object