#pragma once



class Portal
{
private:
	class Actor* BluePortal;
	class Actor* OrangePortal;




public:
	Portal();
	~Portal();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Portaling();
};

