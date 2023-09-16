#pragma once
class Scene1 : public Scene
{
private:
	Vector3 startPoint{ 10, 5, 0 };

	class Cube* cube;
	class Location* nextScene;

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

