#include "stdafx.h"
#include "ObProto.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameManager.h"

void GameManager::Init()
{
	cam1 = Camera::Create();
	player = new Player();
	object = new ObjectManager();

	cam1->LoadFile("Cam.xml");
}

void GameManager::Release()
{
}

void GameManager::Update()
{
	if (INPUT->KeyDown(VK_F1))
	{
		// ��� ��ȯ
		debugMode = !debugMode;
		ShowCursor(debugMode);

		// ����ķ ����
		if (Camera::main == cam1) Camera::main = (Camera*)player->GetActor()->Find("BodyCam");
		else Camera::main = cam1;

		// �������� ��ũ��
		ResizeScreen();
	}

	if (!debugMode)
	{
		//�߾Ӱ�
		POINT ptMouse;
		ptMouse.x = App.GetHalfWidth();
		ptMouse.y = App.GetHalfHeight();
		Vector3 Rot;
		Rot.x = (INPUT->position.y - ptMouse.y) * 0.0005f;
		Rot.y = (INPUT->position.x - ptMouse.x) * 0.0005f;


		//x�� ȸ��
		player->GetActor()->Find("Neck")->rotation.x -= Rot.x;
		Camera::main->rotation.x += Rot.x;

		//y�� ȸ��
		player->GetActor()->rotation.y += Rot.y;

		ClientToScreen(App.GetHandle(), &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);

		

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
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
