#pragma once
class Scene1 : public Scene
{
private:
	Vector3 startPoint{ 10, 6, 0 };
	string  bgm;

	class Cube* cube;
	class Button* button;
	class Door* door;
	class Actor* finish;

public:
	Scene1();
	~Scene1();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void PreRender();
	virtual void ResizeScreen();
};

