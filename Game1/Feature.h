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
	// @brief 지형지물 생성자
	// @param type 지형지물 타입 [1: Concrete, 2: Metal]
	// @param size 지형지물 크기 
	// @param if (type1) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4]
	// @param if (type2) [1: 1x1], [2: 2x2], [3: 4x4]
	// @exception size가 최소보다 작으면 1, 최대보다 크면 최대 사이즈로 초기화
	Feature(int type = 1, int size = 1);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

