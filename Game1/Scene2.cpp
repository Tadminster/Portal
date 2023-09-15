#include "stdafx.h"
#include "Structure.h"
#include "ObProto.h"
#include "Player.h"
#include "Cube.h"
#include "Portal.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Scene2.h"

Scene2::Scene2()
{

    GM->Init();

    Camera::main = (Camera*)PLAYER->GetActor()->Find("BodyCam");
    ResizeScreen();

}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
    cube = new Cube();


    




    PLAYER->GetActor()->SetWorldPos(startPoint);
}

void Scene2::Release()
{
    
}

void Scene2::Update()
{
    // 카메라 조작 (디버그 모드일때만)
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

void Scene2::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
    cube->LateUpdate();
}

void Scene2::Render()
{
    Camera::main->Set();
    GM->grid->Render();
    PLAYER->Render();
    OBJECT->Render();
    GM->portal->Render();
    cube->Render();
}

void Scene2::PreRender()
{
}

void Scene2::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
