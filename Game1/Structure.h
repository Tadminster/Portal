#pragma once

enum Material
{
	Concrete,
	Metal
};

enum StructureType
{
	Ceiling,
	Floor,
	Wall,
	
};

enum StructureSize
{
	_1x1,
	_2x1, _2x2,
	_4x1, _4x2, _4x4, 
	_8x1, _8x2, _8x4, _8x8,
	_16x1, _16x2, _16x4, _16x8, _16x16
};

class Structure
{
private:
	class Actor* actor;

public:
	Material		material;
	StructureType	type;

public:
	// @brief �������� ������, �������� Ÿ�԰� ũ�⸦ �޾Ƽ� �ʱ�ȭ
	// @brief ex) Structure(1, 3) �̸� Concrete 2x2�� ����
	// @param mater �������� ���� 
	// @param [Concrete], [Metal]
	// @param
	// @param size �������� ũ�� 
	// @param [_1x1], [_2x1], [_2x2], [_4x1], [_4x2] [_4x4], [_8x1], [_8x4], [_8x8], [_16x1], [_16x4], [_16x8] [_16x16]
	// @param
	// @param StType �������� �뵵 
	// @param [Ceiling], [Floor], [Wall]
	// @param
	// @exception size�� �ּҺ��� ������ 1x1, �ִ뺸�� ũ�� ������ 16x16���� �ʱ�ȭ
	Structure(Material mater = Concrete, StructureSize size = _1x1, StructureType StType = Floor);
	~Structure();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

