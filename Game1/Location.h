#pragma once
class Location
{
private:
	class Actor* location;

public:
	// @brief Ʈ���Ÿ� �ߵ���ų ���� ������
	// @param scale ������ ũ��
	// @param pos ������ ��ġ
	Location(Vector3 scale, Vector3 pos);
	~Location();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

