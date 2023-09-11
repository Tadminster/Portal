#pragma once

enum Material
{
	Concrete,
	Metal
};

enum StructureType
{
	Floor,
	Wall
};

class Feature
{
private:
	class Actor* actor;

public:
	Material		material;
	StructureType	type;

public:
	// @brief �������� ������, �������� Ÿ�԰� ũ�⸦ �޾Ƽ� �ʱ�ȭ
	// @brief ex) Feature(1, 3) �̸� Concrete 2x2�� ����
	// @param mater �������� ���� 
	// @param [1: Concrete], [2: Metal]
	// @param
	// @param size �������� ũ�� 
	// @param if (mater == Concrete) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4], [6: 8x8], [7: 16x16]
	// @param if (mater == Metal) [1: 1x1], [2: 2x2], [3: 4x4], [4: 8x8], [5: 16x16]
	// @param
	// @param StType �������� �뵵 
	// @param [1: Floor], [2: Wall]
	// @param
	// @exception size�� �ּҺ��� ������ 1, �ִ뺸�� ũ�� ������ �ִ� ������� �ʱ�ȭ
	Feature(Material mater = Concrete, int size = 1, StructureType StType = Floor);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

