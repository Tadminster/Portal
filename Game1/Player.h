enum class PlayerState
{
	IDLE,
	RUN,
	JUMP,
	FIRE,
	DEAD
};

#pragma once
class Player : public ObProto
{
private:
	class Actor* gun;

	PlayerState state	{ PlayerState::IDLE };

	Vector3 lastPos			{ 0, 5, 0 };
	bool	OnGround		{ false };

	
public:
	Player();
	~Player() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	virtual void Control();
	virtual void FireBluePortal();
	virtual void FireYellowPortal();
	virtual void Jump();
	virtual void PortalJump() { OnGround = false; gravity = 20; };
	
	bool    isCatch{ false };
};

