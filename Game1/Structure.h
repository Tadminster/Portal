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
	// @brief 지형지물 생성자, 지형지물 타입과 크기를 받아서 초기화
	// @brief ex) Structure(1, 3) 이면 Concrete 2x2로 생성
	// @param mater 지형지물 재질 
	// @param [Concrete], [Metal]
	// @param
	// @param size 지형지물 크기 
	// @param [_1x1], [_2x1], [_2x2], [_4x1], [_4x2] [_4x4], [_8x1], [_8x4], [_8x8], [_16x1], [_16x4], [_16x8] [_16x16]
	// @param
	// @param StType 지형지물 용도 
	// @param [Ceiling], [Floor], [Wall]
	// @param
	// @exception size가 최소보다 작으면 1x1, 최대보다 크면 가능한 16x16으로 초기화
	Structure(Material mater = Concrete, StructureSize size = _1x1, StructureType StType = Floor);
	~Structure();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

