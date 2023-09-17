#include "stdafx.h"
#include "Structure.h"
#include "ObProto.h"
#include "Player.h"
#include "Cube.h"
#include "Button.h"
#include "Door.h"
#include "Portal.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Scene4.h"

Scene4::Scene4()
{

    GM->Init();

    Camera::main = (Camera*)PLAYER->GetActor()->Find("BodyCam");
    ResizeScreen();

}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
   
    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // ������ġ ���� õ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(12, 1, 0));             // ������ġ �ٴ�
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // ������ġ ������ ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(25, 0, 0), 90);       // ������ġ �ٱ��� ��


    PLAYER->GetActor()->rotation = Vector3(0, 90 * ToRadian, 0);
    PLAYER->GetActor()->Find("Player2")->rotation = Vector3(0, 0, 0);
    PLAYER->GetActor()->SetWorldPos(startPoint);


}

void Scene4::Release()
{
    OBJECT->Release();
}

void Scene4::Update()
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
       
    }
    ImGui::End();

    GM->grid->Update();
    Camera::main->Update();

    

    GM->Update();
    PLAYER->Update();
    OBJECT->Update();
    GM->portal->Update();
   
   
    
}

void Scene4::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
  
   

   
}

void Scene4::Render()
{
    Camera::main->Set();
    GM->grid->Render();
    PLAYER->Render();
    OBJECT->Render();
    GM->portal->Render();
}

void Scene4::PreRender()
{
}

void Scene4::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
