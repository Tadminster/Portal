#pragma once
class GameManager : public Singleton<GameManager>
{
public:
	bool	debugMode   { false };

    class   Camera*         cam1;
    class   Player*         player;
    class   ObjectManager*  object;

public:
    void    Init();
    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};

