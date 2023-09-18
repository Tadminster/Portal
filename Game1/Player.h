enum class PlayerState
{
	SPAWN,
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
	class Actor* gun;							// ��Ż��

	PlayerState state	{ PlayerState::IDLE };	// �÷��̾� ����

	Vector3 lastPos			{ 0, 5, 0 };		// ���� �������� ��ġ
	bool	OnGround		{ false };			// �÷��̾ �ٴڿ� ����ִ���

	Vector3 bounceDir		{ 0, 0, 0 };		// ��Ż�� ���� ƨ���� ������ ����
	float	bounceSpeed		{ 0 };				// ��Ż�� ���� ƨ���� ������ �ӵ�

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
	virtual void PortalBounce() { bounceSpeed = -gravity; gravity = 0; };

	virtual Vector3 GetlastPos() { return lastPos; };

	virtual void SetState(PlayerState state) { this->state = state; };
	virtual void SetBounceDir(Vector3 dir) { bounceDir = dir; };
	bool    isCatch{ false };
};

