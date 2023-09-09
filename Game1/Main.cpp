#include "stdafx.h"
#include "Player.h"
#include "Feature.h"
#include "Main.h"

// [��ġ] �¶��ο� �ִ� ������ ������
// 		    �� git fetch

// [�������(Ǯ)] �¶��ο� �ִ� ������ �����ͼ� ������ǻ��(������ǻ��)�� �����Ŵ
// 	        �� git pull

// [Ŀ��] ����� ������ ����, �� ������ ������ǻ��(������ǻ��)�� �����Ŵ
//  	    �� git commit -m "Ŀ�Ը޼���"

// [Ǫ��] ����� ����(Ŀ�Ե� ����)�� �¶��ο� �����Ŵ
//          �� git push   

// [����] �ΰ��� �귣ġ�� ��ħ
//          �� git merge �귣ġ�̸�

// ����� ������
// [�귱ġ] �۾��� �� ��, ���κ귱ġ�� �ǵ��� �ʰ� ���κ귱ġ���� �۾��� �ϰ�, �۾��� �Ϸ�Ǹ� ���κ귱ġ�� ��ħ
// 1. ���κ귱ġ���� �۾� -> �۾������� Ŀ��, Ǫ��
// 2. ���κ귱ġ�� �̵� -> ��ġ�غ��� ����� ������ �ִ��� Ȯ�� -> ������ �������
// 3. ���κ귱ġ���� ���κ귱ġ�� ����
// 4. ���κ귱ġ�� Ŀ��, Ǫ�� -> �¶��ο� ����� ������ ����� -> �������� �۾��� ������ �ִٰ� �˷��ָ� ����

// �浹�ذ� ���
// 1. �浹���ձ⸦ ��� �浹�� �κ��� ����
// 2. �浹�� ������ Ŀ��, Ǫ��


Main::Main()
{
    grid = Grid::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");

    Camera::main = cam1;
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    player = new Player();
    wall = new Feature(1, 5);

    
}

Main::~Main()
{
    player->~Player();
    wall->~Feature();
}

void Main::Init()
{
    wall->GetActor()->scale = Vector3(1, 1, 1);
}

void Main::Release()
{
   
}

void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    player->GetActor()->RenderHierarchy();
    wall->GetActor()->RenderHierarchy();

    
    ImGui::End();

    grid->Update();
    Camera::main->Update();

    player->Update();
    wall->Update();

    
}

void Main::LateUpdate()
{
}
void Main::PreRender()
{
}

void Main::Render()
{
    Camera::main->Set();
    grid->Render();
    player->Render();
    wall->Render();
}

void Main::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game1");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();

    int wParam = (int)WIN->Run(main);


    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}