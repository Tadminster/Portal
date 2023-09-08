#pragma once
class Feature
{
private:
	class Actor* actor;

public:
	Feature();
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

