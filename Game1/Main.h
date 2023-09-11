#pragma once

class Main : public Scene
{
private:
	// default
	Camera* cam1;
	Grid* grid;
	Actor* gun;

	
	

	// 맵
	class Feature* wall;

	// 오브젝트

	//포탈
	class Portal* portal;

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
