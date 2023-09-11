#pragma once

class Main : public Scene
{
private:
	// default
	Camera* cam1;
	Grid* grid;
	Actor* gun;

	
	

	// ��
	class Feature* wall;

	// ������Ʈ

	//��Ż
	class Portal* portal;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
