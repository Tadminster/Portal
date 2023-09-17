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

    Potatos = Actor::Create();
    Potatos->LoadFile("PotatOS.xml");

    SOUND->AddSound("portal-still_alive.mp3", "Bgm4", true);

    SOUND->Play("Bgm4");

    SOUND->SetVolume("Bgm4", 0.4f);



}

Scene4::~Scene4()
{
    SOUND->DeleteSound("Bgm4");
}

void Scene4::Init()
{

 
 
   
    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // 시작위치 위쪽 천장
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(12, 1, 0));             // 시작위치 바닥
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // 시작위치 뒷쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // 시작위치 왼쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // 시작위치 오른쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(25, 0, 0), 90);       // 시작위치 바깥쪽 벽


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
    SOUND->Play("Bgm4");
    SOUND->Stop("Bgm1");


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
        Potatos->RenderHierarchy();
       
    }
    ImGui::End();

    GM->grid->Update();
    Camera::main->Update();

    if (INPUT->KeyDown('X'))
    {
        exit(EXIT_SUCCESS);
 
    }



    

    GM->Update();
    PLAYER->Update();
    OBJECT->Update();
    GM->portal->Update();
    Potatos->Update();
   
    
}

void Scene4::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
  
   

   
}

void Scene4::Render()
{


    RECT rd;
    rd.right = App.GetWidth() + 820;
    rd.left = rd.right - 2050;
    rd.top = 150;
    rd.bottom = rd.top + 50;
    DWRITE->RenderText(L"Thank you for playing !!", rd, 105.0f, L"Arial", Color(1, 1, 1, 0), DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_ITALIC, DWRITE_FONT_STRETCH_EXPANDED);


    RECT rc;
    rc.right = App.GetWidth() + 820;
    rc.left = rc.right - 1620;
    rc.top = 450;
    rc.bottom = rc.top + 50;
    DWRITE->RenderText(L"'x' key = Die ", rc, 50.0f, L"Arial", Color(1, 1, 1,0), DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_ITALIC, DWRITE_FONT_STRETCH_EXPANDED);


    Camera::main->Set();
    GM->grid->Render();
    PLAYER->Render();
    OBJECT->Render();
    GM->portal->Render();
    Potatos->Render();
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
