#pragma once
#define BlueP 0
#define OrangeP 1



class Portal
{
private:
	class Actor* BluePortal;
	class Actor* OrangePortal;
	class Actor* Ui;


	bool ActivateP[2];


public:
	Portal();
	~Portal();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetBluePortal() { return BluePortal; };
	Actor* GetOrangePortal() { return OrangePortal; };

	void Portaling();
	void PortalInstall();
	
};

