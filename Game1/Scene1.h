#pragma once
class Scene1 : public Scene
{
protected:

public:
	Scene1();
	~Scene1();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};

