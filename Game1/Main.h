#pragma once

class Main : public Scene
{
private:
	class Scene1* sc1;
	class Scene2* sc2;
	class Scene3* sc3;
	class Scene4* sc4;
	

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
