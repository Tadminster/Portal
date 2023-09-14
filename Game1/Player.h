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
	class Actor* gun;							// 포탈건

	PlayerState state	{ PlayerState::IDLE };	// 플레이어 상태

	Vector3 lastPos			{ 0, 0, 0 };		// 이전 프레임의 위치
	bool	OnGround		{ false };			// 플레이어가 바닥에 닿아있는지

	float	bounceSpeed		{ 0 };				// 포탈을 통해 튕겨져 나오는 속도

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
};

