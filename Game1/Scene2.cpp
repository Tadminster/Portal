#include "stdafx.h"
#include "Structure.h"
#include "ObProto.h"
#include "Player.h"
#include "Cube.h"
#include "Portal.h"
#include "Button.h"
#include "Door.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Scene2.h"
#include "Scene3.h"

Scene2::Scene2()
{
    GM->Init();

    Camera::main = (Camera*)PLAYER->GetActor()->Find("BodyCam");
    ResizeScreen();

    finish = Actor::Create();
    finish->LoadFile("Finish.xml");
}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
    Scene3* sc3 = new Scene3();
    SCENE->AddScene("scene3", sc3);


    cube = new Cube();
    cube->GetActor()->SetWorldPos(Vector3(100, 10, -30));

    button = new Button();
    door = new Door();

    OBJECT->AddStructure(new Structure(Metal, _16x16, Floor), Vector3(12, 0, 0));        // 바닥1
    OBJECT->AddStructure(new Structure(Metal, _16x16, Ceiling), Vector3(12, 48, 0));     // 천장1
    OBJECT->AddStructure(new Structure(Metal, _16x16, Floor), Vector3(132, 0, 0));       // 바닥2
    OBJECT->AddStructure(new Structure(Metal, _16x16, Ceiling), Vector3(108, 48, 0));    // 천장2

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // 시작위치 위쪽 천장
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // 시작위치 뒷쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // 시작위치 왼쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // 시작위치 오른쪽 벽

    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(23, 24, 0), 270);     // 시작위치에서 나와서 바로 위쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(23, 0, 36), 270);     // 시작위치에서 나와서 바로 왼쪽 큰벽
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(23, 0, -36), 270);    // 시작위치에서 나와서 바로 오른쪽 큰벽

    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(48, 0, 48));          // 시작위치에서 나와서 왼쪽 큰벽1
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(96, 0, 48));          // 시작위치에서 나와서 왼쪽 큰벽2
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(48, 0, -48), 180);    // 시작위치에서 나와서 오른쪽 큰벽1
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(96, 0, -48), 180);    // 시작위치에서 나와서 오른쪽 큰벽2

    OBJECT->AddStructure(new Structure(Concrete, _16x4, Floor), Vector3(72, -24, 0), 90);      // 떨어지는 곳 바닥
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(72, -24, 48));                // 떨어지는 곳 왼쪽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(72, -24, -48), 180);          // 떨어지는 곳 오른쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(59.001f, -60, 0), 270); // 떨어지는 곳 시작위치 쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(84.999f, -60, 0), 90);  // 떨어지는 곳 도착위치 쪽 벽

    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(120, 24, 0), 90);     // 도작위치 들어가기 전 바로 위쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(120, 0, 36), 90);     // 도작위치 들어가기 전 바로 왼쪽 큰벽
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(120, 0, -36), 90);    // 도작위치 들어가기 전 바로 오른쪽 큰벽

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(131, 23, 0));         // 도착위치 천장
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(143, 0, 0), 90);         // 도착위치 뒷쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(131, 0, 11));            // 도착위치 왼쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(131, 0, -11), 180);      // 도착위치 오른쪽 벽

    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(45, -13, 0),-90);      //  천장 포탈 가능 구역
    
    PLAYER->GetActor()->rotation = Vector3(0, 90 * ToRadian, 0);
    PLAYER->GetActor()->Find("Player2")->rotation = Vector3(0, 0, 0);
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
        cube->GetActor()->RenderHierarchy();
        GM->portal->GetBluePortal()->RenderHierarchy();
        GM->portal->GetOrangePortal()->RenderHierarchy();
        button->GetActor()->RenderHierarchy();
        door->GetActor()->RenderHierarchy();
        finish->RenderHierarchy();
        
    }
    ImGui::End();

    GM->grid->Update();
    Camera::main->Update();

     button->SwitchPress(cube);
    if (button->Getswitched()) door->isOpen = true;
    else door->isOpen = false;

    cube->Update();
    GM->Update();
    PLAYER->Update();
    OBJECT->Update();
    GM->portal->Update();
    button->Update();
    door->Update();
    finish->Update();
   
}

void Scene2::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
    GM->portal->PortalingCube(cube);
    cube->LateUpdate();
    button->LateUpdate();
    door->LateUpdate();

    // 신(다음스테이지) 이동

    if (PLAYER->GetActor()->Find("WallCol")->Intersect(finish))
    {
        SCENE->ChangeScene("scene3");
    }
}

void Scene2::Render()
{
    Camera::main->Set();
    GM->grid->Render();
    PLAYER->Render();
    OBJECT->Render();
    GM->portal->Render();
    cube->Render();
    button->Render();
    door->Render();
    finish->Render();
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
