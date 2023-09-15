#pragma once
class Cube : public ObProto
{
private:
	

	

	Vector3 lastPos{ 5, 5, 5 };
	bool	OnGround{ false };

	bool	isCatched{ false };

public:
	Cube();
	~Cube() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	virtual void Catch();
};

