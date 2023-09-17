#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"

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
// 2. 메인브런치로 이동 -> 페치해보고 변경된 내용이 있는지 확인
//      2.1  -> 있으면 끌어오기 -> 개인브런치로 이동 -> 개인브런치에서 메인을 머지 git merge main 
//      2.2  -> 병합충돌 있으면 해결 후 -> 문제없는지 확인 
// 3. 메인브런치에서 개인브런치를 머지
// 4. 메인브런치를 커밋, 푸쉬 -> 온라인에 변경된 내용이 적용됨 -> 팀원한테 작업한 내용이 있다고 알려주면 좋음

// 충돌해결 방법
// 1. 충돌병합기를 열어서 충돌난 부분을 수정
// 2. 충돌난 파일을 커밋, 푸쉬


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