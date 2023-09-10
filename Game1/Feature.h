#pragma once

enum class FeatureType
{
	Concrete,
	Metal
};

class Feature
{
private:
	class Actor* actor;

public:
	// @brief �������� ������, �������� Ÿ�԰� ũ�⸦ �޾Ƽ� �ʱ�ȭ
	// @brief ex) Feature(1, 3) �̸� Concrete 2x2�� ����
	// @param type �������� Ÿ�� 
	// @param [1: Concrete], [2: Metal]
	// @param
	// @param size �������� ũ�� 
	// @param if (type==1) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4]
	// @param if (type==2) [1: 1x1], [2: 2x2], [3: 4x4]
	// @param
	// @exception size�� �ּҺ��� ������ 1, �ִ뺸�� ũ�� ������ �ִ� ������� �ʱ�ȭ
	Feature(int type = 1, int size = 1);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

