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

    OBJECT->AddStructure(new Structure(Concrete, _8x4, Wall), Vector3(108, -36, 48));           // �������� �� ����
    OBJECT->AddStructure(new Structure(Concrete, _8x4, Wall), Vector3(108, -36, -47), 180);     // �������� �� ������ ��
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(121, -61, 0), 270); // �������� �� ������ġ �� ��
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(89, -61, 0), 90);  // �������� �� ������ġ �� ��



    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(149, 18, 25),90);        // õ�� ��Ż ��
    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(149, 18, -23),90);        // õ�� ��Ż ��2

    OBJECT->AddStructure(new Structure(Metal, _8x8, Ceiling), Vector3(124, 48.9, 36),90);    // ť�� �ִ� õ��
    OBJECT->AddStructure(new Structure(Metal, _8x4, Wall), Vector3(101, 18, 36), 90);        // ť�� �ִ� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(112, 28, 11));            // ť�� �ִ� ��



    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(180, -24, 48));           // �������� �� ����
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(180, -24, -47), 180);     // �������� �� ������ ��
    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(167, -60, 0), 270); // �������� �� ������ġ �� ��
    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(193, -60, 0), 90);  // �������� �� ������ġ �� ��


    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // ������ġ ���� õ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // ������ġ ������ ��

    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(23, 24, 0), 270);     // ������ġ���� ���ͼ� �ٷ� ���� ��
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(23, 0, 36), 270);     // ������ġ���� ���ͼ� �ٷ� ���� ū��
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(23, 0, -36), 270);    // ������ġ���� ���ͼ� �ٷ� ������ ū��

    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(48, 0, 48));          // ������ġ���� ���ͼ� ���� ū��1
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(96, 0, 48));          // ������ġ���� ���ͼ� ���� ū��2
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Wall), Vector3(144, -24, 48));         // ������ġ���� ���ͼ� ���� ū��3
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Wall), Vector3(48, -24, -47), 180);  // ������ġ���� ���ͼ� ������ ū��1
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(120, 0, -47), 180);    // ������ġ���� ���ͼ� ������ ū��2
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(168, 0, -47), 180);    // ������ġ���� ���ͼ� ������ ū��3
   
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, 0, 0), 90);     // ������ġ ���� �� �ٷ� ���� ��
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(193, 0, 36), 90);     // ������ġ ���� �� �ٷ� ���� ū��
    OBJECT->AddStructure(new Structure(Concrete, _8x8, Wall), Vector3(193, 0, -36), 90);    // ������ġ ���� �� �ٷ� ������ ū��

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(204, 49, 0));         // ������ġ õ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(215, 24, 0), 90);         // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(204, 24, 11));            // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(204, 24, -11), 180);      // ������ġ ������ ��

    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(181, -2, 0), 90);     // ������ġ �ٴ� ���� ��
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, -2, 11));      // ������ġ �ٴ� ���� ��
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(193, -2, -11));     // ������ġ �ٴ� ������ ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(192, -3, 0));     // ������ġ �ٴ� ��

   
    OBJECT->AddStructure(new Structure(Concrete, _4x4, Wall), Vector3(150, 30.2, 0),270);     // ������ġ �ǳ��� ��Ż ���� ��

    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(108, -24, 0), 90);      // �������� �� �ٴ�1
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(192, -24, 0), 90);      // �������� �� �ٴ�2
    OBJECT->AddStructure(new Structure(Metal, _8x8, Floor), Vector3(124, 29, 36),90);       // ť�� �ִ� �ٴ�
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(136, 29, -36), 90);     // ť�� �ǳ��� �ٴ�
    OBJECT->AddStructure(new Structure(Metal, _8x4, Floor), Vector3(204, 23.01, 0), 0);     // ������ġ �ٴ�
    OBJECT->AddStructure(new Structure(Metal, _4x4, Floor), Vector3(12, 0.01, 0));          // ������ġ �ٴ�
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Floor), Vector3(42, 0, 0));        // �ٴ�1
    OBJECT->AddStructure(new Structure(Concrete, _16x8, Floor), Vector3(144, 0, 0),90);     // �ٴ�2
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Ceiling), Vector3(48, 49, 0));     // õ��1
    OBJECT->AddStructure(new Structure(Concrete, _16x16, Ceiling), Vector3(144, 49, 0));    // õ��2
   

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



    // ī�޶� ���� (����� ����϶���)
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
