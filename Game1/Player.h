#pragma once
class Player
{
private:
	class Actor* actor;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

