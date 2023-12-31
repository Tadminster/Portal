#pragma once
#define BlueP 0
#define OrangeP 1



class Portal
{
private:
	class Actor* bluePortal;
	class Actor* orangePortal;
	class Actor* ui;
	string bluePortalSoundKey;
	string orangePortalSoundKey;
	string portalEnterSoundKey;

	bool activateP[2];
	float portalDelay;

	void PlayBluePortalSoundEffect();
	void PlayOrangePortalSoundEffect();
	void PlayPortalEnterSoundEffect();

	void spaceCheck(Actor* portal, int portalNumber);

public:
	Portal();
	~Portal();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetBluePortal() { return bluePortal; };
	Actor* GetOrangePortal() { return orangePortal; };

	void Portaling();
	void PortalingCube(class Cube* cube);
	void PortalInstall();
	
	void HandFree(class Cube* cube);
	
};

