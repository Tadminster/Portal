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
	// @brief 지형지물 생성자, 지형지물 타입과 크기를 받아서 초기화
	// @brief ex) Feature(1, 3) 이면 Concrete 2x2로 생성
	// @param type 지형지물 타입 
	// @param [1: Concrete], [2: Metal]
	// @param
	// @param size 지형지물 크기 
	// @param if (type==1) [1: 1x1], [2: 2x1], [3: 2x2], [4: 4x1], [5: 4x4]
	// @param if (type==2) [1: 1x1], [2: 2x2], [3: 4x4]
	// @param
	// @exception size가 최소보다 작으면 1, 최대보다 크면 가능한 최대 사이즈로 초기화
	Feature(int type = 1, int size = 1);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

