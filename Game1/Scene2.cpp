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

    OBJECT->AddStructure(new Structure(Metal, _16x16, Floor), Vector3(12, 0, 0));        // �ٴ�1
    OBJECT->AddStructure(new Structure(Metal, _16x16, Ceiling), Vector3(12, 48, 0));     // õ��1
    OBJECT->AddStructure(new Structure(Metal, _16x16, Floor), Vector3(132, 0, 0));       // �ٴ�2
    OBJECT->AddStructure(new Structure(Metal, _16x16, Ceiling), Vector3(108, 48, 0));    // õ��2

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(12, 23, 0));          // ������ġ ���� õ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(0, 0, 0), 270);          // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, 11));             // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(12, 0, -11), 180);       // ������ġ ������ ��

    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(23, 24, 0), 270);     // ������ġ���� ���ͼ� �ٷ� ���� ��
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(23, 0, 36), 270);     // ������ġ���� ���ͼ� �ٷ� ���� ū��
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(23, 0, -36), 270);    // ������ġ���� ���ͼ� �ٷ� ������ ū��

    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(48, 0, 48));          // ������ġ���� ���ͼ� ���� ū��1
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(96, 0, 48));          // ������ġ���� ���ͼ� ���� ū��2
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(48, 0, -48), 180);    // ������ġ���� ���ͼ� ������ ū��1
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(96, 0, -48), 180);    // ������ġ���� ���ͼ� ������ ū��2

    OBJECT->AddStructure(new Structure(Concrete, _16x4, Floor), Vector3(72, -24, 0), 90);      // �������� �� �ٴ�
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(72, -24, 48));                // �������� �� ����
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(72, -24, -48), 180);          // �������� �� ������ ��
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(59.001f, -60, 0), 270); // �������� �� ������ġ �� ��
    OBJECT->AddStructure(new Structure(Metal, _16x4, Wall), Vector3(84.999f, -60, 0), 90);  // �������� �� ������ġ �� ��

    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(120, 24, 0), 90);     // ������ġ ���� �� �ٷ� ���� ��
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(120, 0, 36), 90);     // ������ġ ���� �� �ٷ� ���� ū��
    OBJECT->AddStructure(new Structure(Metal, _8x8, Wall), Vector3(120, 0, -36), 90);    // ������ġ ���� �� �ٷ� ������ ū��

    OBJECT->AddStructure(new Structure(Metal, _4x4, Ceiling), Vector3(131, 23, 0));         // ������ġ õ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(143, 0, 0), 90);         // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(131, 0, 11));            // ������ġ ���� ��
    OBJECT->AddStructure(new Structure(Metal, _4x4, Wall), Vector3(131, 0, -11), 180);      // ������ġ ������ ��

    OBJECT->AddStructure(new Structure(Concrete, _16x4, Wall), Vector3(45, -13, 0),-90);      //  õ�� ��Ż ���� ����
    
    PLAYER->GetActor()->rotation = Vector3(0, 90 * ToRadian, 0);
    PLAYER->GetActor()->Find("Player2")->rotation = Vector3(0, 0, 0);
    PLAYER->GetActor()->SetWorldPos(startPoint);
}

void Scene2::Release()
{

}

void Scene2::Update()
{
    // ī�޶� ���� (����� ����϶���)
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

    // ��(������������) �̵�

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
