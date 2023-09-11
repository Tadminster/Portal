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
	// @brief 지형지물 생성자, 지형지물 타입과 크기를 받아서 초기화
	// @brief ex) Feature(1, 3) 이면 Concrete 2x2로 생성
	// @param mater 지형지물 재질 
	// @param [1: Concrete], [2: Metal]
	// @param
	// @param size 지형지물 크기 
	// @param if (mater == Concrete) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4], [6: 8x8], [7: 16x16]
	// @param if (mater == Metal) [1: 1x1], [2: 2x2], [3: 4x4], [4: 8x8], [5: 16x16]
	// @param
	// @param StType 지형지물 용도 
	// @param [1: Floor], [2: Wall]
	// @param
	// @exception size가 최소보다 작으면 1, 최대보다 크면 가능한 최대 사이즈로 초기화
	Feature(Material mater = Concrete, int size = 1, StructureType StType = Floor);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

