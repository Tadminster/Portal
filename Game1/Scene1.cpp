#include "stdafx.h"
#include "Feature.h"
#include "ObProto.h"
#include "Player.h"
#include "Cube.h"
#include "Portal.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Scene1.h"

Scene1::Scene1()
{
    GM->Init();

    Camera::main = (Camera*)PLAYER->GetActor()->Find("BodyCam");
    ResizeScreen();
}

Scene1::~Scene1()
{

}

void Scene1::Init()
{
    cube = new Cube();
    
    OBJECT->AddFeature(new Feature(Concrete, 7, Floor), Vector3(12, 0, 0));         // �ٴ�1
    OBJECT->AddFeature(new Feature(Concrete, 7, Ceiling), Vector3(12, 48, 0));      // õ��1
    OBJECT->AddFeature(new Feature(Concrete, 7, Floor), Vector3(132, 0, 0));        // �ٴ�2
    OBJECT->AddFeature(new Feature(Concrete, 7, Ceiling), Vector3(108, 48, 0));     // õ��2
    
    OBJECT->AddFeature(new Feature(Concrete, 5, Ceiling), Vector3(12, 24, 0));      // ������ġ ���� õ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(0, 0, 0), 270);      // ������ġ ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(12, 0, 11));         // ������ġ ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(12, 0, -11), 180);   // ������ġ ������ ��

    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(23, 24, 0), 270);    // ������ġ���� ���ͼ� �ٷ� ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(23, 0, 36), 270);    // ������ġ���� ���ͼ� �ٷ� ���� ū��
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(23, 0, -36), 270);   // ������ġ���� ���ͼ� �ٷ� ������ ū��

    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(48, 0, 48));         // ������ġ���� ���ͼ� ���� ū��1
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(96, 0, 48));         // ������ġ���� ���ͼ� ���� ū��2
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(48, 0, -48), 180);   // ������ġ���� ���ͼ� ������ ū��1
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(96, 0, -48), 180);   // ������ġ���� ���ͼ� ������ ū��2

    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(120, 24, 0), 90);   // ������ġ ���� �� �ٷ� ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(120, 0, 36), 90);   // ������ġ ���� �� �ٷ� ���� ū��
    OBJECT->AddFeature(new Feature(Concrete, 6, Wall), Vector3(120, 0, -36), 90);  // ������ġ ���� �� �ٷ� ������ ū��

    OBJECT->AddFeature(new Feature(Concrete, 5, Ceiling), Vector3(131, 24, 0));     // ������ġ õ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(143, 0, 0), 90);    // ������ġ ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(131, 0, 11));        // ������ġ ���� ��
    OBJECT->AddFeature(new Feature(Concrete, 5, Wall), Vector3(131, 0, -11), 180);  // ������ġ ������ ��
    
    PLAYER->GetActor()->SetWorldPos(startPoint);
}

void Scene1::Release()
{

}

void Scene1::Update()
{
    // ī�޶� ���� (����� ����϶���)
    if (GM->debugMode) Camera::ControlMainCam();

    ImGui::Begin("Hierarchy");
    {
        GM->grid->RenderHierarchy();
        GM->cam1->RenderHierarchy();
        PLAYER->GetActor()->RenderHierarchy();
        OBJECT->RenderHierarchy();
        GM->portal->GetBluePortal()->RenderHierarchy();
        GM->portal->GetOrangePortal()->RenderHierarchy();
        cube->GetActor()->RenderHierarchy();
    }
    ImGui::End();

    GM->grid->Update();
    Camera::main->Update();

    GM->Update();
    PLAYER->Update();
    OBJECT->Update();
    GM->portal->Update();
    cube->Update();
}

void Scene1::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
    cube->LateUpdate();
}

void Scene1::Render()
{
    Camera::main->Set();
    GM->grid->Render();
    PLAYER->Render();
    OBJECT->Render();
    GM->portal->Render();
    cube->Render();
}

void Scene1::PreRender()
{
}

void Scene1::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
