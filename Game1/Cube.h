#pragma once
class Cube : public ObProto
{
private:
	

	

	Vector3 lastPos{ 0,0,0 };
	bool	OnGround{ false };

	Vector3 bounceDir{ 0, 0, 0 };		// ��Ż�� ���� ƨ���� ������ ����
	float	bounceSpeed{ 0 };

	bool	isCatched{ false };

public:
	Cube();
	~Cube() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	virtual void PortalJump() { OnGround = false; gravity = 20; };
	virtual void PortalBounce() { bounceSpeed = -gravity; gravity = 0; };
	virtual void SetBounceDir(Vector3 dir) { bounceDir = dir; };

	virtual void Catch();
	virtual void SetisCatched(bool b) { isCatched = b; };
};

