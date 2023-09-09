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
	PlayerState state	{ PlayerState::IDLE };

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
};

