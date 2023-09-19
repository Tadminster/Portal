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
#include "Scene3.h"
#include "Scene4.h"

Scene3::Scene3()
{
    GM->Init();

    Camera::main = (Camera*)PLAYER->GetActor()->Find("BodyCam");
    ResizeScreen();

   


    finish = Actor::Create();
    finish->LoadFile("Finish.xml");

   // SOUND->AddSound("Portal2-17-The_Reunion.mp3", "Bgm3", true);
   //
   // SOUND->Play("Bgm3");
   //
   // SOUND->SetVolume("Bgm3", 0.15f);


}

Scene3::~Scene3()
{
    //SOUND->DeleteSound("Bgm3");
}

void Scene3::Init()
{
    Scene4* sc4 = new Scene4();
    SCENE->AddScene("scene4", sc4);


    cube = new Cube();
    button = new Button();
    door = new Door();

    cube->GetActor()->SetWorldPos(Vector3(124, 35, 36));
    door->GetActor()->SetWorldPos(Vector3(195, 24, 0));
    button->GetActor()->SetWorldPos(Vector3(144, 2.4, 22.6));
    finish->SetWorldPos(Vector3(208, 31,0));

    OBJECT->AddStructure(new Structure(Concrete, _8x4, Wall), Vector3(108, -36, 48));           // 떨어지는 곳 왼쪽
    OBJECT->AddStructure(new Structure(Concrete, _8x4, Wall), Vector3(108, -36, -47), 180);     // 떨어지는 곳 오른쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(121, -61, 0), 270); // 떨어지는 곳 시작위치 쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(89, -61, 0), 90);  // 떨어지는 곳 도착위치 쪽 벽



    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(149, 18, 25),90);        // 천장 포탈 벽
    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(149, 18, -23),90);        // 천장 포탈 벽2

    OBJECT->AddStructure(new Structure(Metal, _8x8, Ceiling), Vector3(124, 48.9, 36),90);    // 큐브 있는 천장
    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(101, 18, 36), 90);        // 큐브 있는 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(112, 28, 11));            // 큐브 있는 벽



    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(180, -24, 48));           // 떨어지는 곳 왼쪽
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(180, -24, -47), 180);     // 떨어지는 곳 오른쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(167, -60, 0), 270); // 떨어지는 곳 시작위치 쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(193, -60, 0), 90);  // 떨어지는 곳 도착위치 쪽 벽


    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // 시작위치 위쪽 천장
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // 시작위치 뒷쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // 시작위치 왼쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // 시작위치 오른쪽 벽

    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(23, 24, 0), 270);     // 시작위치에서 나와서 바로 위쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(23, 0, 36), 270);     // 시작위치에서 나와서 바로 왼쪽 큰벽
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(23, 0, -36), 270);    // 시작위치에서 나와서 바로 오른쪽 큰벽

    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(48, 0, 48));          // 시작위치에서 나와서 왼쪽 큰벽1
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(96, 0, 48));          // 시작위치에서 나와서 왼쪽 큰벽2
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Wall), Vector3(144, -24, 48));         // 시작위치에서 나와서 왼쪽 큰벽3
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Wall), Vector3(48, -24, -47), 180);  // 시작위치에서 나와서 오른쪽 큰벽1
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(120, 0, -47), 180);    // 시작위치에서 나와서 오른쪽 큰벽2
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(168, 0, -47), 180);    // 시작위치에서 나와서 오른쪽 큰벽3
   
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, 0, 0), 90);     // 도작위치 들어가기 전 바로 위쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(193, 0, 36), 90);     // 도작위치 들어가기 전 바로 왼쪽 큰벽
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(193, 0, -36), 90);    // 도작위치 들어가기 전 바로 오른쪽 큰벽

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(204, 49, 0));         // 도착위치 천장
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(215, 24, 0), 90);         // 도착위치 뒷쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(204, 24, 11));            // 도착위치 왼쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(204, 24, -11), 180);      // 도착위치 오른쪽 벽

    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(181, -2, 0), 90);     // 도착위치 바닥 앞쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, -2, 11));      // 도착위치 바닥 왼쪽 벽
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, -2, -11));     // 도착위치 바닥 오른쪽 벽
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(192, -3, 0));     // 도착위치 바닥 벽

   
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(150, 30.2, 0),270);     // 도착위치 건너편 포탈 전용 벽

    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(108, -24, 0), 90);      // 떨어지는 곳 바닥1
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(192, -24, 0), 90);      // 떨어지는 곳 바닥2
    OBJECT->AddStructure(new Structure(Metal, _8x8, Floor), Vector3(124, 29, 36),90);       // 큐브 있는 바닥
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(136, 29, -36), 90);     // 큐브 건너편 바닥
    OBJECT->AddStructure(new Structure(Metal, _8x4, Floor), Vector3(204, 23.01, 0), 0);     // 도작위치 바닥
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(12, 0.01, 0));          // 시작위치 바닥
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Floor), Vector3(42, 0, 0));        // 바닥1
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(144, 0, 0),90);     // 바닥2
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Ceiling), Vector3(48, 49, 0));     // 천장1
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Ceiling), Vector3(144, 49, 0));    // 천장2
   

    PLAYER->GetActor()->rotation = Vector3(0, 90 * ToRadian, 0);
    PLAYER->GetActor()->Find("Player2")->rotation = Vector3(0, 0, 0);
    PLAYER->GetActor()->SetWorldPos(startPoint);
    PLAYER->SetState(PlayerState::SPAWN);
}

void Scene3::Release()
{
    OBJECT->Release();
}

void Scene3::Update()
{

    SOUND->Stop("Bgm4");



    // 카메라 조작 (디버그 모드일때만)
    if (GM->debugMode) Camera::ControlMainCam();

   // ImGui::Begin("Hierarchy");
   // {
   //     GM->grid->RenderHierarchy();
   //     GM->cam1->RenderHierarchy();
   //     PLAYER->GetActor()->RenderHierarchy();
   //     OBJECT->RenderHierarchy();
   //     GM->portal->GetBluePortal()->RenderHierarchy();
   //     GM->portal->GetOrangePortal()->RenderHierarchy();
   //     cube->GetActor()->RenderHierarchy();
   //     button->GetActor()->RenderHierarchy();
   //     door->GetActor()->RenderHierarchy();
   //     finish->RenderHierarchy();
   // }
   // ImGui::End();
   //
    GM->grid->Update();
    Camera::main->Update();

    button->SwitchPress(cube);
    if (button->Getswitched()) door->isOpen = true;
    else door->isOpen = false;

    GM->Update();
    PLAYER->Update();
    OBJECT->Update();
    GM->portal->Update();
    cube->Update();
    button->Update();
    door->Update();
    finish->Update();

  

}

void Scene3::LateUpdate()
{
    PLAYER->LateUpdate();
    GM->portal->LateUpdate();
    GM->portal->PortalingCube(cube);
    cube->LateUpdate();
    button->LateUpdate();
    door->LateUpdate();

    if (PLAYER->GetActor()->Find("WallCol")->Intersect(finish))
    {
       
        SCENE->ChangeScene("scene4");     

    }

}

void Scene3::Render()
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

void Scene3::PreRender()
{
}

void Scene3::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
