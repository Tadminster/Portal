#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"

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
// 2. ���κ귱ġ�� �̵� -> ��ġ�غ��� ����� ������ �ִ��� Ȯ��
//      2.1  -> ������ ������� -> ���κ귱ġ�� �̵� -> ���κ귱ġ���� ������ ���� git merge main 
//      2.2  -> �����浹 ������ �ذ� �� -> ���������� Ȯ�� 
// 3. ���κ귱ġ���� ���κ귱ġ�� ����
// 4. ���κ귱ġ�� Ŀ��, Ǫ�� -> �¶��ο� ����� ������ ����� -> �������� �۾��� ������ �ִٰ� �˷��ָ� ����

// �浹�ذ� ���
// 1. �浹���ձ⸦ ��� �浹�� �κ��� ����
// 2. �浹�� ������ Ŀ��, Ǫ��


Main::Main()
{
    sc1 = new Scene1();
    sc2 = new Scene2();
    sc3 = new Scene3();
    sc4 = new Scene4();
}

Main::~Main()
{
    //GM->cam1->SaveFile("Cam.xml");
    GM->Release();
}

void Main::Init()
{
    SCENE->AddScene("scene1", sc1);
    SCENE->AddScene("scene2", sc2);
    SCENE->AddScene("scene3", sc3);
    SCENE->AddScene("scene4", sc4);
    SCENE->ChangeScene("scene2");
}

void Main::Release()
{
    SCENE->Release();
}

void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::PreRender()
{
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
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