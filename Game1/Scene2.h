#pragma once
class Scene2 : public Scene
{
private:
	Vector3 startPoint{ 10, 5, 0 };

	class Cube* cube;

public:
	Scene2();
	~Scene2();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void PreRender();
	virtual void ResizeScreen();
};

