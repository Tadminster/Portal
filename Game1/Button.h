#pragma once
class Button : public ObProto
{
private:

	bool switched { false };
	int  buttonCount;
	int	 count;

	string buttonUpSoundKey;
	string buttonDownSoundKey;

	void PlaybuttonUpSoundEffect();
	void PlaybuttonDownSoundEffect();

public:
	Button();
	~Button() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	virtual void SwitchPress(Cube* cube);
	virtual bool Getswitched() { return switched; };
};
