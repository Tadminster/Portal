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
	// @brief �������� ������
	// @param type �������� Ÿ�� [1: Concrete, 2: Metal]
	// @param size �������� ũ�� 
	// @param if (type1) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4]
	// @param if (type2) [1: 1x1], [2: 2x2], [3: 4x4]
	// @exception size�� �ּҺ��� ������ 1, �ִ뺸�� ũ�� �ִ� ������� �ʱ�ȭ
	Feature(int type = 1, int size = 1);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

