#pragma once
class Door : public ObProto
{
private:




	

public:
	Door();
	~Door() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	bool isOpen{ false };

};

