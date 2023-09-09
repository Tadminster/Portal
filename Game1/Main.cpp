#include "stdafx.h"
#include "Player.h"
#include "Feature.h"
#include "Main.h"

// [페치] 온라인에 있는 내용을 가져옴
// 		    ㄴ git fetch

// [끌어오기(풀)] 온라인에 있는 내용을 가져와서 로컬컴퓨터(개인컴퓨터)에 적용시킴
// 	        ㄴ git pull

// [커밋] 변경된 내용을 적고, 그 내용을 로컬컴퓨터(개인컴퓨터)에 적용시킴
//  	    ㄴ git commit -m "커밋메세지"

// [푸쉬] 변경된 내용(커밋된 파일)을 온라인에 적용시킴
//          ㄴ git push   

// [머지] 두개의 브랜치를 합침
//          ㄴ git merge 브랜치이름

// 깃허브 사용순서
// [브런치] 작업을 할 때, 메인브런치를 건들지 않고 개인브런치에서 작업을 하고, 작업이 완료되면 메인브런치에 합침
// 1. 개인브런치에서 작업 -> 작업내용을 커밋, 푸쉬
// 2. 메인브런치로 이동 -> 페치해보고 변경된 내용이 있는지 확인 -> 있으면 끌어오기
// 3. 메인브런치에서 개인브런치를 머지
// 4. 메인브런치를 커밋, 푸쉬 -> 온라인에 변경된 내용이 적용됨 -> 팀원한테 작업한 내용이 있다고 알려주면 좋음

// 충돌해결 방법
// 1. 충돌병합기를 열어서 충돌난 부분을 수정
// 2. 충돌난 파일을 커밋, 푸쉬


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