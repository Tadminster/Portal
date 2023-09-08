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
	// @param type �������� Ÿ��[ 0: Concrete, 1: Metal]
	Feature(int tileSize = 3,int type = 0);
	~Feature();
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	Actor* GetActor() { return actor; }
};

