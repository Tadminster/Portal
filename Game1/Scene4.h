#pragma once
class Scene4 : public Scene
{
private:
	Vector3 startPoint{ 5.2, 6, 0 };

	
public:
	Scene4();
	~Scene4();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void PreRender();
	virtual void ResizeScreen();
};

